import os
from typing import Optional, Hashable
from amulet_nbt import AbstractBaseTag, AbstractBaseArrayTag, NamedTag, load as load_nbt, ReadOffset, ListTag, CompoundTag, AbstractBaseImmutableTag, ByteArrayTag, IntArrayTag, LongArrayTag, bedrock_encoding

VersionsPath = "../versions"


def load_single_line_file(path: str) -> str:
    try:
        with open(path) as f:
            return f.read().strip()
    except FileNotFoundError:
        return ""


def load_lined_file(path: str) -> dict[int, str]:
    try:
        with open(path) as f:
            return dict(enumerate(map(str.strip, f.readlines())))
    except FileNotFoundError:
        return {}


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


class BlockData:
    def __init__(self, path: str):
        self.entity = load_lined_file(
            os.path.join(path, "generated", "block", "block_entity.txt")
        )
        self.is_container = load_lined_file(
            os.path.join(path, "generated", "block", "is_container.txt")
        )
        self.variant = load_lined_file(
            os.path.join(path, "generated", "block", "variant.txt")
        )
        self.states = load_nbt_array(
            os.path.join(path, "generated", "block", "states.nbtarr")
        )


class VersionData:
    def __init__(self, path: str):
        self.actor_digest_version = load_single_line_file(
            os.path.join(path, "generated", "version", "actor_digest_version.txt")
        )
        self.blend_version = load_single_line_file(
            os.path.join(path, "generated", "version", "blend_version.txt")
        )
        self.build_version = load_single_line_file(
            os.path.join(path, "generated", "version", "build_version.txt")
        )
        self.level_chunk_format = load_single_line_file(
            os.path.join(path, "generated", "version", "level_chunk_format.txt")
        )
        self.storage_version = load_single_line_file(
            os.path.join(path, "generated", "version", "storage_version.txt")
        )
        self.sub_chunk_format = load_single_line_file(
            os.path.join(path, "generated", "version", "sub_chunk_format.txt")
        )


class GameData:
    def __init__(self, path: str):
        self.version_string = os.path.basename(path)
        self.versions = VersionData(path)
        self.biomes = load_lined_file(
            os.path.join(path, "generated", "biome", "biome_map.txt")
        )
        self.blocks = BlockData(path)


def freeze_nbt(value: AbstractBaseTag) -> Hashable:
    if isinstance(value, AbstractBaseImmutableTag):
        return (value.tag_id, value)
    elif isinstance(value, CompoundTag):
        return (value.tag_id, frozenset(((k, freeze_nbt(v)) for k, v in value.items())))
    elif isinstance(value, ListTag):
        return (value.tag_id, (freeze_nbt(v) for v in value))
    elif isinstance(value, AbstractBaseArrayTag):
        return (value.tag_id, tuple(value))
    else:
        raise RuntimeError


def main():
    last_game_data: Optional[GameData] = GameData("null")

    for version_number, version_string in sorted(
        (tuple(map(int, version_string.split("."))), version_string)
        for version_string in os.listdir(VersionsPath)
        if os.path.isdir(os.path.join(VersionsPath, version_string))
    ):
        path = os.path.join(VersionsPath, version_string)
        os.makedirs(os.path.join(path, "changes"), exist_ok=True)
        print(version_string)
        game_data = GameData(path)

        # Biome changes
        last_biomes = last_game_data.biomes
        this_biomes = game_data.biomes
        biome_changes = []
        for i in range(max([0, *last_biomes.keys(), *this_biomes.keys()])):
            last = last_biomes.get(i)
            this = this_biomes.get(i)
            if last != this:
                if last is None:
                    biome_changes.append(f"added {i}: {this}")
                elif this is None:
                    biome_changes.append(f"removed {i}: {last}")
                else:
                    biome_changes.append(f"changed {i}: {last} to {this}")
        if biome_changes:
            with open(os.path.join(path, "changes", "biomes.txt"), "w") as f:
                f.write("\n".join(biome_changes))

        # version changes
        # if last_game_data.versions.actor_digest_version != game_data.versions.actor_digest_version and game_data.versions.actor_digest_version != "-1":
        #     with open(os.path.join(path, "changes", "actor_digest_version.txt"), "w") as f:
        #         f.write(game_data.versions.actor_digest_version)
        # if last_game_data.versions.blend_version != game_data.versions.blend_version and game_data.versions.blend_version != "-1":
        #     with open(os.path.join(path, "changes", "blend_version.txt"), "w") as f:
        #         f.write(game_data.versions.blend_version)
        # if last_game_data.versions.level_chunk_format != game_data.versions.level_chunk_format and game_data.versions.level_chunk_format != "-1":
        #     with open(os.path.join(path, "changes", "level_chunk_format.txt"), "w") as f:
        #         f.write(game_data.versions.level_chunk_format)
        # if last_game_data.versions.storage_version != game_data.versions.storage_version and game_data.versions.storage_version != "-1":
        #     with open(os.path.join(path, "changes", "storage_version.txt"), "w") as f:
        #         f.write(game_data.versions.storage_version)
        # if last_game_data.versions.sub_chunk_format != game_data.versions.sub_chunk_format and game_data.versions.sub_chunk_format != "-1":
        #     with open(os.path.join(path, "changes", "sub_chunk_format.txt"), "w") as f:
        #         f.write(game_data.versions.sub_chunk_format)

        # block state changes
        last_states = []
        for state in last_game_data.blocks.states:
            state = state.compound.copy()
            del state["version"]
            last_states.append(state)
        this_states = []
        for state in game_data.blocks.states:
            state = state.compound.copy()
            del state["version"]
            this_states.append(state)

        last_frozen_states = {freeze_nbt(state): state for state in last_states}
        this_frozen_states = {freeze_nbt(state): state for state in this_states}

        removed_states = [v.to_snbt() for k, v in last_frozen_states.items() if k not in this_frozen_states]
        added_states = [v.to_snbt() for k, v in this_frozen_states.items() if k not in last_frozen_states]

        if removed_states:
            with open(os.path.join(path, "changes", "removed_states.snbt"), "w") as f:
                f.write(f"[\n\t")
                f.write(",\n\t".join(sorted(removed_states)))
                f.write(f"\n]")
        if added_states:
            with open(os.path.join(path, "changes", "added_states.snbt"), "w") as f:
                f.write(f"[\n\t")
                f.write(",\n\t".join(sorted(added_states)))
                f.write(f"\n]")

        last_game_data = game_data


if __name__ == "__main__":
    main()
