/*
	File:	FuzzyVariable.cpp
	Author:	Tom Haygarth
	Description:	This is a fuzzy varable. It holds fuzzy sets created using its CreateSet(...) function. 
					It works out the output of the variable by taking in an imput and working out the centroid
					value against its sets.
*/

#ifndef _FUZZY_OUTPUT_H_1_0__
#define _FUZZY_OUTPUT_H_1_0__

#include <vector>
#include "FuzzySet.h"
#include "TriangleSet.h"
#include "..\utils.h"

using std::vector;

class FuzzyVariable
{
public:

	//-- creates and returns a new triangles
	//-- triangle set can then be placed inside a fuzzy and opperator for the rules
	TriangleSet* CreateTriangleSet(char* Name, float minPoint, float midPoint, float maxPoint);

	void CalculateOutput(float input);

	void SetRange(int minRange, int maxRange);

	// Defuzzifys the set using the centroid method
	//--- samples is the numbe of samples that should be used when defuzzyfying. 
	//--- Larger the value the more acurate the defuzzifying
	float DeFuzzifyCentroid(int samples);

	FuzzyVariable();
	~FuzzyVariable();

private:

	vector<FuzzySet*> mSets;

	int mMaxRange, mMinRange;

};

#endif