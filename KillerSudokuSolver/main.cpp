#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>

#include <Solver.h>
#include <AllDiffConstraint.h>
#include <SumConstraint.h>

int main(int argc, char *argv[])
{
	std::ifstream In("KillerSudoku.txt");
	if (!In.good())
		return -1;

	std::vector<Variable> Variables;
	std::vector<Constraint *> Constraints;

	for (unsigned int x = 0; x < 9 * 9; x++)
		Variables.push_back(Variable({ 1, 2, 3, 4, 5, 6, 7, 8, 9 }));

	for (unsigned int x = 0; x < 9; x++)
	{
		Constraint *New = new AllDiffConstraint();
		for (unsigned int y = 0; y < 9; y++)
			New->Variables.push_back(x + 9 * y);
		Constraints.push_back(New);
	}
	for (unsigned int y = 0; y < 9; y++)
	{
		Constraint *New = new AllDiffConstraint();
		for (unsigned int x = 0; x < 9; x++)
			New->Variables.push_back(x + 9 * y);
		Constraints.push_back(New);
	}
	for (unsigned int y = 0; y < 3; y++)
	{
		for (unsigned int x = 0; x < 3; x++)
		{
			Constraint *New = new AllDiffConstraint();
			for (unsigned int w = 0; w < 3; w++)
			{
				for (unsigned int h = 0; h < 3; h++)
					New->Variables.push_back((3 * y * 9) + (x * 3) + (h * 9) + w);
			}
			Constraints.push_back(New);
		}
	}

	while (!In.eof())
	{
		unsigned int Sum, Cells;
		In >> Sum >> Cells;
		
		Constraint *New = new SumConstraint();
		((SumConstraint *)New)->Sum = Sum;
		for (unsigned int x = 0; x < Cells; x++)
		{
			unsigned int w, h;
			In >> w >> h;
			New->Variables.push_back(h * 9 + w);
		}
		Constraints.push_back(New);
	}

	Solution s = Solve(Variables, Constraints);

	if (s.Successful)
	{
		for (unsigned int y = 0; y < 9; y++)
		{
			for (unsigned int x = 0; x < 9; x++)
				std::cout << s.State[y * 9 + x].Value;
			std::cout << std::endl;
		}
	}
	else
		std::cout << "Failed to solve." << std::endl;

	_getch();
}