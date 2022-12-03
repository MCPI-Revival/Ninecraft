cmake_minimum_required(VERSION 3.1)
project(alinker)

if (${IS_ARM_BUILD})
SET(CMAKE_CXX_COMPILER "/usr/lib/android-ndk/toolchains/llvm/prebuilt/linux-x86_64/bin/armv7a-linux-androideabi16-clang++")
SET(CMAKE_C_COMPILER "/usr/lib/android-ndk/toolchains/llvm/prebuilt/linux-x86_64/bin/armv7a-linux-androideabi16-clang")
else()
SET(CMAKE_CXX_COMPILER "/usr/lib/android-ndk/toolchains/llvm/prebuilt/linux-x86_64/bin/i686-linux-android16-clang++")
SET(CMAKE_C_COMPILER "/usr/lib/android-ndk/toolchains/llvm/prebuilt/linux-x86_64/bin/i686-linux-android16-clang")
endif()

file(GLOB SOURCES src/*.c)

add_library(empty SHARED ${SOURCES})
if (${IS_ARM_BUILD})
set_target_properties(empty PROPERTIES COMPILE_FLAGS "-nostdlib -mthumb" LINK_FLAGS "-nostdlib -mthumb")
else()
set_target_properties(empty PROPERTIES COMPILE_FLAGS "-nostdlib" LINK_FLAGS "-nostdlib")
endif()