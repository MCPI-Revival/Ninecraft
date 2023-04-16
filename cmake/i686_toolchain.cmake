set(CMAKE_SYSTEM_NAME Linux)

if (NOT ${CMAKE_HOST_SYSTEM_PROCESSOR} MATCHES "i386|i686")
    set(CMAKE_SYSTEM_PROCESSOR i386)
    set(CMAKE_C_COMPILER i686-linux-gnu-gcc)
    set(CMAKE_CXX_COMPILER i686-linux-gnu-g++)
endif()

set(CMAKE_FIND_ROOT_PATH /usr)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
