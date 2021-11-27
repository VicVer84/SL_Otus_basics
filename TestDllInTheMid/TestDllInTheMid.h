#pragma once

#include "LibFunc.h"
#include "Logger.h"
#include "Structs.h"
#include "Utils.h"


#include <random>
#include <windows.h>


typedef void (__stdcall *CBFind)(void*, DWORD, INT64, const char*);

extern "C" int __declspec(dllexport) __stdcall GetCardInfoEx(INT64 Card, DWORD Restaurant, DWORD UnitNo,
	CardInfo* info, const char* InpBuf, DWORD InpLen, WORD InpKind,
	const char* OutBuf, DWORD &OutLen, WORD &OutKind);

extern "C" int __declspec(dllexport) __stdcall TransactionsEx(DWORD Count,
	Transaction* Transactions[], const char* InpBuf, DWORD InpLen, WORD InpKind,
	const char* OutBuf, DWORD &OutLen, WORD &OutKind);

extern "C" int __declspec(dllexport) __stdcall GetCardImageEx(INT64 Card, CardImageInfo* info);

extern "C" int __declspec(dllexport) __stdcall FindEmail(const char* Email, EmailInfo* emailInfo);

extern "C" void __declspec(dllexport) __stdcall FindCardsL(const char* FindText, CBFind CBfind, void* Back);

extern "C" void __declspec(dllexport) __stdcall Init();

extern "C" void __declspec(dllexport) __stdcall Done();

extern "C" int __declspec(dllexport) __stdcall GetDiscLevelInfoL(int32_t  Account, DiscLevelInfo * info);

extern "C" void __declspec(dllexport) __stdcall AnyInfo(const char* InpBuf, int32_t InpLen, void* OutBuf, int32_t OutLen);

extern "C" void __declspec(dllexport) __stdcall FindAccountsByKind(int Kind, const char* FindText, CBFind CBfind, void* Back);