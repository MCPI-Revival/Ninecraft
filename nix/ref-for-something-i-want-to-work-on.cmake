set(HAVE_MY_SDK OFF)
if(IS_DIRECTORY "${PROJECT_SOURCE_DIR}/../Libs/A")
    if(EXISTS "${PROJECT_SOURCE_DIR}/../Libs/A/CMakeLists.txt")
        set (HAVE_MY_SDK ON)
    endif()
endif()


if(condition)
    # commands to execute if condition is true
elseif(another_condition)
    # commands to execute if another_condition is true
else()
    # commands to execute if no condition is true
endif()

find_library(LUA_LIB lua)
if(NOT LUA_LIB)
  message(FATAL_ERROR "lua library not found")
endif()



#----------------------------
