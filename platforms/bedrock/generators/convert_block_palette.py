import os
from amulet_nbt import NamedTag, load as load_nbt, ReadContext, ListTag, ByteTag, ShortTag, IntTag, LongTag, StringTag
import glob
import json

VersionsPath = "../versions"


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


def main():
    for states_path in glob.glob(os.path.join(glob.escape(VersionsPath), "*", "generated", "block", "states.nbtarr")):
        print(states_path)
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
    main()
