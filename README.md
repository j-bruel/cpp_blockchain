# cpp_blockchain

A custom blockchain made in C++.

Inside this repository, you will found:
- A C++ library wrapping a basic blockchain.
- A C++ http server with one endpoint to dump the current state of the blockchain GET:/blockchain

**NOTE:** Addresse and port are hardly set for now, you can reach the endpoint at this URL: http://localhost:4242/blockchain

## Current state

* Compiles with Windows Visual 2022/C++23

## Prerequisites

### General Prerequisites: 
- Powershell v6 + must be installed. Current versions 7.1.x are recommanded and work for both platforms.
- Git must be installed.

### Prerequisites for Windows build target (Debug or Release configuration)
- Visual Studio 2022 with C++ Desktop development module installed
- Clone [VCPKG repo](https://github.com/microsoft/vcpkg.git) in your main development directory. You put it somewhere else, just consider to update the CMakePresets variable correctly.

### Prerequisites for Linux build target (Linux-GCC-Debug or Linux-GCC-Release configuration)

... Later on ...

### Prerequisites for MacOS build target

... Later on ...

## How to build

### General Prerequisites: 
Setup your cmakepresets:
- Copy the CMakeUserPresets.json.template into a CMakeUserPresets.json file.
- Edit all necessary variables available inside any 'cacheVariables' sections.

### Build with Visual Studio
Make sure that the part of the project you want to build are selectionned in the CMakeUserPresets.json.

On Visual Studio the configure phase should start automatically when the project is opened, if you need to run it manually go to **Project > Configure cpp_blockchain**.
Once the configure phase is finished, go to **Build > Install cpp_blockchain**

### Build with script

... Later on ...

## Debug

### Debug with Visual Studio
 Choose "blockchain_server.exe (Install)" (on Windows)/"blockchain_server (install)" (on Linux) target in **Select Startup Item** menu and launch it.

### Debug with a terminal

... Later on ...

## Test
The **ENABLE_TESTING** variable must be set in the CMakeUserPresets to have the tests included in the project build and be able to see them in Visual Studio interface.

To run the tests, you can change the start-up item to "tests_my_blockchain.exe" (on Windows)/"tests_my_blockchain (runtime\tests_my_blockchain)" (on Linux) and then run it through that.

## Known issues

No issues to declare for now.