"""
A script to automate the downloading of server files and generating data from the servers.
"""
import os
import glob
from zipfile import ZipFile
from urllib.request import urlopen
import shutil
import subprocess
import logging
import argparse
import hashlib
import json
import ssl
from amulet_nbt import (
    NamedTag,
    load as load_nbt,
    ReadOffset,
    ByteTag,
    ShortTag,
    IntTag,
    LongTag,
    StringTag,
    bedrock_encoding,
)
from generate_changes import generate_changes


logging.basicConfig(level=logging.INFO)


def load_nbt_array(path: str) -> list[NamedTag]:
    try:
        with open(path, "rb") as f:
            data = f.read()
    except FileNotFoundError:
        return []
    tags = []
    offset = ReadOffset()
    while data:
        tags.append(
            load_nbt(
                data,
                compressed=False,
                preset=bedrock_encoding,
                read_offset=offset,
            )
        )
        data = data[offset.offset :]
    return tags


def convert_block_palette(states_path: str):
    """Convert raw states format to a more readable JSON format."""
    block_palette = []
    data_version = None
    for state in load_nbt_array(states_path):
        block_palette.append(
            json.dumps(
                {
                    "name": state.compound["name"].py_str,
                    "states": [
                        {
                            "name": prop_name,
                            "type": {
                                ByteTag: "byte",
                                ShortTag: "short",
                                IntTag: "int",
                                LongTag: "long",
                                StringTag: "string",
                            }[prop_value.__class__],
                            "value": prop_value.py_data,
                        }
                        for prop_name, prop_value in state.compound["states"].items()
                    ],
                }
            )
        )
        if data_version is None:
            data_version = state.compound["version"].py_int
        else:
            assert data_version == state.compound["version"].py_int

    if block_palette:
        with open(
            os.path.join(os.path.dirname(states_path), "block_palette.json"), "w"
        ) as f:
            merged_states = ",\n\t\t".join(block_palette)
            f.write(f"""{{\n\t"data_version": {data_version},\n\t"blocks": [\n\t\t{merged_states}\n\t]\n}}""")


def get_modded_server(
    ll_bin_path: str, identifier: str, path: str, server_dir: str
) -> str:
    """
    Download and mod the Bedrock server if it does not exist.

    Directory structure
    path
        server_url.txt - a txt file containing the url to the server zip
        server - a directory where the modded server will be placed

    :param ll_bin_path: The path to the LiteLoader binaries.
    :param identifier: An identifier to use in logging. Use the server version number.
    :param path: The path to the directory
    :param server_dir: The path to the server directory
    :return: The path to the modded exe
    """
    logging.info(f"Processing {path}")

    # Check if the server directory already exists
    if not os.path.isdir(server_dir):
        logging.info(f"Downloading {path}")
        # Get the server URL
        with open(os.path.join(path, "server_url.txt")) as f:
            server_url = f.read()

        # Download the server file
        server_zip = os.path.join(path, "server.zip")
        with urlopen(server_url, context=ssl._create_unverified_context()) as web_file:
            with open(server_zip, "wb") as disk_file:
                while True:
                    data = web_file.read(4096)
                    if data:
                        disk_file.write(data)
                    else:
                        break

        # Extract the server files
        with ZipFile(server_zip, "r") as zip_file:
            zip_file.extractall(server_dir)

        # Delete the zip to reduce memory
        os.remove(server_zip)

    modded_server = os.path.join(server_dir, "bedrock_server_mod.exe")
    if not os.path.isfile(modded_server):
        logging.info(f"Modding {path}")
        # If it has not been modded
        if not os.path.isfile(os.path.join(server_dir, "bedrock_server.pdb")):
            raise Exception(f"The pdb file is missing for {server_dir}")

        # Copy the mod binaries
        editor_path = os.path.join(server_dir, "LLPeEditor.exe")
        shutil.copyfile(os.path.join(ll_bin_path, "LLPeEditor.exe"), editor_path)
        shutil.copyfile(
            os.path.join(ll_bin_path, "LLPreLoader.dll"),
            os.path.join(server_dir, "LLPreLoader.dll"),
        )

        # Run the editor
        process = subprocess.Popen(
            [editor_path, "-m", "--pause=false"],
            cwd=server_dir,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
        )
        with process.stdout:
            for line in iter(process.stdout.readline, b""):
                logging.info(f"\x1b[0m{identifier}: {line.decode().strip()}\x1b[0m")
        assert os.path.isfile(modded_server)
        try:
            os.remove(editor_path)
        except OSError:
            pass

    return modded_server


