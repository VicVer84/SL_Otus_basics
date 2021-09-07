cmake_minimum_required(VERSION 3.5)

project(05.homework)

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
include_directories(${CMAKE_SOURCE_DIR}/statistics)

add_executable(statistics.test 
				statistics.test.cpp
				${CMAKE_SOURCE_DIR}/statistics/Max.cpp
				${CMAKE_SOURCE_DIR}/statistics/Mean.cpp
				${CMAKE_SOURCE_DIR}/statistics/Min.cpp
				${CMAKE_SOURCE_DIR}/statistics/Pct90.cpp
				${CMAKE_SOURCE_DIR}/statistics/Pct95.cpp
				${CMAKE_SOURCE_DIR}/statistics/Std.cpp				
				${CMAKE_SOURCE_DIR}/statistics/IStatistics.h
				${CMAKE_SOURCE_DIR}/statistics/Max.h
				${CMAKE_SOURCE_DIR}/statistics/Mean.h
				${CMAKE_SOURCE_DIR}/statistics/Min.h
				${CMAKE_SOURCE_DIR}/statistics/Pct90.h
				${CMAKE_SOURCE_DIR}/statistics/Pct95.cpp
				${CMAKE_SOURCE_DIR}/statistics/Std.h
				)

target_link_libraries(statistics.test gtest_main)

set_target_properties(statistics PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
