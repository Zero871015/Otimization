#pragma once
#include "Variable.h"
#include <vector>
class Term
{
public:
	Term();
	double coef;
	std::vector<Variable> vars;

	void addVar(Variable);

};

