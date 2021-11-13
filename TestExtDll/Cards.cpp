#include "Cards.h"


//#include <clocale>



KeyValueToken::KeyValueToken(std::string& line, char delimiter) {
	std::wstring wsTmp(line.begin(), line.end());
	std::wstringstream ss;
	ss << wsTmp;
	bool delimFound = false;
	wchar_t c;
	while (ss.get(c)) {
		if (c == delimiter) {
			delimFound = true;
		}
		//std::setlocale(LC_ALL, "ru_RU.utf8");
		if (iswalnum(c) || c == '@' || c == '.') {
			if (!delimFound) {
				_key += c;
			} else {
				_value += c;
			}
		}
	}
}
bool operator<(const KeyValueToken& lhs, const KeyValueToken& rhs) {
	return lhs._key < rhs._key;
}

Cards::Cards(char delimiter) {
	std::ifstream ifs(CardFileName);

	std::string CardNo = "";
	std::string line;
	while (std::getline(ifs, line)) {		
		KeyValueToken token(line, delimiter);
		if (token._key == "CardNo") {
			CardNo = token._value;
			continue;
		}		
		if (CardNo != "") {
			cards[CardNo].insert(token);
		}
	}
}

std::string Cards::GetCards() const{
	std::stringstream ss;
	for (auto& item : cards) {
		ss << item.first << "\n";
		for (auto& t : item.second) {
			ss << '\t' << t._key << " " << t._value << '\n';
		}
		ss << '\n';
	}
	return ss.str();
}

bool Cards::FindCard(std::string& Card) const{
	return cards.count(Card) > 0;
}

int Cards::GetCard(std::string&& Card, CardInfo* info) {
	if (FindCard(Card)) {
		Logger logger("GetCard found");
		if (GetCardData(Card, "isDeleted") == "1" || GetCardData(Card, "isDeleted") == "true") {
			info->isDeleted = true;
		}
		if (GetCardData(Card, "isNeedWithdraw") == "1" || GetCardData(Card, "isNeedWithdraw") == "true") {
			info->isNeedWithdraw = true;
		}
		if (GetCardData(Card, "isExpired") == "1" || GetCardData(Card, "isExpired") == "true") {
			info->isExpired = true;
		}
		if (GetCardData(Card, "isInvalid") == "1" || GetCardData(Card, "isInvalid") == "true") {
			info->isInvalid = true;
		}
		if (GetCardData(Card, "isManagerConfirm") == "1" || GetCardData(Card, "isManagerConfirm") == "true") {
			info->isManagerConfirm = true;
		}
		if (GetCardData(Card, "isBlocked") == "1" || GetCardData(Card, "isBlocked") == "true") {
			info->isBlocked = true;
		}
		CopyMemory(info->blockReason, GetCardData(Card, "blockReason").c_str(), sizeof(GetCardData(Card, "blockReason")));
		CopyMemory(info->cardOwner, GetCardData(Card, "cardOwner").c_str(), sizeof(GetCardData(Card, "cardOwner")));

		info->ownerId = StrToInt(GetCardData(Card, "ownerId"));
		info->accountNum = StrToInt(GetCardData(Card, "accountNum"));
		info->unpayType = StrToInt(GetCardData(Card, "unpayType"));
		info->bonusNum = StrToInt(GetCardData(Card, "bonusNum"));
		info->discountNum = StrToInt(GetCardData(Card, "discountNum"));
		info->amountOnSubAccount1 = StrToInt(GetCardData(Card, "amountOnSubAccount1"));
		info->amountOnSubAccount2 = StrToInt(GetCardData(Card, "amountOnSubAccount2"));
		info->amountOnSubAccount3 = StrToInt(GetCardData(Card, "amountOnSubAccount3"));
		info->amountOnSubAccount4 = StrToInt(GetCardData(Card, "amountOnSubAccount4"));
		info->amountOnSubAccount5 = StrToInt(GetCardData(Card, "amountOnSubAccount5"));
		info->amountOnSubAccount6 = StrToInt(GetCardData(Card, "amountOnSubAccount6"));
		info->amountOnSubAccount7 = StrToInt(GetCardData(Card, "amountOnSubAccount7"));
		info->amountOnSubAccount8 = StrToInt(GetCardData(Card, "amountOnSubAccount8"));

		CopyMemory(info->comment, GetCardData(Card, "comment").c_str(), sizeof(GetCardData(Card, "comment")));
		CopyMemory(info->screenComment, GetCardData(Card, "screenComment").c_str(), sizeof(GetCardData(Card, "screenComment")));
		CopyMemory(info->printComment, GetCardData(Card, "printComment").c_str(), sizeof(GetCardData(Card, "printComment")));
		return 0;
	}
	else {
		Logger logger("GetCard not found");
		logger.AddLog(Card);
	}
	return 1;
}

std::string Cards::GetCardData(std::string& Card, std::string&& FieldName) const {
	for (auto& data : cards.at(Card)) {
		if (data._key == FieldName) {
			return data._value;
		}
	}
	return "";
}
INT64 Cards::StrToInt(std::string num) {
	INT64 number;
	std::istringstream iss(num);
	iss >> number;
	if (iss.fail()) {
		return 0;
	}
	return number;
}

int Cards::FindByEmail(std::string&& Email, EmailInfo* einfo) {

	std::string Card;
	for (auto& card : cards) {
		for (auto& token : card.second) {
			if (token._key == "email" && token._value == Email) {
				Card = card.first;
			}
		}
	}
	if (Card != "") {
		einfo->accountNum = StrToInt(GetCardData(Card, "accountNum"));
		einfo->cardNum = StrToInt(Card);
		CopyMemory(einfo->OwnerName, GetCardData(Card, "cardOwner").c_str(), sizeof(GetCardData(Card, "cardOwner")));
		return 0;
	} else {
		return 1;
	}	
}