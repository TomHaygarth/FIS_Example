/*
	File:	FuzzyVariable.cpp
	Author:	Tom Haygarth
*/


#include "FLogicModule.h"

FLogicModule::~FLogicModule()
{
	for(int i = 0; i < mRule.size(); i++)
	{
		delete mRule[i];
	}

	mRule.clear();

	// create an itterator to delete each variable stored in the map
	map<string, FuzzyVariable*>::iterator varIt = mVariables.begin();

	for(varIt; varIt != mVariables.end(); varIt++)
	{
		delete varIt->second;
	}

	mVariables.clear();
}

FuzzyVariable* FLogicModule::CreateVariable(string Name)
{
	FuzzyVariable* var = new FuzzyVariable();

	mVariables[Name] = var;

	return var;
}

FuzzyRule* FLogicModule::CreateRule(FuzzySet* InputSet1, FuzzyRule::RuleType type, FuzzySet* InputSet2, FuzzySet* OutputSet)
{
	// create a new rule
	FuzzyRule* rule = new FuzzyRule(InputSet1, type, InputSet2, OutputSet);

	// add rule to our vector
	mRule.push_back(rule);

	// return the rule
	return rule;
}

void FLogicModule::SetVariableInput(string VariableName, float input)
{
	mVariables[VariableName]->CalculateOutput(input);
}

void FLogicModule::CalculateRules()
{
	// loop through all rules
	for(int i = mRule.size() - 1; i >= 0; i--)
	{
		// calculate the rule
		mRule[i]->CalculateRule();
	}
}

float FLogicModule::GetOutput(string Variable)
{
	return mVariables[Variable]->DeFuzzifyCentroid(16);
}

void FLogicModule::ResetRules()
{
	vector<FuzzyRule*>::iterator curRule = mRule.begin();
	for (curRule; curRule != mRule.end(); ++curRule)
	{
		(*curRule)->ResetOutputDOM();
	}
}
