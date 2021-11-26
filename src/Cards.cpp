#include "Cards.h"

static const std::string LOGFILENAME = "TestExtDll.log";

Token Cards::KeyValueToken(std::string& line, char delimiter) {
	std::stringstream ss;
	std::string key = "";
	std::string value = "";

	ss << line;
	bool delimFound = false;
	char c;
	while (ss.get(c)) {
		if (c == delimiter) {
			delimFound = true;
		}
		if (iswalnum(c) || c == '@' || c == '.') {
			if (!delimFound) {
				key += c;
			}
			else {
				value += c;
			}
		}
	}
	return std::make_pair(key, value);
}


Cards::Cards(char delimiter) {
	std::ifstream ifs(CardFileName);

	std::string CardNo = "";
	std::string line;
	while (std::getline(ifs, line)) {		
		Token token = Cards::KeyValueToken(line, delimiter);
		if (token.first == "CardNo") {
			CardNo = token.second;
			continue;
		}		
		if (CardNo != "") {
			cards[CardNo].insert(token);
		}
	}
}

std::string Cards::CardsToString() const{
	std::stringstream ss;
	for (auto& item : cards) {
		ss << item.first << "\n";
		for (auto& t : item.second) {
			ss << '\t' << t.first << " " << t.second << '\n';
		}
		ss << '\n';
	}
	return ss.str();
}

int Cards::GetCard(std::string&& Card, CardInfo* info) {
	if (cards.count(Card) > 0) {
		Logger logger(LOGFILENAME, "GetCard found");
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
		CopyStrToCharArray(info->blockReason, sizeof(info->blockReason), Card, "blockReason");
		CopyStrToCharArray(info->cardOwner, sizeof(info->cardOwner), Card, "cardOwner");
		info->ownerId = StrToInt(GetCardData(Card, "ownerId"));
		info->accountNum = StrToInt(GetCardData(Card, "accountNum"));
		info->unpayType = StrToInt(GetCardData(Card, "unpayType"));
		info->bonusNum = StrToInt(GetCardData(Card, "bonusNum"));
		info->discountNum = StrToInt(GetCardData(Card, "discountNum"));
		info->maxDiscountAmount = StrToInt(GetCardData(Card, "maxDiscountAmount"));
		info->amountOnSubAccount1 = StrToInt(GetCardData(Card, "amountOnSubAccount1"));
		info->amountOnSubAccount2 = StrToInt(GetCardData(Card, "amountOnSubAccount2"));
		info->amountOnSubAccount3 = StrToInt(GetCardData(Card, "amountOnSubAccount3"));
		info->amountOnSubAccount4 = StrToInt(GetCardData(Card, "amountOnSubAccount4"));
		info->amountOnSubAccount5 = StrToInt(GetCardData(Card, "amountOnSubAccount5"));
		info->amountOnSubAccount6 = StrToInt(GetCardData(Card, "amountOnSubAccount6"));
		info->amountOnSubAccount7 = StrToInt(GetCardData(Card, "amountOnSubAccount7"));
		info->amountOnSubAccount8 = StrToInt(GetCardData(Card, "amountOnSubAccount8"));
		CopyStrToCharArray(info->comment, sizeof(info->comment), Card, "comment");
		CopyStrToCharArray(info->screenComment, sizeof(info->screenComment), Card, "screenComment");
		CopyStrToCharArray(info->printComment, sizeof(info->printComment), Card, "printComment");

		return 0;
	}
	else {
		Logger logger(LOGFILENAME, "GetCard not found");
		logger.AddLog(Card);
	}
	return 1;
}

void Cards::CopyStrToCharArray(unsigned char* c, int length, std::string& Card, std::string&& FieldName) {
	memcpy(c, cards.at(Card).at(FieldName).c_str(), cards.at(Card).at(FieldName).size() + 1);
}

std::string Cards::GetCardData(std::string& Card, std::string&& FieldName) const {
	try {		
		return cards.at(Card).at(FieldName);
	} catch (std::out_of_range) {
		return "";
	}
	
}

