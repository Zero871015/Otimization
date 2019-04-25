#pragma once
#include <string>
#include <iostream>
#include "Term.h"
class Polynomial
{
public:
	Polynomial();
	Polynomial(std::string);
	Polynomial diff();

	void addTerm(Term*);

	Term *term;
	Term *last;

};

