#pragma once

#include "TestExtDll.h"

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>


struct KeyValueToken {
	std::string _key;
	std::string _value;
	KeyValueToken(std::string& line, char delimiter);
};

class Cards {
public:
	Cards(char delimiter);

	bool FindCard(std::string& Card);
	std::string GetCardData(std::string& Card, std::string&& FieldName);
	int GetCard(std::string&& Card, CardInfo* info);
	int FindByEmail(std::string&& Email, EmailInfo* einfo);
	std::string GetCards();

private:
	std::string CardFileName = "Cards.txt";
	std::map<std::string, std::set<KeyValueToken>> cards;

	INT64 StrToInt(std::string num);
};
bool operator<(const KeyValueToken& lhs, const KeyValueToken& rhs);