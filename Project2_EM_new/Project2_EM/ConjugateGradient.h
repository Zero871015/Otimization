#pragma once
#include <string>
#include <map>
#include "Polynomial.h"

System::String^ ConjugateGradient(Polynomial p, std::map<std::string, double> startPoint, std::map<std::string, double> min, std::map<std::string, double> max);