cmake_minimum_required (VERSION 3.1)

project(ninecraft-core)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.c)

add_executable(ninecraft ${SOURCE_FILES} ../stb/stb_vorbis.c)
target_include_directories(ninecraft PUBLIC include/)
target_link_libraries(ninecraft ${CMAKE_DL_LIBS} zlibstatic SDL2::SDL2 SDL2main glad ancmp)
include_directories(ninecraft PUBLIC include/)

# Build server
add_executable(ninecraft-headless ${SOURCE_FILES} ../stb/stb_vorbis.c)
target_compile_definitions(ninecraft-headless PRIVATE NINECRAFT_HEADLESS)
target_include_directories(ninecraft-headless PUBLIC include/)
target_link_libraries(ninecraft-headless ${CMAKE_DL_LIBS} zlibstatic SDL2::SDL2 SDL2main glad ancmp)
include_directories(ninecraft-headless PUBLIC include/)
