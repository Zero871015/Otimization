#include "Term.h"
#define NULL 0

Term::Term()
{
}

//TODO: add new node to linked list
void Term::addVar(Variable v)
{
	vars.push_back(v);
}
