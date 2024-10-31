# CommonLibSSE-NG Plugin Template

## Setup

- Clone the repository
- Run `cd CLibNGPluginTemplate`
- Run `py project_setup.py` (requires [Python 3.12+](https://www.python.org/download/pre-releases/))

**NOTE**: You should run `vcpkg x-update-baseline` (in the project's root directory) often to make sure that vcpkg is fetching the latest versions of CommonLibSSE-NG and other dependencies

## Building your project

- Select one of the CMake presets (release or debug), configure, and build.
- The .dll and .pdb files will be placed in `contrib\PluginRelease` or `contrib\PluginDebug` depending on your selected preset

## Requirements

- [vcpkg](https://github.com/microsoft/vcpkg)
  - Create a new environment variable called `VCPKG_ROOT` which points to your vcpkg install directory
- [CMake](https://cmake.org)
- [LLVM](https://github.com/llvm/llvm-project/releases) (for `clang-format` and `clang-tidy`)
- Visual Studio 2022 build tools

## Resources

- [Address Library Database](https://github.com/meh321/AddressLibraryDatabase)
- [Address Library Manager](https://github.com/meh321/AddressLibraryManager)
- [Steamless](https://github.com/atom0s/Steamless/releases)
