#ifndef PROGRAMMINGLANGUAGE_COMPILER_H
#define PROGRAMMINGLANGUAGE_COMPILER_H

#include <string>
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

class Compiler
{
private:
	struct Token
	{
		string value;

		Token(string value) : value(std::move(value))
		{
		}
	};

	typedef string::iterator stringIt;

	vector<char> lexemes =
	{
			'>', ';', '=', '+', '-',
			'*', '/', '(', ')', '{',
			'}', '[', ']',
	};

	bool isLexeme(char symbol);

	void removeWhitespaces(string& code);

	vector<Token>* tokenize(string& code);

	string compile(vector<Token>* tokens);
public:
	string compile(string code);
};


#endif
