cmake_minimum_required(VERSION 3.25)

# Review presets systems with more sub-presets (gcc, release, debug ...)

project(cpp_blockchain)

set(CMAKE_INSTALL_RPATH "$ORIGIN") # keep path of shared dependencies after install on Linux
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/") # use include("name") not include("name.cmake") on cmake directory

if (ENABLE_CLANG_TIDY)
	set(CMAKE_CXX_CLANG_TIDY clang-tidy)
endif()

include(cpp_version)
include(destdir)

cpp_version(23)
default_dir()

enable_testing()

add_subdirectory(code)