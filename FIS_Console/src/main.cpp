/*
	File:	main.cpp
	Author:	Tom Haygarth
	Description:	An application that uses a Fuzzy Inference system to produce a steering value between -1.0 and 1.0
					for an AI agent. Where -1.0 is considered "full left" and 1.0 is "full right"
*/

#include <iostream>
#include "fuzzy\FLogicModule.h"


using std::cout;
using std::cin;
using std::endl;

FLogicModule mFuzzyModule;

float Distance;
float Velocity;
float OutputVelocity;


// Application starting point
int main()
{
	// create our distance input variable
	FuzzyVariable* distVar = mFuzzyModule.CreateVariable("Distance");

	// create our sets for the distance variable
	TriangleSet* Distance_left = distVar->CreateTriangleSet("left", -1.0f, -1.0f, -0.2f);
	TriangleSet* Distance_centre = distVar->CreateTriangleSet("centre", -0.4f, 0.0f, 0.4f);
	TriangleSet* Distance_right = distVar->CreateTriangleSet("right", 0.2f, 1.0f, 1.0f);

	// create our velocity input variable
	FuzzyVariable* velVar = mFuzzyModule.CreateVariable("Velocity");

	// create our sets for the distance variable
	TriangleSet* Velocity_left = velVar->CreateTriangleSet("left", -1.0f, -1.0f, -0.3f);
	TriangleSet* Velocity_forward = velVar->CreateTriangleSet("forward", -0.8f, 0.0f, 0.8f);
	TriangleSet* Velocity_right = velVar->CreateTriangleSet("right", 0.3f, 1.0f, 1.0f);

	// create our delta velocity output variable
	FuzzyVariable* dVelVar = mFuzzyModule.CreateVariable("deltaVelocity");

	// create our sets for the distance variable
	TriangleSet* delta_LeftVel = dVelVar->CreateTriangleSet("left",			 -1.0f, -1.0f, -0.6f);
	TriangleSet* delta_ForwardVel = dVelVar->CreateTriangleSet("forward",	 -0.5f, +0.0f, +0.5f);
	TriangleSet* delta_RightVel = dVelVar->CreateTriangleSet("right",		 +0.6f, +1.0f, +1.0f);
	TriangleSet* delta_SmallRightVel = dVelVar->CreateTriangleSet("sRight",	 +0.0f, +0.5f, +0.8f);
	TriangleSet* delta_SmallLeftVel = dVelVar->CreateTriangleSet("sLeft",	 -0.8f, -0.5f, +0.0f);

	// create our fuzzy rules
	mFuzzyModule.CreateRule(Distance_left, FuzzyRule::AND, Velocity_left,		delta_RightVel);
	mFuzzyModule.CreateRule(Distance_left, FuzzyRule::AND, Velocity_forward,	delta_SmallRightVel);
	mFuzzyModule.CreateRule(Distance_left, FuzzyRule::AND, Velocity_right,		delta_ForwardVel);

	mFuzzyModule.CreateRule(Distance_centre, FuzzyRule::AND, Velocity_right,	delta_SmallLeftVel);
	mFuzzyModule.CreateRule(Distance_centre, FuzzyRule::AND, Velocity_forward,	delta_ForwardVel);
	mFuzzyModule.CreateRule(Distance_centre, FuzzyRule::AND, Velocity_left,		delta_SmallRightVel);

	mFuzzyModule.CreateRule(Distance_right, FuzzyRule::AND, Velocity_left,		delta_ForwardVel);
	mFuzzyModule.CreateRule(Distance_right, FuzzyRule::AND, Velocity_forward,	delta_SmallLeftVel);
	mFuzzyModule.CreateRule(Distance_right, FuzzyRule::AND, Velocity_right,		delta_LeftVel);


	char Continue = 'y';

	// create a loop for the application
	while(Continue == 'y')
	{
		// set our inputs for the FIS
		cout << "Set Distance input: ";
		cin >> Distance;

		cout << "Set Velocity input: ";
		cin >> Velocity;

		cout << endl << endl;

		// place the input variables in our system
		mFuzzyModule.SetVariableInput("Distance", Distance);
		mFuzzyModule.SetVariableInput("Velocity", Velocity);

		// calculate our output value
		mFuzzyModule.CalculateRules();

		// Get our output
		OutputVelocity = mFuzzyModule.GetOutput("deltaVelocity") ;

		// reset the triggered rules and all sets in our output variable
		mFuzzyModule.ResetRules();

		// print the results and ask to try new inputs
		cout << "The output velocity is " << OutputVelocity << endl;
		cout << "Would you like to try new inputs? (y/n) ";
		cin >> Continue;
		cout << endl;

	}
}
