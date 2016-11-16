cmake_minimum_required(VERSION 3.5)
project(Cryptography)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Cryptography ${SOURCE_FILES})

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(main)

add_subdirectory(main)
add_subdirectory(tests)

target_link_libraries(Cryptography main)

