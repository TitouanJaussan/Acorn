"""
Setup file to prepare the engine once acquired.
"""

from sys import platform as sys_platform
import platform
import os
import subprocess
import version

RUNTIME_VERSION_HEADER_PATH: str = os.path.join(
    "runtime", "include", "Acorn", "Version", "RuntimeVersion.hpp"
)

def get_distro_name() -> str:
    return platform.freedesktop_os_release()["NAME"]

def generate_header(version: Version) -> str:
    return (
        f"/* RuntimeVersion.hpp (auto-generated, any manual edit will be overwritten when the engine is compiled) */\n"
        f"#ifndef ACORN_RUNTIME_VERSION_HPP\n"
        f"#define ACORN_RUNTIME_VERSION_HPP\n\n"
        f"#define RUNTIME_VERSION_STRING \"{str(version)}\"\n\n"
        f"#define RUNTIME_VERSION_MAJOR {version.major}\n"
        f"#define RUNTIME_VERSION_MINOR {version.minor}\n"
        f"#define RUNTIME_VERSION_PATCH {version.patch}\n\n"
        f"#endif /* ACORN_RUNTIME_VERSION_HPP */\n"
    )

def create_runtime_version_header(version: Version) -> None:
    _dir: str = os.path.dirname(RUNTIME_VERSION_HEADER_PATH)

    if not os.path.exists(_dir):
        os.makedirs(_dir)

    with open(RUNTIME_VERSION_HEADER_PATH, "w") as file:
        file.write(generate_header(version))

def generate_build_files() -> None:
    premake_action: str = "gmake" if sys_platform == "linux" else "vs2022"  # TODO: Replace with vs2026 when supported

    proc = subprocess.Popen(["premake5", premake_action], shell=False)
    proc.communicate()

def setup() -> None:
    create_runtime_version_header(version.RUNTIME_VERSION)
    generate_build_files()

if __name__ == "__main__":
    setup()
