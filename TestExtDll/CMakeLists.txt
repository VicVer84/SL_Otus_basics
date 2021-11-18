cmake_minimum_required(VERSION 3.10)

project(COURSEPROJECT)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_library(TestExtDll SHARED
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


set_target_properties(TestExtDll PROPERTIES COMPILE_FLAGS "/MT" LINK_FLAGS "/DLL" )

set_target_properties(TestExtDll PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
