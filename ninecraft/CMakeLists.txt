cmake_minimum_required (VERSION 3.1)

project(ninecraft-core)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(PNG REQUIRED)
find_package(OpenAL REQUIRED)
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCE_FILES src/*.c)

add_executable(ninecraft ${SOURCE_FILES})
target_compile_definitions(ninecraft PRIVATE _GNU_SOURCE GL_GLEXT_PROTOTYPES)
target_include_directories(ninecraft PUBLIC include/)
target_link_libraries(ninecraft ${CMAKE_DL_LIBS} glfw hybris ${OPENGL_LIBRARY} ${GLFW3_LIBRARY} ${OPENAL_LIBRARY} ${PNG_LIBRARIES})
include_directories(ninecraft PUBLIC include/)
if (${IS_ARM_BUILD})
set_target_properties(ninecraft PROPERTIES COMPILE_FLAGS "-mthumb" LINK_FLAGS "-mthumb")
else()
set_target_properties(ninecraft PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif()