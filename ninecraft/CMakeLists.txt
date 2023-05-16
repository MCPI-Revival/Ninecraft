cmake_minimum_required (VERSION 3.1)

project(ninecraft-core)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenAL REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.c)

add_executable(ninecraft ${SOURCE_FILES})
target_compile_definitions(ninecraft PRIVATE _GNU_SOURCE GL_GLEXT_PROTOTYPES)
target_include_directories(ninecraft PUBLIC include/)
target_link_libraries(ninecraft ${CMAKE_DL_LIBS} m miniz glfw hybris ${OPENGL_LIBRARY} ${OPENAL_LIBRARY})
include_directories(ninecraft PUBLIC include/)
