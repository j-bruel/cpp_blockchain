project(my_blockchain)

find_package(fmt REQUIRED)
find_package(cryptopp CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

set(MY_BLOCKCHAIN_CPP_SOURCES	"src/centor/block.cpp"
								"src/centor/blockchain.cpp")
set(MY_BLOCKCHAIN_INCLUDE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(MY_BLOCKCHAIN_PUBLIC_DIRECTORY "${PROJECT_SOURCE_DIR}/public")

add_library(${PROJECT_NAME} SHARED)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "") # Disable CMake auto add "lib" prefix on Linux
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE 1) # shared libraries need PIC force it to static too we don't care of the very small overhead on full static version
cpp_flags(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE ${MY_BLOCKCHAIN_CPP_SOURCES})
target_include_directories(${PROJECT_NAME}	PRIVATE
												${MY_BLOCKCHAIN_INCLUDE_DIRECTORY}
												${TMP_OUTPUT_DIRECTORY}
											PUBLIC
												$<BUILD_INTERFACE:${MY_BLOCKCHAIN_PUBLIC_DIRECTORY}>
											INTERFACE
												$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_compile_definitions(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_EXPORTS)
target_link_libraries(${PROJECT_NAME}	PRIVATE fmt::fmt cryptopp::cryptopp spdlog::spdlog
										PUBLIC nlohmann_json::nlohmann_json tools)

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME ${TMP_OUTPUT_DIRECTORY}/${PROJECT_NAME}_export.hpp)

include(installdeps)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES ${TMP_OUTPUT_DIRECTORY}/${PROJECT_NAME}_export.hpp TYPE INCLUDE)
if(WIN32)
	installdeps(${PROJECT_NAME} ${CMAKE_INSTALL_PREFIX}/bin ${CMAKE_INSTALL_PREFIX}/bin)
endif()

if (ENABLE_TESTING)
	add_subdirectory("tests")
endif ()