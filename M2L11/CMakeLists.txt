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

#target_include_directories(TestMyVector PRIVATE include)

add_executable(TestMyVector
    TestMyVector.cpp
	MyVector.h
)

add_executable(Test
    Test.cpp
	MyVector.h
)

add_executable(TestMySLList
    TestMySLList.cpp
	MySLList.h
)

add_executable(TestMyDLList
    TestMyDLList.cpp
	MyDLList.h
)

target_link_libraries(TestMyVector gtest_main)
target_link_libraries(TestMySLList gtest_main)
target_link_libraries(TestMyDLList gtest_main)


set_target_properties(TestMyVector PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
set_target_properties(Test PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
set_target_properties(TestMySLList PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
set_target_properties(TestMyDLList PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)