#pragma once
#include <string>
#include <map>
#include "Polynomial.h"
#include "Golden.h"

System::String^ SteepDescent(Polynomial p, std::map<std::string, double> startPoint, std::map<std::string, double> min, std::map<std::string, double> max);