#include "MyVector.h"

#include <iostream>
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <memory>
#include <vector>

TEST(MyVector, creation_empty) {
	const size_t expected = 0;
	MyVector<int> myVec;
	
	std::vector<int> v;

	ASSERT_EQ(myVec.size(), expected);
}

TEST(MyVector, test_size) {
	const size_t expected = 5;
	MyVector<int> myVec(5);
	
	ASSERT_EQ(myVec.size(), expected);
}

TEST(MyVector, test_push_back) {
	const size_t expected = 10;
	MyVector<int> myVec;
	
	for(int i = 0; i < 10; ++i) {
		myVec.push_back(i);
	}
	
	ASSERT_EQ(myVec.size(), expected);
	std::stringstream ss;
	for(auto i : myVec) {
		ss << i << ',';
	}
	ASSERT_EQ(ss.str(), "0,1,2,3,4,5,6,7,8,9,");
}

TEST(MyVector, test_insert_begin) {
	const size_t expected = 11;
	MyVector<int> myVec;
	
	for(int i = 0; i < 10; ++i) {
		myVec.push_back(i);
	}
	myVec.insert(0,20);
	
	std::stringstream ss;	
	for(auto i : myVec) {
		ss << i << ',';
	}		
	
	ASSERT_EQ(myVec.size(), expected);	
	ASSERT_EQ(ss.str(), "20,0,1,2,3,4,5,6,7,8,9,");
}

TEST(MyVector, test_insert_mid) {
	const size_t expected = 11;
	MyVector<int> myVec;
	
	for(int i = 0; i < 10; ++i) {
		myVec.push_back(i);
	}
	myVec.insert(5,20);	
	
	std::stringstream ss;
	for(auto i : myVec) {
		ss << i << ',';
	}	
	
	ASSERT_EQ(myVec.size(), expected);	
	ASSERT_EQ(ss.str(), "0,1,2,3,4,20,5,6,7,8,9,");
}

TEST(MyVector, test_insert_end) {
	const size_t expected = 11;
	MyVector<int> myVec;
	
	for(int i = 0; i < 10; ++i) {
		myVec.push_back(i);
	}
	myVec.insert(10,20);		
	
	std::stringstream ss;
	for(auto i : myVec) {
		ss << i << ',';
	}	
	
	ASSERT_EQ(myVec.size(), expected);	
	ASSERT_EQ(ss.str(), "0,1,2,3,4,5,6,7,8,9,20,");
}

TEST(MyVector, test_erase_begin) {
	const size_t expected = 9;
	MyVector<int> myVec;
	
	for(int i = 0; i < 10; ++i) {
		myVec.push_back(i);
	}
	myVec.erase(0);
	
	std::stringstream ss;
	for(auto i : myVec) {
		ss << i << ',';
	}	
	
	ASSERT_EQ(myVec.size(), expected);	
	ASSERT_EQ(ss.str(), "1,2,3,4,5,6,7,8,9,");
}

TEST(MyVector, test_erase_mid) {
	const size_t expected = 9;
	MyVector<int> myVec;
	
	for(int i = 0; i < 10; ++i) {
		myVec.push_back(i);
	}
	myVec.erase(5);
	
	std::stringstream ss;
	for(auto i : myVec) {
		ss << i << ',';
	}	
	
	ASSERT_EQ(myVec.size(), expected);	
	ASSERT_EQ(ss.str(), "0,1,2,3,4,6,7,8,9,");
}

TEST(MyVector, test_erase_end) {
	const size_t expected = 9;
	MyVector<int> myVec;
	
	for(int i = 0; i < 10; ++i) {
		myVec.push_back(i);
	}
	myVec.erase(9);
	
	std::stringstream ss;
	for(auto i : myVec) {
		ss << i << ',';
	}	
	
	ASSERT_EQ(myVec.size(), expected);	
	ASSERT_EQ(ss.str(), "0,1,2,3,4,5,6,7,8,");
}

TEST(MyVector, test_move) {
	const size_t expected = 1;
	MyVector<std::string> myVec;
	MyVector<std::string> moveToVec;
	
	{
		std::string s = "StringToMove";	
		myVec.push_back(std::move(s));
	}
	moveToVec = std::move(myVec);
	
	
	ASSERT_EQ(myVec.size(), 0);
	ASSERT_EQ(moveToVec.size(), expected);
	ASSERT_EQ(moveToVec[0], "StringToMove");
}

TEST(MySLList, test_copy) {
	const int expected = 1;
	MyVector<std::string> myVec;
	MyVector<std::string> copyToVec;

	{
		std::string s = "StringToMove";
		myVec.push_back(std::move(s));
	}
	copyToVec = myVec;


	ASSERT_EQ(myVec.size(), expected);
	ASSERT_EQ(myVec[0], "StringToMove");
	ASSERT_EQ(copyToVec.size(), expected);
	ASSERT_EQ(copyToVec[0], "StringToMove");
}

TEST(MyVector, full_erase) {
	const size_t expected = 0;
	MyVector<int> myVec;
	
	for(int i = 0; i < 10; ++i) {
		myVec.push_back(i);
	}
	ASSERT_EQ(myVec.size(), 10);
	
	for(int i = 0; i < 10; ++i) {
		myVec.erase(0);
	}	
	ASSERT_EQ(myVec.size(), 0);
}

TEST(MyVector, test_destructor_calls_by_erase) {
	const size_t expected = 0;
	MyVector<std::shared_ptr<int>> myVec;

	std::shared_ptr<int> p = std::make_shared<int>(6);

	for (int i = 0; i < 10; ++i) {
		myVec.push_back(p);
	}
	ASSERT_EQ(p.use_count(), 11);
	ASSERT_EQ(myVec.size(), 10);

	for (int i = 0; i < 10; ++i) {
		myVec.erase(0);
	}
	ASSERT_EQ(myVec.size(), 0);
	ASSERT_EQ(p.use_count(), 1);
}

TEST(MyVector, test_destructor) {
	const size_t expected = 0;
	
	std::shared_ptr<int> p = std::make_shared<int>(6);

	{
		MyVector<std::shared_ptr<int>> myVec;
		for (int i = 0; i < 10; ++i) {
			myVec.push_back(p);
		}
		ASSERT_EQ(p.use_count(), 11);
		ASSERT_EQ(myVec.size(), 10);
	}

	ASSERT_EQ(p.use_count(), 1);
}


int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}