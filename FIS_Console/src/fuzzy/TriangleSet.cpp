
#include "TriangleSet.h"

TriangleSet::TriangleSet(char* SetName, float minPoint, float midPoint, float maxPoint)
{
	mName = SetName;

	mMinPoint = minPoint;
	mMidPoint = midPoint;
	mMaxPoint = maxPoint;
}


float TriangleSet::CalculateDOM()
{
	// makesure the input is within the triangle
	if(mInput > mMaxPoint || mInput < mMinPoint)
	{
		// otherwise set the Degree of Membership to 0.0 and return the function
		return 0.0f;
	}

	// define a variable for the distance between the mid point, and either the min or max point
	float offset;
	float gradient;

	// check if we're on the right hand side of our tringle
	if(mInput > mMidPoint)
	{

		offset = mMaxPoint - mMidPoint;

		// work out the gradient of the slope the input is on
		gradient = 1.0f/ -offset;


		return gradient * (mInput - mMidPoint) + 1.0;

	}

	else if(mInput < mMidPoint)
	{

		// work out the offset distance between the minPoint and midpoint of the triangle
		offset = mMidPoint - mMinPoint;

		// work out the gradient of the slope the input is on
		gradient = 1.0f/ offset;

		return gradient * (mInput - (mMidPoint - offset));

	}

	else
	{
		return 1.0f;
	}

}