#include "pch.h"
#include "../Lab9/List.h"

TEST(Node, Constructor) {
	for (uint64_t i = std::numeric_limits<uint64_t>::max() - 100; i < std::numeric_limits<uint64_t>::max(); i++) {
		Node<uint64_t> n(i);
		EXPECT_EQ(n.value_, i);
	}

	{
		const char sym = 'a';
		Node<std::string> n("");
		for (std::string i = "a"; i.size() < 100; i += sym) {
			n.value_ += sym;
			EXPECT_EQ(n.value_, i);
		}
	}
}

TEST(Node, Template) {
	EXPECT_EQ(typeid(Node<int>(5).value_), typeid(int));
	EXPECT_EQ(typeid(Node<int8_t>(5).value_), typeid(int8_t));
	EXPECT_EQ(typeid(Node<uint8_t>(5).value_), typeid(uint8_t));
	EXPECT_EQ(typeid(Node<int16_t>(5).value_), typeid(int16_t));
	EXPECT_EQ(typeid(Node<uint16_t>(5).value_), typeid(uint16_t));
	EXPECT_EQ(typeid(Node<int32_t>(5).value_), typeid(int32_t));
	EXPECT_EQ(typeid(Node<uint32_t>(5).value_), typeid(uint32_t));
	EXPECT_EQ(typeid(Node<int64_t>(5).value_), typeid(int64_t));
	EXPECT_EQ(typeid(Node<uint64_t>(5).value_), typeid(uint64_t));

	EXPECT_EQ(typeid(Node<std::string>("Some string").value_), typeid(std::string));
	EXPECT_EQ(typeid(Node<bool>(0).value_), typeid(bool));
	EXPECT_EQ(typeid(Node<Node<int>>(Node<int>(0)).value_), typeid(Node<int>));
}
TEST(List, Constructor) {
	List<int> list;
	EXPECT_EQ(NodeCount, 0);
}
TEST(List, Destructor) {
	EXPECT_EQ(ListCount, 0);
	EXPECT_EQ(NodeCount, 0);
	{
		List<int> l;
		EXPECT_EQ(ListCount, 1);
		EXPECT_EQ(NodeCount, 0);

		for (int i = 0; i < 20; i++) {
			l.push_back(i);
		}

		EXPECT_EQ(ListCount, 1);
		EXPECT_EQ(NodeCount, 20);

		for (int i = 0; i < 20; i++) {
			l.remove(l.find(i));
		}

		EXPECT_EQ(ListCount, 1);
		EXPECT_EQ(NodeCount, 0);

		for (int i = 0; i < 20; i++) {
			l.push_front(i);
		}

		EXPECT_EQ(ListCount, 1);
		EXPECT_EQ(NodeCount, 20);

		for (int i = 0; i < 20; i++) {
			l.remove(l.find(i));
		}

		EXPECT_EQ(ListCount, 1);
		EXPECT_EQ(NodeCount, 0);
	}

	EXPECT_EQ(ListCount, 0);
	EXPECT_EQ(NodeCount, 0);
}

TEST(List, push_back) {
	List<int> list;
	for (int i = -10; i < 10; i++) {
		list.push_back(i);
	}

	for (int i = -10; i < 10; i++) {
		EXPECT_EQ(list.find(i)->value_, i);
	}

	for (int i = 10; i < 50; i++) {
		EXPECT_EQ(list.find(i), nullptr);
	}
}

// the correctness of adding elements will be checked in the output statement
TEST(List, push_front) {
	List<int> list;
	for (int i = -10; i < 10; i++) {
		list.push_front(i);
	}

	for (int i = -10; i < 10; i++) {
		EXPECT_EQ(list.find(i)->value_, i);
	}

	for (int i = 10; i < 50; i++) {
		EXPECT_EQ(list.find(i), nullptr);
	}
}

TEST(List, find) {
	List<int> list;
	{
		for (int i = 0; i < 50; i++) {
			EXPECT_EQ(list.find(i), nullptr);
		}
	} // Test Empty

	{
		for (int i = 0; i < 10; i++) {
			list.push_front(i);
		}

		for (int i = 0; i < 10; i++) {
			EXPECT_EQ(list.find(i)->value_, i);
		} // Checking 10 existing elements

		for (int i = 10; i < 50; i++) {
			EXPECT_EQ(list.find(i), nullptr);
		} // Checking non-existent elements
	}

	{
		for (int i = 50; i < 100; i++) {
			EXPECT_EQ(list.find(i), nullptr);
			list.push_front(i);
			EXPECT_EQ(list.find(i)->value_, i);
		}
	}
}

