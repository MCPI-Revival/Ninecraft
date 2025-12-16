cmake_minimum_required(VERSION 3.1)
project(ninecraft)

# Dependencies
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/stb")
option(USE_SYSTEM_DEPENDENCIES "Use System Dependencies For Common Libraries" FALSE)
if(USE_SYSTEM_DEPENDENCIES)
    # SDL
    find_package(SDL2 REQUIRED)
    # ZLib
    find_package(ZLIB REQUIRED)
    add_library(zlibstatic ALIAS ZLIB::ZLIB)
else()
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
    add_subdirectory(SDL)

    # ZLib
    add_subdirectory(zlib)
endif()

# OpenGL
add_subdirectory(glad/cmake)
glad_add_library(glad REPRODUCIBLE LOADER API gl:compatibility=2.0)

# Build
add_subdirectory(ancmp)
add_subdirectory(anjni)
add_subdirectory(ninecraft)