def process_version(
    ll_bin_path: str,
    dll_path: str,
    dll_file: bytes,
    dll_file_hash: str,
    version_path: str,
    last_version_path: str,
    force_regenerate: bool = False,
):
    """Create the server and generate data for a specific version."""
    rebuild = force_regenerate

    try:
        with open(os.path.join(version_path, "generated", "data_hash.txt")) as f:
            rebuild |= f.read() != dll_file_hash
    except OSError:
        rebuild = True

    if rebuild:
        # If the generator changed we need to regenerate the data

        # Download the server
        identifier = os.path.basename(version_path)
        server_dir = os.path.join(version_path, "server")
        modded_server = get_modded_server(ll_bin_path, identifier, version_path, server_dir)

        # Copy the plugin
        plugin_dir = os.path.join(server_dir, "plugins")
        if os.path.isdir(plugin_dir):
            shutil.rmtree(plugin_dir)
        os.makedirs(plugin_dir)
        with open(os.path.join(plugin_dir, os.path.basename(dll_path)), "wb") as f:
            f.write(dll_file)

        # Remove any generated data
        generated_dir = os.path.join(server_dir, "generated")
        if os.path.isdir(generated_dir):
            shutil.rmtree(generated_dir)
        os.makedirs(generated_dir)

        # Run the server
        process = subprocess.Popen(
            [modded_server],
            cwd=server_dir,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
        )
        with process.stdout:
            for line in iter(process.stdout.readline, b""):
                logging.info(f"\x1b[0m{identifier}: {line.decode().strip()}\x1b[0m")

        # Write the dll hash to the generated files
        with open(os.path.join(generated_dir, "data_hash.txt"), "w") as f:
            f.write(dll_file_hash)

        # Copy the generated files to the output location
        generated_out_dir = os.path.join(version_path, "generated")
        if os.path.isdir(generated_out_dir):
            shutil.rmtree(generated_out_dir)
        shutil.copytree(generated_dir, generated_out_dir)

    rebuild |= not os.path.isfile(os.path.join(version_path, "generated", "block", "block_palette.json"))

    if rebuild:
        states_path = os.path.join(version_path, "generated", "block", "states.nbtarr")
        if os.path.isfile(states_path):
            convert_block_palette(states_path)

        generate_changes(last_version_path, version_path)


def main(
    min_version: tuple[int, ...],
    max_version: tuple[int, ...],
    force_regenerate: bool,
    dll_path: str,
    versions_path: str,
    ll_bin_path: str,
) -> None:
    """Configure the server and generate data for every server in the specified version range."""
    with open(dll_path, "rb") as f:
        dll_file = f.read()
    dll_file_hash = hashlib.md5(dll_file).hexdigest()
    last_server_path = "null"

    for version, server_path in sorted(
        (tuple(map(int, os.path.basename(os.path.dirname(txt_path)).split("."))), os.path.dirname(txt_path))
        for txt_path in glob.glob(
            os.path.join(glob.escape(versions_path), "*", "server_url.txt")
        )
    ):
        if min_version <= version <= max_version:
            print(f"Processing version {version}")
            process_version(
                ll_bin_path,
                dll_path,
                dll_file,
                dll_file_hash,
                server_path,
                last_server_path,
                force_regenerate,
            )
        else:
            print(f"Skipping version {version}")
        last_server_path = server_path


def main_cli() -> None:
    """A CLI which calls the main function."""
    current_dir = os.path.dirname(__file__)
    parser = argparse.ArgumentParser()
    parser.add_argument("--min_version", type=str, default="0.0.0.0")
    parser.add_argument("--max_version", type=str, default="9.9.9.9")
    parser.add_argument("--force_regenerate", type=bool, default=False)
    parser.add_argument(
        "--dll_path",
        type=str,
        default=os.path.realpath(os.path.join(current_dir, "BedrockData.dll")),
    )
    parser.add_argument(
        "--versions_path",
        type=str,
        default=os.path.realpath(os.path.join(current_dir, "..", "versions")),
    )
    parser.add_argument(
        "--ll_bin_path",
        type=str,
        default=os.path.realpath(os.path.join(current_dir, "LL", "bin")),
    )

    args = parser.parse_args()

    min_version = tuple(map(int, args.min_version.split(".")))
    max_version = tuple(map(int, args.max_version.split(".")))
    force_regenerate = args.force_regenerate
    dll_path = args.dll_path
    versions_path = args.versions_path
    ll_bin_path = args.ll_bin_path

    main(
        min_version, max_version, force_regenerate, dll_path, versions_path, ll_bin_path
    )


if __name__ == "__main__":
    main_cli()
