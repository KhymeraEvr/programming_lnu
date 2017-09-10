#pragma once

#include <iostream>
#include <conio.h>
#include <list>

using namespace std;

template<typename T> struct Node
{
	T value;
	int shift;
	Node<T>* left;
	Node<T>* right;

	Node<T>(int value) : value(value), left(nullptr), right(nullptr), shift(0)
	{
	}
};

enum NodeType
{
	ROOT,
	LEFT,
	RIGHT
};

template<typename T> class BinaryTree
{
private:
	Node<T>* root;

	void add(Node<T>* node, T value)
	{
		if (value > node->value)
		{
			if (node->right == nullptr)
			{
				node->right = new Node<T>(value);
			}
			else
			{
				add(node->right, value);
			}
		}
		else
		{
			if (node->left == nullptr)
			{
				node->left = new Node<T>(value);
			}
			else
			{
				add(node->left, value);
			}
		}
	}

	void removeSubtree(Node<T>* node)
	{
		if (node != nullptr)
		{
			removeSubtree(node->left);
			removeSubtree(node->right);
			delete node;
		}
	}

#pragma region _PRETTY_PRINT_

	void printNodes(Node<T>* node, ostream& out)
	{
		if (node == nullptr)
		{
			return;
		}

		out << "\t(value:  " << node->value << "\tshift: " << node->shift << ")" << endl;
		printNodes(node->left, out);
		printNodes(node->right, out);
	}

	void calculateNodeShift(Node<T>* node, int direction, int parrentShift)
	{
		if (node == nullptr)
		{
			return;
		}

		node->shift = direction + parrentShift;
		calculateNodeShift(node->left, -1, node->shift);
		calculateNodeShift(node->right, 1, node->shift);
	}

	void addShiftToEachNode(Node<T>* node, int shift)
	{
		if (node == nullptr)
		{
			return;
		}

		node->shift += shift;
		addShiftToEachNode(node->left, shift);
		addShiftToEachNode(node->right, shift);
	}

	void positionLeftNodeToAbsoluteZero()
	{
		Node<T>* leftNode = root;
		while (leftNode->left != nullptr)
		{
			leftNode = leftNode->left;
		}

		addShiftToEachNode(root, -leftNode->shift);
	}

	Node<T>* rightNode(Node<T>* node)
	{
		while (node->right != nullptr)
		{
			node = node->right;
		}
		return node;
	}

	Node<T>* leftNode(Node<T>* node)
	{
		// FIXME: this method is not returning the most 'left' node
		while (node->left != nullptr)
		{
			node = node->left;
		}
		return node;
	}

	void fixNodeColisions(Node<T>* parrentNode, Node<T>* node, NodeType nodeType)
	{
		if (node->left == nullptr && node->right == nullptr)
		{
			if (nodeType == NodeType::LEFT)
			{
				node->shift--;
			}
			else if (nodeType == NodeType::RIGHT)
			{
				node->shift++;
			}

			return;
		}
		if (node->left != nullptr)
		{
			fixNodeColisions(node, node->left, NodeType::LEFT);
		}
		if (node->right != nullptr)
		{
			fixNodeColisions(node, node->right, NodeType::RIGHT);
		}

		
		if (nodeType == NodeType::ROOT)
		{
			return;
		}
		else if (nodeType == NodeType::LEFT)
		{
			Node<T>* _rightNode = rightNode(node);

			if (parrentNode->shift <= _rightNode->shift)
			{
				addShiftToEachNode(node, -(_rightNode->shift - parrentNode->shift + 1));
			}
		}
		else
		{
			Node<T>* _leftNode = leftNode(node);

			if (parrentNode->shift >= _leftNode->shift)
			{
				addShiftToEachNode(node, parrentNode->shift - _leftNode->shift + 1);
			}
		}
	}

	list<Node<T>*>* getNodesOnLevel(Node<T>* node, int level, bool isFirstInvocation)
	{
		static list<Node<T>*>* nodes = new list<Node<T>*>();
		static int currentLevel = 0;

		if (isFirstInvocation)
		{
			nodes->clear();
		}
		
		if (currentLevel == level)
		{
			nodes->push_back(node);
			return nodes;
		}
		else
		{
			if (node->left != nullptr)
			{
				currentLevel++;
				getNodesOnLevel(node->left, level, false);
				currentLevel--;
			}
			if (node->right != nullptr)
			{
				currentLevel++;
				getNodesOnLevel(node->right, level, false);
				currentLevel--;
			}
		}
		return nodes;
	}

#pragma endregion

public:
	BinaryTree()
	{
	}

	~BinaryTree()
	{
		removeSubtree(root);
	}

	void add(T value)
	{
		if (root == nullptr)
		{
			root = new Node<T>(value);
		}
		else
		{
			add(root, value);
		}
	}

	void prettyPrint(ostream& out)
	{
		calculateNodeShift(root, 0, 0);
		fixNodeColisions(nullptr, root, NodeType::ROOT);
		positionLeftNodeToAbsoluteZero();
		
		for (int i = 0; true ; i++)
		{
			list<Node<T>*>* nodesOnLevel = getNodesOnLevel(root, i, true);

			if (nodesOnLevel->size() == 0)
			{
				return;
			}
			
			int horizontalIndex = 0;
			for each (Node<T>* node in *nodesOnLevel)
			{
				while (horizontalIndex < node->shift)
				{
					out << " ";
					horizontalIndex++;
				}
				out << node->value;
				horizontalIndex++;
			}
			out << endl;
		}
	}
};
