/*
	Note:	I modified the DeFuzzifyCentroid(...) implementation from the Mat Buckland book
			Programming Game AI by Example to work with my implementation of the FIS. Making
			possible to use a range of input values < 0
*/

#include "FuzzyVariable.h"

using std::vector;

FuzzyVariable::FuzzyVariable()
{
	mMaxRange = 1;

	mMinRange = -1;
}

FuzzyVariable::~FuzzyVariable()
{
	for(int i = 0; i < mSets.size(); i++)
	{
		delete mSets[i];
	}

	mSets.clear();
}

TriangleSet* FuzzyVariable::CreateTriangleSet(char* Name, float minPoint, float midPoint, float maxPoint)
{
	TriangleSet* newSet = new TriangleSet(Name,minPoint, midPoint, maxPoint);
	mSets.push_back(newSet);

	return newSet;
}

void FuzzyVariable::SetRange(int minRange, int maxRange)
{
	mMinRange = minRange;
	mMaxRange - maxRange;
}

void FuzzyVariable::CalculateOutput(float input)
{
	if (input < mMinRange)
	{
		input = mMinRange;
	}
	else if (input > mMaxRange)
	{
		input = mMaxRange;
	}
	// loop through all the sets and calculate their DOM
	for(int i = 0; i < mSets.size(); i++)
	{
		mSets[i]->SetInput(input);
		mSets[i]->SetDOM(mSets[i]->CalculateDOM());
	}
}

float FuzzyVariable::DeFuzzifyCentroid(int NumSamples)
{
	//calculate the step size
  double StepSize = (mMaxRange - mMinRange)/(double)(NumSamples -1);

  double TotalArea    = 0.0;
  double SumOfMoments = 0.0;

  //step through the range of this variable in increments equal to StepSize
  //adding up the contribution (lower of CalculateDOM or the actual DOM of this
  //variable's fuzzified value) for each subset. This gives an approximation of
  //the total area of the fuzzy manifold.(This is similar to how the area under
  //a curve is calculated using calculus... the heights of lots of 'slices' are
  //summed to give the total area.)
  //
  //in addition the moment of each slice is calculated and summed. Dividing
  //the total area by the sum of the moments gives the centroid. (Just like
  //calculating the center of mass of an object)
  for (int samp=0; samp<=NumSamples; ++samp)
  {
    //for each set get the contribution to the area. This is the lower of the 
    //value returned from CalculateDOM or the actual DOM of the fuzzified 
    //value itself   
		vector<FuzzySet*>::iterator curSet = mSets.begin();


    for (curSet; curSet != mSets.end(); ++curSet)
    {
		FuzzySet* set = *curSet;
		set->SetInput(mMinRange + samp * StepSize);

      double contribution = 
		  MinOf(set->CalculateDOM(),
		  set->GetDegreeOfMembership());

      TotalArea += contribution;

      SumOfMoments += (mMinRange + samp * StepSize)  * contribution;
    }
  }

  //make sure total area is not equal to zero
  if (0 == TotalArea) return 0.0;
  
  return (SumOfMoments / TotalArea);
}