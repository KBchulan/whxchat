cmake_minimum_required(VERSION 3.25)

project(GateServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(jsoncpp REQUIRED)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(GateServer ${SRC_LIST})

target_link_libraries(GateServer jsoncpp_lib)