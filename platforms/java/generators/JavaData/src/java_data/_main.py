import glob
import os
from zipfile import ZipFile
import re
import urllib.request
from concurrent.futures import ThreadPoolExecutor
import logging
import subprocess
import time

from jawa.classloader import ClassLoader
from jawa.constants import UTF8

from ._javap import javap
from ._manifest import get_versions, ReleaseType, MinecraftVersion
from ._deobfuscate import deobfuscate

ServerPattern = re.compile(r"META-INF/versions/.*?/server-.*?\.jar")

log = logging.getLogger(__name__)


def main(versions_dir: str):
    count = 0
    with ThreadPoolExecutor() as executor:
        for version_data in get_versions():
            if version_data.release_type is ReleaseType.Release:
                version_dir = os.path.join(versions_dir, version_data.version)
                executor.submit(process_version, version_dir, version_data)
                count += 1
                if count >= 2:
                    break


def process_version(version_dir: str, version_data: MinecraftVersion):
    try:
        os.makedirs(version_dir, exist_ok=True)
        version_data2 = version_data.get_data()

        server_path = os.path.join(version_dir, "server.jar")
        if not os.path.isfile(server_path):
            with urllib.request.urlopen(version_data2.server_url) as f:
                server_file = f.read()
            with open(server_path, "wb") as server:
                server.write(server_file)

        mapping_path = os.path.join(version_dir, "server.txt")
        if not os.path.isfile(mapping_path) and version_data2.server_mapping_url is not None:
            with urllib.request.urlopen(version_data2.server_mapping_url) as f:
                mapping_file = f.read()
            with open(mapping_path, "wb") as server:
                server.write(mapping_file)

        # The server format changed around 1.18.
        # There is a jar file packaged within the jar file.
        # If that is the case we must extract it.
        with ZipFile(server_path) as jar_file:
            server_paths_in_jar = list(filter(ServerPattern.fullmatch, jar_file.namelist()))
            if len(server_paths_in_jar) == 0:
                # Old style server
                pass
            elif len(server_paths_in_jar) == 1:
                server_path_in_jar = server_paths_in_jar[0]
                # TODO: server_path_in_jar may contain illegal characters that are escaped by the extract method.
                #  This means that it could have been extracted before but the path we made is not the correct one.
                server_path = os.path.join(version_dir, server_path_in_jar)
                if not os.path.isfile(server_path):
                    server_path = jar_file.extract(server_path_in_jar, path=version_dir)
            else:
                raise RuntimeError(f"Expected 1 matching version jar but found {len(server_paths_in_jar)}")

        server_deob_path = os.path.join(version_dir, "server_deob.jar")
        if os.path.isfile(mapping_path):
            if not os.path.isfile(server_deob_path):
                # Deobfuscate the jar file
                deobfuscate(server_path, server_deob_path, mapping_path)
            server_path = server_deob_path

        loader = ClassLoader(server_path, max_cache=0)

        # t = time.time()
        # print("start", t)

        # for class_path in loader.classes:
        #     cf = loader[class_path]
        # print("end", time.time() - t)
        # return

        # Find the serialisation method
        cls = loader["net/minecraft/world/level/chunk/storage/ChunkSerializer"]
        write_methods = list(cls.methods.find(f=lambda m: len(m.args) == 2 and m.returns.name == "net/minecraft/nbt/CompoundTag"))
        if len(write_methods) != 1:
            raise RuntimeError("Did not find exactly 1 chunk write method.")
        write_method = write_methods[0]

        # for cls_path in loader.classes:
        #     cls = loader[cls_path]
        #     for const in cls.constants:
        #         if isinstance(const, UTF8):
        #             if const.value == "xPos":
        #                 print(cls_path)

        assembly = javap(
            loader,
            cls,
            write_method
        )

        generated_path = os.path.join(os.path.dirname(os.path.dirname(version_dir)), "generated", version_data.version)
        os.makedirs(generated_path, exist_ok=True)
        with open(os.path.join(generated_path, "chunk.txt"), "w") as f:
            f.write(assembly)

    except Exception as e:
        log.exception(e)
