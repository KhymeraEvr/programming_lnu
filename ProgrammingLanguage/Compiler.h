#ifndef PROGRAMMINGLANGUAGE_COMPILER_H
#define PROGRAMMINGLANGUAGE_COMPILER_H

#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
#include <map>
#include <list>

using namespace std;

class Compiler
{
private:
	struct Command
	{
		string op;
		string first;
		string second;
		string third;

		Command(string op, string first, string second = "", string third = "")
				: op(move(op)), first(move(first)), second(move(second)), third(move(third))
		{
		}
	};

	typedef string::iterator stringIt;
	typedef vector<string>::iterator tokenIt;

	vector<char> lexemes =
	{
			'>', ';', '=', '+', '-',
			'*', '/', '(', ')', '{',
			'}', '[', ']',
	};

	int lineIndex = 0;
	int tempCount = 0;

	vector<Command> result;

	stack<string> args;
	stack<string> operators;

	map<string, string> numberCommand {
			{"+", "ADD"},
			{"-", "SUB"},
			{"*", "MUL"},
			{"/", "DIV"},
	};

	map<string, int> priority {
			{"+", 1},
			{"-", 1},
			{"*", 2},
			{"/", 2},
	};


	void removeWhitespaces(string& code);

	vector<string>* tokenize(string& code);

	void handleBlock(tokenIt begin, tokenIt end);

	string handleExpression(tokenIt begin, tokenIt end, const string& lastVariable = "");

	void generateCommand();

	void addCommand(Command command);

	bool isLexeme(char symbol);

	bool isNumberOrVariable(const string& variable);

	bool isOperator(string& token);
	
	tokenIt getTokenFrom(tokenIt it, string terminator);

public:

	string compile(string code);
};


#endif
