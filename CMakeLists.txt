cmake_minimum_required(VERSION 3.1)
project(ninecraft)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "(arm)|(armhf)|(aarch64)|(arm64)")
    set(IS_ARM_BUILD TRUE)
    set(IS_ARMHF_BUILD TRUE)
else()
    set(IS_ARM_BUILD FALSE)
endif()

set(GLFW_BUILD_X11 TRUE)

include_directories(${GLFW_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/minivorbis)
include_directories(${PROJECT_SOURCE_DIR}/stb)

add_subdirectory(libhybris)
add_subdirectory(glfw)
add_subdirectory(ninecraft)
if(APPLE)
add_subdirectory(osx-elf-header)
add_subdirectory(epoll-shim)
endif()

include_directories(${PROJECT_SOURCE_DIR}/libhybris/include)