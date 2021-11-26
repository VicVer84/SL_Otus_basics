#pragma once

#include <windows.h>

#pragma pack(push, 1)
struct CardInfo {
	WORD size;
	BYTE isDeleted;
	BYTE isNeedWithdraw;
	BYTE isExpired;
	BYTE isInvalid;
	BYTE isManagerConfirm;
	BYTE isBlocked;
	unsigned char blockReason[256] = {0};
	unsigned char cardOwner[40] = {0};
	INT64 ownerId;
	DWORD accountNum;
	DWORD unpayType;
	WORD bonusNum;
	WORD discountNum;
	INT64 maxDiscountAmount;
	INT64 amountOnSubAccount1;
	INT64 amountOnSubAccount2;
	INT64 amountOnSubAccount3;
	INT64 amountOnSubAccount4;
	INT64 amountOnSubAccount5;
	INT64 amountOnSubAccount6;
	INT64 amountOnSubAccount7;
	INT64 amountOnSubAccount8;
	unsigned char comment[256] = {0};
	unsigned char screenComment[256]= {0};
	unsigned char printComment[256] = {0};
	
	bool operator==(const CardInfo rhs) const {
		return (size == rhs.size
			&& isDeleted == rhs.isDeleted
			&& isNeedWithdraw == rhs.isNeedWithdraw
			&& isExpired == rhs.isExpired
			&& isInvalid == rhs.isInvalid
			&& isManagerConfirm == rhs.isManagerConfirm
			&& isBlocked == rhs.isBlocked
			&& (memcmp(blockReason, rhs.blockReason, sizeof(blockReason)) == 0)
			&& (memcmp(cardOwner, rhs.cardOwner, sizeof(cardOwner)) == 0)
			&& ownerId == rhs.ownerId
			&& accountNum == rhs.accountNum
			&& unpayType == rhs.unpayType
			&& bonusNum == rhs.bonusNum
			&& discountNum == rhs.discountNum
			&& maxDiscountAmount == rhs.maxDiscountAmount
			&& amountOnSubAccount1 == rhs.amountOnSubAccount1
			&& amountOnSubAccount2 == rhs.amountOnSubAccount2
			&& amountOnSubAccount3 == rhs.amountOnSubAccount3
			&& amountOnSubAccount4 == rhs.amountOnSubAccount4
			&& amountOnSubAccount5 == rhs.amountOnSubAccount5
			&& amountOnSubAccount6 == rhs.amountOnSubAccount6
			&& amountOnSubAccount7 == rhs.amountOnSubAccount7
			&& amountOnSubAccount8 == rhs.amountOnSubAccount8
			&& (memcmp(comment, rhs.comment, sizeof(comment)) == 0)
			&& (memcmp(screenComment, rhs.screenComment, sizeof(screenComment)) == 0)
			&& (memcmp(printComment, rhs.printComment, sizeof(printComment)) == 0));
	}
};

struct Transaction {
	WORD Size;  //122
	INT64 Card;
	INT64 UID; //Идентификатор владельца карты  
	DWORD Account;   // номер счёта
	BYTE Kind;
	INT64 Summa;
	WORD Restaurant;
	DWORD RKDate;
	BYTE RKUnit;
	DWORD RKCheckA;

	INT64 VatSumA;
	WORD VatPrcA;
	INT64 VatSumB;
	WORD VatPrcB;
	INT64 VatSumC;
	WORD VatPrcC;
	INT64 VatSumD;
	WORD VatPrcD;
	INT64 VatSumE;
	WORD VatPrcE;
	INT64 VatSumF;
	WORD VatPrcF;
	INT64 VatSumG;
	WORD VatPrcG;
	INT64 VatSumH;
	WORD VatPrcH;
};

struct CardImageInfo {
	WORD size;
	unsigned char fileName[256];
};

struct EmailInfo {
	WORD size;
	DWORD accountNum;
	INT64 cardNum;
	unsigned char OwnerName[40];
};

struct DiscLevelInfo {
	WORD size;
	unsigned char CurrentDiscLvlName[40];
	unsigned char NextDiscLvlName[40];
	INT64 SumToNextLvl;
};
#pragma pack(pop)