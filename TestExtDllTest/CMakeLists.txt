cmake_minimum_required(VERSION 3.10)

project(COURSEPROJECT)

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

set_target_properties(TestExtDllTest PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)