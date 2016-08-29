#ifndef _VARIABLE_H
#define _VARIABLE_H

#include <set>

class Variable
{
public:
	bool HasValue;
	unsigned int Value;
	std::set<unsigned int> Domain;

	Variable();
	Variable(const std::set<unsigned int> &Domain);
	Variable(const Variable &Copy);

	bool operator<(const Variable &Right) const
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
	bool operator==(const Variable &Right) const
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
};

#endif