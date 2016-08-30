#ifndef _STATE_H
#define _STATE_H

#include "Variable.h"

#include <vector>
#include <set>

class State
{
public:
	std::vector<Variable> Variables;
	std::set<unsigned int> ExpandedVariables;

	double Fitness;

	State();

	bool operator<(const State &Right) const;
	bool operator==(const State &Right) const;
};

class PointerComparator
{
public:
	bool operator()(const State *const Left, const State *const Right) const;
};

#endif