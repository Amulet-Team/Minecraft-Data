"""
A script to check for new game versions and update the version list
and then generate data if there is a new version.
"""

from urllib.request import urlopen, Request
import re
import zlib
import argparse
import os

from data_main import main as data_main


ServerURLPattern = re.compile(
    r"https://minecraft\.azureedge\.net/bin-win/bedrock-server-(?P<version>.*)\.zip"
)


def get_current_server_match() -> re.Match[str]:
    with urlopen(
        Request(
            "https://www.minecraft.net/en-us/download/server/bedrock",
            headers={
                "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:105.0) Gecko/20100101 Firefox/105.0",
                "Accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8",
                "Accept-Encoding": "gzip, deflate, br",
            },
        ),
        timeout=5,
    ) as f:
        match = ServerURLPattern.search(zlib.decompress(f.read(), 15 + 32).decode())
    if match is None:
        raise RuntimeError("Could not find server URL")
    return match


def get_current_server_url() -> str:
    """Get the current server url from https://www.minecraft.net/en-us/download/server/bedrock"""
    return get_current_server_match().group()


def get_current_version() -> str:
    """Get the current server version from the current server url"""
    return get_current_server_match().group("version")


def main(
    dll_path: str,
    versions_path: str,
    ll_bin_path: str,
) -> None:
    match = get_current_server_match()
    version = match.group("version")
    version_path = os.path.join(versions_path, version)

    if os.path.isdir(version_path):
        # The current version has already been processed
        return

    os.makedirs(version_path)
    with open(os.path.join(version_path, "server_url.txt"), "w") as f:
        f.write(match.group())

    version_tuple = tuple(map(int, version.split(".")))

    data_main(version_tuple, (999,), False, dll_path, versions_path, ll_bin_path)


def main_cli() -> None:
    current_dir = os.path.dirname(__file__)
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--dll_path",
        type=str,
        default=os.path.realpath(
            os.path.join(
                current_dir, "BedrockData", "x64", "Release", "BedrockData.dll"
            )
        ),
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

    dll_path = args.dll_path
    versions_path = args.versions_path
    ll_bin_path = args.ll_bin_path

    main(dll_path, versions_path, ll_bin_path)


if __name__ == "__main__":
    main_cli()
