#pragma once
#include "Variable.h"
class Term
{
public:
	Term();
	double coef;
	Variable *vars;
	Variable *last;

	Term *next;

	void addVar(Variable*);

};

