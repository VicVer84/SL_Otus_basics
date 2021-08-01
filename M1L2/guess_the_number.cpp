#include "GameParameters.h"

#include <string>
#include <iostream>
#include <vector>

std::string FILENAME = "ScoreBoard.txt";

int MakeGuess(int target_value){
	int cnt = 0;
	int current_value;
	do {
		std::cin >> current_value;
		cnt++;
		if (current_value < target_value) {
			std::cout << "greater than " << current_value << std::endl;
		} else if (current_value > target_value) {
			std::cout << "less than " << current_value << std::endl;
		} else {
			std::cout << "you win!" << std::endl;
			break;
		}
	} while(true);
	return cnt;
}

int main(int argc, char** argv) {
	std::vector<std::string> allArgs(argv, argv + argc);
	
	GameParameters params(FILENAME);
	params.Init(allArgs);
	
	if (!params.init) {
		return 0;
	}
	params.GenTargetValue();
	
	std::cout << "Enter your Name:" << std::endl;
	std::cin >> params.Name;
	
	int target_value = params.GenTargetValue();


	std::cout << "Enter your guess: [0 - " << params.maxNum << ']' << std::endl;
	
	params.UpdateHighScores(params.Name, MakeGuess(target_value));
	params.PrintPersonalHighScores(params.Name);
	params.WriteHighScores();
	
	return 0;
}