"""
A script to automate the downloading of server files and generating data from the servers.
"""
import os
import glob
from zipfile import ZipFile
from urllib.request import urlopen
from concurrent.futures import ThreadPoolExecutor
import shutil
import subprocess
import re
from threading import RLock
import logging

PluginPath = os.path.join("BedrockData", "x64", "Release", "BedrockData.dll")
VersionsPath = os.path.join("..", "versions")
BinPath = os.path.join("LL", "bin")

_exit = False

logging.basicConfig(level=logging.INFO)


def get_modded_server(identifier: str, path: str, server_dir: str) -> str:
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
        shutil.copyfile(os.path.join(BinPath, "LLPeEditor.exe"), editor_path)
        shutil.copyfile(os.path.join(BinPath, "LLPreLoader.dll"), os.path.join(server_dir, "LLPreLoader.dll"))

        # Run the editor
        process = subprocess.Popen([editor_path, "-m", "--pause=false"], cwd=server_dir, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        with process.stdout:
            for line in iter(process.stdout.readline, b""):
                logging.info(f"\x1b[0m{identifier}: {line.decode().strip()}\x1b[0m")
        assert os.path.isfile(modded_server)
        os.remove(editor_path)

    return modded_server


_port = 19135
_port_lock = RLock()
PortPattern = re.compile(r"server-port=\d+")
Port6Pattern = re.compile(r"server-portv6=\d+")

def set_unique_port(path: str):
    """
    Modify the server.properties file to have a unique port.

    :param path: The path to the server.properties file.
    """
    global _port
    with open(path, "r+") as f:
        config = f.read()
        f.seek(0)
        f.truncate(0)
        with _port_lock:
            this_port = _port
            _port += 2
        config = PortPattern.sub(f"server-port={this_port}", config)
        config = Port6Pattern.sub(f"server-portv6={this_port+1}", config)

        f.write(config)


def process_version(path: str):
    identifier = os.path.basename(path)
    server_dir = os.path.join(path, "server")
    modded_server = get_modded_server(identifier, path, server_dir)

    # Copy the plugin
    plugin_dir = os.path.join(server_dir, "plugins")
    if os.path.isdir(plugin_dir):
        shutil.rmtree(plugin_dir)
    os.makedirs(plugin_dir)
    shutil.copyfile(PluginPath, os.path.join(plugin_dir, os.path.basename(PluginPath)))

    # Remove any generated data
    generated_dir = os.path.join(server_dir, "generated")
    if os.path.isdir(generated_dir):
        shutil.rmtree(generated_dir)
    os.makedirs(generated_dir)

    set_unique_port(os.path.join(server_dir, "server.properties"))

    # Run the server
    process = subprocess.Popen([modded_server], cwd=server_dir, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    with process.stdout:
        for line in iter(process.stdout.readline, b""):
            logging.info(f"\x1b[0m{identifier}: {line.decode().strip()}\x1b[0m")

    generated_out_dir = os.path.join(path, "generated")
    if os.path.isdir(generated_out_dir):
        shutil.rmtree(generated_out_dir)
    shutil.copytree(generated_dir, generated_out_dir)


def safely_process_version(path: str):
    global _exit
    if _exit:
        return
    try:
        process_version(path)
    except SystemExit:
        _exit = True
    except Exception as e:
        logging.exception(e)


def main():
    with ThreadPoolExecutor(2) as e:
        e.map(
            safely_process_version,
            map(os.path.dirname, glob.glob(os.path.join(glob.escape(VersionsPath), "*", "server_url.txt")))
        )


if __name__ == '__main__':
    main()
