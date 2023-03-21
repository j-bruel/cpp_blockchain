# cpp_blockchain

A custom blockchain made in C++.

Inside this repository, you will found:
- A C++ library wrapping a basic blockchain.
- A C++ http server with one endpoint to dump the current state of the blockchain GET:/blockchain

**NOTE:** Addresse and port are hardly set for now, you can reach the endpoint at this URL: http://localhost:4242/blockchain

## Current state

Compiles with:
* Windows Visual 2022/C++23 & Clang-cl (MVC-Clang) 16
* Linux/gcc12
* MacOS/Clang 15

## Prerequisites

### General Prerequisites: 
- Powershell v6 + must be installed. Current versions 7.1.x are recommended and work for both platforms.
- Git must be installed.

### Prerequisites for Windows build target (Debug or Release configuration)
- Visual Studio 2022 with C++ Desktop development module installed
- Clone [VCPKG repo](https://github.com/microsoft/vcpkg.git) in your main development directory (<project_dir>/..) on windows and your HOME directory on linux. You put it somewhere else, just consider to update the CMakePresets variable correctly.

For clang-cl target, you must install "C++ Clang for Windows" and "LLVM tools".

### Prerequisites for Linux build target (Linux-GCC-Debug or Linux-GCC-Release configuration)
- Visual Studio 2022 with C++ Desktop development module and [Linux development tools for Visual Studio](https://docs.microsoft.com/en-us/cpp/linux/download-install-and-setup-the-linux-development-workload) installed
- [Docker](https://docs.docker.com/desktop/windows/) installed
- Make sure that you [use Linux containers](https://docs.docker.com/desktop/windows/#switch-between-windows-and-linux-containers)

Go to [docker](https://github.com/j-bruel/cpp_blockchain/blob/master/docker) folder and run `docker compose --profile devenv up -d` then [set up the remote connection from Visual Studio](https://devblogs.microsoft.com/cppblog/build-c-applications-in-a-linux-docker-container-with-visual-studio/#connect-to-your-docker-container-from-visual-studio) using this configuration:
- Host name: **localhost**
- Port: **5000**
- User name: **centor**
- Authentication type: **Password**
- Password: **centor**

### Prerequisites for MacOS build target
- Install XCode
- Install brew: **/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"**
- Install pkg-config: brew install pkg-config
- Install LLVM: brew install llvm

## How to build

### General Prerequisites: 
Setup your cmakepresets:
- Copy the CMakeUserPresets.json.template into a CMakeUserPresets.json file.
- Edit all necessary variables available inside any 'cacheVariables' sections.

### Build with Visual Studio
Make sure that the part of the project you want to build are selectionned in the CMakeUserPresets.json.

On Visual Studio the configure phase should start automatically when the project is opened, if you need to run it manually go to **Project > Configure cpp_blockchain**.
Once the configure phase is finished, go to **Build > Install cpp_blockchain**

### Build with terminal

On Windows open a 'x64 native tools command prompt for vs 2022' terminal.
On linux open your favorite terminal with appropriated environment variables already set.

```
cmake --preset <preset_name>
cmake --build out/<preset_name>
```

## Debug

### Debug with Visual Studio
 Choose "blockchain_server.exe (Install)" (on Windows)/"blockchain_server (install)" (on Linux) target in **Select Startup Item** menu and launch it.

### Debug with a terminal

- Go inside the build directory <project_directory/out/<preset_name>/bin
- run ./cpp_blockchain(.exe)

## Test
The **ENABLE_TESTING** variable must be set in the CMakeUserPresets to have the tests included in the project build and be able to see them in Visual Studio interface.

To run the tests, you can change the start-up item to "tests_my_blockchain.exe" (on Windows)/"tests_my_blockchain (runtime\tests_my_blockchain)" (on Linux) and then run it through that.

## Build images

- To build development environment image (for developing purpose only) : **docker compose --profile devenv up -d**
- To run dockerized tests (useful for CI pipeline) : **docker compose --profile test up --exit-code-from test**
- To build production image : **docker compose --profile production build**
- To run dockerized server : **docker compose --profile production up**
- Remove all builded images forever : **docker system prune --all --volumes**

## Known issues

### CLion not up to date
To use CLion on MacOS or Linux, the preset version need to be downgraded to v3.

### Clang 16 on MacOS
Clang 16 is not available using brew for now.
Because clang 15 is not integrating all c++20 feature, std::jthread were replaced by std::thread and additional build flag has been added to enable c++20 feature like ranges.