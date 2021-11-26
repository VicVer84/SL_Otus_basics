#include "TestExtDllTest.h"

//callback function using same convention as in TestExtDll
void __stdcall CBFind_(void* vec, DWORD count, INT64 card, const char* name) {
	FindInfo info;
	info.Card = card;
	info.Name = name;
	std::vector<FindInfo> &myVec = *reinterpret_cast<std::vector<FindInfo>*>(vec);
	myVec.push_back(info);
}

TEST(TestExtDllTest, Init) {
	Logger logger(TESTEXTDLLTEST, "Test Init");
	const std::string expected = "Init";

	std::stringstream ss;
	
	LoadExtDll TestExtDll(DLLNAME.c_str(), ss);
	
	TestExtDll.Init(ss);

	logger.AddLog(ss.str());

	ASSERT_EQ(ss.str(), expected);
}

TEST(TestExtDllTest, Done) {
	Logger logger(TESTEXTDLLTEST, "Test Done");
	const std::string expected = "Done";

	
	std::stringstream ss;

	LoadExtDll TestExtDll(DLLNAME.c_str(), ss);

	TestExtDll.Done(ss);

	logger.AddLog(ss.str());

	ASSERT_EQ(ss.str(), expected);
}

TEST(TestExtDllTest, GetCardInfoEx) {
	Logger logger(TESTEXTDLLTEST, "Test GetCardInfoEx");
	auto& ofs = logger.GetStream();
	std::stringstream ss;
	LoadExtDll TestExtDll(DLLNAME.c_str(), ofs);

	INT64 Card = 1;
	DWORD Restaurant = 1;
	DWORD UnitNo = 1;	
	CardInfo info{};
		info.size = 1164;
	const char* InpBuf = "";
	DWORD InpLen = 0;
	WORD InpKind = 0;
	const char* OutBuf = "";
	DWORD OutLen = 0;
	WORD OutKind = 0;	
	
	
	int result = TestExtDll.GetCardInfoEx(Card, Restaurant, UnitNo, &info, InpBuf, InpLen, InpKind, OutBuf, OutLen, OutKind, ofs);
	
	ASSERT_EQ(result, 0);

	CardInfo expected{};
	expected.size = 1164;
	expected.isDeleted = 0;
	expected.isNeedWithdraw = 0;
	expected.isExpired = 0;
	expected.isInvalid = 0;
	expected.isManagerConfirm = 0;
	expected.isBlocked = 0;	
	CopyMemory((&expected)->blockReason, "0", sizeof("0"));
	CopyMemory((&expected)->cardOwner, "TestOwner", sizeof("TestOwner"));
	expected.ownerId = 1;
	expected.accountNum = 1;
	expected.unpayType = 0;
	expected.bonusNum = 0;
	expected.discountNum = 0;
	expected.maxDiscountAmount = 100000000;
	expected.amountOnSubAccount1 = info.amountOnSubAccount1;
	expected.amountOnSubAccount2 = info.amountOnSubAccount2;
	expected.amountOnSubAccount3 = 3000;
	expected.amountOnSubAccount4 = 4000;
	expected.amountOnSubAccount5 = 5000;
	expected.amountOnSubAccount6 = 6000;
	expected.amountOnSubAccount7 = 7000;
	expected.amountOnSubAccount8 = 8000;

	ASSERT_EQ(info, expected);
}

TEST(TestExtDllTest, GetCardImageEx) {
	Logger logger(TESTEXTDLLTEST, "Test GetCardImageEx");
	auto& ofs = logger.GetStream();

	LoadExtDll TestExtDll(DLLNAME.c_str(), ofs);

	std::set<std::string> expected = {
		".\\Images\\Gannibal.jpeg",
		".\\Images\\God.jpeg",
		".\\Images\\Sertificate.jpg",
		".\\Images\\Jedi.jpg"
	};

	CardImageInfo info{};
	info.size = 258;
	INT64 Card = 1;

	int result = TestExtDll.GetCardImageEx(Card , &info, ofs);
	ASSERT_EQ(result, 0);

	std::stringstream ss;
	ss << info.fileName;
	auto it = expected.find(ss.str());
	ASSERT_TRUE(expected.find(ss.str()) != expected.end());
}

TEST(TestExtDllTest, FindCardsL) {
	Logger logger(TESTEXTDLLTEST, "Test FindCardsL");
	auto& ofs = logger.GetStream();

	LoadExtDll TestExtDll(DLLNAME.c_str(), ofs);

	std::vector<FindInfo> vec;
	std::string Findstr = "Owner";

	TestExtDll.FindCardsL(Findstr.c_str(), &CBFind_, &vec, ofs);

	const char* InpBuf = "";
	DWORD InpLen = 0;
	WORD InpKind = 0;
	const char* OutBuf = "";
	DWORD OutLen = 0;
	WORD OutKind = 0;

	for (size_t i = 0; i < vec.size(); ++i) {
		CardInfo info{};
		INT64 Card = vec[i].Card;
		TestExtDll.GetCardInfoEx(Card, 1, 1, &info, InpBuf, InpLen, InpKind, OutBuf, OutLen, OutKind, ofs);
		std::stringstream ss;
		ss << info.cardOwner;
		ASSERT_EQ(ss.str(), vec[i].Name);
	}
}

