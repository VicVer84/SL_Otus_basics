#include "GameParameters.h"



GameParameters::GameParameters(std::string filename) {
	FileName = filename;
	ReadHighScores();
}

void GameParameters::ToInt(std::string str) {
	try {
		maxNum = std::stoi(str);
	} catch (std::invalid_argument e) {
		std::cout << str << " is invalid number.\n";
		std::getchar();
		init = false;
	}
}

void GameParameters::PrintAndWait(const std::string& str) {
	std::cout << str << '\n';
	std::getchar();
}

int GameParameters::GenTargetValue() {
	std::srand(std::time(nullptr));
	return std::rand() % maxNum;
}

void GameParameters::Init(std::vector<std::string> allArgs) {
	int argc = allArgs.size();
	if (argc > 0) {
		for (int i = 1; i < argc; i++) {
			if (allArgs[i] == "-table") {
				PrintHighScores();
				init = false;
				break; 
			} else if (allArgs[i] == "-max") {
				if (i + 1 < argc) {
					ToInt(allArgs[++i]);
				} else {
					PrintAndWait("Missing value for arg: " + allArgs[i]);
					init = false;
				}
				break; // выходим из цикла, т.к. вместе -max и -level не должны встречаться
			} else if (allArgs[i] == "-level") {
				if (i + 1 < argc) {
					ToInt(allArgs[++i]);
					
					if (maxNum > 3) { // в задании не определено что будет если указать лвл больше 3.
						maxNum = 3;
					}

					switch (maxNum) {
					case 1:
						maxNum = 9;
						break;
					case 2:
						maxNum = 49;
						break;
					case 3:
						maxNum = 99;
						break;
					}
				} else {
					PrintAndWait("Missing value for arg: " + allArgs[i]);
					init = false;
				}
				break; // выходим из цикла, т.к. вместе -max и -level не должны встречаться
			} 
		}
	}
}

void GameParameters::ReadHighScores(){
	std::ifstream ifs(FileName);
	if (!ifs.is_open()) {
		std::cout << "Can't open " << FileName << '\n';
		return;
	}

	for (std::string w; std::getline(ifs, w); ) {
		std::stringstream ss;
		ss << w;
		std::string name;
		int number;
		ss >> name;
		ss >> number;
		results[name] = number;
	}
}

void GameParameters::WriteHighScores(){
	std::ofstream fs(FileName, std::ios::out);
	for(auto w : results){
		fs << w.first << ' ' << w.second << '\n';
	}
}

void GameParameters::PrintHighScores() {
	std::cout << "SCOREBOARD: \n";
	std::cout << std::setw(30) << "Name" << ' ' << std::setw(30) << "Score" << '\n';
	for(auto w : results){
		std::cout << std::setw(30) << w.first << ' ' << std::setw(30) << w.second << '\n';
	}
	std::getchar();
}

void GameParameters::PrintPersonalHighScores(const std::string& name) {
	std::cout << "PERSONAL BEST: \n";
	std::cout << std::setw(30) << "Name" << ' ' << std::setw(30) << "Score" << '\n';
	std::cout << std::setw(30) << name << ' ' << std::setw(30) << results[name] << '\n';
	std::getchar();
}

void GameParameters::UpdateHighScores(const std::string& name, int num) {
	if (results[name] == 0) {
		results[name] = num;
	}
	if(results[name] > num) {
		results[name] = num;
	}
}