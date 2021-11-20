#include "LibFunc.h"
#include "Structs.h"

#include <windows.h>
#include <gtest/gtest.h>

TEST(TestExtDllTest, Init) {
	const std::string expected = "Init";
	std::stringstream ss;
	TestExtDll::Init(ss);

	ASSERT_EQ(ss.str(), expected);
}

TEST(TestExtDllTest, Done) {
	const std::string expected = "Done";
	std::stringstream ss;
	TestExtDll::Done(ss);

	ASSERT_EQ(ss.str(), expected);
}

TEST(TestExtDllTest, GetCardInfoEx) {
	CardInfo info{};
	CardInfo expected{};
	INT64 Card = 1;
	int result = TestExtDll::GetCardInfoEx(&info, Card);
	
	ASSERT_EQ(result, 0);

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
	std::set<std::string> expected = {
		".\\Images\\Gannibal.jpeg",
		".\\Images\\God.jpeg",
		".\\Images\\Sertificate.jpg",
		".\\Images\\Jedi.jpg"
	};

	CardImageInfo info{};
	INT64 Card = 1;

	int result = TestExtDll::GetCardImageEx(&info, Card);
	ASSERT_EQ(result, 0);

	std::stringstream ss;
	ss << info.fileName;
	auto it = expected.find(ss.str());
	ASSERT_TRUE(expected.find(ss.str()) != expected.end());
}
TEST(TestExtDllTest, FindCardsL) {
	std::vector<FindInfo> vec;
	std::string Findstr = "Owner";
	vec = TestExtDll::FindCardsL(Findstr);

	for (size_t i = 0; i < vec.size(); ++i) {
		CardInfo info{};
		INT64 Card = vec[i].Card;
		TestExtDll::GetCardInfoEx(&info, Card);
		std::stringstream ss;
		ss << info.cardOwner;
		ASSERT_EQ(ss.str(), vec[i].Name);
	}
}

TEST(TestExtDllTest, FindEmail) {
	std::string Findstr = "test@test.ru";
	EmailInfo einfo{};
	int result = TestExtDll::FindEmail(Findstr, &einfo);
	ASSERT_EQ(result, 0);

	CardInfo info{};
	TestExtDll::GetCardInfoEx(&info, einfo.cardNum);

	ASSERT_TRUE(memcmp(einfo.OwnerName, info.cardOwner, sizeof(einfo.OwnerName)));
	ASSERT_EQ(einfo.accountNum, info.accountNum);
}

TEST(TestExtDllTest, TransactionsEx) {
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

	CardInfo expected{};
	int result = TestExtDll::GetCardInfoEx(&expected, Card);
	ASSERT_EQ(result, 0);
	expected.amountOnSubAccount1 += sum1;
	expected.amountOnSubAccount2 += sum2;

	result = TestExtDll::TransactionsEx(2, transactions);
	ASSERT_EQ(result, 0);

	CardInfo info{};
	result = TestExtDll::GetCardInfoEx(&info, Card);
	ASSERT_EQ(result, 0);
	ASSERT_EQ(info.amountOnSubAccount1, expected.amountOnSubAccount1);
	ASSERT_EQ(info.amountOnSubAccount2, expected.amountOnSubAccount2);
}

int main (int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}