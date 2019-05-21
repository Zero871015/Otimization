#include "MyVector.h"
#include "Exceptions.h"
#include <cmath>

#define ZERO 0.0001

MyVector::MyVector()
{
}

double &MyVector::operator[](int index)
{
	return this->data[index];
}

std::ostream& operator<<(std::ostream& os, MyVector& v) {
	for (int i = 0; i < v.dimension(); i++)
	{
		os << std::setprecision(6) << v[i] << " ";
	}
	return os;
}

MyVector & operator+(MyVector &a, MyVector &b)
{
	a = add(a, b);
	return a;
}
MyVector & operator-(MyVector &a, MyVector &b)
{
	a = sub(a, b);
	return a;
}
double &operator*(MyVector &a, MyVector &b)
{
	double ans;
	ans = dot(a, b)[0];
	return ans;
}

int MyVector::dimension()
{
	return this->data.size();
}

MyVector dot(MyVector a, MyVector b)
{
	MyVector v;
	//a is const, do scale.
	if (a.dimension() == 1)
	{
		for (int i = 0; i < b.dimension(); i++)
		{
			v.data.push_back(b[i] * a[0]);
		}
	}
	//b is const, do scale.
	else if (b.dimension() == 1)
	{
		for (int i = 0; i < a.dimension(); i++)
		{
			v.data.push_back(a[i] * b[0]);
		}
	}
	else if (a.dimension() != b.dimension())
	{
		throw Exceptions(dimension);
	}
	else
	{
		v.data.push_back(0);
		for (int i = 0; i < a.dimension(); i++)
		{
			v.data[0] += a[i] * b[i];
		}
	}

	return v;
}

MyVector add(MyVector a, MyVector b)
{
	if (a.dimension() != b.dimension())
		throw Exceptions(dimension);

	MyVector v;
	for (int i = 0; i < a.dimension(); i++)
	{
		v.data.push_back(a[i] + b[i]);
	}
	return v;
}

MyVector sub(MyVector a, MyVector b)
{
	if (a.dimension() != b.dimension())
		throw Exceptions(dimension);

	MyVector v;
	for (int i = 0; i < a.dimension(); i++)
	{
		v.data.push_back(a[i] - b[i]);
	}
	return v;
}

MyVector length(MyVector a)
{
	MyVector v = dot(a, a);
	v[0] = std::sqrt(v[0]);
	return v;
}

MyVector normalize(MyVector a)
{
	MyVector v;
	MyVector temp;
	v = length(a);
	temp = a;
	// error when divide 0
	if (v[0] <= ZERO)
		throw Exceptions(divideZero);

	for (int i = 0; i < a.dimension(); i++)
	{
		temp[i] = temp[i] / v[0];
	}
	return temp;
}

MyVector cross(MyVector a, MyVector b)
{
	MyVector v;
	v.data.push_back(a[1] * b[2] - a[2] * b[1]);
	v.data.push_back(a[2] * b[0] - a[0] * b[2]);
	v.data.push_back(a[0] * b[1] - a[1] * b[0]);
	return v;
}

MyVector component(MyVector a, MyVector b)
{
	MyVector v;
	MyVector temp = length(b);
	// error when divide 0
	if (temp[0] <= ZERO)
		throw Exceptions(divideZero);

	v.data.push_back(dot(a, b)[0] / length(b)[0]);
	return v;
}

MyVector projection(MyVector a, MyVector b)
{
	MyVector v;
	v = dot(component(a, b), normalize(b));
	return v;
}

MyVector triangle(MyVector a, MyVector b)
{
	MyVector v;
	v.data.push_back(0.5*std::sqrt(dot(a, a)[0] * dot(b, b)[0] - dot(a, b)[0] * dot(a, b)[0]));
	return v;
}

bool parallel(MyVector a, MyVector b)
{
	if (a.dimension() != b.dimension())
	{
		throw (dimension);
	}

	double scaler;
	bool Isscale = false;
	for (int i = 0; i < a.dimension(); i++)
	{
		if (a[i] == 0 && b[i] == 0)
		{
			continue;
		}
		else if (b[i] == 0)
		{
			return false;
		}
		if (!Isscale)
		{
			scaler = a[i] / b[i];
			Isscale = true;
		}
		else if (a[i] / b[i] - scaler > ZERO)
		{
			return false;
		}
	}
	return true;
}

bool orthogonal(MyVector a, MyVector b)
{
	bool isZero_a = true;
	bool isZero_b = true;
	for (int i = 0; i < a.dimension(); i++)
	{
		if (a[i] >= ZERO)
		{
			isZero_a = false;
			break;
		}
	}
	for (int i = 0; i < b.dimension(); i++)
	{
		if (b[i] >= ZERO)
		{
			isZero_b = false;
			break;
		}
	}
	if (isZero_a || isZero_b)
	{
		return true;
	}
	a = normalize(a);
	b = normalize(b);
	if (dot(a, b)[0] <= ZERO && dot(a, b)[0] >= -ZERO)
	{
		return true;
	}
	return false;
}

MyVector findAngle(MyVector a, MyVector b)//only 3 digits after point we need 6
{
	MyVector v;
	v = dot(a, b);
	//maybe error when divide 0?
	v[0] = v[0] / (length(a)[0] * length(b)[0]);
	v[0] = acos(v[0]) * 180 / acos(-1);
	return v;
}

MyVector planeNormal(MyVector a, MyVector b)//only 2 digits after point we need 6
{
	return cross(a, b);
}

bool linearIndependent(MyVector a, MyVector b)
{

	double ratio;
	bool isZero = true;
	for (int i = 0; i < a.dimension(); i++)
	{
		if (abs(b[i]) > ZERO)
		{
			ratio = a[i] / b[i];
			isZero = false;
			break;
		}
	}
	if (isZero)
	{
		return false;
	}
	for (int i = 0; i < b.dimension(); i++)
	{
		b[i] *= ratio;
		if (abs(b[i] - a[i]) >= ZERO)
		{
			return true;
		}
	}
	return false;
}

std::vector<MyVector> gramSchmidt(std::vector<MyVector> vectors)
{
	MyVector v;
	std::vector<MyVector>ans;
	for (int i = 0; i < (int)vectors.size(); i++)
	{
		MyVector sum;
		v = vectors[i];
		for (int j = 0; j < (int)ans.size(); j++)
		{
			v = sub(v, projection(v, ans[j]));
		}
		ans.push_back(normalize(v));

	}
	return ans;
}

bool MyVector::isZero(double error)
{
	for (int i = 0; i < this->dimension(); i++)
	{
		if (abs(this->data[i]) > error)
			return false;
	}
	return true;
}