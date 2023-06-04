# CommonLibSSE NG Plugin Template

## Setup

- Clone the repository
- In `vcpkg.json`, specify the name, version etc. of your plugin
- In `vcpkg-configuration.json`, set the `baseline` to the latest commit for each repo
- In `CMakeLists.txt`, specify the name of your plugin and add your .h and .cpp files

## Building your project

- Hit `Ctrl+Shift+B`

## Dependencies

- [vcpkg](https://github.com/microsoft/vcpkg/releases)
  - Create a new Windows environment variable called `VCPKG_ROOT` which points to your vcpkg install directory
- [CMake](https://cmake.org/)
- [LLVM](https://github.com/llvm/llvm-project/releases)
- Visual Studio 2022 with C++ workload
