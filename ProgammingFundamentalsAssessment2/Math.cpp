#include "Math.h"

std::random_device device;
std::mt19937 randomGenerator(device());

int random(int minBound, int maxBound)
{
	//We have to do this because if the ranges aren't
	//ordered then C++ will throw an error
	int trueMin = std::min<int>(minBound, maxBound);
	int trueMax = std::max<int>(maxBound, minBound);

	//Build a uniform distribution
	std::uniform_int_distribution<int> udist(trueMin, trueMax);

	//Sample the distribution using the generator
	return udist(randomGenerator);
}

std::string convertStringToLowercase(std::string input)
{
	for (int i = 0; i < input.length(); i++) { 
		
		input[i] = tolower(input[i]); 	
	} 
	return input;
}


