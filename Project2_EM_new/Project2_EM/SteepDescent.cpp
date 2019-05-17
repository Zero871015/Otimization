#include "SteepDescent.h"
#include <sstream>

//#define SHOW_PROCESS_CPP
#define SHOW_PROCESS_CSHARP

System::String ^ SteepDescent(Polynomial p, std::map<std::string, double> startPoint, std::map<std::string, double> min, std::map<std::string, double> max)
{
	System::String^ outputdata = gcnew System::String("");
	double height = p.Solution(startPoint);
	for (int count = 0; count < 100; count++)
	{
		//Find direction vector.
		std::map<std::string, double> dir;
		for (auto i = startPoint.begin(); i != startPoint.end(); i++)
		{
			dir[i->first] = -1 * p.diff(i->first, startPoint);
		}
#ifdef SHOW_PROCESS_CPP
		std::wcout << "i = " << count << std::endl;
		std::cout << "h = " << std::endl << "[" << std::endl;
		for (auto j = dir.begin(); j != dir.end(); j++)
		{
			std::cout << j->second << std::endl;
		}
		std::cout << "]" << std::endl;
#endif // SHOW_PROCESS_CPP

#ifdef SHOW_PROCESS_CSHARP
		outputdata += "i = " + count + "\r\n";

		outputdata += "h = " + "\r\n" + "[" + "\r\n";
		for (auto j = dir.begin(); j != dir.end(); j++)
		{
			outputdata += j->second + "\r\n";
		}
		outputdata += "]\r\n";
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
		double delta = 0;
		for (auto j = dir.begin(); j != dir.end(); j++)
		{
			startPoint[j->first] += X * j->second;
			delta += X * j->second;
		}
		double newHeight = p.Solution(startPoint);
#ifdef SHOW_PROCESS_CPP
		std::cout << "Lambda = " << X << std::endl;

		std::cout << "X" << "[";
		for (auto j = startPoint.begin(); j != startPoint.end(); j++)
		{
			std::cout << j->second << " ";
		}
		std::cout << "]" << std::endl << std::endl;
#endif // SHOW_PROCESS_CPP
#ifdef SHOW_PROCESS_CSHARP
		outputdata += "Lambda = " + X + "\r\n";
		outputdata += "X" + "[";
		for (auto j = startPoint.begin(); j != startPoint.end(); j++)
		{
			outputdata += j->second + " ";
		}

		outputdata += "]\r\n\r\n";
#endif // SHOW_PROCESS_CSHARP

		if (abs(newHeight - height) < 0.00001) break;
		else	height = newHeight;
	}
#ifdef SHOW_PROCESS_CPP
	std::cout << std::endl;

	std::cout << "[";
	for (auto j = startPoint.begin(); j != startPoint.end(); j++)
	{
		std::cout << j->first << " ";
	}
	std::cout << "] =" << std::endl;

	std::cout << "[";
	for (auto j = startPoint.begin(); j != startPoint.end(); j++)
	{
		std::cout << j->second << " ";
	}
	std::cout << "]" << std::endl;

	std::cout << "min = " << height << std::endl;
#endif // SHOW_PROCESS_CPP
#ifdef SHOW_PROCESS_CSHARP
	outputdata += "\r\n";

	outputdata += "[";
	for (auto j = startPoint.begin(); j != startPoint.end(); j++)
	{
		outputdata += gcnew System::String(j->first.c_str()) + " ";
	}
	outputdata += "] =\r\n";

	outputdata += "[";
	for (auto j = startPoint.begin(); j != startPoint.end(); j++)
	{
		outputdata += j->second + " ";
	}
	outputdata += "]\r\n";

	outputdata += "min = " + height + "\r\n";
#endif // SHOW_PROCESS_CSHARP

	return outputdata;
}
