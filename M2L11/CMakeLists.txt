cmake_minimum_required(VERSION 3.10)

project(Containers CXX)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

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

target_link_libraries(gtest_main)

set_target_properties(TestMyVector PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)