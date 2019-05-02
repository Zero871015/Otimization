#pragma once
#include <string>
#include <iostream>
#include "Term.h"
#include <map>
#include <vector>
class Polynomial
{
public:
	Polynomial();
	Polynomial(std::string);

	Polynomial diff();
	void addTerm(Term);
	double Solution(std::map<std::string,double>);
	double Solution(double);
	Polynomial GivenNum(std::map<std::string, double>);
	Polynomial VartoPoly(char,Polynomial);

	std::vector<Term> term;

};

