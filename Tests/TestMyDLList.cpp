#include "MyDLList.h"

#include <iostream>
#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <string>

TEST(MyDLList, push_front) {
	MyDLList<int> list;
	
	list.push_front(1);	
	ASSERT_EQ(list.front()->value, 1);
	
	list.push_front(2);	
	ASSERT_EQ(list.front()->value, 2);
	
	list.push_front(3);	
	ASSERT_EQ(list.front()->value, 3);
		
	
	const std::vector<int> expected = {3, 2, 1};
	std::vector<int> result;
	for (auto node = list.front(); node; node = node->next) {
		result.push_back(node->value);
	}
	ASSERT_EQ(result, expected);
	ASSERT_EQ(list.size(), 3);
}

TEST(MyDLList, insert) {
	MyDLList<std::string> list;

	list.push_front("a");
	auto first_node = list.front();

	ASSERT_EQ(first_node->value, "a");

	list.insert(first_node, "b");	//insert "b" before "a"
	
	{
		const std::vector<std::string> expected1 = {"b", "a"};
		std::vector<std::string> result;
		for (auto node = list.front(); node; node = node->next) {
			result.push_back(node->value);
		}
		ASSERT_EQ(result, expected1);
		ASSERT_EQ(list.size(), 2);
	}
	
	list.insert(first_node, "c"); // first_node still point to "a" node so "c" will be inserted before "a"
	
	{
		const std::vector<std::string> expected2 = {"b", "c", "a"};
		std::vector<std::string> result;
		for (auto node = list.front(); node; node = node->next) {
			result.push_back(node->value);
		}
		ASSERT_EQ(result, expected2);
		ASSERT_EQ(list.size(), 3);
	}
	
}

TEST(MyDLList, pop_front) {
	MyDLList<int> list;
	for (int i = 1; i <= 5; ++i) {
		list.push_front(i);
	}
	while (list.front() != nullptr) {
		list.pop_front();
	}
	ASSERT_EQ(list.size(), 0);
	ASSERT_EQ(list.front(), nullptr);
	ASSERT_EQ(list.back(), nullptr);
}

TEST(MyDLList, pop_back) {
	MyDLList<int> list;
	for (int i = 1; i <= 5; ++i) {
		list.push_back(i);
	}
	while (list.back() != nullptr) {
		list.pop_back();
	}
	ASSERT_EQ(list.size(), 0);
	ASSERT_EQ(list.front(), nullptr);
	ASSERT_EQ(list.back(), nullptr);
}

TEST(MyDLList, erase) {
	MyDLList<int> list;
	for (int i = 1; i <= 5; ++i) {
		list.push_front(i);
	}
	{
		const std::vector<int> expected = {5, 4, 3, 2, 1};
		std::vector<int> result;
		for (auto node = list.front(); node; node = node->next) {
			result.push_back(node->value);
		}
		ASSERT_EQ(result, expected);
	}
	
	auto next_to_head = list.front()->next;
	list.erase(next_to_head); 
	next_to_head = list.front()->next;
	list.erase(next_to_head);

	{
		const std::vector<int> expected = {5, 2, 1};
		std::vector<int> result;
		for (auto node = list.front(); node; node = node->next) {
			result.push_back(node->value);
		}
		ASSERT_EQ(result, expected);
	}
	
	while (list.front()->next) {
		list.erase(list.front());
	}
	ASSERT_EQ(list.front()->value, 1);
	ASSERT_EQ(list.size(), 1);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}