#pragma once
#include <string>
#include <iostream>
#include "Term.h"
#include <map>
class Polynomial
{
public:
	Polynomial();
	Polynomial(std::string);
	Polynomial diff();

	void addTerm(Term*);
	double Solution(std::map<char,double>);
	double Solution(double);

	Term *term;
	Term *last;

};

