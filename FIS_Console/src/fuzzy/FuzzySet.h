/*
	File:	FuzzyVariable.cpp
	Author:	Tom Haygarth
*/

#ifndef _FUZZY_LOGIC_SET_H_1_0__
#define _FUZZY_LOGIC_SET_H_1_0__

class FuzzySet
{
public:

	void SetInput(float inputValue) {mInput = inputValue;}
	float GetDegreeOfMembership() {return mDOM;}
	char* GetName()	{return mName;}
	void SetDOM(float DOM) {mDOM = DOM;}


	virtual float CalculateDOM() = 0;

protected:

	char* mName;

	float mInput;
	float mDOM;
};

#endif