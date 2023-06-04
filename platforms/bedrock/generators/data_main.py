"""
A script to automate the downloading of server files and generating data from the servers.
"""
from typing import Optional, NamedTuple
import os
import glob
from zipfile import ZipFile
from urllib.request import urlopen
import shutil
import subprocess
import re
from threading import RLock
import logging
import argparse
import hashlib
import json
from amulet_nbt import NamedTag, load as load_nbt, ReadContext, ListTag, ByteTag, ShortTag, IntTag, LongTag, StringTag


logging.basicConfig(level=logging.INFO)


def load_nbt_array(path: str) -> list[NamedTag]:
    try:
        with open(path, "rb") as f:
            data = f.read()
    except FileNotFoundError:
        return []
    tags = []
    context = ReadContext()
    while data:
        tags.append(load_nbt(data, compressed=False, little_endian=True, read_context=context, string_decoder=bytes.decode))
        data = data[context.offset:]
    return tags


class DataGenerator:
    # CLI
    min_version: Optional[tuple[int, ...]]
    max_version: Optional[tuple[int, ...]]
    force_regenerate: bool
    dll_path: str
    versions_path: str
    ll_bin_path: str

    # attributes
    dll_file: bytes
    dll_file_hash: str
    all_version_paths: list[str]
    process_version_paths: list[str]

    def __init__(self):
        self._parse_args()

        with open(self.dll_path, "rb") as f:
            self.dll_file = f.read()
        self.dll_file_hash = hashlib.md5(self.dll_file).hexdigest()

        versions: list[tuple[tuple[int, ...], str]] = []
        for server_path in glob.glob(os.path.join(glob.escape(self.versions_path), "*", "server_url.txt")):
            server_path = os.path.dirname(server_path)
            dir_name = os.path.basename(server_path)
            versions.append((tuple(map(int, dir_name.split("."))), server_path))
        self.all_version_paths = [path for _, path in versions]
        self.process_version_paths = [path for v, path in versions if self.min_version <= v <= self.max_version]

        self._main()

    def _parse_args(self):
        parser = argparse.ArgumentParser()
        parser.add_argument("--min_version", type=str, default="0.0.0.0")
        parser.add_argument("--max_version", type=str, default="9.9.9.9")
        parser.add_argument("--force_regenerate", type=bool, default=False)
        parser.add_argument("--dll_path", type=str, default=os.path.join("BedrockData", "x64", "Release", "BedrockData.dll"))
        parser.add_argument("--versions_path", type=str, default=os.path.join("..", "versions"))
        parser.add_argument("--ll_bin_path", type=str, default=os.path.join("LL", "bin"))

        args = parser.parse_args()

        self.min_version = tuple(map(int, args.min_version.split(".")))
        self.max_version = tuple(map(int, args.max_version.split(".")))
        self.force_regenerate = args.force_regenerate
        self.dll_path = args.dll_path
        self.versions_path = args.versions_path
        self.ll_bin_path = args.ll_bin_path

    def _main(self):
        for server_path in self.process_version_paths:
            self._process_version(server_path)

    def _process_version(self, path: str):
        try:
            with open(os.path.join(path, "generated", "data_hash.txt")) as f:
                generator_changed = f.read() != self.dll_file_hash
        except OSError:
            generator_changed = True

        if generator_changed or self.force_regenerate:
            # If the generator changed we need to regenerate the data

            # Download the server
            identifier = os.path.basename(path)
            server_dir = os.path.join(path, "server")
            modded_server = self._get_modded_server(identifier, path, server_dir)

            # Copy the plugin
            plugin_dir = os.path.join(server_dir, "plugins")
            if os.path.isdir(plugin_dir):
                shutil.rmtree(plugin_dir)
            os.makedirs(plugin_dir)
            with open(os.path.join(plugin_dir, os.path.basename(self.dll_path)), "wb") as f:
                f.write(self.dll_file)

            # Remove any generated data
            generated_dir = os.path.join(server_dir, "generated")
            if os.path.isdir(generated_dir):
                shutil.rmtree(generated_dir)
            os.makedirs(generated_dir)

            # Run the server
            process = subprocess.Popen([modded_server], cwd=server_dir, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
            with process.stdout:
                for line in iter(process.stdout.readline, b""):
                    logging.info(f"\x1b[0m{identifier}: {line.decode().strip()}\x1b[0m")

            # Write the dll hash to the generated files
            with open(os.path.join(generated_dir, "data_hash.txt"), "w") as f:
                f.write(self.dll_file_hash)

            # Copy the generated files to the output location
            generated_out_dir = os.path.join(path, "generated")
            if os.path.isdir(generated_out_dir):
                shutil.rmtree(generated_out_dir)
            shutil.copytree(generated_dir, generated_out_dir)

        if generator_changed or self.force_regenerate or not os.path.isfile(os.path.join(path, "generated", "block", "block_palette.json")):
            states_path = os.path.join(path, "generated", "block", "states.nbtarr")
            if os.path.isfile(states_path):
                self._convert_block_palette(states_path)

    def _get_modded_server(self, identifier: str, path: str, server_dir: str) -> str:
        """
        Download and mod the Bedrock server if it does not exist.

        Directory structure
        path
            server_url.txt - a txt file containing the url to the server zip
            server - a directory where the modded server will be placed

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
            with urlopen(server_url) as web_file:
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
            shutil.copyfile(os.path.join(self.ll_bin_path, "LLPeEditor.exe"), editor_path)
            shutil.copyfile(os.path.join(self.ll_bin_path, "LLPreLoader.dll"), os.path.join(server_dir, "LLPreLoader.dll"))

            # Run the editor
            process = subprocess.Popen([editor_path, "-m", "--pause=false"], cwd=server_dir, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
            with process.stdout:
                for line in iter(process.stdout.readline, b""):
                    logging.info(f"\x1b[0m{identifier}: {line.decode().strip()}\x1b[0m")
            assert os.path.isfile(modded_server)
            try:
                os.remove(editor_path)
            except OSError:
                pass

        return modded_server

    def _convert_block_palette(self, states_path: str):
        states = load_nbt_array(states_path)
        block_palette = []
        data_version = None
        for state in states:
            block_palette.append({
                "name": state.compound["name"].py_str,
                "states": [
                    {
                        "name": prop_name,
                        "type": {ByteTag: "byte", ShortTag: "short", IntTag: "int", LongTag: "long", StringTag: "string"}[prop_value.__class__],
                        "value": prop_value.py_data
                    } for prop_name, prop_value in state.compound["states"].items()
                ]
            })
            if data_version is None:
                data_version = state.compound["version"].py_int
            else:
                assert data_version == state.compound["version"].py_int

        if block_palette:
            with open(os.path.join(os.path.dirname(states_path), "block_palette.json"), "w") as f:
                json.dump({
                    "data_version": data_version,
                    "blocks": block_palette
                }, f, indent="\t")


if __name__ == '__main__':
    DataGenerator()
