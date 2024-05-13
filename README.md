# CommonLibSSE-NG Plugin Template

## Setup

- Clone the repository
- Optional:
  - Run `cd .\CLibNGPluginTemplate\`
  - Run `py .\project_setup.py\` (requires [Python 3.12+](https://www.python.org/download/pre-releases/))
  - Enter your project name (in CamelCase)
  - Select how you want to fetch CommonLibSSE-NG:
    - Local instance (default): Use CommonLibSSE-NG from the path defined in the `CommonLibSSEPath` environment variable
    - Submodule: Use CommonLibSSE-NG as a git submodule
  - `project_setup.py` just does a few convenience things like setting the project name in `vcpkg.json` and `CMakeLists.txt`

## Building your project

- Select one of the CMake presets (release or debug), configure, and build.
- The .dll and .pdb files will be placed in `contrib\PluginRelease` or `contrib\PluginDebug` depending on your selected preset

## Requirements

- [vcpkg](https://github.com/microsoft/vcpkg)
  - Create a new environment variable called `VCPKG_ROOT` which points to your vcpkg install directory
- [CMake](https://cmake.org/)
- [LLVM](https://github.com/llvm/llvm-project/releases)
- Visual Studio 2022 build tools
- Optional: If using a common instance of CommonLibSSE-NG, create a new environment variable called `CommonLibSSEPath` that points to the instance

## Resources

- [Address Library Database](https://github.com/meh321/AddressLibraryDatabase)
- [Address Library Manager](https://github.com/meh321/AddressLibraryManager)
- [Steamless](https://github.com/atom0s/Steamless/releases)
