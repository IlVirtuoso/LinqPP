project(LinqPP)

cmake_minimum_required(VERSION 3.14)
include(CheckCXXCompilerFlag)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/)

get_filename_component(_CWD ./ ABSOLUTE)
set(CMAKE_SUPPORT_DIR ${_CWD}/cmake)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
include(./cmake/FlagManager.cmake)
include(./cmake/TestProjectGenerator.cmake)
include(GoogleTest)
enable_testing()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
      force_flag("--coverage")
endif()

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS test/*.cpp src/*.cpp)
file(GLOB_RECURSE SRC_LIST CONFIGURE_DEPENDS src/*.cpp)

list(REMOVE_ITEM TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

generate_gtest(COVERAGE TEST_DIR "test" INCLUDE_DIR "include" SRC_DIR "src" MAIN_SRC_NAME "main.cpp")