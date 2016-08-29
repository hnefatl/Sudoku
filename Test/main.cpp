#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>

#include <Solver.h>
#include <AllDiffConstraint.h>

int main(int argc, char *argv[])
{
	std::vector<Variable> Variables;
	std::vector<Constraint *> Constraints;

	Variables.resize(2);
	for (unsigned int x = 0; x < Variables.size(); x++)
		Variables[x] = Variable({ 1, 2 });

	Constraint *New = new AllDiffConstraint();
	for (unsigned int x = 0; x < Variables.size(); x++)
		New->Variables.push_back(x);
	Constraints.push_back(New);

	Solution s = Solve(Variables, Constraints);

	if (s.Successful)
	{
		for (unsigned int x = 0; x < s.State.size(); x++)
			std::cout << s.State[x].Value;
	}
	else
		std::cout << "Failed to solve." << std::endl;

	_getch();
}