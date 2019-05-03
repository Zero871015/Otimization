#include "Powell.h"
#include "Polynomial.h"
#include "Golden.h"
#include <sstream>

#define SHOW_PROCESS

std::map<std::string, double> Powell(Polynomial p, std::map<std::string, double> startPoint, std::map<std::string, double> min, std::map<std::string, double> max)
{
	double num;
	for (int k = 0; k < 1000; k++)	//most do 1000 times
	{
		num = p.Solution(startPoint);
		std::map<std::string, double> s;
		int count = 1;
		for (auto i = startPoint.begin(); i != startPoint.end(); i++)	//search for each dirction
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
			//find step size by golden section
			double X = Golden(p2, min[i->first] - startPoint[i->first], max[i->first]- startPoint[i->first]);
			startPoint[i->first] += X;
			s[i->first] = X;

#ifdef SHOW_PROCESS
			std::cout << "X" << count << "[";
			for (auto j = startPoint.begin(); j != startPoint.end(); j++)
				std::cout << j->second << " ";
			std::cout << "]" << std::endl;
#endif // SHOW_PROCESS

			count++;
		}

		//do the mix dirction S
		Polynomial p2 = p;
		double s_min = -1000000, s_max = 1000000;
		for (auto j = s.begin(), t = startPoint.begin(); j != s.end(); j++,t++)
		{
			std::ostringstream strs;
			strs << t->second;
			strs << "+X*";
			strs << j->second;
			std::string str = "(" + strs.str();
			str += ")";
			p2.data = p2.Replace(j->first, str);

			//compute min,max
			double temp;
			temp = (min[j->first] - startPoint[j->first]) / j->second;
			s_min = s_min < temp ? temp : s_min;

			temp = (max[j->first] - startPoint[j->first]) / j->second;
			s_max = s_max > temp ? temp : s_max;
		}
		//find step size
		double X = Golden(p2, s_min, s_max);
		double delta = 0;
		for (auto j = s.begin(); j != s.end(); j++)
		{
			startPoint[j->first] += X * j->second;
			delta += X * j->second;
		}
#ifdef SHOW_PROCESS
		std::cout << "alpha = " << X << std::endl;
		std::cout << "S" << count << "[";
		for (auto j = s.begin(); j != s.end(); j++)
			std::cout << X * j->second << " ";
		std::cout << "]" << std::endl;

		std::cout << "X" << count + 1 << "[";
		for (auto j = startPoint.begin(); j != startPoint.end(); j++)
			std::cout << j->second << " ";
		std::cout << "]" << std::endl << std::endl;
#endif // SHOW_PROCESS
		double num2 = p.Solution(startPoint);

		if (abs(num - num2) < 0.00001)break;
		//if (delta < 0.00001)break;
	}
#ifdef SHOW_PROCESS
	std::cout << "min = " << num << std::endl;
#endif // SHOW_PROCESS



	return startPoint;
}