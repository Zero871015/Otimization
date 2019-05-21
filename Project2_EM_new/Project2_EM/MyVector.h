#pragma once
using namespace System;
using namespace System::Collections::Generic;
#include <vector>
#include <iostream>

class MyVector
{
public:
	MyVector();

	friend std::ostream& operator<<(std::ostream& os, MyVector& v);
	friend MyVector& operator+(MyVector&, MyVector&);
	friend MyVector& operator-(MyVector&, MyVector&);
	friend double &operator*(MyVector&, MyVector&);
	double &operator[](int index);

	friend MyVector dot(MyVector, MyVector);
	friend MyVector add(MyVector, MyVector);
	friend MyVector sub(MyVector, MyVector);
	friend MyVector length(MyVector);
	friend MyVector normalize(MyVector);
	friend MyVector cross(MyVector, MyVector);
	friend MyVector component(MyVector, MyVector);
	friend MyVector projection(MyVector, MyVector);
	friend MyVector triangle(MyVector, MyVector);
	friend bool parallel(MyVector, MyVector);
	friend bool orthogonal(MyVector, MyVector);
	friend MyVector findAngle(MyVector, MyVector);
	friend MyVector planeNormal(MyVector, MyVector);
	friend bool linearIndependent(MyVector, MyVector);
	friend std::vector<MyVector> gramSchmidt(std::vector<MyVector>);

	bool isZero(double error = 0.001);


	std::vector<double> data;
	int dimension();
};