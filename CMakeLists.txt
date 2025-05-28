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

# SDL
SET(SDL_STATIC ON CACHE BOOL "Enable SDL_STATIC" FORCE)
SET(SDL_SHARED OFF CACHE BOOL "Disable SDL_SHARED" FORCE)
SET(SDL_MMX OFF CACHE BOOL "Disable SDL_MMX" FORCE)
SET(SDL_SSE OFF CACHE BOOL "Disable SDL_SSE" FORCE)
SET(SDL_SSE2 OFF CACHE BOOL "Disable SDL_SSE2" FORCE)
SET(SDL_SSE3 OFF CACHE BOOL "Disable SDL_SSE3" FORCE)
SET(SDL_SSEMATH OFF CACHE BOOL "Disable SDL_SSEMATH" FORCE)
SET(SDL_3DNOW OFF CACHE BOOL "Disable SDL_3DNOW" FORCE)
SET(SDL_TEST OFF CACHE BOOL "Disable SDL_TEST" FORCE)
SET(SDL_TESTS OFF CACHE BOOL "Disable SDL_TESTS" FORCE)

# add_subdirectory(SDL)
find_package(SDL2)
if(NOT SDL2_FOUND)
MESSAGE(STATUS "Including SDL2 from submodule")
add_subdirectory(SDL)
endif()




add_subdirectory(ninecraft)
