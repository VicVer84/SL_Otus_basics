#pragma once

#include <fstream>
#include <map>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class GameParameters {
public:
	explicit GameParameters(std::string Filename);
	std::string Name;
	std::map<std::string, int> results;
	std::string FileName;
	bool init = true;
	int maxNum = RAND_MAX;

	void Init(std::vector<std::string> allArgs);
	void ReadHighScores();
	void WriteHighScores();
	void PrintHighScores();
	void PrintPersonalHighScores(const std::string& name);
	void UpdateHighScores(const std::string& name, int num);
	int GenTargetValue();
private:
	void ToInt(std::string str);
	void PrintAndWait(const std::string& str);
	
};