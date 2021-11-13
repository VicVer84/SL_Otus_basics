
#pragma once
#include "Structs.h"
#include "Logger.h"
#include "Cards.h"
#include "Structs.h"
#include "Utils.h"

#include <random>
#include <exception>
#include <utility>
#include <limits>
#include <iostream>


typedef void (__stdcall *CBFind)(void*, DWORD, INT64, const char*);

extern "C" int __declspec(dllexport) __cdecl GetCardInfoEx(INT64 Card, DWORD Restaurant, DWORD UnitNo,
	CardInfo* info, const char* InpBuf, DWORD InpLen, WORD InpKind,
	const char* OutBuf, DWORD &OutLen, WORD &OutKind);

extern "C" int __declspec(dllexport) __cdecl TransactionsEx(DWORD Count,
	Transaction* Transactions[], const char* InpBuf, DWORD InpLen, WORD InpKind,
	void* OutBuf, DWORD &OutLen, WORD &OutKind);

extern "C" int __declspec(dllexport) __cdecl GetCardImageEx(INT64 Card, CardImageInfo* info);

extern "C" int __declspec(dllexport) __cdecl FindEmail(const char* Email, EmailInfo* emailInfo);

extern "C" void __declspec(dllexport) __cdecl FindCardsL(const char* FindText, CBFind CBfind, void* Back);

extern "C" void __declspec(dllexport) __cdecl Init();

extern "C" void __declspec(dllexport) __cdecl Done();