TEST(List, remove) {
	{
		List<int> list;
		for (int i = 50; i < 100; i++) {
			EXPECT_EQ(list.find(i), nullptr);
			list.push_front(i);
			EXPECT_EQ(list.find(i)->value_, i);
			list.remove(list.find(i));
			EXPECT_EQ(list.find(i), nullptr);
		}

		for (int i = 0; i < 50; i++) {
			EXPECT_EQ(list.find(i), nullptr);
			list.remove(list.find(i));
			EXPECT_EQ(list.find(i), nullptr);
		}
	}

	{
		List<int> list;
		for (int i = 0; i < 10; i++) {
			list.push_front(i);
		}

		for (int i = 9; i >= 0; i--) {
			list.remove(list.find(i));
		}

		for (int i = 0; i < 10; i++) {
			EXPECT_EQ(list.find(i), nullptr);
		}
	}

	{
		List<int> list;
		for (int i = 0; i < 10; i++) {
			list.push_front(i);
		}
		list.remove(list.find(9));
		for (int i = 0; i < 9; i++) {
			EXPECT_EQ(list.find(i)->value_, i);
		}
		EXPECT_EQ(list.find(9), nullptr);
	}

	{
		List<int> list;
		for (int i = 0; i < 10; i++) {
			list.push_front(i);
		}
		list.remove(list.find(5));
		for (int i = 0; i < 5; i++) {
			EXPECT_EQ(list.find(i)->value_, i);
		}
		EXPECT_EQ(list.find(5), nullptr);
		for (int i = 6; i < 10; i++) {
			EXPECT_EQ(list.find(i)->value_, i);
		}
	}

	{
		List<int> list;
		for (int i = 0; i < 10; i++) {
			list.push_front(i);
		}
		list.remove(list.find(0));
		for (int i = 1; i < 10; i++) {
			EXPECT_EQ(list.find(i)->value_, i);
		}
		EXPECT_EQ(list.find(0), nullptr);
	}
}

TEST(List, pop_back) {
	{
		bool error = false;
		try {
			List<int> list;
			list.pop_back();
		}
		catch (const std::exception&) {
			error = true;
		}
		EXPECT_TRUE(error);
	}

	{
		List<int> list;
		const int VALUE = 50;
		for (int i = 0; i <= VALUE; i++) {
			list.push_back(i);
		}
		for (int i = 0; i <= VALUE; i++) {
			std::cout << list.pop_back() << std::endl;
		}
		for (int i = 0; i <= VALUE; i++) {
			EXPECT_EQ(list.find(i), nullptr);
		}
	}

	{
		List<int> list;
		const int VALUE = 50;
		for (int i = 0; i <= VALUE; i++) {
			list.push_back(i);
		}
		for (int i = 0; i < VALUE; i++) {
			EXPECT_EQ(list.pop_back(), VALUE - i);
		}
	}
}

TEST(List, pop_front) {
	{
		bool error = false;
		try {
			List<int> list;
			list.pop_front();
		}
		catch (const std::exception&) {
			error = true;
		}
		EXPECT_TRUE(error);
	}

	{
		List<int> list;
		const int VALUE = 50;
		for (int i = 0; i <= VALUE; i++) {
			list.push_back(i);
		}
		for (int i = 0; i <= VALUE; i++) {
			list.pop_front();
		}
		for (int i = 0; i <= VALUE; i++) {
			EXPECT_EQ(list.find(i), nullptr);
		}
	}

	{
		List<int> list;
		const int VALUE = 50;
		for (int i = 0; i <= VALUE; i++) {
			list.push_back(i);
		}
		for (int i = 0; i < VALUE; i++) {
			EXPECT_EQ(list.pop_front(), i);
		}
	}
}

