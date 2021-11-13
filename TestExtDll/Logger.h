#pragma once

#include <chrono>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std::chrono;

const std::string LOGFILENAME = "TestExtDll.log";


class Logger {
public:
	explicit Logger(std::string Method);

	void AddLog(std::string Message);
	void AddLogCrit(std::string Message);

	static std::string PrintTimeNow();

	~Logger();
private:
	std::string methodName;
	std::ofstream ofs;
	steady_clock::time_point start;
};