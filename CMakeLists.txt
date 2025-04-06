cmake_minimum_required(VERSION 3.1)
project(ninecraft)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "(arm)|(armhf)|(aarch64)|(arm64)")
    set(IS_ARM_BUILD TRUE)
    set(IS_ARMHF_BUILD TRUE)
else()
    set(IS_ARM_BUILD FALSE)
endif()

include_directories(${PROJECT_SOURCE_DIR}/minivorbis)
include_directories(${PROJECT_SOURCE_DIR}/stb)

set(LIBTYPE "STATIC" CACHE BOOL "" FORCE)

add_subdirectory(glad/cmake)
glad_add_library(glad REPRODUCIBLE LOADER API egl=1.5 gl:compatibility=2.0)
add_subdirectory(zlib)
add_subdirectory(ancmp)
add_subdirectory(glfw)
add_subdirectory(openal-soft)
add_subdirectory(ninecraft)

include_directories(${PROJECT_SOURCE_DIR}/libhybris/include)