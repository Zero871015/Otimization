#include "Golden.h"

const double resphi = 0.618;

double Golden(Polynomial p, double min, double max,int count)
{
	//std::cout << count << std::endl;
	double c1 = (max - min) * (1 - resphi) + min;
	double c2 = (max - min) * resphi + min;
	double s1 = p.Solution(c1);
	double s2 = p.Solution(c2);
	//std::cout << min << "\t" << max << "\t" << c1 << "\t" << c2 << "\t" << s1 << "\t" << s2 << std::endl;
	if (s1 > s2)
	{
		min = c1;
	}
	else
	{
		max = c2;
	}

	//At least do 100 times, but no more than 1000 times.
	if (count > 100 && (count > 1000 || abs(max - min) < 0.001))
		return (min + max) / 2.0;
	return Golden(p, min, max, count+1);
}

double test(Polynomial p, double a, int count)
{
	if (count == 500)return a;
	double num = p.Solution(a);
	double num2 = p.Solution(a + 0.01);
	double num3 = p.Solution(a - 0.01);
	if (num2 > num3)
	{
		if (abs(num - num3) < 0.0001) return a - 0.01;
		else return test(p, a - 0.01, count + 1);
	}
	else
	{
		if (abs(num - num2) < 0.0001) return a + 0.01;
		else return test(p, a + 0.01, count + 1);
	}
}