TEST(List, outputs) {
	{
		std::stringstream ss;
		List<int> list;
		for (int i = 0; i < 10; i++) {
			list.push_back(i);
		}
		ss << list;
		EXPECT_EQ(ss.str(), "[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]");
	}

	{
		std::stringstream ss;
		List<int> list;
		list.push_back(5);
		list.push_front(4);
		list.push_back(6);
		list.push_front(3);
		list.push_back(7);
		list.push_front(2);
		list.push_back(8);
		list.push_front(1);
		list.push_back(9);
		list.push_front(0);
		ss << list;
		EXPECT_EQ(ss.str(), "[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]");
	}

	{
		std::stringstream ss;
		List<int> list;
		for (int i = 0; i < 10; i++) {
			list.push_back(i);
		}
		list.remove(list.find(0)); // head
		list.remove(list.find(9)); // tail
		ss << list;
		EXPECT_EQ(ss.str(), "[1, 2, 3, 4, 5, 6, 7, 8]");
	}

	{
		std::stringstream ss;
		List<int> list;
		for (int i = -10; i < 10; i++) {
			list.push_back(i);
		}
		ss << list;
		EXPECT_EQ(ss.str(), "[-10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9]");
	}

	{
		std::stringstream ss;
		List<int> list;
		for (int i = 0; i < 10; i++) {
			list.push_front(i);
		}
		ss << list;
		EXPECT_EQ(ss.str(), "[9, 8, 7, 6, 5, 4, 3, 2, 1, 0]");
	}

	{
		std::stringstream ss;
		List<int> list;
		for (int i = -10; i < 10; i++) {
			list.push_front(i);
		}
		ss << list;
		EXPECT_EQ(ss.str(), "[9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10]");
	}

	{
		std::stringstream ss;
		List<int> list;
		for (int i = 0; i < 10; i++) {
			list.push_front(i);
		}
		list.pop_back();
		list.pop_back();
		list.pop_back();
		list.pop_back();
		list.pop_back();
		ss << list;
		EXPECT_EQ(ss.str(), "[9, 8, 7, 6, 5]");
	}

	{
		std::stringstream ss;
		List<int> list;
		for (int i = 0; i < 10; i++) {
			list.push_front(i);
		}
		list.pop_front();
		list.pop_front();
		list.pop_front();
		list.pop_front();
		list.pop_front();
		ss << list;
		EXPECT_EQ(ss.str(), "[4, 3, 2, 1, 0]");
	}

	{
		std::stringstream ss;
		List<int> list;
		for (int i = 0; i < 10; i++) {
			list.push_front(i);
		}
		list.remove(list.find(1));
		list.remove(list.find(5));
		list.remove(list.find(8));
		ss << list;
		EXPECT_EQ(ss.str(), "[9, 7, 6, 4, 3, 2, 0]");
	}

	{
		std::stringstream ss;
		List<int> list;
		for (int i = 0; i < 10; i++) {
			list.push_front(i);
		}
		list.remove(list.find(1));
		list.remove(list.find(3));
		list.remove(list.find(5));
		list.remove(list.find(7));
		list.remove(list.find(9));
		ss << list;
		EXPECT_EQ(ss.str(), "[8, 6, 4, 2, 0]");
	}

	{
		std::stringstream ss;
		List<int> list;
		for (int i = 0; i < 10; i++) {
			list.push_front(i);
		}
		list.remove(list.find(1));
		list.remove(list.find(3));
		list.remove(list.find(5));
		list.remove(list.find(7));
		list.remove(list.find(9));
		ss << list;
		EXPECT_EQ(ss.str(), "[8, 6, 4, 2, 0]");
	}

	{
		std::stringstream ss;
		List<int> list;
		for (int i = 0; i < 10; i++) {
			list.push_front(i);
		}
		for (int i = 0; i < 10; i++) {
			list.remove(list.find(i));
		}
		ss << list;
		EXPECT_EQ(ss.str(), "[]");
	}

	{
		std::stringstream ss;
		List<int> list;
		ss << list;
		EXPECT_EQ(ss.str(), "[]");
	}

	{
		std::stringstream ss;
		List<int> list;
		for (int i = 0; i < 10; i++) {
			list.push_back(i);
		}
		ss << list;
		EXPECT_EQ(ss.str(), "[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]");

		for (int i = 0; i < 10; i++) {
			list.remove(list.find(i));
		}

		ss.str("");
		ss << list;
		EXPECT_EQ(ss.str(), "[]");

		for (int i = 0; i < 10; i++) {
			list.push_back(i);
		}

		ss.str("");
		ss << list;
		EXPECT_EQ(ss.str(), "[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]");
	}

	{
		std::stringstream ss;
		List<int> list;
		for (int i = 0; i < 10; i++) {
			list.push_back(i);
		}
		ss << list;
		EXPECT_EQ(ss.str(), "[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]");

		list.pop_back();
		ss.str("");
		ss << list;
		EXPECT_EQ(ss.str(), "[0, 1, 2, 3, 4, 5, 6, 7, 8]");

		list.push_back(9);
		ss.str("");
		ss << list;
		EXPECT_EQ(ss.str(), "[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]");

		list.pop_front();
		ss.str("");
		ss << list;
		EXPECT_EQ(ss.str(), "[1, 2, 3, 4, 5, 6, 7, 8, 9]");

		list.push_front(0);
		ss.str("");
		ss << list;
		EXPECT_EQ(ss.str(), "[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]");
	}
}

