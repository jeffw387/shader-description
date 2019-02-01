cmake_minimum_required(VERSION 3.10)
project(json-shader-project LANGUAGES CXX)

include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(src)