cmake_minimum_required(VERSION 3.1)
project(mcpereborn)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "(arm)|(armhf)|(aarch64)|(arm64)")
    set(IS_ARM_BUILD TRUE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mthumb")
else()
    set(IS_ARM_BUILD FALSE)
endif()

add_subdirectory(libhybris)
add_subdirectory(glad)
add_subdirectory(ninecraft)