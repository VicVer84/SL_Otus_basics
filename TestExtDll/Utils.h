#pragma once

#include "Structs.h"

#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>

std::string GetCardInfo(const CardInfo* Info);
std::string GetTransaction(const Transaction* tr);
void CreateCardsTxt();
std::string GetEmailInfo(const EmailInfo* einfo);
std::string InpBufToStr(const char* InpBuf, DWORD& InpLen);