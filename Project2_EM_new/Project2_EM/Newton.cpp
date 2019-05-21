#include "Newton.h"
#define threshold 1E-6

System::String ^Newton(Polynomial p, std::map<std::string, double> startPoint)
{
	int step_count = 0;
	int index = 0;
	MyMatrix last;
	MyVector temp_v;
	std::string str = "";
	System::String^ outputdata=gcnew System::String("");


	//copy the initial point
	for (auto  i = startPoint.begin(); i != startPoint.end(); i++)
	{
		temp_v.data.push_back(i->second);
	}
	last.data.push_back(temp_v);


	while (1)
	{
		Polynomial	f_partial, s_partial,temp_p;
		MyMatrix Hessian;
		MyMatrix gradient_Fx_m;
		MyMatrix delta_x;
		std::vector < double > blank(startPoint.size());
		


		//get the Hessian Matrix 
		temp_v.data = blank;
		for (auto i = startPoint.begin(); i != startPoint.end(); i++)
		{
			gradient_Fx_m.data.push_back(temp_v);
			Hessian.data.push_back(temp_v);
		}

		int index_hi = 0, index_hj = 0, index_g = 0;
		for (auto i = startPoint.begin(); i != startPoint.end(); i++)
		{	
			f_partial = p;
			f_partial.data = f_partial.partial(i->first, startPoint);
			gradient_Fx_m[0][index_g]=f_partial.Solution(startPoint);
			index_g++;
			for (auto j = startPoint.begin() ; j != startPoint.end(); j++)
			{
				s_partial = f_partial;
				s_partial.data = s_partial.partial(j->first,startPoint);
				Hessian[index_hi][index_hj] = s_partial.Solution(startPoint);
				index_hj++;
			}
			index_hi++;
			index_hj = 0;
		}


		//output
		outputdata += "Hessian:\r\n[\r\n";
		for (int i = 0; i < Hessian.row(); i++)
		{
			for (int j = 0; j < Hessian.col(); j++)
			{
				outputdata += " " + Hessian[i][j];
			}
			outputdata += "\r\n";
		}
		outputdata += "]\r\n";


		//calculate the delta_X
		Hessian=Inverse(Hessian);
		delta_x = transpose(mul(Hessian,transpose(gradient_Fx_m)));

		
		int stop_count = 0;
		//add the delta_X to Xn become Xn+1
		for (int i = 0; i < delta_x[0].dimension(); i++)
		{
			if (delta_x[0].data[i] <= threshold)
			{
				stop_count++;
			}
			last[0].data[i] += (-1)* delta_x[0].data[i];
		}

		index = 0;
		for (auto i = startPoint.begin(); i != startPoint.end(); i++)
		{
			i->second = last[0][index];
			index++;
		}


		//output
		outputdata += "Hessian inverse:\r\n[\r\n";
		for (int i = 0; i < Hessian.row(); i++)
		{
			for (int j = 0; j < Hessian.col(); j++)
			{
				outputdata += " " + Hessian[i][j];
			}
			outputdata += "\r\n";
		}
		outputdata += "]\r\n";

		outputdata += "x:\r\n[\r\n";
		for (int i = 0; i < last[0].dimension(); i++)
		{
			outputdata += last[0][i] + "\r\n";
		}
		outputdata += "]\r\n\r\n";


		//stop condition
		if (stop_count == delta_x[0].dimension())
		{
			if (step_count < 2)
				continue;
			break;
		}
		step_count++;
		if (step_count == 100)
		{
			break;
		}
		
	}

	index = 0;
	for (auto i = startPoint.begin(); i != startPoint.end(); i++)
	{
		i->second = last[0][index];
		index++;
		if (i == startPoint.begin())
		{
			str += "[" + i->first;
		}
		else
		{
			str += "," + i->first;
		}
	}
	str += "]";
	System::String^ temp_s = gcnew System::String((str).c_str());
	outputdata += temp_s + " = [";
	for (int i = 0; i < last[0].dimension(); i++)
	{
		if (i != 0)
		{
			outputdata += "," + last[0][i];
		}
		else
		{
			outputdata += last[0][i];
		}
	}
	outputdata += "]\r\n";
	outputdata += "min = " + p.Solution(startPoint) + "\r\n";
	return outputdata;
}