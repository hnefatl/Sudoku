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

bool Variable::operator<(const Variable &Right) const
{
	if (!HasValue && Right.HasValue)
		return true;
	else if (HasValue && !Right.HasValue)
		return false;
	else if (HasValue && Right.HasValue)
		return Value < Right.Value;
	else
	{
		if (Domain.size() < Right.Domain.size())
			return true;
		else if (Domain.size() > Right.Domain.size())
			return false;
		else
			return std::lexicographical_compare(Domain.begin(), Domain.end(), Right.Domain.begin(), Right.Domain.end());
	}
}
bool Variable::operator==(const Variable &Right) const
{
	if (HasValue != Right.HasValue)
		return false;
	else if (HasValue && Right.HasValue)
	{
		if (Value != Right.Value)
			return false;
	}
	return Domain == Right.Domain;
}