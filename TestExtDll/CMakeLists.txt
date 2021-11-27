cmake_minimum_required(VERSION 3.10)

project(COURSEPROJECT)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(TestExtDll SHARED
    ${CMAKE_SOURCE_DIR}/TestExtDll/TestExtDll.cpp	
	${CMAKE_SOURCE_DIR}/src/Cards.cpp
	${CMAKE_SOURCE_DIR}/src/Logger.cpp
	${CMAKE_SOURCE_DIR}/src/Utils.cpp
	${CMAKE_SOURCE_DIR}/TestExtDll/TestExtDll.h
	${CMAKE_SOURCE_DIR}/TestExtDll/RemoveMangling.def
	${CMAKE_SOURCE_DIR}/src/Cards.h
	${CMAKE_SOURCE_DIR}/src/Logger.h
	${CMAKE_SOURCE_DIR}/src/Utils.h
	${CMAKE_SOURCE_DIR}/src/Structs.h
)


set_target_properties(TestExtDll PROPERTIES COMPILE_FLAGS "/MT" LINK_FLAGS "/DLL" )
set_target_properties(TestExtDll PROPERTIES LINK_FLAGS "/DEF:RemoveMangling.def")

set_target_properties(TestExtDll PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
