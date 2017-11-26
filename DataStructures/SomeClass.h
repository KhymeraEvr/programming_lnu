//
// Created by oles on 11/26/17.
//

#ifndef DATASTRUCTURES_SOMECLASS_H
#define DATASTRUCTURES_SOMECLASS_H

#include <iostream>
#include "SomeInterface.h"

using namespace std;

class SomeClass
{
public:
	int a;

	class Inner : public SomeInterface
	{
	public:
		int b;

		void go() override
		{
			cout << "GO () !!!" << endl;
		}
	};

	Inner* getInner()
	{
		return new Inner();
	}
};


#endif //DATASTRUCTURES_SOMECLASS_H
