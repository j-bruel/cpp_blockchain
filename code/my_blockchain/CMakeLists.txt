project(my_blockchain)

set(CPP_SOURCES "src/main.cpp")

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE ${CPP_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "src")

include(installdeps)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
if(WIN32)
	installdeps(${PROJECT_NAME} ${CMAKE_INSTALL_PREFIX}/bin ${CMAKE_INSTALL_PREFIX}/bin)
endif()