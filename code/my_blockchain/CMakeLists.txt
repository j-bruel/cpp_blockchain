project(my_blockchain)

find_package(fmt REQUIRED)
find_package(cryptopp CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

set(MY_BLOCKCHAIN_CPP_SOURCES	"${CMAKE_CURRENT_SOURCE_DIR}/src/block.cpp"
								"${CMAKE_CURRENT_SOURCE_DIR}/src/blockchain.cpp")
set(MY_BLOCKCHAIN_INCLUDE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE "src/main.cpp" ${MY_BLOCKCHAIN_CPP_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${MY_BLOCKCHAIN_INCLUDE_DIRECTORY})
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt cryptopp::cryptopp spdlog::spdlog)

include(installdeps)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
if(WIN32)
	installdeps(${PROJECT_NAME} ${CMAKE_INSTALL_PREFIX}/bin ${CMAKE_INSTALL_PREFIX}/bin)
endif()

if (ENABLE_TESTING)
	add_subdirectory("tests")
endif ()