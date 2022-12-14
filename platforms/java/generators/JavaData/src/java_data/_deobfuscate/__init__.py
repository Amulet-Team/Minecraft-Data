import subprocess


def deobfuscate(in_jar, out_jar, mapping_path):
    subprocess.run(
        [
            "java",
            "-cp",
            "SpecialSource-1.10.0.jar;*;.",
            "net.md_5.specialsource.SpecialSource",
            "--in-jar",
            in_jar,
            "--out-jar",
            out_jar,
            "--srg-in",
            mapping_path,
            "--kill-lvt",
        ],
        cwd=__path__[0],
        check=True
    )
