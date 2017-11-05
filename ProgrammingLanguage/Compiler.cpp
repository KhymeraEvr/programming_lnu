#include "Compiler.h"

string Compiler::compile(string code)
{
	// makes the code easier to tokenize
	removeWhitespaces(code);

	// returns pointer to vector<Token>
	auto tokens = tokenize(code);

	// compiles tokens to VM code
	string result = compile(tokens);

	delete tokens;

	return result;
}

void Compiler::removeWhitespaces(string& code)
{
	auto end = remove_if(code.begin(), code.end(), ::isspace);
	code.erase(end, code.end());
}

vector<Compiler::Token>* Compiler::tokenize(string& code)
{
	auto tokens = new vector<Compiler::Token>();
	auto leftIt = code.begin();

	for (auto rightIt = code.begin(); rightIt != code.end(); ++rightIt)
	{
		if (isLexeme(*rightIt))
		{
			cout << "IS LEXEME:" << *rightIt << endl;
			if (leftIt != rightIt)
			{
				tokens->push_back(string(leftIt, rightIt));
			}
			tokens->push_back(string(1, *rightIt));
			leftIt = rightIt;
			++leftIt;
		}
	}

	return tokens;
}

bool Compiler::isLexeme(char symbol)
{
	return find(lexemes.begin(), lexemes.end(), symbol) != lexemes.end();
}

string Compiler::compile(vector<Compiler::Token>* tokens)
{
	return "NOTHING";
}