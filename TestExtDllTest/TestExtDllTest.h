#include "Logger.h"
#include "LibFunc.h"
#include "Structs.h"

#include <windows.h>
#include <gtest/gtest.h>

std::string TESTEXTDLLTEST = "TestExtDllTest.log";
std::string DLLNAME = "TestExtDll.dll";

struct FindInfo {
	INT64 Card = 0;
	std::string Name = "";
	bool operator==(FindInfo rhs) {
		return Card == rhs.Card && Name == rhs.Name;
	}
};

void __stdcall CBFind_(void* vec, DWORD count, INT64 card, const char* name);