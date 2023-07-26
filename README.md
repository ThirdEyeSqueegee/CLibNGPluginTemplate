# CommonLibSSE NG Plugin Template

## Setup

- Clone the repository
- Run `cd .\CLibNGPluginTemplate\`
- Run `py .\project_setup.py\`
- Enter your project name (in CamelCase)

## Building your project

- Visual Studio should prompt you to generate a CMake cache. Click on `Generate` and wait
- One the CMake cache is generated, hit `Ctrl+Shift+B` to build your project
- The .dll and .pdb files will be placed in `contrib\PluginRelease`

## Dependencies

- [vcpkg v2023.06.20+](https://github.com/microsoft/vcpkg/releases)
  - Create a new Windows environment variable called `VCPKG_ROOT` which points to your vcpkg install directory
- [CMake v3.27+](https://cmake.org/)
- [LLVM v16.0.6+](https://github.com/llvm/llvm-project/releases)
- Visual Studio 2022 with C++ workload

## Resources

- [Address Library Database](https://github.com/meh321/AddressLibraryDatabase)
- [Address Library Manager](https://github.com/meh321/AddressLibraryManager/releases)
- [Steamless](https://github.com/atom0s/Steamless/releases)
