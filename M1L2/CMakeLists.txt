cmake_minimum_required(VERSION 3.5)

project(05.homework)

add_executable(
	guess_the_number	
	GuessTheNumber.cpp
	GameParameters.cpp
)
set_target_properties(guess_the_number PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)