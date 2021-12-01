#include "MySLList.h"

#include <iostream>
#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <string>

TEST(MySLList, creation_empty) {
	const size_t expected = 0;
	MySLList<int> list;

	ASSERT_EQ(list.size(), expected);
}

TEST(MySLList, test_size) {
	const size_t expected = 5;
	MySLList<int> list;

	for (int i = 1; i <= 5; ++i) {
		list.push_front(i);
	}
	ASSERT_EQ(list.size(), expected);
}

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
	
	list.insert(head, "c"); // head points to "a", insert after head
	
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

TEST(MySLList, test_copy) {
	MySLList<int> copyToList;
	MySLList<int> list;

	for (int i = 0; i < 10; ++i) {
		list.push_front(i);
	}
	copyToList = list;

	ASSERT_EQ(copyToList.size(), list.size());
	for (auto newl_node = copyToList.getHead(), oldl_node = list.getHead(); newl_node; newl_node = newl_node->next, oldl_node = oldl_node->next) {
		ASSERT_EQ(newl_node->value, oldl_node->value);
	}
}

TEST(MySLList, test_move) {
	std::string expected = "9876543210";
	MySLList<int> list;
	MySLList<int> moveToList;
	for (int i = 0; i < 10; ++i) {
		list.push_front(i);
	}
	moveToList = std::move(list);
	ASSERT_EQ(list.size(), 0);

	std::stringstream ss;
	for (auto node = moveToList.getHead(); node; node = node->next) {
		ss << node->value;
	}
	ASSERT_EQ(ss.str(), expected);
}

TEST(MySLList, test_destructor) {
	const size_t expected = 0;

	std::shared_ptr<int> p = std::make_shared<int>(6);

	{
		MySLList<std::shared_ptr<int>> list;
		for (int i = 0; i < 10; ++i) {
			list.push_front(p);
		}
		ASSERT_EQ(p.use_count(), 11);
		ASSERT_EQ(list.size(), 10);
	}

	ASSERT_EQ(p.use_count(), 1);
}



int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}