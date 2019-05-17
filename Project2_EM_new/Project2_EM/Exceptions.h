#pragma once
#include <vector>
#include <string>
#include <iomanip>
using namespace System;
class Exceptions
{
public:
	Exceptions();
	int type;
	//std::vector<String>text;
	int getType();
	Exceptions(int);
};

enum error { dimension, divideZero, rowNotEqualCol, noInverse, readError, done, computeError, egienerror, totalError };
