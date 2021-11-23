
#include "LibFunc.h"
#include "Utils.h"

typedef void (*v_ptr)();
typedef int (*CardInfo_ptr)(INT64, DWORD, DWORD, CardInfo*, const char*, DWORD, WORD, const char*, DWORD& , WORD&);
typedef int (*CardImage_ptr)(INT64, CardImageInfo*);

typedef void (*FindCardsL_ptr)(const char*, void (__stdcall *CBFind_ptr)(std::vector<FindInfo>*, DWORD, INT64, char*), std::vector<FindInfo>*);
typedef int (*FindEmail_ptr)(const char*, EmailInfo*);
typedef int (*TransactionsEx_ptr)(DWORD, Transaction* Transactions[], const char*, DWORD, WORD, void*, DWORD&, WORD&);



namespace TestExtDll {

	void Init(std::ostream& os) {
		HINSTANCE hDLL = ::LoadLibrary("TestExtDll.dll");
		if (!hDLL) {
			os << "Could not load the dynamic library" << std::endl;
			return;
		}

		v_ptr init = (v_ptr)::GetProcAddress(hDLL, "Init");
		if (!init) {
			os << "could not locate the function" << std::endl;
			return;
		}
		init();
		
		os << "Init";

		::FreeLibrary(hDLL);
	}
	
	void Done(std::ostream& os) {
		HINSTANCE hDLL = ::LoadLibrary("TestExtDll.dll");
		if (!hDLL) {
			os << "Could not load the dynamic library" << std::endl;
			return;
		}

		v_ptr done = (v_ptr)::GetProcAddress(hDLL, "Done");
		if (!done) {
			os << "could not locate the function" << std::endl;
			return;
		}
		done();
		
		os << "Done";

		::FreeLibrary(hDLL);
	}
	
	int GetCardInfoEx(CardInfo *info, INT64 Card){
		HINSTANCE hDLL = ::LoadLibrary("TestExtDll.dll");
		if (!hDLL) {
			std::cout << "Could not load the dynamic library" << std::endl;
			return 1;
		}

		CardInfo_ptr getCardInfoEx = (CardInfo_ptr)::GetProcAddress(hDLL, "GetCardInfoEx");
		if (!getCardInfoEx) {
			std::cout << "could not locate the function" << std::endl;
			return 1;
		}		
		
		
		DWORD Restaurant = 1;
		DWORD UnitNo = 1;	

		info->size = 1164;
		const char* InpBuf = "";
		DWORD InpLen = 0;
		WORD InpKind = 0;
		const char* OutBuf = "";
		DWORD OutLen = 0;
		WORD OutKind = 0;				
		
		int result = getCardInfoEx(Card, Restaurant, UnitNo, info, InpBuf, InpLen, InpKind, OutBuf, OutLen, OutKind);

		::FreeLibrary(hDLL);

		return result;
	}

	int GetCardImageEx(CardImageInfo* info, INT64 Card) {
		HINSTANCE hDLL = ::LoadLibrary("TestExtDll.dll");
		if (!hDLL) {
			std::cout << "Could not load the dynamic library" << std::endl;
			return 1;
		}

		CardImage_ptr getCardImageEx = (CardImage_ptr)::GetProcAddress(hDLL, "GetCardImageEx");
		if (!getCardImageEx) {
			std::cout << "could not locate the function" << std::endl;
			return 1;
		}		
		
		info->size = 258;
		
		int result = getCardImageEx(Card, info);

		::FreeLibrary(hDLL);

		return result;
	}

	//callback function using same convention as in TestExtDll
	void __stdcall CBFind(std::vector<FindInfo>* vec, DWORD count, INT64 card, char* name) {
		FindInfo info;
		info.Card = card;
		info.Name = name;
		(*vec).push_back(info);
	}

	
	std::vector<FindInfo> FindCardsL(std::string Findstr) {
		HINSTANCE hDLL = ::LoadLibrary("TestExtDll.dll");
		if (!hDLL) {
			std::cout << "Could not load the dynamic library" << std::endl;
			return {};
		}

		FindCardsL_ptr findCardsL = (FindCardsL_ptr)::GetProcAddress(hDLL, "FindCardsL");
		if (!findCardsL) {
			std::cout << "could not locate the function" << std::endl;
			return {};
		}
		
		std::vector<FindInfo> vec;

		findCardsL(Findstr.c_str(), &CBFind, &vec);

		::FreeLibrary(hDLL);
		return vec;
	}

	int FindEmail(std::string Findstr, EmailInfo* info) {
		HINSTANCE hDLL = ::LoadLibrary("TestExtDll.dll");
		if (!hDLL) {
			std::cout << "Could not load the dynamic library" << std::endl;
			return 1;
		}

		FindEmail_ptr findEmail = (FindEmail_ptr)::GetProcAddress(hDLL, "FindEmail");
		if (!findEmail) {
			std::cout << "could not locate the function" << std::endl;
			return 1;
		}	
		
		info->size = 54;

		int result = findEmail(Findstr.c_str(), info);

		::FreeLibrary(hDLL);

		return result;
	}
	
	int TransactionsEx(DWORD Count, Transaction* transactions[]){
		HINSTANCE hDLL = ::LoadLibrary("TestExtDll.dll");
		if (!hDLL) {
			std::cout << "Could not load the dynamic library" << std::endl;
			return 1;
		}

		TransactionsEx_ptr transactionsEx = (TransactionsEx_ptr)::GetProcAddress(hDLL, "TransactionsEx");
		if (!transactionsEx) {
			std::cout << "could not locate the function" << std::endl;
			return 1;
		}
	
		
		const char* InpBuf = "";
		DWORD InpLen = 0;
		WORD InpKind = 0;
		void* OutBuf = "";
		DWORD OutLen = 0; 
		WORD OutKind = 0;

		int result = transactionsEx(Count, transactions, InpBuf, InpLen, InpKind, OutBuf, OutLen, OutKind);
		
		::FreeLibrary(hDLL);

		return result;
	}

}

