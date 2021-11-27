#pragma once

#include "Structs.h"

#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

std::string GetCardInfo(const CardInfo*);
std::string GetTransaction(const Transaction*);
std::string GetEmailInfo(const EmailInfo*);
std::string BufToStr(const char*, DWORD&);
std::string PrintTimeNow();
INT64 StrToInt(std::string);