#pragma once

#include "Utils.h"

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>


using namespace std::chrono;

class Logger {
public:
	explicit Logger(std::string Method);

	void AddLog(std::string Message);
	void AddLogCrit(std::string Message);

	~Logger();
private:
	const std::string LogFileName = "TestExtDll.log";
	std::string methodName;
	std::ofstream ofs;
	steady_clock::time_point start;
};