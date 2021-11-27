#include "List.h"
#include <iostream>

int main() {
	List<int> l;
	l.push_back(5);
	std::cout << l;
}