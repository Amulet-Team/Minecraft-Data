import glob
from typing import Iterable
import os
import subprocess
import sys
from undname import undname


def get_symbols(pdb_path: str):
    """Get a list of symbols from a pdb file"""
    process = subprocess.Popen(["cvdump.exe", "-p", pdb_path], stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    with process.stdout:
        line: bytes
        for line in iter(process.stdout.readline, b""):
            line_s = line.decode()
            if not line_s.startswith("S_PUB32"):
                continue
            yield line_s.split(",", 2)[-1].strip()


def generate_header_from_symbols(header_path: str, decorated_symbols: Iterable[str]):
    """Generate a header file from an iterable of decorated symbols."""
    symbols: list[tuple[bool, str, str, str]] = []
    for decorated_symbol in decorated_symbols:
        try:
            qualname = undname(decorated_symbol, name_only=True)
            undecorated_symbol = undname(decorated_symbol)
        except:
            symbols.append((True, "", "", decorated_symbol))
        else:
            symbols.append((qualname == undecorated_symbol, qualname, undecorated_symbol, decorated_symbol))

    os.makedirs(os.path.dirname(header_path), exist_ok=True)
    with open(header_path, "w") as f:
        for odd, _, undecorated_symbol, decorated_symbol in sorted(symbols):
            if odd:
                f.write(f"// {decorated_symbol}\n// {undecorated_symbol}\n")
            else:
                f.write(f"// {decorated_symbol}\n{undecorated_symbol}\n")


def generate_header(pdb_path: str):
    """Generate a header file for all symbols in a pdb file."""
    server_dir = os.path.dirname(pdb_path)
    generate_header_from_symbols(os.path.join(server_dir, "symbols.hpp"), get_symbols(pdb_path))


def generate_diff(path: str):
    """
    Generate the header difference compared to the previous version for all versions in the directory.

    path/*/server/bedrock_server.pdb

    :param path: A path to a directory containing a server version per directory
    """
    pdb_files = glob.glob(os.path.join(glob.escape(path), "*", "server", "bedrock_server.pdb"))
    versions: list[tuple[tuple[int, ...], str]] = []
    for pdb_path in pdb_files:
        *_, version_s, _, _ = pdb_path.split(os.sep)
        versions.append((tuple(map(int, version_s.split("."))), version_s))

    previous_symbols = set()
    for version, version_s in sorted(versions):
        print(version_s)
        server_dir = os.path.join(path, version_s, "server")
        pdb_path = os.path.join(server_dir, "bedrock_server.pdb")
        symbols = set(get_symbols(pdb_path))
        generate_header_from_symbols(os.path.join(path, "..", "headers", f"{version_s}_added.hpp"), symbols.difference(previous_symbols))
        generate_header_from_symbols(os.path.join(path, "..", "headers", f"{version_s}_removed.hpp"), previous_symbols.difference(symbols))
        previous_symbols = symbols


def main():
    generate_diff(os.path.join("..", "versions"))

if __name__ == '__main__':
    main()
