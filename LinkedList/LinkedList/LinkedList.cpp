#include "LinkedList.h"

template<typename T> LinkedList<T>::LinkedList()
{
	root = new Node<T>();
	current = root;
}

template<typename T> LinkedList<T>::~LinkedList()
{
	Node<T>* walk = root;
	while (walk->next != nullptr)
	{
		Node<T>* toRemove = walk;
		walk = walk->next;
		delete toRemove;
	}
	delete current;
}

template<typename T> void LinkedList<T>::add(T value)
{
	current->value = value;
	current->next = new Node<T>();
	current = current->next;
}


template<typename T> void LinkedList<T>::remove(T searchedValue)
{
	if (root->value == searchedValue)
	{
		Node<T>* toRemove = root;
		root = root->next;
		delete toRemove;
		return;
	}

	Node<T>* previous = root;
	Node<T>* walk = root->next;

	while (walk->next != nullptr)
	{
		if (walk->value == searchedValue)
		{
			previous->next = walk->next;
			delete walk;
			return;
		}
		walk = walk->next;
		previous = previous->next;
	}
}


template<typename T> bool LinkedList<T>::contains(T value)
{
	Node<T>* walk = root;

	while (walk->next != nullptr)
	{
		if (walk->value == value)
		{
			return true;
		}
		walk = walk->next;
	}
	return false;
}

template<typename T> void LinkedList<T>::prettyPrint(ostream& out)
{
	if (root->next == nullptr)
	{
		out << "NULL" << endl;
		return;
	}

	out << root->value;

	Node<T>* walk = root->next;
	while (walk->next != nullptr)
	{
		out << " -> " << walk->value;
		walk = walk->next;
	}
	out << endl;
}

// You can find more about this last line in the project description (README.md)
template class LinkedList<int>;