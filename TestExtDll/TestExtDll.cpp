#include "TestExtDll.h"


void Init() {
	Logger logger("Init");
	logger.AddLogCrit("Call Init");
	std::ifstream ifs("Cards.txt");
	if (!ifs) {
		logger.AddLog("Cards.txt not found\n");
		logger.AddLog("Creating Cards.txt\n");
		Cards::CreateCardsTxt();
	}
}

void Done() {
	Logger logger("Done");
	logger.AddLogCrit("Call Done");
}


std::string xml;

int __cdecl GetCardInfoEx(INT64 Card, DWORD Restaurant, DWORD UnitNo,
					CardInfo* info, const char* InpBuf, DWORD InpLen, WORD InpKind,
					const char* OutBuf, DWORD &OutLen, WORD &OutKind)
{
	Logger logger("GetCardInfoEx");
	logger.AddLog("CardInfo size: " + std::to_string(sizeof(CardInfo)));

	Cards card('=');
	logger.AddLog("\nCards:\n" + card.CardsToString());

	logger.AddLog("Card: " + std::to_string(Card));
	logger.AddLog("Restaurant: " + std::to_string(Restaurant));
	logger.AddLog("UnitNo: " + std::to_string(UnitNo));
	logger.AddLog("InpLen: " + std::to_string(InpLen));
	logger.AddLog("InpKind: " + std::to_string(InpKind));
	
	logger.AddLogCrit(InpBufToStr(InpBuf, InpLen));

	int result = card.GetCard(std::to_string(Card), info);
	
	logger.AddLog("result: " + std::to_string(result));
	logger.AddLog(GetCardInfo(info));
	return result;
}


int TransactionsEx(DWORD Count, Transaction* Transactions[], const char* InpBuf, DWORD InpLen,
					WORD InpKind, void* OutBuf, DWORD &OutLen, WORD &OutKind) 
{
	Logger logger("TransactionsEx");

	logger.AddLog("Transaction size: " + std::to_string(sizeof(Transaction)));

	logger.AddLogCrit(InpBufToStr(InpBuf, InpLen));

	logger.AddLog("Count: " + std::to_string(Count));

	for (size_t i = 0; i < Count; i++) {
		Transaction* tr = Transactions[i];
		logger.AddLog("Transaction num:" + std::to_string(i));
		logger.AddLog(GetTransaction(tr));	
	}
	Cards card('=');
	card.UpdateCards(Count, Transactions);
	return 0;
}

int GetCardImageEx(INT64 Card, CardImageInfo* info) {
	Logger logger("GetCardImageEx");
	logger.AddLog("CardImageInfo size: " + std::to_string(sizeof(CardImageInfo)));

	std::string strings[4];
	
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist3(0, 3);
	
	strings[0] = ".\\Images\\Gannibal.jpeg";
	strings[1] = ".\\Images\\God.jpeg";
	strings[2] = ".\\Images\\Sertificate.jpg";
	strings[3] = ".\\Images\\Jedi.jpg";

	int k = dist3(rng);
	char path[256];
	strcpy_s(path, strings[k].c_str());

	CopyMemory(info->fileName, path, sizeof(path));
	logger.AddLog(strings[k]);	
	return 0;
}

int FindEmail(const char* Email, EmailInfo* emailInfo) {
	Logger logger("FindEmail");

	Cards cards('=');

	logger.AddLog("Email: " + std::string(Email));
	logger.AddLog("EmailInfo size: " + std::to_string(sizeof(EmailInfo)));
	
	int result = cards.FindByEmail(std::string(Email), emailInfo);

	logger.AddLog(GetEmailInfo(emailInfo));
	return result;
}


void FindCardsL(const char* FindText, CBFind CBfind, void* Back) {
	Logger logger("FindCardsL");
	Cards cards('=');
	cards.FindOwnerByNamePart(FindText, CBfind, Back);
}

int GetDiscLevelInfoL(int32_t  Account, DiscLevelInfo* info) {
	return 1;
}

void AnyInfo(const char* InpBuf, int32_t InpLen, void* OutBuf, int32_t OutLen) {}

void FindAccountsByKind(int Kind, const char* FindText, CBFind CBfind, void* Back) {}