#pragma once

#include "Logger.h"
#include "Structs.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <windows.h>

typedef void (__stdcall *CBFind)(void*, DWORD, INT64, const char*);
using Token = std::pair<std::string, std::string> ;

class Cards {
public:
	Cards(char delimiter);

	bool FindCard(std::string&) const;
	std::string GetCardData(std::string&, std::string&&) const;
	void UpdateCharArray(unsigned char* c, int length, std::string& Card, std::string&& FieldName);
	int GetCard(std::string&&, CardInfo*);
	int FindByEmail(std::string&&, EmailInfo*);
	void FindOwnerByNamePart(std::string&&, CBFind, void*);
	std::string GetCards() const;
	void UpdateCards(DWORD Count, Transaction* Transactions[]);
	void static CreateCardsTxt();
	Token KeyValueToken(std::string& line, char delimiter);
private:

	inline static std::string CardFileName = "Cards.txt";
	std::map<std::string, std::map<std::string, std::string>> cards;
	void SaveCards() const;
};