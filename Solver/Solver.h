#ifndef _SOLVER_H
#define _SOLVER_H

#include "State.h"
#include "Constraint.h"

#include <functional>
#include <time.h>

// Returns the percentage of filled cells
double DefaultEvaluator(const std::vector<Variable> &State, const std::vector<Constraint *> &Constraints);

class Solution
{
public:
	std::vector<Variable> State;
	bool Successful;
	double Fitness;
	clock_t Time;

	Solution();
	Solution(const std::vector<Variable> &State, const double Fitness, const clock_t Time);
};

extern bool SolverVerbose;

Solution Solve(const std::vector<Variable> &Variables, const std::vector<Constraint *> &Constraints);
Solution Solve(const std::vector<Variable> &Variables, const std::vector<Constraint *> &Constraints, const double OptimalThreshold);
Solution Solve(const std::vector<Variable> &Variables, const std::vector<Constraint *> &Constraints, const std::function<double(const std::vector<Variable> &, const std::vector<Constraint *> &)> &Evaluator);
Solution Solve(const std::vector<Variable> &Variables, const std::vector<Constraint *> &Constraints, const std::function<double(const std::vector<Variable> &, const std::vector<Constraint *> &)> &Evaluator, const double OptimalThreshold);

bool UpdateConstraints(std::vector<Variable> &Variables, const unsigned int Index, const std::vector<Constraint *> &Constraints, const std::vector<std::vector<Constraint *>> &LinkedConstraints);

#endif