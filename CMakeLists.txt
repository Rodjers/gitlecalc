cmake_minimum_required(VERSION 3.10)
project(calc VERSION 0.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(libcalc)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/libcalc")
add_executable(calc main.cxx)
target_link_libraries(calc PUBLIC libcalc)
target_include_directories(calc PUBLIC
        ${EXTRA_INCLUDES}
)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        main_test
        main_test.cxx
)
target_link_libraries(
        main_test
        GTest::gtest_main
        libcalc
)

include(GoogleTest)
gtest_discover_tests(main_test)
