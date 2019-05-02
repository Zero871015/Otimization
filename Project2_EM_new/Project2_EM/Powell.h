#pragma once
#include <string>
#include <map>
#include "Polynomial.h"

std::map<std::string,double> Powell(Polynomial p,std::map<std::string,double> startPoint, std::map<std::string, double> min, std::map<std::string, double> max);