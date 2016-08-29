#ifndef _ALLDIFFCONSTRAINT_H
#define _ALLDIFFCONSTRAINT_H

#include "Constraint.h"

class AllDiffConstraint
	: public Constraint
{
protected:
	bool _Holds(const std::vector<Variable> &StateVariables) const;
	bool _Enforce(std::vector<Variable> &StateVariables, std::set<unsigned int> &ModifiedVariables) const;
};

#endif