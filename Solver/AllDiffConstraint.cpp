#include "AllDiffConstraint.h"

bool AllDiffConstraint::_Holds(const std::vector<Variable> &StateVariables) const
{
	std::set<unsigned int> Checker;

	for (unsigned int x = 0; x < Variables.size(); x++)
	{
		if (!StateVariables[Variables[x]].HasValue)
			return false;
		if (!Checker.emplace(StateVariables[Variables[x]].Value).second)
			return false;
	}

	return true;
}

bool AllDiffConstraint::_Enforce(std::vector<Variable> &StateVariables, std::set<unsigned int> &ModifiedVariables) const
{
	for (unsigned int x = 0; x < Variables.size(); x++)
	{
		if (StateVariables[Variables[x]].HasValue)
		{
			for (unsigned int y = 0; y < Variables.size(); y++)
			{
				if (x == y)
					continue;

				std::set<unsigned int>::iterator i = StateVariables[Variables[y]].Domain.find(StateVariables[Variables[x]].Value);
				if (i != StateVariables[Variables[y]].Domain.end())
				{
					StateVariables[Variables[y]].Domain.erase(i);
					ModifiedVariables.emplace(Variables[y]);
					if (StateVariables[Variables[y]].Domain.size() == 0)
						return false;
				}
			}
		}
	}

	return true;
}
