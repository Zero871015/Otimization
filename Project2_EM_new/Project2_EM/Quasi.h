#pragma once
#include "Polynomial.h"
#include "MyVector.h"
#include "Matrix.h"
#include "Golden.h"


std::string dtos(double);
std::string changeVar(Polynomial, std::map<std::string, double>, MyMatrix);
System::String ^QuasiNewton(Polynomial, std::map<std::string, double>);
