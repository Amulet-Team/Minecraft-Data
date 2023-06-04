import shutil
import urllib.request
import re
import zlib
import os
import hashlib
import glob
import subprocess
import zipfile


ServerURLPattern = re.compile(r"https://minecraft\.azureedge\.net/bin-win/bedrock-server-(?P<version>.*)\.zip")

GeneratorsDir = os.path.dirname(__file__)
DataGeneratorPath = os.path.join(GeneratorsDir, "BedrockData", "BedrockData")
BedrockDir = os.path.dirname(GeneratorsDir)
BedrockVersionsDir = os.path.join(BedrockDir, "versions")
HeaderGenerator = next(glob.iglob(os.path.join(GeneratorsDir, "HeaderGenerator", "HeaderGenerator*.jar")), None)


def get_generator_hash() -> str:
    """
    Get the hash of all the generator code files.
    This is used to check if the code changed between runs.
    """
    hashes = []
    for path in sorted(glob.glob(os.path.join(DataGeneratorPath, "**", "*.[ch]pp"), recursive=True)):
        fname = os.path.relpath(path, DataGeneratorPath)
        if not os.path.isfile(path):
            continue
        with open(path, "rb") as f:
            hashes.append(f"{fname} {hashlib.md5(f.read()).hexdigest()}")
    return "\r\n".join(hashes)


GeneratorCodeHash = get_generator_hash()


# # Load the previously stored hash. This is used to check if the generator code has changed.
# try:
#     with open(os.path.join(BedrockVersionsDir, "code_hash.txt")) as f:
#         GeneratorCodeHash = f.read()
# except Exception:
#     GeneratorCodeHash = None


def get_current_server_url() -> str:
    """Get the current server url from https://www.minecraft.net/en-us/download/server/bedrock"""
    with urllib.request.urlopen(
        urllib.request.Request(
            "https://www.minecraft.net/en-us/download/server/bedrock",
            headers={
                "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:105.0) Gecko/20100101 Firefox/105.0",
                "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8",
                "Accept-Encoding": "gzip, deflate, br",
            }
        ),
        timeout=5
    ) as f:
        match = ServerURLPattern.search(zlib.decompress(f.read(), 15+32).decode())
    if match is None:
        raise RuntimeError("Could not find server URL")
    return match.group()


def get_current_version() -> str:
    """Get the current server version from the current server url"""
    match = ServerURLPattern.fullmatch(get_current_server_url())
    if not match:
        raise RuntimeError("Could not extract server version from the server URL.")
    return match.group("version")


def create_headers(version_dir: str):
    """Generate the header files"""
    # TODO: generate the JSON at runtime if that code gets made public
    if HeaderGenerator is None:
        raise RuntimeError("Could not find header generator")

    # Extract the JSON file from the zip
    with zipfile.ZipFile(os.path.join(version_dir, "originalData.zip")) as zip_ref:
        zip_ref.extractall(os.path.join(version_dir, "originalData"))

    json_paths = glob.glob(os.path.join(version_dir, "originalData", "**", "originalData.json"), recursive=True)
    if len(json_paths) != 1:
        raise RuntimeError("Expected exactly 1 json file in the zip")

    try:
        # Generate the headers
        header_path = os.path.join(version_dir, "include", "MC")
        os.makedirs(header_path, exist_ok=True)
        subprocess.run([
            "java", "-jar", HeaderGenerator,
            "--config", os.path.join(GeneratorsDir, "HeaderGenerator", "config.json"),
            "--json", json_paths[0],
            "--generate", header_path,
            "--old", header_path,
        ])
    finally:
        # Delete the JSON file
        shutil.rmtree(os.path.join(version_dir, "originalData"), ignore_errors=True)


def extract_data(version: str):
    """Extract the data from a given version"""
    version_dir = os.path.join(BedrockVersionsDir, version)

    server_dir = os.path.join(version_dir, "server")
    server_path = os.path.join(server_dir, "bedrock_server.exe")
    symbols_path = os.path.join(server_dir, "bedrock_server.pdb")

    # Download and extract the server
    create_headers(version_dir)
    # Compile
    # Run


def main():
    # for version in os.listdir(BedrockVersionsDir):
    #     path = os.path.join(BedrockVersionsDir, version)
    #     if not os.path.isdir(path):
    #         continue
    #     extract_data(version)
    extract_data("1.19.30.04")


if __name__ == '__main__':
    main()
