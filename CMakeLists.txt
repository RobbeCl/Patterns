cmake_minimum_required(VERSION 3.5)
project(patterns)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
add_subdirectory(lib/googletest)

include_directories(include)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)


set(SOURCE_FILES
        main.cpp
        include/Builder.h)

set(SOURCE_FILES_TESTING
        Test/ObserverTest.cpp
        Test/BuilderTest.cpp
)

add_executable(patterns ${SOURCE_FILES})
add_executable(patterns_testing ${SOURCE_FILES_TESTING})

target_link_libraries(patterns_testing gtest gtest_main)