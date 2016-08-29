#include "Variable.h"

Variable::Variable()
{
	HasValue = false;
	Value = 0;
}
Variable::Variable(const std::set<unsigned int> &Domain)
{
	HasValue = false;
	Value = 0;
	this->Domain = Domain;
}
Variable::Variable(const Variable &Copy)
{
	HasValue = Copy.HasValue;
	Value = Copy.Value;
	Domain = Copy.Domain;
}