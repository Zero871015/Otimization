#include "Powell.h"
#include "Polynomial.h"
#include "Golden.h"
#include <sstream>

std::map<std::string, double> Powell(Polynomial p, std::map<std::string, double> startPoint, std::map<std::string, double> min, std::map<std::string, double> max)
{
	double num = p.Solution(startPoint);
	std::map<std::string, double> s;
	for (auto i = startPoint.begin(); i != startPoint.end(); i++)
	{
		Polynomial p2 = p;
		for (auto j = startPoint.begin(); j != startPoint.end(); j++)
		{
			std::ostringstream strs;
			strs << j->second;
			std::string str = "(" + strs.str();
			if (j == i)
			{
				str += "+X";
			}
			str += ")";
			p2.data = p2.Replace(j->first, str);
		}
		double X = Golden(p2, min[i->first] - startPoint[i->first], startPoint[i->first] - max[i->first]);
		startPoint[i->first] += X;
		s[i->first] = X;
		double num2 = p.Solution(startPoint);
	}

	return startPoint;
}