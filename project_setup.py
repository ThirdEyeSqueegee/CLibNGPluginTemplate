import os
import re
import shutil
import stat
import subprocess
import json

cwd = os.path.dirname(os.path.abspath(__file__))

vcpkg_repo = "https://github.com/microsoft/vcpkg"
stdout, stderr = subprocess.Popen(
    ["git", "ls-remote", vcpkg_repo], stdout=subprocess.PIPE
).communicate()
vcpkg_sha = re.split(r"\t+", stdout.decode("ascii"))[0]

subprocess.Popen(["git", "submodule", "update", "--init"], cwd=cwd).communicate()


def onexc(func, path, exc_info):
    if not os.access(path, os.W_OK):
        os.chmod(path, stat.S_IWUSR)
        func(path)
    else:
        raise


if os.path.isdir(os.path.join(cwd, ".git")):
    shutil.rmtree(os.path.join(cwd, ".git"), onexc=onexc)

os.remove(os.path.join(cwd, "README.md"))

project_name = input("Enter project name: ")
author = input("Enter author: ")
pattern = re.compile(r"(?<!^)(?=[A-Z])")

with open(os.path.join(cwd, "vcpkg.json"), "r", encoding="utf-8") as vcpkg_json_file:
    vcpkg_json = json.load(vcpkg_json_file)

name = pattern.sub("-", project_name).lower()
vcpkg_json["name"] = name
vcpkg_json["version-semver"] = "1.0.0"

vcpkg_json["vcpkg-configuration"]["default-registry"]["baseline"] = vcpkg_sha

with open(os.path.join(cwd, "vcpkg.json"), "w", encoding="utf-8") as vcpkg_json_file:
    json.dump(vcpkg_json, vcpkg_json_file, indent=2)

with open(
    os.path.join(cwd, "CMakeLists.txt"), "r", encoding="utf-8"
) as cmakelists_file:
    cmakelists = cmakelists_file.read()

cmakelists = cmakelists.replace("PluginName", project_name)
cmakelists = cmakelists.replace("AuthorName", author)
cmakelists = cmakelists.replace("0.0.1", "1.0.0")

with open(
    os.path.join(cwd, "CMakeLists.txt"), "w", encoding="utf-8"
) as cmakelists_file:
    cmakelists_file.write(cmakelists)

os.rename(
    os.path.join(cwd, "contrib", "Config", "PluginName.ini"),
    os.path.join(cwd, "contrib", "Config", f"{project_name}.ini"),
)

with open(
    os.path.join(cwd, "src", "Settings.cpp"), "r", encoding="utf-8"
) as settings_cpp_file:
    settings_cpp = settings_cpp_file.read()

settings_cpp = settings_cpp.replace("PluginName.ini", f"{project_name}.ini")

with open(
    os.path.join(cwd, "src", "Settings.cpp"), "w", encoding="utf-8"
) as settings_cpp_file:
    settings_cpp_file.write(settings_cpp)
