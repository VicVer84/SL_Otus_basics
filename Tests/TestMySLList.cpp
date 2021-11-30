#include "MySLList.h"

#include <iostream>
#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <string>

TEST(MySLList, push_front) {
	MySLList<int> list;
	
	list.push_front(1);	
	ASSERT_EQ(list.getHead()->value, 1);
	
	list.push_front(2);	
	ASSERT_EQ(list.getHead()->value, 2);
	
	list.push_front(3);	
	ASSERT_EQ(list.getHead()->value, 3);
		
	
	const std::vector<int> expected = {3, 2, 1};
	std::vector<int> result;
	for (auto node = list.getHead(); node; node = node->next) {
		result.push_back(node->value);
	}
	ASSERT_EQ(result, expected);
}

TEST(MySLList, insert) {
	MySLList<std::string> list;

	list.push_front("a");
	auto head = list.getHead();

	ASSERT_EQ(head->value, "a");

	list.insert(head, "b");	
	
	{
		const std::vector<std::string> expected1 = {"a", "b"};
		std::vector<std::string> result;
		for (auto node = list.getHead(); node; node = node->next) {
			result.push_back(node->value);
		}
		ASSERT_EQ(result, expected1);
	}
	
	list.insert(head, "c");
	
	{
		const std::vector<std::string> expected2 = {"a", "c", "b"};
		std::vector<std::string> result;
		for (auto node = list.getHead(); node; node = node->next) {
			result.push_back(node->value);
		}
		ASSERT_EQ(result, expected2);
	}
	
}

TEST(MySLList, erase) {
	MySLList<int> list;
	for (int i = 1; i <= 5; ++i) {
		list.push_front(i);
	}
	{
		const std::vector<int> expected = {5, 4, 3, 2, 1};
		std::vector<int> result;
		for (auto node = list.getHead(); node; node = node->next) {
			result.push_back(node->value);
		}
		ASSERT_EQ(result, expected);
	}
	
	auto next_to_head = list.getHead()->next;
	list.erase(next_to_head); 
	list.erase(next_to_head);

	{
		const std::vector<int> expected = {5, 4, 1};
		std::vector<int> result;
		for (auto node = list.getHead(); node; node = node->next) {
			result.push_back(node->value);
		}
		ASSERT_EQ(result, expected);
	}
	
	while (list.getHead()->next) {
		list.erase(list.getHead());
	}
	ASSERT_EQ(list.getHead()->value, 5);
}


TEST(MySLList, pop_front) {
	MySLList<int> list;

	for (int i = 1; i <= 5; ++i) {
		list.push_front(i);
	}
	for (int i = 1; i <= 5; ++i) {
		list.pop_front();
	}
	ASSERT_EQ(list.getHead(), nullptr);
}


int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}