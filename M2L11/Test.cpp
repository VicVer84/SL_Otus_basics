#include "MyVector.h"

#include <iostream>

void Print(MyVector<int>& myVec) {
	bool flag = false;
	// print via iterator
	
	for (auto iter = myVec.begin(); iter != myVec.end(); ++iter) {
		if(!flag) {
			flag = true;
			std::cout << *iter;
		} else {
			std::cout << ',' << *iter;
		}		
	}
	std::cout << std::endl;
}

int main() {
	
	MyVector<int> myVec;
	for(int i = 0; i < 10; ++i) {
		myVec.push_back(i);
	}	
	Print(myVec);

	std::cout << "myVec size: " << myVec.size() << std::endl;
	
	std::cout << "\nerase 3rd element '" << myVec[2] << "' : ";
	myVec.erase(2);
	Print(myVec);
	
	std::cout << "erase 5th element '" << myVec[4] << "' : ";
	myVec.erase(4);
	Print(myVec);
	
	std::cout << "erase 7th element '" << myVec[6] << "' : ";
	myVec.erase(6);
	Print(myVec);
	
	std::cout << "\ninsert 10 to begin: ";
	myVec.insert(0, 10);
	Print(myVec);
	
	std::cout << "insert 20 to mid  : ";
	myVec.insert(4, 20);
	Print(myVec);
	
	std::cout << "insert 30 to end  : ";
	myVec.insert(9, 30);
	Print(myVec);
	
	return 0;
}