#pragma once

#include <iostream>

using namespace std;

template<typename T> struct Node
{
	T value;
	Node* next;
};

template<typename T> class LinkedList
{
private:
	Node<T>* root;
	Node<T>* current;

public:
	LinkedList();

	~LinkedList();

	void add(T value);
	void remove(T searchedValue);
	bool contains(T value);
	bool equals(LinkedList&);

	void prettyPrint(ostream& out);

	void forEach(void (*alter)(T&));
};
