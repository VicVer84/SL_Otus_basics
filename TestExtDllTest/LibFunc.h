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

struct FindInfo {
	INT64 Card = 0;
	std::string Name = "";
	bool operator==(FindInfo rhs) {
		return Card == rhs.Card && Name == rhs.Name;
	}
};

namespace TestExtDll {
	void AnyInfo();
	void __stdcall CBFind(std::vector<FindInfo>*, DWORD, INT64, const char*);
	void Done(std::ostream&);
	void FindAccountsByKind();
	std::vector<FindInfo> FindCardsL(std::string);
	int FindEmail(std::string, EmailInfo*);
	int GetCardImageEx(CardImageInfo*, INT64);
	int GetCardInfoEx(CardInfo*, INT64);
	int GetDiscLevelInfoL();
	void Init(std::ostream&);
	int TransactionsEx(DWORD Count, Transaction* transactions[]);
}

