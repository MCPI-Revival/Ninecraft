cmake_minimum_required(VERSION 3.1)
project(ninecraft)

find_package(PkgConfig)

#STB
if(EXISTS "$ENV{stb}")
MESSAGE(STATUS "Including STB from external")
set(STB_DIR "$ENV{stb}")
elseif(EXISTS "${PROJECT_SOURCE_DIR}/stb/CMakeLists.txt")
MESSAGE(STATUS "Including STB from submodule")
set(STB_DIR "${PROJECT_SOURCE_DIR}/stb")
else()
MESSAGE(FATAL_ERROR "Please set $stb or include submodules")
endif()
include_directories(${STB_DIR})

#GLAD
if(EXISTS "$ENV{glad}")
MESSAGE(STATUS "Including GLAD from external")
add_subdirectory($ENV{glad}/cmake $ENV{glad})
else()
MESSAGE(STATUS "Including GLAD from submodule")
add_subdirectory(glad/cmake)
endif()
glad_add_library(glad REPRODUCIBLE LOADER API egl=1.5 gl:compatibility=2.0)


# ZLIB
find_package(ZLIB)
if(NOT ZLIB_FOUND)
MESSAGE(STATUS "Including ZLIB from submodule")
add_subdirectory(zlib)
endif()

#ANCMP
if(EXISTS "$ENV{ancmp}")
MESSAGE(STATUS "Including ANCMP from external")
add_subdirectory($ENV{ancmp} $ENV{ancmp})
else()
MESSAGE(STATUS "Including ANCMP from submodule")
add_subdirectory(ancmp)
endif()

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