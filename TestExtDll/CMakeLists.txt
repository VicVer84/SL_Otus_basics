cmake_minimum_required(VERSION 3.10)

project(COURSEPROJECT)

add_library(TestExtDll shared
    ${CMAKE_SOURCE_DIR}/TestExtDll/TestExtDll.cpp
	${CMAKE_SOURCE_DIR}/TestExtDll/Cards.cpp
	${CMAKE_SOURCE_DIR}/TestExtDll/Logger.cpp
	${CMAKE_SOURCE_DIR}/TestExtDll/Utils.cpp
	${CMAKE_SOURCE_DIR}/TestExtDll/TestExtDll.h
	${CMAKE_SOURCE_DIR}/TestExtDll/Cards.h
	${CMAKE_SOURCE_DIR}/TestExtDll/Logger.h
	${CMAKE_SOURCE_DIR}/TestExtDll/Utils.h
	${CMAKE_SOURCE_DIR}/TestExtDll/Structs.h
)

set_target_properties(TestExtDll PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)