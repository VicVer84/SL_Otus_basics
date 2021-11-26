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
	
	void static CreateCardsTxt();
	int FindByEmail(std::string&&, EmailInfo*); // search by email
	void FindOwnerByNamePart(std::string&&, CBFind, void*); // search by owner name part and make callbacks with what was found
	int GetCard(std::string&&, CardInfo*); // funcion fills structure with card data
	std::string GetCardData(std::string&, std::string&&) const;	
	std::string CardsToString() const; 
	void UpdateCards(DWORD Count, Transaction* Transactions[]); // update cards data according to the Kind of transaction except for unsigned char*
	
	Token KeyValueToken(std::string& line, char delimiter); // create pair with cards key=value data 
private:

	inline static std::string CardFileName = "Cards.txt";
	std::map<std::string, std::map<std::string, std::string>> cards;
	void SaveCards() const; // save cards to file
	void CopyStrToCharArray(unsigned char* c, int length, std::string& Card, std::string&& FieldName); // copy str to unsigned char*
};