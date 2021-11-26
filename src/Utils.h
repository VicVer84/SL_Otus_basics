#pragma once

#include "Structs.h"

#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

std::string GetCardInfo(const CardInfo* Info);
std::string GetTransaction(const Transaction* tr);
std::string GetEmailInfo(const EmailInfo* einfo);
std::string InpBufToStr(const char* InpBuf, DWORD& InpLen);
std::string PrintTimeNow();
INT64 StrToInt(std::string num);