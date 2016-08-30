#include "Solver.h"

#include <queue>
#include <iostream>
#include <iomanip>

double DefaultEvaluator(const std::vector<Variable> &Variables, const std::vector<Constraint *> &Constraints)
{
	unsigned int HaveValue = 0;
	for (unsigned int x = 0; x < Variables.size(); x++)
	{
		if (Variables[x].HasValue)
			HaveValue++;
	}
	return (double)HaveValue / (double)Variables.size();
}

bool SolverVerbose = false;

Solution Solve(const std::vector<Variable> &Variables, const std::vector<Constraint *> &Constraints)
{
	return Solve(Variables, Constraints, 1.0);
}
Solution Solve(const std::vector<Variable> &Variables, const std::vector<Constraint *> &Constraints, const double OptimalThreshold)
{
	return Solve(Variables, Constraints, DefaultEvaluator, OptimalThreshold);
}
Solution Solve(const std::vector<Variable> &Variables, const std::vector<Constraint *> &Constraints, const std::function<double(const std::vector<Variable> &, const std::vector<Constraint *> &)> &Evaluator)
{
	return Solve(Variables, Constraints, Evaluator, 1.0);
}
Solution Solve(const std::vector<Variable> &Variables, const std::vector<Constraint *> &Constraints, const std::function<double(const std::vector<Variable> &, const std::vector<Constraint *> &)> &Evaluator, const double OptimalThreshold)
{
	clock_t StartClock = clock();
	// Generate relationship from Variable->Constraint for efficiency
	std::vector<std::vector<Constraint *>> LinkedConstraints;
	LinkedConstraints.resize(Variables.size());
	for (unsigned int x = 0; x < Constraints.size(); x++)
	{
		for (unsigned int y = 0; y < Constraints[x]->Variables.size(); y++)
			LinkedConstraints[Constraints[x]->Variables[y]].push_back(Constraints[x]);
	}


	std::set<State *, PointerComparator> Visited;
	std::priority_queue<State *, std::vector<State *>, PointerComparator> Pending;
	State *Start = new State();
	Start->Variables = Variables;
	for (unsigned int x = 0; x < Variables.size(); x++)
	{
		if (!UpdateConstraints(Start->Variables, x, Constraints, LinkedConstraints))
			return Solution();
	}
	Start->Fitness = Evaluator(Start->Variables, Constraints);
	Visited.emplace(Start);
	Pending.push(Start);

	unsigned int Generated = 0;
	while (!Pending.empty() && Pending.top()->Fitness < OptimalThreshold)
	{
		const State Seed = *Pending.top();

		if (SolverVerbose)
			std::cout << "Pending: " << Pending.size() << "    Visited: " << Visited.size() << "    Generated: " << Generated << "    Greatest Fitness: " << std::setprecision(20) << Seed.Fitness << std::endl;

		Pending.pop();
		for (unsigned int x = 0; x < Seed.Variables.size(); x++)
		{
			if (!Seed.Variables[x].HasValue)
			{
				for (std::set<unsigned int>::iterator DomainVal = Seed.Variables[x].Domain.begin(); DomainVal != Seed.Variables[x].Domain.end(); DomainVal++)
				{
					State *New = new State();
					New->Variables = Seed.Variables;
					New->Variables[x].Value = *DomainVal;
					New->Variables[x].HasValue = true;
					New->Variables[x].Domain.clear();
					New->Variables[x].Domain.emplace(*DomainVal);
					Generated++;

					if (!UpdateConstraints(New->Variables, x, Constraints, LinkedConstraints))
					{
						delete New;
						continue;
					}
					New->Fitness = Evaluator(New->Variables, Constraints);

					if (Visited.emplace(New).second) // Store in pending if not already visited
						Pending.push(New);
				}
			}
		}
	}

	clock_t EndClock = clock();

	Solution s;
	if (Pending.empty())
		s = Solution();
	else
		s = Solution(Pending.top()->Variables, Pending.top()->Fitness, EndClock - StartClock);

	for (std::set<State *>::iterator i = Visited.begin(); i != Visited.end(); i++)
		delete *i;

	return s;
}

bool UpdateConstraints(std::vector<Variable> &Variables, const unsigned int Index, const std::vector<Constraint *> &Constraints, const std::vector<std::vector<Constraint *>> &LinkedConstraints)
{
	std::set<unsigned int> Pending;
	Pending.emplace(Index);
	while (!Pending.empty())
	{
		unsigned int VariableIndex = *Pending.begin();
		for (std::vector<Constraint *>::const_iterator Constraint = LinkedConstraints[VariableIndex].begin(); Constraint != LinkedConstraints[VariableIndex].end(); Constraint++)
		{
			if (!(*Constraint)->Enforce(Variables, Pending))
				return false;
		}
		Pending.erase(Pending.begin());
	}

	return true;
}

Solution::Solution()
{
	Successful = false;
	Fitness = 0;
	Time = 0;
}
Solution::Solution(const std::vector<Variable> &State, const double Fitness, const clock_t Time)
{
	Successful = true;
	this->State = State;
	this->Fitness = Fitness;
	this->Time = Time;
}