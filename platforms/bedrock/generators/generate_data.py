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

PluginPath = os.path.join("BedrockData", "BedrockData.dll")
VersionsPath = os.path.join("..", "versions")
BinPath = os.path.join("LL", "bin")


def get_modded_server(path: str, server_dir: str) -> str:
    """
    Download and mod the Bedrock server if it does not exist.

    Directory structure
    path
        server_url.txt - a txt file containing the url to the server zip
        server - a directory where the modded server will be placed

    :param path: The path to the directory
    :param server_dir: The path to the server directory
    :return: The path to the modded exe
    """
    print(f"Processing {path}")


    # Check if the server directory already exists
    if not os.path.isdir(server_dir):
        print(f"Downloading {path}")
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
        print(f"Modding {path}")
        # If it has not been modded
        if not os.path.isfile(os.path.join(server_dir, "bedrock_server.pdb")):
            raise Exception(f"The pdb file is missing for {server_dir}")

        # Copy the mod binaries
        editor_path = os.path.join(server_dir, "LLPeEditor.exe")
        shutil.copyfile(os.path.join(BinPath, "LLPeEditor.exe"), editor_path)
        shutil.copyfile(os.path.join(BinPath, "LLPreLoader.dll"), os.path.join(server_dir, "LLPreLoader.dll"))

        # Run the editor
        subprocess.run([editor_path, "-m", "--pause=false"], cwd=server_dir)
        assert os.path.isfile(modded_server)
        os.remove(editor_path)

    return modded_server


def process_version(path: str):
    server_dir = os.path.join(path, "server")
    modded_server = get_modded_server(path, server_dir)

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

    # Run the server
    subprocess.run(modded_server, cwd=server_dir)

    generated_out_dir = os.path.join(path, "generated")
    if os.path.isdir(generated_out_dir):
        shutil.rmtree(generated_out_dir)
    shutil.copytree(generated_dir, generated_out_dir)


def main():
    # with ThreadPoolExecutor(1) as e:
    #     for url_txt_path in glob.glob(os.path.join(glob.escape(VersionsPath), "*", "server_url.txt")):
    #         e.submit(process_version, os.path.dirname(url_txt_path))

    for url_txt_path in glob.glob(os.path.join(glob.escape(VersionsPath), "*", "server_url.txt")):
        process_version(os.path.dirname(url_txt_path))


if __name__ == '__main__':
    main()
