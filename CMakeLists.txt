cmake_minimum_required(VERSION 2.8)

project(libtvdb)

# add directory of additional cmake modules
set(CMAKE_MODULE_PATH ${libtvdb_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

# force the build directory to be different from source directory
include(MacroOutOfSourceBuild)
macro_ensure_out_of_source_build("${PROJECT_NAME} requires an out of source build.")

# add source code sub directories
add_subdirectory(src)
