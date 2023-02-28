include_guard()

# Set all directories
# ${CMAKE_BINARY_DIR} is set from command line or from json (buildRoot)
# this block depends of platforms initializations

macro (default_dir)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/runtime)
    set(TEST_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/runtime/testsdata)
    set(TMP_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tmp)
    if(DEFINED ENV{NUGET_SERVER_SOURCE})
        set(NUGET_SERVER_SOURCE $ENV{NUGET_SERVER_SOURCE})
    else()
        set(NUGET_SERVER_SOURCE ${CMAKE_BINARY_DIR}/../localnugets)
    endif()

    if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
        # use the path given by the caller (see CMakeSettings.json in VS) (= use default instead of overwrite)
        set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install CACHE PATH "The root of the installation tree" FORCE)
    endif()

    set (ARTIFACTS_DIRECTORY ${CMAKE_INSTALL_PREFIX}/artifacts)
endmacro()