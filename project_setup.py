import os
import subprocess
import shutil
import stat


def onexc(func, path, exc_info):
    if not os.access(path, os.W_OK):
        os.chmod(path, stat.S_IWUSR)
        func(path)
    else:
        raise


# Remove original git repo
if os.path.isdir(".git"):
    shutil.rmtree(".git", onexc=onexc)

# Remove README.md
os.remove("README.md")

# Get project name and author
project_name = input("Enter project name: ")
author = input("Enter author: ")
print()

# Update CMakeLists.txt
with open("CMakeLists.txt", "r", encoding="utf-8") as cmakelists_file:
    cmakelists = cmakelists_file.read()

cmakelists = cmakelists.replace("PluginName", project_name)
cmakelists = cmakelists.replace("AuthorName", author)
cmakelists = cmakelists.replace("0.0.1", "1.0.0")

with open("CMakeLists.txt", "w", encoding="utf-8") as cmakelists_file:
    cmakelists_file.write(cmakelists)

# Rename ini file
os.rename(
    os.path.join("contrib", "Config", "PluginName.ini"),
    os.path.join("contrib", "Config", f"{project_name}.ini"),
)

# Update Settings.cpp
with open(
    os.path.join("src", "Settings.cpp"), "r", encoding="utf-8"
) as settings_cpp_file:
    settings_cpp = settings_cpp_file.read()

settings_cpp = settings_cpp.replace("PluginName.ini", f"{project_name}.ini")

with open(
    os.path.join("src", "Settings.cpp"), "w", encoding="utf-8"
) as settings_cpp_file:
    settings_cpp_file.write(settings_cpp)

# Update vcpkg.json builtin-baseline
print("Updating vcpkg.json...")
subprocess.run(
    [f"{os.environ["VCPKG_ROOT"]}\\vcpkg.exe", "x-update-baseline"], shell=True
)
print()

# Initialize empty git repo
subprocess.run(["git", "init"])

# Self-destruct
os.remove(__file__)
