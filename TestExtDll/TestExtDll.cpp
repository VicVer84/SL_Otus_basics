
#include "pch.h" // use pch.h in Visual Studio 2019
#include "TestExtDll.h"






//char* CSTR = new char[100000];

void Init() {
	Logger logger("Init");
	logger.AddLogCrit("Call Init");
	std::ifstream ifs("Cards.txt");
	if (!ifs) {
		logger.AddLog("Cards.txt not found\n");
		logger.AddLog("Creating Cards.txt\n");
		CreateCardsTxt();
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
	/*
	xml = "<ident_info>\n";
	xml += "\t<item_content hint = \"Ваш купон позволяет выбрать 2 товара из первой группы и любой товар из второй.\">\n";
	xml += "\t\t<group name = \"group name\" printname = \"Имя группы\" order = \"1\" maxquant = \"2\">\n";
	xml += "\t\t\t<item code = \"123\" kind = \"summ\" val = \"10.00\" order = \"3\" max = \"3\" default = \"1\" disccode = \"22\" />\n";
	xml += "\t\t\t<item code = \"321\" kind = \"percent\" val = \"10.00\"order = \"2\" max = \"2\" disccode = \"123\" />\n";
	xml += "\t\t\t<item code = \"213\" kind = \"price\" val = \"10\" order = \"10\" max = \"1\" />\n";
	xml += "\t\t</group>\n";
	xml += "\t\t<group name = \"group name2\" printname = \"Бренди\" order = \"2\">\n";
	xml += "\t\t\t<item code = \"117\" kind = \"percent\" val = \"1000\" order = \"3\" disccode = \"22\" />\n";
	xml += "\t\t\t<item code = \"118\" kind = \"percent\" val = \"1230\" order = \"3\" disccode = \"22\" />\n";
	xml += "\t\t</group>\n";
	xml += "\t</item_content>\n";
	xml += "</ident_info>";
	

	*/
	
	//CopyMemory(OutBuf, xml.c_str(), sizeof(xml.c_str()));
	//OutLen = xml.size();
	//OutKind = 3;
	//OutBuf = reinterpret_cast<const unsigned char*> (xml.c_str());
	//OutBuf = xml.c_str();
	
	/*xml.copy(CSTR, xml.size() + 1);
	CSTR[xml.size()] = '\0';
	OutBuf = CSTR;
	OutLen = xml.size();
	OutKind = 3;
	logger.AddLog("\nCardInfo size: " + std::to_string(sizeof(CardInfo)));
	logger.AddLog("\nOutBuf: " + std::to_string(xml.size()));*/

/*	for (int i = 0; i < xml.size(); ++i) {
		outfile << outBuf[i]; 
	}
	outfile << '\n' << delim << '\n';*/
	
	/*outfile << "OutBuf:\n";
	for (int i = 0; i < OutLen; ++i) {
		outfile << OutBuf[i];		
	}*/

	Cards card('=');
	logger.AddLog("\nCards:\n" + card.GetCards());

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
	std::stringstream ss;
	ss << "InpBuf:\n";
	char prev = '\r';
	for (size_t i = 0; i < InpLen; ++i) {
		if (!((prev == '\r' && InpBuf[i] == '\n') || (prev == '\n' && InpBuf[i] == '\r'))) {
			ss << InpBuf[i];
		}
		prev = InpBuf[i];
	}
	logger.AddLog(ss.str());
	logger.AddLog("Count: " + std::to_string(Count));

	for (size_t i = 0; i < Count; i++) {
		Transaction* tr = Transactions[i];
		logger.AddLog("Transaction num:" + std::to_string(i));
		logger.AddLog(GetTransaction(tr));	
	}
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

	std::string maximus = "Maximus";
	CBfind(Back, 100, 123, maximus.c_str());
	logger.AddLog("Found Maximus");

	std::string julius = "Julius";
	CBfind(Back, 150, 200, julius.c_str());
	logger.AddLog("Found Julius");
}

