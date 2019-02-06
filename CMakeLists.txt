cmake_minimum_required(VERSION 3.10)
project(json-shader-project LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.13/conan.cmake"
                 "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(CONANFILE conanfile.py
                BASIC_SETUP 
                BUILD missing
                PROFILE_AUTO
                SETTINGS cppstd=17)

add_subdirectory(src)