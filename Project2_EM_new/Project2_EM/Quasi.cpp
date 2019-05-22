#include "Quasi.h"
#include <sstream>
#define threshold 1E-6




std::string dtos(double num)
{
	std::ostringstream out;
	out << num;
	return out.str();
}


std::string changeVar(Polynomial p, std::map<std::string, double>startpoint, MyMatrix dk)
{
	std::string str;
	std::string	temp_s;
	int next = 0;
	int index = 0;
	str = p.data;
	for (auto i = startpoint.begin(); i != startpoint.end(); i++)
	{
		next = 0;
		while (1)
		{
			next = str.find(i->first, next + 1);
			if (next == -1)
			{
				break;
			}
			str.erase(next, i->first.length());
			if (dk[index][0] < 0)
			{
				temp_s = "(" + dtos(i->second) + dtos(dk[index][0]) + "*a)";
			}
			else
			{
				temp_s = "(" + dtos(i->second) + "+" + dtos(dk[index][0]) + "*a)";
			}
			str.insert(next, temp_s);
		}
		index++;
	}
	return str;
}


System::String ^QuasiNewton(Polynomial p, std::map<std::string, double>startpoint)
{

	System::String^ outputdata = gcnew System::String("");
	MyMatrix dk, Hessian, Hessian_inverse, delta_x, xk, gk, delta_gk, xk_next;
	MyVector initial_point;
	MyVector temp_v;
	std::vector<Polynomial>partials;
	double alpha;
	int num_var = startpoint.size();
	int step_count = 0;
	bool firstTime = false;

	//create a indentity matrix
	for (int i = 0; i < startpoint.size(); i++)
	{
		std::vector < double >blank(num_var);
		blank[i] = 1;
		temp_v.data = blank;
		Hessian_inverse.data.push_back(temp_v);
	}

	for (auto i = startpoint.begin(); i != startpoint.end(); i++)
	{
		temp_v.data.clear();
		temp_v.data.push_back(i->second);
		//get initial point
		xk.data.push_back(temp_v);
		initial_point.data.push_back(i->second);

		//get partial functions
		Polynomial temp_p;
		temp_p.data = p.partial(i->first, startpoint);
		partials.push_back(temp_p);
	}



	while (1)
	{
		gk.data.clear();
		delta_gk.data.clear();

		//get the gradient(k)
		int index = 0;
		for (auto i = startpoint.begin(); i != startpoint.end(); i++)
		{
			temp_v.data.clear();
			temp_v.data.push_back(partials[index].Solution(startpoint));
			gk.data.push_back(temp_v);
			index++;
		}

		//get the dk
		dk = Hessian_inverse * gk;
		for (int i = 0; i < dk.row(); i++)
		{
			for (int j = 0; j < dk.col(); j++)
			{
				dk[i][j] *= -1;
			}
		}

		//find the alpha
		Polynomial new_p;
		new_p.data = changeVar(p, startpoint, dk);
		alpha = test(new_p);
		if (alpha < 0.05)alpha = 0.05;
		//get the delta_x
		delta_x = dk;
		for (int i = 0; i < delta_x.row(); i++)
		{
			for (int j = 0; j < delta_x.col(); j++)
			{
				delta_x[i][j] *= alpha;
			}
		}

		//get x(k+1)
		xk_next = xk + delta_x;

		//update the data to map
		index = 0;
		for (auto i = startpoint.begin(); i != startpoint.end(); i++)
		{
			i->second = xk_next[index][0];
			index++;
		}


		//get delta_gk
		temp_v.data.clear();
		for (index = 0; index < num_var; index++)
		{
			temp_v.data.push_back(partials[index].Solution(startpoint));
		}
		delta_gk.data.push_back(temp_v);
		delta_gk = transpose(delta_gk);
		delta_gk = delta_gk - gk;


		//get Hessian_inverse(k+1)
		MyMatrix m1, m2;
		m1 = delta_x * transpose(delta_x);
		m1[0][0] /= (transpose(delta_x) * delta_gk)[0][0];
		m2 = (Hessian_inverse * delta_gk) * transpose(Hessian_inverse * delta_gk);
		for (int i = 0; i < num_var; i++)
		{
			for (int j = 0; j < num_var; j++)
			{
				m2[i][j] /= (transpose(delta_gk) * Hessian_inverse * delta_gk)[0][0];
			}
		}
		Hessian_inverse = Hessian_inverse + m1 - m2;


		//threshold
		int stop_count = 0;
		for (int i = 0; i < num_var; i++)
		{
			if (partials[i].Solution(startpoint) <= threshold)
			{
				stop_count++;
			}
		}
		if (stop_count == num_var)
		{
			if (step_count < 2)
			{
				continue;
			}
			break;
		}
		step_count++;
		if (step_count == 100)
		{
			break;
		}



		//output
		Hessian = Inverse(Hessian_inverse);
		if (!firstTime)
		{
			outputdata += "Initial Hessian:\r\n[\r\n";
			for (int i = 0; i < num_var; i++)
			{
				for (int j = 0; j < num_var; j++)
				{
					outputdata += " " + Hessian[i][j];
				}
				outputdata += "\r\n";
			}
			outputdata += "]\r\n";

			outputdata += "Initial Hessian inverse:\r\n[\r\n";
			for (int i = 0; i < num_var; i++)
			{
				for (int j = 0; j < num_var; j++)
				{
					outputdata += " " + Hessian_inverse[i][j];
				}
				outputdata += "\r\n";
			}
			outputdata += "]\r\n";
		}
		else
		{
			outputdata += "Hessian:\r\n[\r\n";
			for (int i = 0; i < num_var; i++)
			{
				for (int j = 0; j < num_var; j++)
				{
					outputdata += " " + Hessian[i][j];
				}
				outputdata += "\r\n";
			}
			outputdata += "]\r\n";

			outputdata += "Hessian inverse:\r\n[\r\n";
			for (int i = 0; i < num_var; i++)
			{
				for (int j = 0; j < num_var; j++)
				{
					outputdata += " " + Hessian_inverse[i][j];
				}
				outputdata += "\r\n";
			}
			outputdata += "]\r\n";
		}

		outputdata += "x:\r\n[\r\n";
		for (int i = 0; i < num_var; i++)
		{
			outputdata += xk_next[i][0] + "\r\n";
		}
		outputdata += "]\r\n";

		firstTime = true;
	}

	outputdata += "\r\n";

	std::string str = "";
	for (auto i = startpoint.begin(); i != startpoint.end(); i++)
	{
		if (i == startpoint.begin())
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
	for (int i = 0; i < xk_next.row(); i++)
	{
		if (i != 0)
		{
			outputdata += "," + xk_next[i][0];
		}
		else
		{
			outputdata += xk_next[i][0];
		}
	}
	outputdata += "]\r\n";
	outputdata += "min = " + p.Solution(startpoint) + "\r\n";
	return outputdata;
}