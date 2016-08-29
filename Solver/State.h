#ifndef _STATE_H
#define _STATE_H

#include "Variable.h"

#include <vector>

class State
{
public:
	std::vector<Variable> Variables;
	double Fitness;

	State();

	bool operator<(const State &Right) const
	{
		if (Fitness < Right.Fitness)
			return true;
		else if (Fitness > Right.Fitness)
			return false;
		else
			return std::lexicographical_compare(Variables.begin(), Variables.end(), Right.Variables.begin(), Right.Variables.end());
	}
	bool operator==(const State &Right) const
	{
		return Variables == Right.Variables;
	}
};

class PointerComparator
{
public:
	bool operator()(const State *const Left, const State *const Right) const
	{
		if (Left->Variables == Right->Variables)
			int x = 0;

		return *Left < *Right;
	}
};

#endif