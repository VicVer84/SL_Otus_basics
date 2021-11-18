
#include "LibFunc.h"


int main () {
	TestExtDll::Init(std::cout);
	TestExtDll::GetCardInfoEx(std::cout);
	TestExtDll::GetCardImageEx(std::cout);
	TestExtDll::FindCardsL(std::cout);
	TestExtDll::FindEmail(std::cout);
	TestExtDll::TransactionsEx(std::cout);
	TestExtDll::Done(std::cout);
	return 0;
}