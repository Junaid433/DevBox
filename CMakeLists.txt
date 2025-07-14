cmake_minimum_required(VERSION 3.16)
project(devbox LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(SRC
    src/main.cpp
    src/commands/new_env.cpp
    src/commands/enter_env.cpp
    src/commands/clean_env.cpp
    src/commands/list_env.cpp
    src/utils/filesystem.cpp
    src/utils/template_manager.cpp
    src/utils/sandbox.cpp
    src/utils/config.cpp
)

add_executable(devbox ${SRC})

set(TEST_SRC
    tests/test_main.cpp
)

add_executable(devbox_tests ${TEST_SRC})

target_link_libraries(devbox_tests PRIVATE GTest::GTest GTest::Main)

target_include_directories(devbox PRIVATE src)
target_include_directories(devbox_tests PRIVATE src)

add_test(NAME devbox_tests COMMAND devbox_tests)
