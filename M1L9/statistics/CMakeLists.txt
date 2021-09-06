cmake_minimum_required(VERSION 3.5)

project(05.homework)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(statistics 
				statistics.cpp
				Max.cpp
				Mean.cpp
				Min.cpp
				Std.cpp
				IStatistics.h
				Max.h
				Mean.h
				Min.h
				Std.h
				)
set_target_properties(statistics PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

