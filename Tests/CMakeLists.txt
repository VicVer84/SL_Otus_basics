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

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(TestMyVector
    TestMyVector.cpp
	${CMAKE_SOURCE_DIR}/src/MyVector.h
)

add_executable(TestMySLList
    TestMySLList.cpp
	${CMAKE_SOURCE_DIR}/src/MySLList.h
)

add_executable(TestMyDLList
    TestMyDLList.cpp
	${CMAKE_SOURCE_DIR}/src/MyDLList.h
)

target_link_libraries(TestMyVector gtest_main)
target_link_libraries(TestMySLList gtest_main)
target_link_libraries(TestMyDLList gtest_main)


set_target_properties(TestMyVector PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
set_target_properties(TestMySLList PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
set_target_properties(TestMyDLList PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)