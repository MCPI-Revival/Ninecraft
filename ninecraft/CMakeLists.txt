cmake_minimum_required (VERSION 3.1)

project(ninecraft)

include(../cmake/FindGLFW3.cmake)

find_package(PNG REQUIRED)
find_package(OpenAL REQUIRED)

include_directories(../libhybris/include)
include_directories(../glad/include)

file(GLOB SOURCE_FILES src/*.cpp)

add_executable(ninecraft ${GLAD_SOURCES} ${SOURCE_FILES})
target_include_directories(ninecraft PUBLIC include/)
target_link_libraries(ninecraft ${CMAKE_DL_LIBS} hybris glad ${GLFW3_LIBRARY} ${OPENAL_LIBRARY} ${PNG_LIBRARIES})
include_directories(ninecraft PUBLIC include/)
if (NOT ${IS_ARM_BUILD})
set_target_properties(ninecraft PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif()