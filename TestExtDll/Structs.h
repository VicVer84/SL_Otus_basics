#pragma once
#pragma pack(push, 1)
#include <windows.h>

struct CardInfo {
	WORD size;
	BYTE isDeleted;
	BYTE isNeedWithdraw;
	BYTE isExpired;
	BYTE isInvalid;
	BYTE isManagerConfirm;
	BYTE isBlocked;
	unsigned char blockReason[256];
	unsigned char cardOwner[40];
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
	unsigned char comment[256];
	unsigned char screenComment[256];
	unsigned char printComment[256];

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
