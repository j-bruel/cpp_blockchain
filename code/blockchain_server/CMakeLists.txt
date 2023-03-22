project(blockchain_server)

find_package(fmt REQUIRED)
find_package(httplib CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(cpplog CONFIG REQUIRED)

set(BLOCKCHAIN_SERVER_CPP_SOURCES	"${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp" "src/server/listener.cpp")
set(BLOCKCHAIN_SERVER_INCLUDE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_executable(${PROJECT_NAME})

cpp_flags(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE ${BLOCKCHAIN_SERVER_CPP_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${BLOCKCHAIN_SERVER_INCLUDE_DIRECTORY} ${MY_BLOCKCHAIN_PUBLIC_DIRECTORY} ${TMP_OUTPUT_DIRECTORY})
target_link_libraries(${PROJECT_NAME} PRIVATE my_blockchain fmt::fmt httplib::httplib nlohmann_json::nlohmann_json centor::cpplog)

include(installdeps)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
if(WIN32)
	installdeps(${PROJECT_NAME} ${CMAKE_INSTALL_PREFIX}/bin ${CMAKE_INSTALL_PREFIX}/bin)
endif()