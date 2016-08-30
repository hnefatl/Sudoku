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

	bool operator<(const Variable &Right) const;
	bool operator==(const Variable &Right) const;
};

#endif