cmake_minimum_required(VERSION 3.16)
project(ComputationalGeometry LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Header-only library
add_library(cg INTERFACE)

target_include_directories(cg INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


add_executable(cg_example examples/main.cpp)
target_link_libraries(cg_example cg)
