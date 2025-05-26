cmake_minimum_required (VERSION 3.1)

project(ninecraft-core)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.c)


add_executable(ninecraft ${SOURCE_FILES} ${STB_DIR}/stb_vorbis.c)

target_include_directories(ninecraft PUBLIC include/)
target_link_libraries(ninecraft ${CMAKE_DL_LIBS} glad SDL2::SDL2 SDL2main ancmp)
if(ZLIB_FOUND)
	target_link_libraries(ninecraft ZLIB::ZLIB)
else()
	target_link_libraries(ninecraft zlibstatic)
endif()
include_directories(ninecraft PUBLIC include/)
