
#include "LibFunc.h"
#include "Utils.h"

typedef void (*v_ptr)();
typedef int (*CardInfo_ptr)(INT64, DWORD, DWORD, CardInfo*, const char*, DWORD, WORD, const char*, DWORD& , WORD&);
typedef int (*CardImage_ptr)(INT64, CardImageInfo*);

typedef void (*FindCardsL_ptr)(const char*, void (__stdcall *CBFind_ptr)(std::vector<FindInfo>*, DWORD, INT64, char*), std::vector<FindInfo>*);
typedef int (*FindEmail_ptr)(const char*, EmailInfo*);
typedef int (*TransactionsEx_ptr)(DWORD, Transaction* Transactions[], const char*, DWORD, WORD, void*, DWORD&, WORD&);



namespace TestExtDll {

	void Init(std::ostream& os) {
		HINSTANCE hDLL = ::LoadLibrary("TestExtDll.dll");
		if (!hDLL) {
			os << "Could not load the dynamic library" << std::endl;
			return;
		}

		v_ptr init = (v_ptr)::GetProcAddress(hDLL, "Init");
		if (!init) {
			os << "could not locate the function" << std::endl;
			return;
		}
		init();
		
		os << "Init" << std::endl;

		::FreeLibrary(hDLL);
	}
	
	void Done(std::ostream& os) {
		HINSTANCE hDLL = ::LoadLibrary("TestExtDll.dll"); // 310 MB
		if (!hDLL) {
			os << "Could not load the dynamic library" << std::endl;
			return;
		}

		v_ptr done = (v_ptr)::GetProcAddress(hDLL, "Done");
		if (!done) {
			os << "could not locate the function" << std::endl;
			return;
		}
		done();
		
		os << "Done" << std::endl;

		::FreeLibrary(hDLL);
	}
	
	int GetCardInfoEx(std::ostream& os){
		HINSTANCE hDLL = ::LoadLibrary("TestExtDll.dll");
		if (!hDLL) {
			os << "Could not load the dynamic library" << std::endl;
			return 1;
		}

		CardInfo_ptr getCardInfoEx = (CardInfo_ptr)::GetProcAddress(hDLL, "GetCardInfoEx");
		if (!getCardInfoEx) {
			os << "could not locate the function" << std::endl;
			return 1;
		}		
		
		
		INT64 Card = 1;
		DWORD Restaurant = 1;
		DWORD UnitNo = 1;	
		CardInfo info;
		info.size = 1164;
		const char* InpBuf = "";
		DWORD InpLen = 0;
		WORD InpKind = 0;
		const char* OutBuf = "";
		DWORD OutLen = 0;
		WORD OutKind = 0;				
		
		int result = getCardInfoEx(Card, Restaurant, UnitNo, &info, InpBuf, InpLen, InpKind, OutBuf, OutLen, OutKind);
		os << "GetCardInfoEx -> result: " << result << std::endl << GetCardInfo(&info) << std::endl;
		os << std::endl;

		::FreeLibrary(hDLL);

		return result;
	}

	int GetCardImageEx(std::ostream& os) {
		HINSTANCE hDLL = ::LoadLibrary("TestExtDll.dll");
		if (!hDLL) {
			os << "Could not load the dynamic library" << std::endl;
			return 1;
		}

		CardImage_ptr getCardImageEx = (CardImage_ptr)::GetProcAddress(hDLL, "GetCardImageEx");
		if (!getCardImageEx) {
			os << "could not locate the function" << std::endl;
			return 1;
		}		
		
		INT64 Card = 1;
		CardImageInfo info;
		info.size = 258;
		
		int result = getCardImageEx(Card, &info);
		os << "GetCardImageEx -> result: " << result << " filename: " << info.fileName << std::endl;
		os << std::endl;

		::FreeLibrary(hDLL);

		return result;
	}

	//callback function using same convention as in TestExtDll
	void __stdcall CBFind(std::vector<FindInfo>* vec, DWORD count, INT64 card, char* name) {
		FindInfo info;
		info.Card = card;
		info.Name = name;
		(*vec).push_back(info);
	}

	
	std::vector<FindInfo> FindCardsL(std::ostream& os) {
		HINSTANCE hDLL = ::LoadLibrary("TestExtDll.dll");
		if (!hDLL) {
			os << "Could not load the dynamic library" << std::endl;
			return {};
		}

		FindCardsL_ptr findCardsL = (FindCardsL_ptr)::GetProcAddress(hDLL, "FindCardsL");
		if (!findCardsL) {
			os << "could not locate the function" << std::endl;
			return {};
		}
		
		std::vector<FindInfo> vec;

		findCardsL("Owner", &CBFind, &vec);

		for(size_t i = 0; i < vec.size() ; ++i){
			os << "FindInfoL -> Card: " << vec[i].Card << " Name: " << vec[i].Name << std::endl;
		}
		os << std::endl;

		::FreeLibrary(hDLL);
		return vec;
	}

	int FindEmail(std::ostream& os) {
		HINSTANCE hDLL = ::LoadLibrary("TestExtDll.dll");
		if (!hDLL) {
			os << "Could not load the dynamic library" << std::endl;
			return 1;
		}

		FindEmail_ptr findEmail = (FindEmail_ptr)::GetProcAddress(hDLL, "FindEmail");
		if (!findEmail) {
			os << "could not locate the function" << std::endl;
			return 1;
		}
	
		EmailInfo info;
		info.size = 54;

		int result = findEmail("test@test.ru", &info);

		os << "FindEmail -> Account: " << info.accountNum << " Card: " << info.cardNum << " Owner: " << info.OwnerName << std::endl;			
		os << std::endl;

		::FreeLibrary(hDLL);

		return result;
	}
	
	int TransactionsEx(std::ostream& os){
		HINSTANCE hDLL = ::LoadLibrary("TestExtDll.dll");
		if (!hDLL) {
			os << "Could not load the dynamic library" << std::endl;
			return 1;
		}

		TransactionsEx_ptr transactionsEx = (TransactionsEx_ptr)::GetProcAddress(hDLL, "TransactionsEx");
		if (!transactionsEx) {
			os << "could not locate the function" << std::endl;
			return 1;
		}
		
		Transaction tr1;
		tr1.Size = 122;
		tr1.Card = 1;
		tr1.UID = 1;
		tr1.Account = 1;
		tr1.Kind = 0;  //sale
		tr1.Summa = 10;
		tr1.Restaurant = 75;
		tr1.RKDate = 782611;
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
	
		Transaction tr2;
		tr2.Size = 122;
		tr2.Card = 1;
		tr2.UID = 1;
		tr2.Account = 1;
		tr2.Kind = 1; //discount 
		tr2.Summa = 60;
		tr2.Restaurant = 75;
		tr2.RKDate = 782615;
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

		std::vector<Transaction> vec;
		vec.push_back(tr1);
		vec.push_back(tr2);
		
		Transaction* transactions[2];
		
		transactions[0] = &tr1;
		transactions[1] = &tr2;
		
		const char* InpBuf = "";
		DWORD InpLen = 0;
		WORD InpKind = 0;
		void* OutBuf = "";
		DWORD OutLen = 0; 
		WORD OutKind = 0;

		int result = transactionsEx(2, transactions, InpBuf, InpLen, InpKind, OutBuf, OutLen, OutKind);
		
		os << "TransactionsEx -> result: " << result << std::endl;			
		os << std::endl;

		::FreeLibrary(hDLL);

		return result;
	}

}

