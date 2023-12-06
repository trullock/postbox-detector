#include "./node.h"
#include <iostream>

int main()
{
	Node root;
	Node child1;
	child1.height = 1;
	Node child2;
	child2.height = 2;
	Node children[2] = { child1, child2 };
	root.children = children;
	
	std::cout << (root.children + 1)->height;
	return 0;
}