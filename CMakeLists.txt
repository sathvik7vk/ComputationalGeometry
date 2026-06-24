cmake_minimum_required(VERSION 3.16)
project(ComputationalGeometry LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

# Header-only library
add_library(cg INTERFACE)
target_include_directories(cg INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#add_executable
add_executable(cg_example examples/main.cpp)
#Link executable to library
target_link_libraries(cg_example cg)
