#include "Logger.h"

Logger::Logger(std::string MethodName) : start(steady_clock::now()), methodName(MethodName) {
	ofs.open(LOGFILENAME, std::ios::app);
	if (ofs) {
		AddLogCrit(methodName);
	}
}

std::string Logger::PrintTimeNow() {
	time_t rawtime;
	struct tm* timeinfo = new tm;
	char buffer[80];

	time(&rawtime);
	localtime_s(timeinfo, &rawtime);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
	delete timeinfo;

	return buffer;
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