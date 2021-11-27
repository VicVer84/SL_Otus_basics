#include "TestDllInTheMid.h"

static const std::string LOGFILENAME = "TestDllInTheMid.log";
static const std::string INIFILENAME = "TestDllInTheMid.ini";
std::string DLLNAME = "TestExtDll.dll";


void Init() {
	Logger logger(LOGFILENAME, "TestDllInTheMid::Init");
	auto& ofs = logger.GetStream();
	
	std::ifstream ifs(INIFILENAME);
	std::string str;
	if (ifs) {
		std::getline(ifs, str);
		if (str.size() <= 40) {
			DLLNAME = str;
		}
	}
	else {
		std::ofstream ini(INIFILENAME);		
		ini << DLLNAME << std::endl;
		ofs << INIFILENAME << " created" << std::endl;
	}
	ofs << "Loaded: " << DLLNAME << std::endl;


	LoadExtDll TestExtDll(DLLNAME, ofs);
	TestExtDll.Init(ofs);
	
	logger.AddLogCrit("Call Init TestDllInTheMid");
}

void Done() {
	Logger logger(LOGFILENAME, "TestDllInTheMid::Done");
	auto& ofs = logger.GetStream();

	LoadExtDll TestExtDll(DLLNAME, ofs);
	TestExtDll.Done(ofs);
	
	logger.AddLogCrit("Call Done TestDllInTheMid");
}

int __cdecl GetCardInfoEx(INT64 Card, DWORD Restaurant, DWORD UnitNo,
					CardInfo* info, const char* InpBuf, DWORD InpLen, WORD InpKind,
					const char* OutBuf, DWORD &OutLen, WORD &OutKind) {
		
	Logger logger(LOGFILENAME, "TestDllInTheMid::GetCardInfoEx");
	auto& ofs = logger.GetStream();

	LoadExtDll TestExtDll(DLLNAME, ofs);

	logger.AddLog("-------- Before Call ---------");
	logger.AddLog("Card: " + std::to_string(Card));
	logger.AddLog("Restaurant: " + std::to_string(Restaurant));
	logger.AddLog("UnitNo: " + std::to_string(UnitNo));
	logger.AddLog("InpLen: " + std::to_string(InpLen));
	logger.AddLog("InpKind: " + std::to_string(InpKind));	
	logger.AddLogCrit("InpBuf: \n" + InpBufToStr(InpBuf, InpLen));

	int result = TestExtDll.GetCardInfoEx(Card, Restaurant, UnitNo, info, InpBuf, InpLen, InpKind, OutBuf, OutLen, OutKind, ofs);
	
	logger.AddLog("-------- After Call ---------");
	logger.AddLog("result: " + std::to_string(result));
	logger.AddLog(GetCardInfo(info));
	logger.AddLogCrit("OutBuf: \n" + InpBufToStr(OutBuf, OutLen));
	logger.AddLog(std::to_string(OutKind));
	
	return result;
}


int TransactionsEx(DWORD Count, Transaction* transactions[], const char* InpBuf, DWORD InpLen,
					WORD InpKind, const char* OutBuf, DWORD &OutLen, WORD &OutKind) 
{
	Logger logger(LOGFILENAME, "TransactionsEx");
	auto& ofs = logger.GetStream();

	LoadExtDll TestExtDll(DLLNAME, ofs);
	logger.AddLog("-------- Before Call ---------");
	
	logger.AddLogCrit("InpBuf: \n" + InpBufToStr(InpBuf, InpLen));
	logger.AddLog("Count: " + std::to_string(Count));
	for (size_t i = 0; i < Count; i++) {
		Transaction* tr = transactions[i];
		logger.AddLog("Transaction num:" + std::to_string(i));
		logger.AddLog(GetTransaction(tr));
	}
	
	int result = TestExtDll.TransactionsEx(Count, transactions, InpBuf, InpLen, InpKind, OutBuf, OutLen, OutKind, ofs);
	
	logger.AddLog("-------- After Call ---------");
	logger.AddLogCrit("OutBuf: \n" + InpBufToStr(OutBuf, OutLen));
	logger.AddLog(std::to_string(OutKind));
	
	return result;
}

int GetCardImageEx(INT64 Card, CardImageInfo* info) {
	Logger logger(LOGFILENAME, "GetCardImageEx");
	auto& ofs = logger.GetStream();

	LoadExtDll TestExtDll(DLLNAME, ofs);
	int result = TestExtDll.GetCardImageEx(Card, info, ofs);
	
	logger.AddLog("Card: " + std::to_string(Card));

	ofs << "FileName: " << info->fileName;
	return result;
}

int FindEmail(const char* Email, EmailInfo* emailInfo) {
	Logger logger(LOGFILENAME, "FindEmail");
	auto& ofs = logger.GetStream();

	LoadExtDll TestExtDll(DLLNAME, ofs);
	logger.AddLog("Email: " + std::string(Email));
	
	int result = TestExtDll.FindEmail(Email, emailInfo, ofs);

	logger.AddLog(GetEmailInfo(emailInfo));
	return result;
}


void FindCardsL(const char* FindText, CBFind CBfind, void* Back) {
	Logger logger(LOGFILENAME, "FindCardsL");
	auto& ofs = logger.GetStream();

	LoadExtDll TestExtDll(DLLNAME, ofs);
	logger.AddLog(FindText);
	TestExtDll.FindCardsL(FindText, CBfind, Back, ofs);
}

int GetDiscLevelInfoL(int32_t  Account, DiscLevelInfo* info) {
	return 1;
}

void AnyInfo(const char* InpBuf, int32_t InpLen, void* OutBuf, int32_t OutLen) {}

void FindAccountsByKind(int Kind, const char* FindText, CBFind CBfind, void* Back) {}