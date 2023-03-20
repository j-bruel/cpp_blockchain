# cpp_blockchain

A custom blockchain made in C++.

Inside this repository, you will found:
- A C++ library wrapping a basic blockchain.
- A C++ http server with one endpoint to dump the current state of the blockchain GET:/blockchain

**NOTE:** Addresse and port are hardly set for now, you can reach the endpoint at this URL: http://localhost:4242/blockchain

## Current state

* Compiles with Windows Visual 2022/C++23 and Linux/gcc12

## Prerequisites

### General Prerequisites: 
- Powershell v6 + must be installed. Current versions 7.1.x are recommanded and work for both platforms.
- Git must be installed.

### Prerequisites for Windows build target (Debug or Release configuration)
- Visual Studio 2022 with C++ Desktop development module installed
- Clone [VCPKG repo](https://github.com/microsoft/vcpkg.git) in your main development directory (<project_dir>/..) on windows and your HOME directory on linux. You put it somewhere else, just consider to update the CMakePresets variable correctly.

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

## Known issues

No issues to declare for now.