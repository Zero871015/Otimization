#pragma once
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "InorderToPostorder.h"
class Polynomial
{
public:
	Polynomial();
	Polynomial(std::string);

	double diff(std::string, std::map<std::string, double> m);
	double Solution(std::map<std::string,double>);
	double Solution(double);
	std::string Replace(std::string, std::string);

	std::string data;
	friend void ShowVars(std::map<std::string, double>);
};

