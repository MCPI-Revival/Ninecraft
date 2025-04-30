cmake_minimum_required(VERSION 3.1)
project(ninecraft)

find_package(PkgConfig)

include_directories(${PROJECT_SOURCE_DIR}/stb)

add_subdirectory(glad/cmake)
glad_add_library(glad REPRODUCIBLE LOADER API egl=1.5 gl:compatibility=2.0)


# ZLIB
find_package(ZLIB)
if(NOT ZLIB_FOUND)
MESSAGE(STATUS "Including ZLIB from submodule")
add_subdirectory(zlib)
endif()

add_subdirectory(ancmp)

# GLFW
find_package(glfw3)
if(NOT glfw3_FOUND)
MESSAGE(STATUS "Including GLFW from submodule")
add_subdirectory(glfw)
endif()

if(WIN32)
    set(LIBTYPE "STATIC" CACHE BOOL "" FORCE)
    add_subdirectory(openal-soft)
endif()
add_subdirectory(ninecraft)