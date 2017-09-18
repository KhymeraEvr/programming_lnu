#include <iostream>

#include "BinaryTree.h"

using namespace std;

int main()
{
	BinaryTree<int>* tree = new BinaryTree<int>();
	tree->add(8);
	tree->add(4);
	tree->add(10);
	tree->add(2);
	tree->add(6);
	tree->add(9);
	tree->add(11);
	tree->add(5);
	tree->add(7);

	tree->prettyPrint(cout);

	return 0;
}