TEST(TestExtDllTest, FindEmail) {
	Logger logger(TESTEXTDLLTEST, "Test FindEmail");
	auto& ofs = logger.GetStream();

	LoadExtDll TestExtDll(DLLNAME.c_str(), ofs);

	std::string Findstr = "test@test.ru";
	EmailInfo einfo{};
	int result = TestExtDll.FindEmail(Findstr.c_str(), &einfo, ofs);
	ASSERT_EQ(result, 0);

	CardInfo info{};
	info.size = 54;
	DWORD OutLen = 0;
	WORD OutKind = 0;

	result = TestExtDll.GetCardInfoEx(einfo.cardNum, 1, 1, &info, "",0,0,"", OutLen, OutKind, ofs);
	ASSERT_EQ(result, 0);

	ASSERT_TRUE(memcmp(einfo.OwnerName, info.cardOwner, sizeof(einfo.OwnerName)));
	ASSERT_EQ(einfo.accountNum, info.accountNum);
}

TEST(TestExtDllTest, TransactionsEx) {
	Logger logger(TESTEXTDLLTEST, "Test TransactionsEx");
	auto& ofs = logger.GetStream();

	LoadExtDll TestExtDll(DLLNAME.c_str(), ofs);

	INT64 Card = 1;
	INT64 sum1 = 60;
	INT64 sum2 = 10;


	Transaction tr1{};
	tr1.Size = 122;
	tr1.Card = Card;
	tr1.UID = 1;
	tr1.Account = 1;
	tr1.Kind = 0;  //sale
	tr1.Summa = sum1;
	tr1.Restaurant = 75;
	tr1.RKDate = 44520;
	tr1.RKUnit = 53;
	tr1.RKCheckA = 10;
	tr1.VatSumA = 0;
	tr1.VatPrcA = 0;
	tr1.VatSumB = 0;
	tr1.VatPrcB = 0;
	tr1.VatSumC = 0;
	tr1.VatPrcC = 0;
	tr1.VatSumD = 0;
	tr1.VatPrcD = 0;
	tr1.VatSumE = 0;
	tr1.VatPrcE = 0;
	tr1.VatSumF = 0;
	tr1.VatPrcF = 0;
	tr1.VatSumG = 0;
	tr1.VatPrcG = 0;
	tr1.VatSumH = 0;
	tr1.VatPrcH = 0;

	Transaction tr2{};
	tr2.Size = 122;
	tr2.Card = Card;
	tr2.UID = 1;
	tr2.Account = 1;
	tr2.Kind = 1; //discount 
	tr2.Summa = sum2;
	tr2.Restaurant = 75;
	tr2.RKDate = 44520;
	tr2.RKUnit = 53;
	tr2.RKCheckA = 10;
	tr2.VatSumA = 0;
	tr2.VatPrcA = 0;
	tr2.VatSumB = 0;
	tr2.VatPrcB = 0;
	tr2.VatSumC = 0;
	tr2.VatPrcC = 0;
	tr2.VatSumD = 0;
	tr2.VatPrcD = 0;
	tr2.VatSumE = 0;
	tr2.VatPrcE = 0;
	tr2.VatSumF = 0;
	tr2.VatPrcF = 0;
	tr2.VatSumG = 0;
	tr2.VatPrcG = 0;
	tr2.VatSumH = 0;
	tr2.VatPrcH = 0;

	Transaction* transactions[2]{};

	transactions[0] = &tr1;
	transactions[1] = &tr2;

	const char* InpBuf = "";
	DWORD InpLen = 0;
	WORD InpKind = 0;
	const char* OutBuf = "";
	DWORD OutLen = 0;
	WORD OutKind = 0;

	CardInfo expected{};
	int result = TestExtDll.GetCardInfoEx(Card, 1, 1, &expected, InpBuf, InpLen, InpKind, OutBuf, OutLen, OutKind, ofs);
	ASSERT_EQ(result, 0);
	expected.amountOnSubAccount1 += sum1; 
	expected.amountOnSubAccount2 += sum2;

	result = TestExtDll.TransactionsEx(2, transactions, InpBuf, InpLen, InpKind, OutBuf, OutLen, OutKind, ofs);
	ASSERT_EQ(result, 0);

	CardInfo info{};
	result = TestExtDll.GetCardInfoEx(Card, 1, 1, &info, InpBuf, InpLen, InpKind, OutBuf, OutLen, OutKind, ofs);
	ASSERT_EQ(result, 0);
	ASSERT_EQ(info.amountOnSubAccount1, expected.amountOnSubAccount1);
	ASSERT_EQ(info.amountOnSubAccount2, expected.amountOnSubAccount2);
}


int main (int argc, char** argv) {
	std::ifstream ifs("TestExtDllTest.ini");
	std::string str;
	std::cout << ifs.is_open();
	if (ifs.is_open()) {
		std::getline(ifs, str);
		if (str.size() <= 40) {
			DLLNAME = str;
		}
	}
	std::cout << "Loaded " << DLLNAME << ", to change dll name write it in TestExtDllTest.ini";
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}