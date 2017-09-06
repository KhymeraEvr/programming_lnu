#include <iostream>
#include <string>
#include <conio.h>

#include "LinkedList.h"

using namespace std;

void log(string message);

int main()
{
	LinkedList<int>* list = new LinkedList<int>();

	log("print empty list");
	list->prettyPrint(cout);
	cout << endl;

	log("printing one element");
	list->add(3);
	list->prettyPrint(cout);
	cout << endl;

	log("printing more elements");
	list->add(5);
	list->add(-3);
	list->add(45);
	list->prettyPrint(cout);
	cout << endl;

	log("removing first element");
	list->remove(3);
	list->prettyPrint(cout);
	cout << endl;

	log("removing middle element");
	list->remove(-3);
	list->prettyPrint(cout);
	cout << endl;

	log("adding some more elements");
	list->add(-43);
	list->add(908);
	list->add(123);
	list->prettyPrint(cout);
	cout << endl;

	log("removing last element");
	list->remove(123);
	list->prettyPrint(cout);
	cout << endl;

	log("checking if list contains elements");
	cout << boolalpha << "Contains:" << endl
		<< "\tnot existing element: " << list->contains(876543) << endl
		<< "\texisting element: " << list->contains(908) << endl
		<< "\tremoved element: " << list->contains(123) << endl;
	cout << endl;

	log("testing forEach method");
	log(" before:");
	list->prettyPrint(cout);
	log(" after:");
	list->forEach([](int& value)
	{
		value += 3;
	});
	list->prettyPrint(cout);


	_getch();
	return 0;
}

void log(string message)
{
	cout << "-----" << message << endl;
}