int Cards::FindByEmail(std::string&& Email, EmailInfo* einfo) {

	std::string Card;
	for (auto& card : cards) {
		for (auto& token : card.second) {
			if (token.first == "email" && token.second == Email) {
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

std::string str_tolower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), 
		[](unsigned char c){ return std::tolower(c); }
	);
    return s;
}

void Cards::FindOwnerByNamePart(std::string&& Name, CBFind CBfind, void* Back) {
	Logger logger(LOGFILENAME, "FindOwnerByNamePart");
	int i = 0;
	for (auto& card : cards) {
		for (auto& token : card.second) {
			if (token.first == "cardOwner" && str_tolower(token.second).find(str_tolower(Name)) != std::string::npos) {
				CBfind(Back, i, StrToInt(card.first), token.second.c_str());
				++i;
				logger.AddLog("Found: Card: " + card.first + " OwnerName: " + token.second + '\n');
			}
		}
	}
}

void Cards::CreateCardsTxt() {
	std::ofstream ofs(CardFileName, std::ios::app);
	ofs << "[CardNo=1]\n";
	ofs << "isDeleted = 0\n";
	ofs << "isNeedWithdraw = 0\n";
	ofs << "isExpired = 0\n";
	ofs << "isInvalid = 0\n";
	ofs << "isManagerConfirm = 0\n";
	ofs << "isBlocked = 0\n";
	ofs << "blockReason = 0\n";
	ofs << "cardOwner = TestOwner\n";
	ofs << "ownerId = 1\n";
	ofs << "accountNum = 1\n";
	ofs << "unpayType = 0\n";
	ofs << "bonusNum = 0\n";
	ofs << "discountNum = 0\n";
	ofs << "maxDiscountAmount = 100000000\n";
	ofs << "amountOnSubAccount1 = 1000\n";
	ofs << "amountOnSubAccount2 = 2000\n";
	ofs << "amountOnSubAccount3 = 3000\n";
	ofs << "amountOnSubAccount4 = 4000\n";
	ofs << "amountOnSubAccount5 = 5000\n";
	ofs << "amountOnSubAccount6 = 6000\n";
	ofs << "amountOnSubAccount7 = 7000\n";
	ofs << "amountOnSubAccount8 = 8000\n";
	ofs << "comment =\n";
	ofs << "screenComment =\n";
	ofs << "printComment =\n";
	ofs << "email = test@test.ru\n";
	
	ofs << "[CardNo=2]\n";
	ofs << "isDeleted = 0\n";
	ofs << "isNeedWithdraw = 0\n";
	ofs << "isExpired = 0\n";
	ofs << "isInvalid = 0\n";
	ofs << "isManagerConfirm = 0\n";
	ofs << "isBlocked = 0\n";
	ofs << "blockReason = 0\n";
	ofs << "cardOwner = ownerNew\n";
	ofs << "ownerId = 2\n";
	ofs << "accountNum = 2\n";
	ofs << "unpayType = 0\n";
	ofs << "bonusNum = 0\n";
	ofs << "discountNum = 0\n";
	ofs << "maxDiscountAmount = 100000000\n";
	ofs << "amountOnSubAccount1 = 1000\n";
	ofs << "amountOnSubAccount2 = 2000\n";
	ofs << "amountOnSubAccount3 = 3000\n";
	ofs << "amountOnSubAccount4 = 4000\n";
	ofs << "amountOnSubAccount5 = 5000\n";
	ofs << "amountOnSubAccount6 = 6000\n";
	ofs << "amountOnSubAccount7 = 7000\n";
	ofs << "amountOnSubAccount8 = 8000\n";
	ofs << "comment =\n";
	ofs << "screenComment =\n";
	ofs << "printComment =\n";
	ofs << "email = test1@test.ru\n";
	ofs.close();
}

void Cards::SaveCards() const{
	std::ofstream ofs(CardFileName, std::ios::out);
	for (auto& card : cards) {
		ofs  << "[CardNo = " << card.first << "]" << '\n';
		for(auto& token : card.second) {
			ofs << token.first << " = " << token.second << '\n';
		}
	}
}

void Cards::UpdateCards(DWORD Count, Transaction* Transactions[]) {
	Logger logger(LOGFILENAME, "UpdateCards");
	for (size_t i = 0; i < Count; ++i) {
		Transaction* tr = Transactions[i];
		std::string Card;
		{
			std::stringstream ss;
			ss << tr->Card;		
			Card = ss.str();
		}
		if (tr->Kind == 0) {
			std::stringstream ss;
			INT64 sum = StrToInt(cards[Card]["amountOnSubAccount1"]); //sale accoumt
			ss << sum + tr->Summa;
			cards[Card]["amountOnSubAccount1"] = ss.str();
		} else if (tr->Kind == 1) {
			std::stringstream ss;
			INT64 sum = StrToInt(cards[Card]["amountOnSubAccount2"]); //discount accoumt
			ss << sum + tr->Summa;
			cards[Card]["amountOnSubAccount2"] = ss.str();
		} else if (tr->Kind == 2) {
			std::stringstream ss;
			INT64 sum = StrToInt(cards[Card]["amountOnSubAccount3"]); // bonus account
			ss << sum + tr->Summa;
			cards[Card]["amountOnSubAccount3"] = ss.str();
		} else if (tr->Kind == 3) {
			std::stringstream ss;
			INT64 sum = StrToInt(cards[Card]["amountOnSubAccount4"]); // expends account
			ss << sum + tr->Summa;
			cards[Card]["amountOnSubAccount4"] = ss.str();
		}
	}
	SaveCards();
}