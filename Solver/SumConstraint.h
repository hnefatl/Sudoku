#ifndef _SUMCONSTRAONT_H
#define _SUMCONSTRAINT_H

#include "Constraint.h"

class SumConstraint
	: public Constraint
{
public:
	unsigned int Sum;

protected:
	virtual bool _Holds(const std::vector<Variable> &StateVariables) const;
	virtual bool _Enforce(std::vector<Variable> &StateVariables, std::set<unsigned int> &ModifiedVariables) const;
};

#endif