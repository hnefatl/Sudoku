#include "State.h"

State::State()
{
}

bool State::operator<(const State &Right) const
{
	if (Fitness < Right.Fitness)
		return true;
	else if (Fitness > Right.Fitness)
		return false;
	else
		return std::lexicographical_compare(Variables.begin(), Variables.end(), Right.Variables.begin(), Right.Variables.end());
}
bool State::operator==(const State &Right) const
{
	return Variables == Right.Variables;
}


bool PointerComparator::operator()(const State *const Left, const State *const Right) const
{
	return *Left < *Right;
}