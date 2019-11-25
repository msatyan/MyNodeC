project (mync1)
cmake_minimum_required(VERSION 3.10)

# if (MSVC)
#     # warning level 4 and all warnings as errors
#     add_compile_options(/W4 /WX)
# else()
#     # lots of warnings and all warnings as errors
#     add_compile_options(-Wall -Wextra -pedantic -Werror)
# endif()

# When compiling in Debug mode, it defines DEBUG (available Cmake >= 3.0)
add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(mync1_include_dir "${PROJECT_SOURCE_DIR}/src/include")
set(mync1_source_dir "${PROJECT_SOURCE_DIR}/src/mync1")

# Include N-API wrappers
execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
        )
string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
include_directories(${CMAKE_JS_INC})

file(GLOB SOURCE_FILES
        "${mync1_include_dir}/addon_api.h"
        "${mync1_include_dir}/addon_api_4cpp.h"
        "${mync1_include_dir}/cpp_util.h"
        "${mync1_include_dir}/extutil.h"
        "${mync1_include_dir}/MyEventEmit.h"
        "${mync1_include_dir}/MyNativeObj.h"
        "${mync1_source_dir}/addon_main.cpp"
        "${mync1_source_dir}/addon_main_4cpp.cpp"
        "${mync1_source_dir}/cpp_util.cpp"
        "${mync1_source_dir}/extutil.cpp"
        "${mync1_source_dir}/HelloWorld1.cpp"
        "${mync1_source_dir}/MyPrintJSObject.cpp"
        "${mync1_source_dir}/MyCallback.cpp"
        "${mync1_source_dir}/MyEventEmit.cpp"
        "${mync1_source_dir}/MyNativeObj.cpp"
        "${mync1_source_dir}/MyPromise1.cpp"
        "${mync1_source_dir}/SpeedTest.cpp"
        "${mync1_source_dir}/ArrayBuff.cpp"
)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src/include
    PRIVATE
        ${NODE_ADDON_API_DIR}
        ${CMAKE_JS_INC}
)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS=1)
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})

# Define NAPI_VERSION
add_definitions(-DNAPI_VERSION=3)
