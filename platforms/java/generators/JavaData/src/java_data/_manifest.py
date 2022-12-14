import urllib.request
from typing import NamedTuple, Optional
import json
from enum import Enum


class ReleaseType(Enum):
    Release = "release"
    Snapshot = "snapshot"
    OldBeta = "old_beta"
    OldAlpha = "old_alpha"

    @classmethod
    def get(cls, value: str):
        out = next(filter(lambda v: v.value == value, ReleaseType), None)
        if out is None:
            raise ValueError(f"Could not find value {value}")
        return out


class MinecraftVersionData(NamedTuple):
    server_url: str
    server_mapping_url: Optional[str]


class MinecraftVersion(NamedTuple):
    version: str
    release_type: str
    version_url: str

    def get_data(self) -> MinecraftVersionData:
        with urllib.request.urlopen(self.version_url) as f:
            version_data = json.loads(f.read().decode())
        server_url = version_data["downloads"]["server"]["url"]
        server_mappings_url = version_data["downloads"].get("server_mappings", {}).get("url", None)
        return MinecraftVersionData(
            server_url,
            server_mappings_url
        )


def get_versions() -> list[MinecraftVersion]:
    """Get a list of Minecraft versions from the launcher manifest."""
    with urllib.request.urlopen("https://piston-meta.mojang.com/mc/game/version_manifest_v2.json") as f:
        manifest = json.loads(f.read().decode())
    return [
        MinecraftVersion(
            version_data["id"],
            ReleaseType.get(version_data["type"]),
            version_data["url"]
        )
        for version_data in manifest["versions"]
    ]
