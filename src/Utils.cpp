#include "Utils.h"


std::string GetCardInfo(const CardInfo* Info) {
	std::stringstream ss;
	ss << std::left;
	ss << '\n';
	ss << std::setw(30) << "����� ������?: " << ((Info->isDeleted == 0) ? "���" : "��") << '\n';
	ss << std::setw(30) << "���������� ������?: " << ((Info->isNeedWithdraw == 0) ? "���" : "��") << '\n';
	ss << std::setw(30) << "����� ���� ��������?: " << ((Info->isExpired == 0) ? "���" : "��") << '\n';
	ss << std::setw(30) << "����� �� �������������?: " << ((Info->isInvalid == 0) ? "���" : "��") << '\n';
	ss << std::setw(30) << "������������� ���������?: " << ((Info->isManagerConfirm == 0) ? "���" : "��") << '\n';
	ss << std::setw(30) << "����� �������������?: " << ((Info->isBlocked == 0) ? "���" : "��") << '\n';
	ss << std::setw(30) << "������� ���������� �����: " << Info->blockReason << '\n';
	ss << std::setw(30) << "�������� �����: " << Info->cardOwner << '\n';
	ss << std::setw(30) << "������������� ���������: " << Info->ownerId << '\n';
	ss << std::setw(30) << "����� �����: " << Info->accountNum << '\n';
	ss << std::setw(30) << "��� �������������: " << Info->unpayType << '\n';
	ss << std::setw(30) << "����� ������: " << Info->bonusNum << '\n';
	ss << std::setw(30) << "����� ������: " << Info->discountNum << '\n';
	ss << std::setw(30) << "������������ ������ ������: " << Info->maxDiscountAmount << '\n';
	ss << std::setw(30) << "������� 1: " << Info->amountOnSubAccount1 << '\n';
	ss << std::setw(30) << "������� 2: " << Info->amountOnSubAccount2 << '\n';
	ss << std::setw(30) << "������� 3: " << Info->amountOnSubAccount3 << '\n';
	ss << std::setw(30) << "������� 4: " << Info->amountOnSubAccount4 << '\n';
	ss << std::setw(30) << "������� 5: " << Info->amountOnSubAccount5 << '\n';
	ss << std::setw(30) << "������� 6: " << Info->amountOnSubAccount6 << '\n';
	ss << std::setw(30) << "������� 7: " << Info->amountOnSubAccount7 << '\n';
	ss << std::setw(30) << "������� 8: " << Info->amountOnSubAccount8 << '\n';
	ss << std::setw(30) << "���������� � �����: " << Info->comment << '\n';
	ss << std::setw(30) << "����� �� �����: " << Info->screenComment << '\n';
	ss << std::setw(30) << "����� �� ������: " << Info->printComment << '\n';
	return ss.str();
}
std::string GetTransaction(const Transaction* tr) {
	std::stringstream ss;
	ss << std::left;
	ss << '\n';
	ss << std::setw(30) << "Account: " << tr->Account << '\n';
	ss << std::setw(30) << "Card: " << tr->Card << '\n';

	if (tr->Kind == 0) {
		ss << std::setw(30) << "Kind: " << "�����" << '\n';
	}
	else if (tr->Kind == 1) {
		ss << std::setw(30) << "Kind: " << "������" << '\n';
	}
	else if (tr->Kind == 2) {
		ss << std::setw(30) << "Kind: " << "�����" << '\n';
	}
	else if (tr->Kind == 3) {
		ss << std::setw(30) << "Kind: " << "������� �����" << '\n';
	}
	else {
		ss << std::setw(30) << "Kind: " << "����������� ���" << '\n';
	}

	ss << std::setw(30) << "Restaurant: " << tr->Restaurant << '\n';
	ss << std::setw(30) << "RKCheckA: " << tr->RKCheckA << '\n';
	ss << std::setw(30) << "RKDate: " << tr->RKDate << '\n';
	ss << std::setw(30) << "RKUnit: " << tr->RKUnit << '\n';
	ss << std::setw(30) << "Summa: " << tr->Summa << '\n';
	ss << std::setw(30) << "UID: " << tr->UID << '\n';
	ss << std::setw(30) << "VatPrcA: " << tr->VatPrcA << '\n';
	ss << std::setw(30) << "VatPrcA: " << tr->VatSumA << '\n';
	ss << std::setw(30) << "VatPrcA: " << tr->VatPrcB << '\n';
	ss << std::setw(30) << "VatPrcA: " << tr->VatSumB << '\n';
	ss << std::setw(30) << "VatPrcA: " << tr->VatPrcC << '\n';
	ss << std::setw(30) << "VatPrcA: " << tr->VatSumC << '\n';
	ss << std::setw(30) << "VatPrcA: " << tr->VatPrcD << '\n';
	ss << std::setw(30) << "VatPrcA: " << tr->VatSumD << '\n';
	ss << std::setw(30) << "VatPrcA: " << tr->VatPrcE << '\n';
	ss << std::setw(30) << "VatPrcA: " << tr->VatSumE << '\n';
	ss << std::setw(30) << "VatPrcA: " << tr->VatPrcF << '\n';
	ss << std::setw(30) << "VatPrcA: " << tr->VatSumF << '\n';
	ss << std::setw(30) << "VatPrcA: " << tr->VatPrcG << '\n';
	ss << std::setw(30) << "VatPrcA: " << tr->VatSumG << '\n';
	ss << std::setw(30) << "VatPrcA: " << tr->VatPrcH << '\n';
	ss << std::setw(30) << "VatPrcA: " << tr->VatSumH << '\n';
	return ss.str();
}

std::string GetEmailInfo(const EmailInfo* einfo) {
	std::stringstream ss;
	ss << std::left;
	ss << '\n';
	ss << std::setw(30) << "Account: " << einfo->accountNum << '\n';
	ss << std::setw(30) << "Card: " << einfo->cardNum << '\n';
	ss << std::setw(30) << "Owner: " << einfo->OwnerName << '\n';
	return ss.str();
}

std::string InpBufToStr(const char* InpBuf, DWORD& InpLen) {
	std::stringstream ss;
	ss << "InpBuf:\n";

	char prev = '\r';
	for (size_t i = 0; i < (size_t)InpLen; ++i) {
		if (!((prev == '\r' && InpBuf[i] == '\n') || (prev == '\n' && InpBuf[i] == '\r'))) {
			ss << InpBuf[i];
		}
		prev = InpBuf[i];
	}
	return ss.str();
}

std::string PrintTimeNow() {
	time_t rawtime;
	struct tm* timeinfo = new tm;
	char buffer[80];

	time(&rawtime);
	localtime_s(timeinfo, &rawtime);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
	delete timeinfo;

	return buffer;
}
INT64 StrToInt(std::string num) {
	INT64 number;
	std::istringstream iss(num);
	iss >> number;
	if (iss.fail()) {
		return 0;
	}
	return number;
}