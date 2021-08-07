#pragma once

#include <fstream>
#include <map>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool ToInt(const std::string& str, int& out);
void PrintAndWait(const std::string& str);

class GameParameters {
public:
	explicit GameParameters(const std::string& Filename);

	void Init(std::vector<std::string>& allArgs);
	void ReadHighScores();
	void WriteHighScores();
	void PrintHighScores();
	void PrintPersonalHighScores();
	void UpdateHighScores(int num);
	int GenTargetValue();
	void SetName(std::string&& name);
	int GetMaxNum();
	operator bool();
private:
	std::string Name;
	std::map<std::string, int> results;
	std::string FileName;
	bool init = true;
	int maxNum = RAND_MAX;
	
};