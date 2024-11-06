cmake_minimum_required(VERSION 3.16)
project(CaTaBoard VERSION 0.0)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
include_directories("${PROJECT_SOURCE_DIR}/include")

add_subdirectory(
        "${PROJECT_SOURCE_DIR}/src"
)




