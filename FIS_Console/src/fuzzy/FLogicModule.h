/*
	File:	FuzzyVariable.cpp
	Author:	Tom Haygarth
*/

#ifndef _FUZZY_LOGIC_MODULE_H_1_0__
#define _FUZZY_LOGIC_MODULE_H_1_0__

#include <map>
#include <string>
#include <vector>
#include "FuzzyVariable.h"
#include "FuzzyRule.h"

using namespace std;

class FLogicModule
{
public:

	~FLogicModule();

	// create variable
	FuzzyVariable* CreateVariable(string Name);

	// create rule;
	FuzzyRule* CreateRule(FuzzySet* InputSet1, FuzzyRule::RuleType type, FuzzySet* InputSet2, FuzzySet* OutputSet);

	// loop through rules and get the DOM of the anded sets and if they return higher than 0 do shizz
	void SetVariableInput(string VariableName, float input);

	// calculate variables
	void CalculateRules();

	// returns the defuzzified output value from the variable
	float GetOutput(string Variable);

	void ResetRules();

private:

	vector<FuzzyRule*> mRule;
	map<string, FuzzyVariable*> mVariables;
};

#endif