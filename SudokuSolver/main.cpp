#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>

#include <Solver.h>
#include <AllDiffConstraint.h>

double Evaluator(const std::vector<Variable> &State, const std::vector<Constraint *> &Constraints)
{
	double CellsFilledWeighting = 0.6;
	double CellsFilled = DefaultEvaluator(State, Constraints);

	unsigned int Satisfied = 0;
	for (unsigned int x = 0; x < Constraints.size(); x++)
	{
		if (Constraints[x]->Holds(State))
			Satisfied++;
	}
	return CellsFilled * CellsFilledWeighting + ((double)Satisfied / (double)Constraints.size()) * (1 - CellsFilledWeighting);
}

int main(int argc, char *argv[])
{
	std::ifstream In("Sudoku.txt");
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

	for (unsigned int y = 0; y < 9; y++)
	{
		std::string Line;
		In >> Line;

		if (Line.size() != 9)
			return -1;
		for (unsigned int x = 0; x < Line.size(); x++)
		{
			if (Line[x] >= '1' && Line[x] <= '9')
			{
				Variables[y * 9 + x].HasValue = true;
				Variables[y * 9 + x].Value = Line[x] - '0';
				Variables[y * 9 + x].Domain.clear();
				Variables[y * 9 + x].Domain.emplace(Line[x] - '0');
			}
		}
	}
	In.close();

	SolverVerbose = true;
	Solution s = Solve(Variables, Constraints, Evaluator);

	if (s.Successful)
	{
		for (unsigned int y = 0; y < 9; y++)
		{
			for (unsigned int x = 0; x < 9; x++)
				std::cout << s.State[y * 9 + x].Value;
			std::cout << std::endl;
		}
		std::cout << "Took " << s.Time * 1000 / CLOCKS_PER_SEC << "ms." << std::endl;
	}
	else
		std::cout << "Failed to solve." << std::endl;

	_getch();
}