cmake_minimum_required (VERSION 3.1)

project(ninecraft-core)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.c)

add_executable(ninecraft ${SOURCE_FILES})
target_compile_definitions(ninecraft PRIVATE _GNU_SOURCE AL_LIBTYPE_STATIC)
target_include_directories(ninecraft PUBLIC include/)
target_link_libraries(ninecraft ${CMAKE_DL_LIBS} zlibstatic glad glfw ancmp OpenAL::OpenAL)
include_directories(ninecraft PUBLIC include/)
