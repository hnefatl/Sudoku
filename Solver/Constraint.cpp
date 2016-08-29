#include "Constraint.h"

bool Constraint::Holds(const std::vector<Variable> &StateVariables) const
{
	return _Holds(StateVariables);
}

bool Constraint::Enforce(std::vector<Variable> &StateVariables, std::set<unsigned int> &ModifiedVariables) const
{
	if (!_Enforce(StateVariables, ModifiedVariables))
		return false;

	for (unsigned int x = 0; x < Variables.size(); x++)
	{
		if (StateVariables[Variables[x]].Domain.size() == 1)
		{
			StateVariables[Variables[x]].Value = *StateVariables[Variables[x]].Domain.begin();
			StateVariables[Variables[x]].HasValue = true;
		}
		else if (StateVariables[Variables[x]].Domain.size() == 0)
			return false;
	}

	return true;
}