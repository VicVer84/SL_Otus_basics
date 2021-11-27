
#include "LibFunc.h"
#include "Utils.h"


LoadExtDll::LoadExtDll(std::string DLLNAME, std::ostream& os) : hDLL(::LoadLibrary(DLLNAME.c_str())) {
	if (!hDLL) {
		os << "LoadExtDll ctor:: Could not load the dynamic library" << std::endl;
	}
}

LoadExtDll::~LoadExtDll() {
	::FreeLibrary(hDLL);
}

void LoadExtDll::Init(std::ostream& os) {
	v_ptr init = (v_ptr)::GetProcAddress(hDLL, "Init");
	if (!init) {
		os << "LoadExtDll::Init:: could not locate the function" << std::endl;
		return;
	}
	init();
		
	os << "Init";
}
	
void LoadExtDll::Done(std::ostream& os) {
	v_ptr done = (v_ptr)::GetProcAddress(hDLL, "Done");
	if (!done) {
		os << "LoadExtDll::Done:: Could not locate the function" << std::endl;
		return;
	}
	done();
		
	os << "Done";
}
	
int LoadExtDll::GetCardInfoEx(INT64 Card, DWORD Restaurant, DWORD UnitNo, CardInfo* info, const char* InpBuf,
					DWORD InpLen, WORD InpKind, const char* OutBuf, DWORD& OutLen, WORD& OutKind, std::ostream& os){

	CardInfo_ptr getCardInfoEx = (CardInfo_ptr)::GetProcAddress(hDLL, "GetCardInfoEx");
	if (!getCardInfoEx) {
		os << "LoadExtDll::GetCardInfoEx:: Could not locate the function" << std::endl;
		return -1;
	}			
	int result = getCardInfoEx(Card, Restaurant, UnitNo, info, InpBuf, InpLen, InpKind, OutBuf, OutLen, OutKind);
	
	return result;
}

int LoadExtDll::GetCardImageEx(INT64 Card, CardImageInfo* info, std::ostream& os) {
	CardImage_ptr getCardImageEx = (CardImage_ptr)::GetProcAddress(hDLL, "GetCardImageEx");
	if (!getCardImageEx) {
		os << "LoadExtDll::GetCardImageEx:: Could not locate the function" << std::endl;
		return -1;
	}		
		
	int result = getCardImageEx(Card, info);

	return result;
}
	
void LoadExtDll::FindCardsL(const char* FindText, CBFind CBfind, void* Back, std::ostream& os) {
	FindCardsL_ptr findCardsL = (FindCardsL_ptr)::GetProcAddress(hDLL, "FindCardsL");
	if (!findCardsL) {
		os << "LoadExtDll::FindCardsL:: Could not locate the function" << std::endl;
	}

	findCardsL(FindText, CBfind, Back);
}

int LoadExtDll::FindEmail(const char* Email, EmailInfo* emailInfo, std::ostream& os) {
	FindEmail_ptr findEmail = (FindEmail_ptr)::GetProcAddress(hDLL, "FindEmail");
	if (!findEmail) {
		os << "LoadExtDll::FindEmail:: Could not locate the function" << std::endl;
		return 1;
	}	

	int result = findEmail(Email, emailInfo);

	return result;
}
	
int LoadExtDll::TransactionsEx(DWORD Count, Transaction* transactions[], const char* InpBuf,
				DWORD InpLen, WORD InpKind, const char* OutBuf, 
				DWORD &OutLen, WORD &OutKind, std::ostream& os) {

	TransactionsEx_ptr transactionsEx = (TransactionsEx_ptr)::GetProcAddress(hDLL, "TransactionsEx");
	if (!transactionsEx) {
		os << "LoadExtDll::TransactionsEx:: Could not locate the function" << std::endl;
		return -1;
	}

	int result = transactionsEx(Count, transactions, InpBuf, InpLen, InpKind, OutBuf, OutLen, OutKind);

	return result;
}


