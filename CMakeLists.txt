cmake_minimum_required(VERSION 3.10)
project(json-shader-project LANGUAGES CXX)

include(build/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(json-shader src/main.cpp)
target_link_libraries(json-shader PRIVATE ${CONAN_LIBS})