#include "SumConstraint.h"

bool SumConstraint::_Holds(const std::vector<Variable> &StateVariables) const
{
	unsigned int Sum = 0;
	for (unsigned int x = 0; x < Variables.size(); x++)
	{
		if (!StateVariables[Variables[x]].HasValue)
			return false;

		Sum += StateVariables[Variables[x]].Value;
	}

	return this->Sum == Sum;
}
bool SumConstraint::_Enforce(std::vector<Variable> &StateVariables, std::set<unsigned int> &ModifiedVariables) const
{
	unsigned int CurrentSum = 0;
	unsigned int LeastExtra = 0;
	unsigned int HasValue = 0;
	for (unsigned int x = 0; x < Variables.size(); x++)
	{
		if (StateVariables[Variables[x]].HasValue)
		{
			CurrentSum += StateVariables[Variables[x]].Value;
			HasValue++;
		}
		else
			LeastExtra += *StateVariables[Variables[x]].Domain.begin();
	}

	for (unsigned int x = 0; x < Variables.size(); x++)
	{
		for (std::set<unsigned int>::const_iterator i = StateVariables[Variables[x]].Domain.begin(); i != StateVariables[Variables[x]].Domain.end(); i++)
		{
			// Existing sum + current value in the domain + smallest extra added by using lowest in each domain - smallest from this domain > Allowed maximum sum?
			if (CurrentSum + *i + LeastExtra - *StateVariables[Variables[x]].Domain.begin() > Sum)
			{
				i = StateVariables[Variables[x]].Domain.erase(i);
				ModifiedVariables.emplace(Variables[x]);
				if (i != StateVariables[Variables[x]].Domain.begin())
					i--;

				if (StateVariables[Variables[x]].Domain.size() == 0)
					return false;
			}
		}
	}

	if (HasValue == Variables.size()) // All variables have value
		return CurrentSum == Sum;
	else
		return true;
}