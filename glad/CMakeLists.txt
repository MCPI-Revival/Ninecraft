cmake_minimum_required (VERSION 3.1)

project(glad)

set(GLAD_SOURCES src/glad.c)

add_library(glad ${GLAD_SOURCES})
target_include_directories(glad PUBLIC include/)
if (NOT ${IS_ARM_BUILD})
set_target_properties(glad PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif()