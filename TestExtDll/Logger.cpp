#include "Logger.h"

Logger::Logger(std::string MethodName) : start(steady_clock::now()), methodName(MethodName) {
	ofs.open(LogFileName, std::ios::app);
	if (ofs) {
		AddLogCrit(methodName);
	}
}



void Logger::AddLog(std::string Message) {
	if (!ofs) {
		return;
	}
	ofs << PrintTimeNow();
	ofs << " " << Message << '\n';
}

void Logger::AddLogCrit(std::string Message) {
	if (!ofs) {
		return;
	}
	ofs << PrintTimeNow();
	ofs << " " << Message << std::endl;
}

Logger::~Logger() {
	if (!ofs) {
		return;
	}
	auto finish = steady_clock::now();
	auto dur = finish - start;
	AddLogCrit(methodName + ' ' + std::to_string(duration_cast<nanoseconds>(dur).count()) + "ns");
	ofs << "\n-------------------------------------------------------------------------------------\n";
	ofs.close();
}