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

struct KeyValueToken {
	std::string _key;
	std::string _value;
	KeyValueToken(std::string& line, char delimiter);
};

class Cards {
public:
	Cards(char delimiter);

	bool FindCard(std::string&) const;
	std::string GetCardData(std::string&, std::string&&) const;
	int GetCard(std::string&&, CardInfo*);
	int FindByEmail(std::string&&, EmailInfo*);
	void FindOwnerByNamePart(std::string&&, CBFind, void*);
	std::string GetCards() const;

private:
	std::string CardFileName = "Cards.txt";
	std::map<std::string, std::set<KeyValueToken>> cards;

	INT64 StrToInt(std::string num);
};