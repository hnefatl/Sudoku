#ifndef _CONSTRAINT_H
#define _CONSTRAINT_H

#include <vector>
#include <set>

#include "Variable.h"

class Constraint
{
public:
	std::vector<unsigned int> Variables;

protected:
	virtual bool _Holds(const std::vector<Variable> &StateVariables) const = 0;
	virtual bool _Enforce(std::vector<Variable> &StateVariables, std::set<unsigned int> &ModifiedVariables) const = 0;

public:
	bool Holds(const std::vector<Variable> &StateVariables) const;
	// Enforces the constraint on the variables. Returns true if successful, returns false if the constraint cannot be satisfied.
	bool Enforce(std::vector<Variable> &StateVariables, std::set<unsigned int> &ModifiedVariables) const;
};

#endif