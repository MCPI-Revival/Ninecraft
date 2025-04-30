cmake_minimum_required(VERSION 3.1)
project(ninecraft)

find_package(PkgConfig)

# STB
if(EXISTS $ENV{stb}/stb_vorbis.c)
	set(STB_DIR $ENV{stb})
elseif(EXISTS ${PROJECT_SOURCE_DIR}/stb)
	set(STB_DIR ${PROJECT_SOURCE_DIR}/stb)
endif()
include_directories(${STB_DIR})

# GLAD
if(EXISTS $ENV{glad}/cmake/CMakeLists.txt)
	add_subdirectory($ENV{glad}/cmake $ENV{glad})
elseif(EXISTS glad/cmake/CMakeLists.txt)
	add_subdirectory(glad/cmake)
endif()
if(glad)
	glad_add_library(glad REPRODUCIBLE LOADER API egl=1.5 gl:compatibility=2.0)
endif()

# ZLIB
find_package(ZLIB REQUIRED)
if(ZLIB::ZLIB)
	set(zlibstatic ZLIB::ZLIB)
elseif(EXISTS "zlib/CMakeLists.txt")
	add_subdirectory(zlib)
	set(zlibstatic zlibstatic)
endif()

# ancmp
if(EXISTS $ENV{ancmp}/CMakeLists.txt)
	add_subdirectory($ENV{ancmp} $ENV{ancmp})
elseif(EXISTS acmp/CMakeLists.txt)
	add_subdirectory(ancmp)
endif()


find_library(glfw3 REQUIRED)
if(NOT glfw and EXISTS "glfw/CMakeLists.txt")
	# fallback to included submodule
	add_subdirectory(glfw)
endif()

if(WIN32)
    set(LIBTYPE "STATIC" CACHE BOOL "" FORCE)
    add_subdirectory(openal-soft)
endif()
add_subdirectory(ninecraft)
