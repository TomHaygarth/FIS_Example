/*
	File:	FuzzyVariable.cpp
	Author:	Tom Haygarth
*/

#ifndef _FUZZY_RULE_H_1_0__
#define _FUZZY_RULE_H_1_0__

#include "..\utils.h"
#include "FuzzySet.h"

class FuzzyRule
{
public:

	enum RuleType {	AND, OR	};

	FuzzyRule(FuzzySet* InputSet1, RuleType type, FuzzySet* InputSet2, FuzzySet* OutputSet);

	void CalculateRule();

	void ResetOutputDOM();

private:

	FuzzySet* mInputSets[2];

	FuzzySet* mOutputSet;

	RuleType mType;
};

#endif