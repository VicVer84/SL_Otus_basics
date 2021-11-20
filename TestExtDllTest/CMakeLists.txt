cmake_minimum_required(VERSION 3.10)

project(COURSEPROJECT)

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
include_directories(${CMAKE_SOURCE_DIR}/TestExtDll)

add_executable(TestExtDllTest 
    ${CMAKE_SOURCE_DIR}/TestExtDllTest/TestExtDllTest.cpp
	${CMAKE_SOURCE_DIR}/TestExtDllTest/LibFunc.cpp
	${CMAKE_SOURCE_DIR}/TestExtDllTest/LibFunc.h
	${CMAKE_SOURCE_DIR}/TestExtDll/Structs.h
	${CMAKE_SOURCE_DIR}/TestExtDll/Utils.cpp
	${CMAKE_SOURCE_DIR}/TestExtDll/Utils.h
)


target_link_libraries(TestExtDllTest gtest_main)

set_target_properties(TestExtDllTest PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)