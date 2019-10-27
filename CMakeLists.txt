project (mync1)
cmake_minimum_required(VERSION 3.10)

# Include N-API wrappers
execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
        )
string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
include_directories(${CMAKE_JS_INC})

file(GLOB SOURCE_FILES
            "src/addon_main.cpp"
            "src/HelloWorld1.cpp"
            "src/HelloWorld2.cpp"
            "src/SpeedTest.cpp"
            "src/MyNativeObj.cpp"
            "src/MyCallback.cpp"
            "src/MyPromise1.cpp"
            "src/MyEventEmit.cpp"
            "src/cpp_util.cpp"
            "src/extutil.cpp"
            "src/addon_main_4cpp.cpp"
            "src/*.h")

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS=1)
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})


