#include "ConjugateGradient.h"
#include "Golden.h"
#include <sstream>

#define SHOW_PROCESS_CPP
#define SHOW_PROCESS_CSHARP

System::String ^ ConjugateGradient(Polynomial p, std::map<std::string, double> startPoint, std::map<std::string, double> min, std::map<std::string, double> max)
{
	System::String^ outputdata = gcnew System::String("");

	std::map<std::string, double> dir;
	//std::map<std::string, double> newPoint;
	double beta;
	double num;
	for (int i = 0; i < 100; i++)
	{
#ifdef SHOW_PROCESS_CPP
		std::cout << "i = " << i << std::endl;
		std::cout << "Si = " << std::endl;
		std::cout << "[" << std::endl;
#endif // SHOW_PROCESS_CPP
#ifdef SHOW_PROCESS_CSHARP
		outputdata += "i = " + i + "\r\n";
		outputdata += "Si = \r\n";
		outputdata += "[\r\n";
#endif // SHOW_PROCESS_CSHARP

		num = p.Solution(startPoint);
		if (i == 0)
		{
			for (auto j = startPoint.begin(); j != startPoint.end(); j++)
			{
				dir[j->first] = -1 * p.diff(j->first, startPoint);
#ifdef SHOW_PROCESS_CPP
				std::cout << dir[j->first] << std::endl;
#endif // SHOW_PROCESS_CPP
#ifdef SHOW_PROCESS_CSHARP
				outputdata += dir[j->first] + "\r\n";
#endif // SHOW_PROCESS_CSHARP
			}
		}
		else
		{
			double child = 0,mother = 0;
			for (auto j = dir.begin(); j != dir.end(); j++)
			{
				child += pow(p.diff(j->first, startPoint),2);
				mother += pow(j->second, 2);
			}
			beta = child / mother;
			for (auto j = startPoint.begin(); j != startPoint.end(); j++)
			{
				dir[j->first] = -1 * p.diff(j->first, startPoint) + beta * dir[j->first];
#ifdef SHOW_PROCESS_CPP
				std::cout << dir[j->first] << std::endl;
#endif // SHOW_PROCESS_CPP
#ifdef SHOW_PROCESS_CSHARP
				outputdata += dir[j->first] + "\r\n";
#endif // SHOW_PROCESS_CSHARP
			}
		}

#ifdef SHOW_PROCESS_CPP
		std::cout << "]" << std::endl << std::endl;
#endif // SHOW_PROCESS_CPP
#ifdef SHOW_PROCESS_CSHARP
		outputdata += "]\r\n\r\n";
#endif // SHOW_PROCESS_CSHARP

		Polynomial p2 = p;
		double s_min = -1000000, s_max = 1000000;
		for (auto j = dir.begin(), t = startPoint.begin(); j != dir.end(); j++, t++)
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
			if (j->second > 0)
			{
				temp = (min[j->first] - startPoint[j->first]) / j->second;
				s_min = s_min < temp ? temp : s_min;

				temp = (max[j->first] - startPoint[j->first]) / j->second;
				s_max = s_max > temp ? temp : s_max;
			}
			else
			{
				temp = (min[j->first] - startPoint[j->first]) / j->second;
				s_max = s_max > temp ? temp : s_max;

				temp = (max[j->first] - startPoint[j->first]) / j->second;
				s_min = s_min < temp ? temp : s_min;
			}
		}
		//find step size
		double X = Golden(p2, s_min, s_max);
#ifdef SHOW_PROCESS_CPP
		std::cout << "alpha = " << X << std::endl;
		std::cout << "Xi = " << std::endl;
		std::cout << "[" << std::endl;
#endif // SHOW_PROCESS_CPP
#ifdef SHOW_PROCESS_CSHARP
		outputdata += "alpha = " + X + "\r\n";
		outputdata += "Xi = \r\n";
		outputdata += "[\r\n";
#endif // SHOW_PROCESS_CSHARP
		double delta = 0;
		for (auto j = dir.begin(); j != dir.end(); j++)
		{
			startPoint[j->first] += X * j->second;
#ifdef SHOW_PROCESS_CPP
			std::cout << startPoint[j->first] << std::endl;
#endif // SHOW_PROCESS_CPP
#ifdef SHOW_PROCESS_CSHARP
			outputdata += startPoint[j->first] + "\r\n";
#endif // SHOW_PROCESS_CSHARP
			delta += X * j->second;
		}
#ifdef SHOW_PROCESS_CPP
		std::cout << "]" << std::endl << std::endl;
#endif // SHOW_PROCESS_CPP
#ifdef SHOW_PROCESS_CSHARP
		outputdata += "]" + "\r\n\r\n";
#endif // SHOW_PROCESS_CSHARP
		double num2 = p.Solution(startPoint);

		if (abs(num - num2) < 0.00001)break;
	}


#ifdef SHOW_PROCESS_CPP
	std::cout << "[";
	for (auto i = startPoint.begin(); i != startPoint.end(); i++)
	{
		std::cout << i->first << " ";
	}
	std::cout << "] = [";
	for (auto i = startPoint.begin(); i != startPoint.end(); i++)
	{
		std::cout << i->second << " ";
	}
	std::cout << "]" << std::endl;

	std::cout << "min = " << num << std::endl;
#endif // SHOW_PROCESS_CPP
#ifdef SHOW_PROCESS_CSHARP
	outputdata += "[";
	for (auto i = startPoint.begin(); i != startPoint.end(); i++)
	{
		outputdata += gcnew System::String(i->first.c_str()) + " ";
	}
	outputdata += "] = [";
	for (auto i = startPoint.begin(); i != startPoint.end(); i++)
	{
		outputdata += i->second + " ";
	}
	outputdata += "]\r\n";

	outputdata += "min = " + num +"\r\n";
#endif // SHOW_PROCESS_CSHARP

	return outputdata;
}
