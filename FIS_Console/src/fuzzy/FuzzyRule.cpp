
#include "FuzzyRule.h"

FuzzyRule::FuzzyRule(FuzzySet* InputSet1, RuleType type, FuzzySet* InputSet2, FuzzySet* OutputSet)
{
	mInputSets[0] = InputSet1;
	mInputSets[1] = InputSet2;

	mType = type;

	mOutputSet = OutputSet;
}

void FuzzyRule::CalculateRule()
{
	// the Degree Of Membership
	float DOM = 0.0f;

	// make sure that both sets that fit this rule both have a degree of membership
	if(mInputSets[0]->GetDegreeOfMembership() <= 0.0f && mInputSets[1]->GetDegreeOfMembership() <= 0.0f)
	{
		//mOutputSet->SetDOM(0.0f);
	}

	else if(mType == AND)
	{
		// get the smallest of the two 
		DOM = MinOf(mInputSets[0]->GetDegreeOfMembership(), mInputSets[1]->GetDegreeOfMembership());
	}

	else
	{
		// todo: add OR code here
	}

	// makesure the DOM is the largest as the sets can be shared between rules
	if(DOM > mOutputSet->GetDegreeOfMembership())
	{
		// set the DOM
		mOutputSet->SetDOM(DOM);
	}
}

void FuzzyRule::ResetOutputDOM()
{
	mOutputSet->SetDOM(0.0f);
}