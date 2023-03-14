message("Tests for ${PROJECT_NAME}")
set(PARENT_PROJECT ${PROJECT_NAME}) # create name of project dependent on parent project name

project(tests_${PROJECT_NAME}) # all tests should be prefix by "tests_" to find them in directory and targets

find_package(GTest CONFIG REQUIRED)

include(GoogleTest)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE	"src/block_tests.cpp"
										"src/blockchain_tests.cpp")
target_include_directories(${PROJECT_NAME} PRIVATE "src" ${MY_BLOCKCHAIN_PUBLIC_DIRECTORY} ${TMP_OUTPUT_DIRECTORY})
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest GTest::gtest_main ${PARENT_PROJECT})
if(UNIX) # needed by google test
	target_link_libraries(${PROJECT_NAME} PRIVATE "-lpthread")
endif(UNIX)

if(MSVC) # need to add /FC for macro __FILE__ to resolve to fullpath for google test (useful to have usable call stack on Visual Studio Test Explorer)
	target_compile_options(${PROJECT_NAME} PRIVATE "/FC")
endif(MSVC)

gtest_discover_tests(${PROJECT_NAME} WORKING_DIRECTORY ${CMAKE_BINARY_DIR} DISCOVERY_MODE PRE_TEST)