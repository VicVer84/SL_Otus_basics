#pragma once 

#include "Structs.h"

#include <windows.h>
#include <iostream>
#include <vector>
#include <string>

/*
dumpbin /exports
   ordinal hint RVA      name

          1    0 00002C50 AnyInfo
          2    1 00004380 Done
          3    2 00002C50 FindAccountsByKind
          4    3 00004410 FindCardsL
          5    4 000045F0 FindEmail
          6    5 00004890 GetCardImageEx
          7    6 00004C80 GetCardInfoEx
          8    7 00002FE0 GetDiscLevelInfoL
          9    8 00005370 Init
         10    9 000054F0 TransactionsEx
*/
typedef void(__stdcall *CBFind)(void*, DWORD, INT64, const char*);

typedef void (*v_ptr)();
typedef int (*CardInfo_ptr)(INT64, DWORD, DWORD, CardInfo*, const char*, DWORD, WORD, const char*, DWORD&, WORD&);
typedef int (*CardImage_ptr)(INT64, CardImageInfo*);
typedef void (*FindCardsL_ptr)(const char*, CBFind, void*);
typedef int (*FindEmail_ptr)(const char*, EmailInfo*);
typedef int (*TransactionsEx_ptr)(DWORD, Transaction* Transactions[], const char*, DWORD, WORD, const char*, DWORD&, WORD&);

class LoadExtDll {
private:
	HINSTANCE hDLL;
public:	
	LoadExtDll(std::string, std::ostream&);
	void AnyInfo();
	void Done(std::ostream&);
	void FindAccountsByKind();
	void FindCardsL(const char* FindText, CBFind CBfind, void* Back, std::ostream&);
	int FindEmail(const char*, EmailInfo*, std::ostream&);
	int GetCardImageEx(INT64, CardImageInfo*, std::ostream&);
	int GetCardInfoEx(INT64, DWORD, DWORD, CardInfo*, const char*,
		DWORD, WORD, const char*, DWORD&, WORD&, std::ostream&);
	int GetDiscLevelInfoL();
	void Init(std::ostream&);
	int TransactionsEx(DWORD, Transaction* Transactions[], const char*,
		DWORD, WORD, const char*, DWORD&, WORD&, std::ostream&);

	~LoadExtDll();
};

