import os
import re
import shutil
import stat

cwd = os.path.dirname(os.path.abspath(__file__))
print(cwd)


def onerror(func, path, exc_info):
    if not os.access(path, os.W_OK):
        os.chmod(path, stat.S_IWUSR)
        func(path)
    else:
        raise


if os.path.isdir(os.path.join(cwd, ".git")):
    shutil.rmtree(os.path.join(cwd, ".git"), onerror=onerror)
if os.path.isdir(os.path.join(cwd, ".vs")):
    shutil.rmtree(os.path.join(cwd, ".vs"), onerror=onerror)

project_name = input("Enter project name: ")
pattern = re.compile(r"(?<!^)(?=[A-Z])")

with open(os.path.join(cwd, "vcpkg.json"), "r", encoding="utf-8") as vcpkg_json_file:
    vcpkg_json = vcpkg_json_file.read()

name = pattern.sub("-", project_name).lower()
vcpkg_json = vcpkg_json.replace("plugin-name", name)
vcpkg_json = vcpkg_json.replace("0.0.1", "1.0.0")

with open(os.path.join(cwd, "vcpkg.json"), "w", encoding="utf-8") as vcpkg_json_file:
    vcpkg_json_file.write(vcpkg_json)

with open(
    os.path.join(cwd, "CMakeLists.txt"), "r", encoding="utf-8"
) as cmakelists_file:
    cmakelists = cmakelists_file.read()

cmakelists = cmakelists.replace("PluginName", project_name)
cmakelists = cmakelists.replace("0.0.1", "1.0.0")

with open(
    os.path.join(cwd, "CMakeLists.txt"), "w", encoding="utf-8"
) as cmakelists_file:
    cmakelists_file.write(cmakelists)

os.rename(
    os.path.join(cwd, "contrib\\Config\\PluginName.ini"),
    os.path.join(cwd, f"contrib\\Config\\{project_name}.ini"),
)

with open(
    os.path.join(cwd, "src\\Settings.cpp"), "r", encoding="utf-8"
) as settings_cpp_file:
    settings_cpp = settings_cpp_file.read()

settings_cpp = settings_cpp.replace("PluginName.ini", f"{project_name}.ini")

with open(
    os.path.join(cwd, "src\\Settings.cpp"), "w", encoding="utf-8"
) as settings_cpp_file:
    settings_cpp_file.write(settings_cpp)
