project (mync1)
cmake_minimum_required(VERSION 3.10)
include_directories(${CMAKE_JS_INC})
file(GLOB SOURCE_FILES
            "src/addon_main.cpp"
            "src/HelloWorld1.cpp"
            "src/SpeedTest.cpp"
            "src/MyNativeObj.cpp"
            "src/MyCallback.cpp"
            "src/MyPromise1.cpp"
            "src/MyEventEmit.cpp"
            "src/cpp_util.cpp"
            "src/extutil.cpp"
            "src/*.h")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})
