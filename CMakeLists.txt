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
            "src/mync1/addon_main.cpp"
            "src/mync1/HelloWorld1.cpp"
            "src/mync1/HelloWorld2.cpp"
            "src/mync1/SpeedTest.cpp"
            "src/mync1/MyNativeObj.cpp"
            "src/mync1/MyCallback.cpp"
            "src/mync1/MyPromise1.cpp"
            "src/mync1/MyEventEmit.cpp"
            "src/mync1/cpp_util.cpp"
            "src/mync1/extutil.cpp"
            "src/mync1/addon_main_4cpp.cpp"
            "src/include/*.h")

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS=1)
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})


