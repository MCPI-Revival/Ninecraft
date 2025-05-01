cmake_minimum_required (VERSION 3.1)

project(ninecraft-core)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.c)


add_executable(ninecraft ${SOURCE_FILES} ${STB_DIR}/stb_vorbis.c)

if(WIN32)
    target_compile_definitions(ninecraft PRIVATE AL_LIBTYPE_STATIC)
    target_link_libraries(ninecraft OpenAL::OpenAL)
else()
    find_package(OpenAL REQUIRED)
    target_compile_definitions(ninecraft PRIVATE _GNU_SOURCE)
    target_link_libraries(ninecraft ${OPENAL_LIBRARY})
endif()
target_include_directories(ninecraft PUBLIC include/)
target_link_libraries(ninecraft ${CMAKE_DL_LIBS} glad glfw ancmp)
if(ZLIB_FOUND)
	target_link_libraries(ninecraft ZLIB::ZLIB)
else()
	target_link_libraries(ninecraft zlibstatic)
endif()
include_directories(ninecraft PUBLIC include/)
