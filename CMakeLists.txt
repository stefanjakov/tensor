cmake_minimum_required(VERSION 3.18)

# --------------------------------------------
# Project
# --------------------------------------------
project(my_project LANGUAGES CXX CUDA)

# --------------------------------------------
# Standards
# --------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

# --------------------------------------------
# Output Directories
# --------------------------------------------
# Executables -> build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Static libraries -> build/lib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Shared libraries -> build/lib
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# --------------------------------------------
# CUDA Settings
# --------------------------------------------
# Adjust architecture to match your GPU
# (75 = Turing, 86 = Ampere, etc.)
set(CMAKE_CUDA_ARCHITECTURES 75)

# --------------------------------------------
# Library
# --------------------------------------------
add_library(my_lib
    src/hello.cu
)

target_include_directories(my_lib
    PUBLIC ${PROJECT_SOURCE_DIR}/src
)

# Required for proper CUDA device linking
set_target_properties(my_lib PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON
)

# --------------------------------------------
# Main Application
# --------------------------------------------
add_executable(my_app
    src/main.cpp
)

target_link_libraries(my_app
    PRIVATE my_lib
)

# --------------------------------------------
# Testing Option
# --------------------------------------------
option(BUILD_TESTING "Build unit tests" ON)

if(BUILD_TESTING)

    enable_testing()

    include(FetchContent)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(googletest)

    add_executable(hello_test
        tests/hello_test.cc
    )

    target_link_libraries(hello_test
        PRIVATE
        my_lib
        GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(hello_test)

endif()