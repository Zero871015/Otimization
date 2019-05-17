#pragma once
#include <vector>
#include "MyVector.h"
using namespace System;
using namespace System::Collections::Generic;
class MyMatrix
{
public:
	MyMatrix();
	MyMatrix(MyVector);
	int col();
	int row();
	MyVector &operator[](int index);
	friend std::ostream& operator<<(std::ostream& os, MyMatrix& m);

	friend MyMatrix add(MyMatrix, MyMatrix);
	friend MyMatrix sub(MyMatrix, MyMatrix);
	friend MyMatrix mul(MyMatrix, MyMatrix);
	friend int rank(MyMatrix);
	friend MyMatrix GaussianElimination(MyMatrix);
	friend MyMatrix transpose(MyMatrix);
	friend MyMatrix SolveLinearSystem(MyMatrix, MyMatrix);
	friend double Determinants(MyMatrix);
	friend MyMatrix subMatrix(MyMatrix, int, int);
	friend MyMatrix Inverse(MyMatrix);
	friend MyMatrix Adjoint(MyMatrix);
	friend MyMatrix LeastSquare(MyMatrix, MyMatrix);
	friend void FindEigen(MyMatrix, MyMatrix&, MyMatrix&);
	friend void PowerMethod(MyMatrix, MyMatrix&, MyMatrix&);

	std::vector<MyVector> data;
};