template <typename T>
void ListTemplateTest() {
	List<T> l;
	l.push_back(T());
	EXPECT_EQ(typeid(l.find(T())->value_), typeid(T));
}
TEST(List, Template) {
	ListTemplateTest<int>();
	ListTemplateTest<int8_t>();
	ListTemplateTest<uint8_t>();
	ListTemplateTest<int16_t>();
	ListTemplateTest<uint16_t>();
	ListTemplateTest<int32_t>();
	ListTemplateTest<uint32_t>();
	ListTemplateTest<int64_t>();
	ListTemplateTest<uint64_t>();

	ListTemplateTest<std::string>();
	ListTemplateTest<bool>();
	ListTemplateTest<List<int>>();

	{
		List<std::string> list;
		for (int i = 0; i < 100; i++) {
			list.push_back(std::to_string(i));
		}
		for (int i = 0; i < 100; i++) {
			EXPECT_EQ(list.find(std::to_string(i))->value_, std::to_string(i));
		}
		for (int i = -100; i < 0; i++) {
			EXPECT_EQ(list.find(std::to_string(i)), nullptr);
		}
		for (int i = 100; i < 200; i++) {
			EXPECT_EQ(list.find(std::to_string(i)), nullptr);
		}
	}
}

TEST(List, size) {
	{
		List<int> l;
		EXPECT_EQ(l.size(), 0);
		for (int i = 0; i < 10; i++) {
			EXPECT_EQ(l.size(), i);
			l.push_back(i);
		}
		EXPECT_EQ(l.size(), 10);

		for (int i = 0; i < 10; i++) {
			l.remove(l.find(i));
		}
		EXPECT_EQ(l.size(), 0);

		for (int i = 0; i < 10; i++) {
			EXPECT_EQ(l.size(), i);
			l.push_front(i);
		}
		EXPECT_EQ(l.size(), 10);

		for (int i = 0; i < 10; i++) {
			l.remove(l.find(i));
		}
		EXPECT_EQ(l.size(), 0);
	}
}

TEST(List, getMiddle) {
	List<int> l;
	EXPECT_EQ(l.getMiddle(), nullptr);
	l.push_back(0);
	EXPECT_EQ(l.getMiddle()->value_, 0);
	l.push_back(1);
	EXPECT_EQ(l.getMiddle()->value_, 0);
	l.push_back(2);
	EXPECT_EQ(l.getMiddle()->value_, 1);
	l.push_back(3);
	EXPECT_EQ(l.getMiddle()->value_, 1);
	l.push_back(4);
	EXPECT_EQ(l.getMiddle()->value_, 2);
	l.push_back(5);
	EXPECT_EQ(l.getMiddle()->value_, 2);
	l.push_back(6);
	EXPECT_EQ(l.getMiddle()->value_, 3);
	l.push_back(7);
	EXPECT_EQ(l.getMiddle()->value_, 3);
	l.push_back(8);
	EXPECT_EQ(l.getMiddle()->value_, 4);
	l.push_back(9);
	EXPECT_EQ(l.getMiddle()->value_, 4);
	l.push_back(10);
	EXPECT_EQ(l.getMiddle()->value_, 5);
	l.push_back(11);
	EXPECT_EQ(l.getMiddle()->value_, 5);
}

TEST(List, Iterators) {
	{
		List<int> l;
		EXPECT_EQ(l.begin(), l.end());

		l.push_back(0);
		auto it = l.begin();
		EXPECT_EQ(++it, l.end());

		for (int i = 1; i < 10; i++) {
			l.push_back(i);
		}

		auto iter = l.begin();
		for (int i = 0; i < 10; i++) {
			EXPECT_EQ(*iter++, i);
		}
	}

	{
		List<int> l;
		l.push_back(0);
		auto it = l.end();

		bool error = false;
		try {
			*it;
		}
		catch (const std::exception&) {
			error = true;
		}
		EXPECT_TRUE(error);
	}

	{
		List<int> l;
		l.push_back(0);
		auto it = l.end();
		--it;
		EXPECT_EQ(*it, 0);
	}

	{
		List<int> l;
		l.push_back(0);
		l.push_back(1);
		auto it = l.end();
		--it;
		--it;
		EXPECT_EQ(*it, 0);
		++it;
		EXPECT_EQ(*it, 1);
		--it;
		EXPECT_EQ(*it, 0);
		EXPECT_EQ(it, l.begin());
		++it;
		++it;
		EXPECT_EQ(it, l.end());
	}
}

