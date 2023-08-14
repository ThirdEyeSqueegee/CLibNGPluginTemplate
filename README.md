# CommonLibSSE NG Plugin Template

## Setup

- Clone the repository
- Run `cd .\CLibNGPluginTemplate\`
- Run `py .\project_setup.py\`
- Enter your project name (in CamelCase)

## Building your project

- Visual Studio should prompt you to generate a CMake cache. Click on `Generate` and wait
- One the CMake cache is generated, hit `Ctrl+Shift+B` to build your project
- The .dll and .pdb files will be placed in `contrib\PluginRelease` or `contrib\PluginDebug` depending on your build configuration

### Build configs

- Two build configs are provided:
  - `Release`: Optimized release build, produces small and fast DLLs with associated PDBs
  - `Debug`: Debug build, produces DLLs and PDBs with full debug info, allowing the use of an interactive debugger

## Dependencies

- [vcpkg v2023.07.21+](https://github.com/microsoft/vcpkg/releases)
  - Create a new Windows environment variable called `VCPKG_ROOT` which points to your vcpkg install directory
- [CMake v3.27+](https://cmake.org/)
- [LLVM v16.0.6+](https://github.com/llvm/llvm-project/releases)
- Visual Studio 2022 with C++ workload

## Resources

- [Address Library Database](https://github.com/meh321/AddressLibraryDatabase)
- [Address Library Manager](https://github.com/meh321/AddressLibraryManager/releases)
- [Steamless](https://github.com/atom0s/Steamless/releases)

# Context

## What you need to know

- C++ and the tools mentioned in the Dependencies section
- Assembly (specifically, x86-64)
- x64 calling convention

## What is Skyrim reverse engineering?

We're all (hopefully) familiar with executables. The process of turning a set of human-readable source code files into machine-readable instructions consists of several layers of translation. Reverse engineering is the process of working back from machine-readable instructions to human-readable source code. Since we don't have the source code for Skyrim, we must use tools like the [Interactive Disassembler (IDA)](https://en.wikipedia.org/wiki/Interactive_Disassembler) to, you guessed it, reverse engineer the source code so that we may "hack into" the game's functionality and do all the interesting things that SKSE plugins do. Thankfully, a bunch of Really Smart People did most of the heavy lifting and went ahead and reverse engineered huge swathes of the game, resulting in [CommonLibSSE](https://github.com/Ryan-rsm-McKenzie/CommonLibSSE) and its various forks. Although these libraries provide a great deal of convenience and significantly speed up development, it is nonetheless often necessary to inspect the disassembled Skyrim executable in IDA or Ghidra.

## But what _is_ CommonLibSSE?

A library, written in C++, which consists of reverse-engineered classes, functions, etc. found in the disassembled Skyrim executable. Due to its age, there are several different runtime versions of Skyrim. The main versions of interest are v1.5.97, v1.6.640, and VR. Due to differences in struct layouts etc. amongst these runtimes and the resulting difficulty of building DLLs that target different runtimes, [CommonLibSSE-NG](https://github.com/CharmedBaryon/CommonLibSSE-NG) (the basis of this template) was created, which allows building a single DLL that can target every Skyrim runtime using clever tricks like [relocations](<https://en.wikipedia.org/wiki/Relocation_(computing)>).

## The Address Library:tm:

The Address Library is a mapping of integer IDs (e.g. 57463) to addresses in different Skyrim runtimes. It allows version-independent targeting of functions etc. using relocations. `REL::Relocation<decltype(&MyHook)> func{RELOCATION_ID(SE_ID, AE_ID), REL::Relocate(se_offset, ae_offset, vr_offset))}` returns a runtime-adjusted pointer to the function mapped by the given SE or AE address library IDs.

## Some terminology

- [Hooking](https://en.wikipedia.org/wiki/Hooking): Hooking involves intercepting function/subroutine calls and replacing or extending their logic. There are two types of hooks commonly seen in SKSE plugins:
  - Call site hook: These hooks target individual `call` instructions at specific addresses, allowing you to intercept and replace/extend a specific function call.
    - See `stl::write_call` in `CommonLibSSE-NG\include\SKSE\Trampoline.h`
  - Virtual function hook: These hooks target _every_ invocation of a given function via the virtual function table of its parent class.
    - See `stl::write_vfunc` in `CommonLibSSE-NG\include\REL\Relocation.h`
  - More about function hooks: [CommonLibSSE NG sample plugin repo](https://gitlab.com/colorglass/commonlibsse-sample-plugin/-/blob/main/README.md#function-hooks)
- [Trampoline](<https://en.wikipedia.org/wiki/Trampoline_(computing)>): TODO
- [Thunk](https://en.wikipedia.org/wiki/Thunk): A thin wrapper around a hooked function, allowing the execution of arbitrary logic before or after the hooked code
- [Xbyak](https://github.com/herumi/xbyak): A just-in-time assembler that allows applying assembly patches anywhere in the disassembled executable

## Events

Those familiar with Papyrus-based mod development know that the game fires various events for things that occur in game (OnHit, OnCellAttach, etc.). CommonLibSSE-NG exposes various events, allowing you to listen for and execute logic during events relevant to your plugin. Note that events are passed from one loaded SKSE plugin to the next in succession at runtime in alphabetical order of loaded SKSE plugins. Since your plugin is only one of multiple plugins that may be overriding a given event's `ProcessEvent` method, it's important to return `RE::BSEventNotifyControl::kContinue` in all control paths of your `ProcessEvent` override.
