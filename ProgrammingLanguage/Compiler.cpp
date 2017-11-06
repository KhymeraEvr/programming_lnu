#include "Compiler.h"

string Compiler::compile(string code)
{
	lineIndex = 0;

	removeWhitespaces(code);

	auto tokens = tokenize(code);

	handleBlock(tokens->begin(), tokens->end());

	delete tokens;

	stringstream _result;

	for (Command& command : result)
	{
		_result << command.op << ' ' << command.first;
		if (!command.second.empty())
		{
			_result << ' ' << command.second;

			if (!command.third.empty())
			{
				_result << ' ' << command.third;
			}
		}
		_result << endl;
	}

	return _result.str();
}

void Compiler::removeWhitespaces(string& code)
{
	auto end = remove_if(code.begin(), code.end(), ::isspace);
	code.erase(end, code.end());
}

vector<string>* Compiler::tokenize(string& code)
{
	auto tokens = new vector<string>();
	auto leftIt = code.begin();

	for (auto rightIt = code.begin(); rightIt != code.end(); ++rightIt)
	{
		if (isLexeme(*rightIt))
		{
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

void Compiler::handleBlock(tokenIt begin, tokenIt end)
{
	static int innerFunc = 0;

	for (auto it = begin; it != end; ++it)
	{
		string tokenValue = *it;

		if (tokenValue == "read" || tokenValue == "write")
		{
			// skip '>' and read/write variable
			it += 2;
			transform(tokenValue.begin(), tokenValue.end(), tokenValue.begin(), ::toupper);
			addCommand(Command(tokenValue, *it));
		}
		else if (*(it + 1) == "=")
		{
			auto endExpression = getTokenFrom(it, ";");
			handleExpression(it + 2, endExpression, *it);
			it = endExpression;
		}
		else if (tokenValue == "if")
		{
			string resultVariable = handleExpression(it + 2, getTokenFrom(it, "]"));

			int beginIfIndex = lineIndex;

			it = getTokenFrom(it, "{") + 1;
			auto endBlock = getTokenFrom(it, "}");
			
			innerFunc++;
			handleBlock(it, endBlock);
			innerFunc--;

			result.insert(result.begin() + beginIfIndex, Command("GOTOIFNOT", resultVariable, to_string(lineIndex + 1)));
			lineIndex++;
			it = endBlock;
		}
		else if (tokenValue == "while")
		{
			auto endExpression = getTokenFrom(it, "]");

			string resultVariable = handleExpression(it + 2, endExpression);

			it = endExpression;
			auto endBlock = getTokenFrom(it, "}");

			int beginWhileIndex = lineIndex;

			handleBlock(it + 2, endBlock);

			result.insert(result.begin() + beginWhileIndex, Command("GOTOIFNOT", resultVariable, to_string(lineIndex + 2)));
			lineIndex++;

			addCommand(Command("GOTO", to_string(beginWhileIndex)));

			it = endBlock;
		}
	}
}

string Compiler::handleExpression(Compiler::tokenIt begin, Compiler::tokenIt end, const string& lastVariable)
{
	if (distance(begin, end) == 1)
	{
		string resultVariable = lastVariable.empty() ? "t" + to_string(tempCount++) : lastVariable;
		addCommand(Command("COPY", *begin, resultVariable));
		return lastVariable;
	}

	for (auto it = begin; it != end; ++it)
	{
		string token = *it;

		if (isNumberOrVariable(token))
		{
			args.push(token);
		}
		else if (isOperator(token))
		{
			while (!operators.empty() && isOperator(operators.top()) && priority[operators.top()] >= priority[token])
			{
				generateCommand();
			}
			operators.push(token);
		}
		else if (token == "(")
		{
			operators.push(token);
		}
		else if (token == ")")
		{
			while (operators.top() != "(")
			{
				generateCommand();
			}
			operators.pop();
		}
	}

	while (!operators.empty())
	{
		if (operators.top() == "(" || operators.top() == ")")
		{
			throw invalid_argument("Invalid argument");
		}
		generateCommand();
	}

	Command& lastCommand = result.back();
	if (!lastVariable.empty())
	{
		lastCommand.third = lastVariable;
	}

	return lastCommand.third;
}

void Compiler::generateCommand()
{
	string op = operators.top(); operators.pop();
	string rhs = args.top(); args.pop();
	string lhs = args.top(); args.pop();

	string resultVariable = "t" + to_string(tempCount++);
	addCommand(Command(numberCommand[op], lhs, rhs, resultVariable));
	args.push(resultVariable);
}

void Compiler::addCommand(Command command)
{
	result.push_back(command);
	lineIndex++;
}

bool Compiler::isLexeme(char symbol)
{
	return find(lexemes.begin(), lexemes.end(), symbol) != lexemes.end();
}

bool Compiler::isNumberOrVariable(const string& value)
{
	bool isNumber = true;
	for (char symbol : value)
		if ((symbol < '0' || symbol > '9') && symbol != '.')
		{
			isNumber = false;
		}

	if (isNumber)
	{
		return true;
	}

	for (char symbol : value)
		if (!::isalpha(symbol))
		{
			return false;
		}

	return true;
}

bool Compiler::isOperator(string& token)
{
	return numberCommand.count(token) == 1;
}

Compiler::tokenIt Compiler::getTokenFrom(Compiler::tokenIt it, string terminator)
{
	int shift = 1;
	while (*(it + shift) != terminator)
	{
		shift++;
	}
	return it + shift;
}
