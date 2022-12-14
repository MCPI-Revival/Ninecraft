cmake_minimum_required(VERSION 3.1)
project(ninecraft)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

if(CMAKE_SYSTEM_PROCESSOR MATCHES "(arm)|(armhf)|(aarch64)|(arm64)")
    set(IS_ARM_BUILD TRUE)
    set(IS_ARMHF_BUILD TRUE)
else()
    set(IS_ARM_BUILD FALSE)
endif()

set(GLFW_BUILD_X11 TRUE)

add_subdirectory(libhybris)
add_subdirectory(glfw)
add_subdirectory(ninecraft)
if(APPLE)
add_subdirectory(osx-elf-header)
add_subdirectory(epoll-shim)
endif()

include_directories(${PROJECT_SOURCE_DIR}/libhybris/include)
include_directories(${GLFW_SOURCE_DIR}/include)

if (${IS_ARM_BUILD})
set_target_properties(glfw PROPERTIES COMPILE_FLAGS "-mthumb" LINK_FLAGS "-mthumb")
set_target_properties(hybris PROPERTIES COMPILE_FLAGS "-mthumb" LINK_FLAGS "-mthumb")
else()
set_target_properties(glfw PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
set_target_properties(hybris PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif()