project(my_blockchain)

find_package(fmt REQUIRED)
find_package(cryptopp CONFIG REQUIRED)

set(CPP_SOURCES "src/main.cpp"
				"src/block.cpp"
				"src/blockchain.cpp")

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE ${CPP_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "src")
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt cryptopp::cryptopp)

include(installdeps)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
if(WIN32)
	installdeps(${PROJECT_NAME} ${CMAKE_INSTALL_PREFIX}/bin ${CMAKE_INSTALL_PREFIX}/bin)
endif()