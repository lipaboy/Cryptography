include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runFiniteFieldTests
        polynomial_tests.cpp main.cpp)

target_link_libraries(runFiniteFieldTests gtest gtest_main)
target_link_libraries(runFiniteFieldTests main)

