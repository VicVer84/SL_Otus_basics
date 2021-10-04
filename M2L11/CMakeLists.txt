cmake_minimum_required(VERSION 3.10)

project(Containers CXX)

add_executable(TestMyVector
    TestMyVector.cpp
	MyVector.h
)

target_include_directories(TestMyVector PRIVATE include)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(TestMyVector PRIVATE 
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(TestMyVector PRIVATE
        /EHsc
        /W4
        /WX
    )
endif()

target_compile_features(TestMyVector PUBLIC cxx_std_17)