TEST(List, merge) {
	{
		List<int> l1;
		for (int i = 0; i < 10; i++) {
			l1.push_back(i);
		}

		List<int> l2;
		for (int i = 10; i < 20; i++) {
			l2.push_back(i);
		}

		List<int>* newList = merge(&l1, &l2);
		auto it = newList->begin();
		for (int i = 0; i < 20; i++) {
			EXPECT_EQ(*it++, i);
		}

		bool error = false;
		try {
			*it;
		}
		catch (const std::exception&) {
			error = true;
		}
		EXPECT_TRUE(error);
	}

	{
		List<int> l1;
		List<int> l2;
		List<int>* newList = merge(&l1, &l2);
		EXPECT_EQ(newList->size(), 0);
	}

	{
		List<int> l1;
		for (int i = 0; i < 10; i++) {
			l1.push_back(2 * i);
		}
		List<int> l2;
		for (int i = 0; i < 10; i++) {
			l2.push_back(2 * i + 1);
		}
		List<int>* newList = merge(&l1, &l2);
		auto it = newList->begin();
		for (int i = 0; i < 20; i++) {
			EXPECT_EQ(*it, i);
			++it;
		}
		EXPECT_EQ(it, newList->end());
	}

	{
		List<int> l1;
		for (int i = 9; i >= 0; i--) {
			l1.push_back(-2 * i);
		}
		List<int> l2;
		for (int i = 9; i >= 0; i--) {
			l2.push_back(-2 * i - 1);
		}
		List<int>* newList = merge(&l1, &l2);
		auto it = newList->begin();
		for (int i = 19; i >= 0; i--) {
			EXPECT_EQ(*it++, -i);
		}
		EXPECT_EQ(it, newList->end());
	}
}

TEST(List, ItConstructor) {
	{
		List<int> l1;
		List<int> l2(l1.begin(), l1.end());
		EXPECT_EQ(l2.begin(), l2.end());
		bool error = false;
		try {
			*l2.begin();
		}
		catch (const std::exception&) {
			error = true;
		}
		EXPECT_TRUE(error);
	}

	{
		List<int> l1;
		l1.push_back(0);
		List<int> l2(l1.begin(), l1.end());
		auto iter = l2.begin();
		EXPECT_EQ(++iter, l2.end());
		EXPECT_EQ(*l2.begin(), 0);
	}

	{
		List<int> l1;
		l1.push_back(0);
		l1.push_back(5);
		l1.push_back(-253);
		l1.push_back(233223);
		l1.push_back(233223);

		List<int> l2(l1.begin(), l1.end());
		auto iter = l2.begin();
		EXPECT_EQ(*iter++, 0);
		EXPECT_EQ(*iter++, 5);
		EXPECT_EQ(*iter++, -253);
		EXPECT_EQ(*iter++, 233223);
		EXPECT_EQ(*iter++, 233223);

		bool error = false;
		try {
			*iter;
		}
		catch (const std::exception&) {
			error = true;
		}
		EXPECT_TRUE(error);
	}
}

TEST(List, mergeSort) {
	{
		List<int> list;
		for (int i = 9; i >= 0; i--) {
			list.push_back(i);
		}
		List<int>* newList = mergeSort(&list);
		auto it = newList->begin();
		for (int i = 0; i < 10; i++) {
			EXPECT_EQ(*it++, i);
		}
	}

	{
		List<int> list;
		list.push_back(0);
		list.push_back(35252);
		list.push_back(-253);
		list.push_back(131313);
		list.push_back(-255553);
		list.push_back(15);
		list.push_back(155);
		list.push_back(16);
		list.push_back(-16);
		list.push_back(-156);
		List<int>* newList = mergeSort(&list);
		auto it = newList->begin();
		++it;
		while (it != newList->end()) {
			auto iter = it;
			iter--;
			EXPECT_LT(*iter, *it++);
		}
	}

	{
		List<int> list;
		for (int i = 0; i < 100; i++) {
			list.push_back((rand() % 10000) * pow(-1, i));
		}
		List<int>* newList = mergeSort(&list);
		auto it = newList->begin();
		++it;
		while (it != newList->end()) {
			auto iter = it;
			iter--;
			EXPECT_LE(*iter, *it++);
		}
	}
}