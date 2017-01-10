/*
	File:	FuzzyVariable.cpp
	Author:	Tom Haygarth
*/

#ifndef _FUZZY_TRIANGLE_SET_H_1_0__
#define _FUZZY_TRIANGLE_SET_H_1_0__

#include "FuzzySet.h"

class TriangleSet : public FuzzySet
{
public:

	TriangleSet(char* SetName, float minPoint, float midPoint, float maxPoint);

	float CalculateDOM();

private:
	
	float mMinPoint;
	float mMidPoint;
	float mMaxPoint;
};

#endif