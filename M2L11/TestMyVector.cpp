#include "MyVector.h"

#include <iostream>

int main() {
	
	MyVector<int> myVec;
	for(int i = 0; i < 10; ++i) {
		myVec.push_back(i);
	}
	
	for(auto i = 0; i < myVec.size(); ++i) {
		std::cout << myVec[i] << ','; 
	}
	std::cout << std::endl; 
	
	myVec.insert(5, 20);
	
	for(auto i : myVec) {
		std::cout << i << ','; 
	}
	std::cout << std::endl; 
	
	myVec.erase(5);
	
	for(auto i : myVec) {
		std::cout << i << ','; 
	}
	std::cout << std::endl; 
	
	return 0;
}