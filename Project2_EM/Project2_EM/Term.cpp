#include "Term.h"
#define NULL 0

Term::Term()
{
	this->last = NULL;
	this->vars = NULL;
}

void Term::addVar(Variable* v)
{
	if (vars == NULL)
	{
		vars = v;
		last = v;
	}
	else
	{
		last->next = v;
		last = last->next;
	}
}
