#ifndef PROGRAMMINGLANGUAGE_VIRTUALMACHINE_H
#define PROGRAMMINGLANGUAGE_VIRTUALMACHINE_H

#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

class VirtualMachine
{
private:
	map<string, double> variables;

	vector<pair<string, vector<string>>> steps;
	int stepIndex = 0;

	map<string, function<void(vector<string>)>> functions =
			{
					{
							"READ",
							[this](vector<string> params)
							{
								double variable;
								cin >> variable;
								variables[params[0]] = variable;
							}
					},
					{
							"WRITE",
							[this](vector<string> params)
							{
								cout << getVariable(params[0]) << endl;
							}
					},
					{
							"ADD",
							[this](vector<string> params)
							{
								double a = getVariable(params[0]);
								double b = getVariable(params[1]);
								variables[params[2]] = a + b;
							}
					},
					{
							"SUB",
							[this](vector<string> params)
							{
								double a = getVariable(params[0]);
								double b = getVariable(params[1]);
								variables[params[2]] = a - b;
							}
					},
					{
							"DIV",
							[this](vector<string> params)
							{
								double a = getVariable(params[0]);
								double b = getVariable(params[1]);
								variables[params[2]] = a / b;
							}
					},
					{
							"MUL",
							[this](vector<string> params)
							{
								double a = getVariable(params[0]);
								double b = getVariable(params[1]);
								variables[params[2]] = a * b;
							}
					},
					{
							"GOTO",
							[this](vector<string> params)
							{
								stepIndex = stoi(params[0]) - 1;
							}
					},
					{
							"GOTOIF",
							[this](vector<string> params)
							{
								double variable = getVariable(params[0]);
								if (variable != 0)
								{
									stepIndex = stoi(params[1]) - 1;
								}
							}
					},
					{
							"GOTOIFNOT",
							[this](vector<string> params)
							{
								double variable = getVariable(params[0]);
								if (variable == 0)
								{
									stepIndex = stoi(params[1]) - 1;
								}
							}
					},
					{
							"COPY",
							[this](vector<string> params)
							{
								double value = getVariable(params[0]);
								variables[params[1]] = value;
							}
					}
			};


	void parseCommands(string&);

	void executeSteps();

	double getVariable(string);

public:
	void run(string);
};


#endif
