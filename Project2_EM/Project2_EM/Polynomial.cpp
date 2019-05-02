#include "Polynomial.h"
#include <vector>


Polynomial::Polynomial()
{
}

Polynomial::Polynomial(std::string str)
{
	std::vector<std::string> terms;	//store every strings of term
	std::string temp;
	//TODO: split str to each term
	for (int i = 0; i < str.length(); i++)
	{
		temp += str[i];
		if (i == str.length() - 1)
		{
			terms.push_back(temp);
			temp = "";
		}
		else if (str[i + 1] == '+' || str[i + 1] == '-')
		{
			terms.push_back(temp);
			temp = "";
		}
	}

	//TODO: run every string
	for (int i = 0; i < (int)terms.size(); i++)
	{
		Term term;
		temp = "";
		bool isVarPart = false;

		//TODO: convert each string of term to term
		for (int j = 0; j < (int)terms[i].length(); j++)
		{
			Variable var;
			//coefficient part
			if (!isVarPart)
			{
				if ((terms[i][j] < '0' || terms[i][j] > '9') &&
					terms[i][j] != '+' &&
					terms[i][j] != '-' &&
					terms[i][j] != '.')
				{
					//hide number will  when 1 or -1
					if (temp == "" || temp == "-" || temp == "+")
					{
						temp += '1';
					}
					term.coef = std::stod(temp);
					isVarPart = true;
				}
				else
				{
					temp += terms[i][j];
				}
			}
			//variable part
			if(isVarPart)
			{
				if (terms[i][j] == '*') j++;
				var.name = terms[i][j];
				//hide number when exponent is 1 and j+1 over index
				if (j + 1 == terms[i].length())
				{
					var.exp = 1;
				}
				else if (terms[i][j+1] == '^')
				{
					temp = "";
					j += 2;
					while (j  < terms[i].length() && terms[i][j]!='*')
					{
						temp += terms[i][j];
						j++;
					}
					var.exp = std::stod(temp);
				}
				//hide number when exponent is 1
				else
					var.exp = 1;

				term.addVar(var);
			}
			

		}
		//only const number
		if (!isVarPart)
		{
			if (temp == "" || temp == "-" || temp == "+")
			{
				temp += '1';
			}
			term.coef = std::stod(temp);
		}

		this->addTerm(term);
		std::cout << std::endl;
	}
}

//TODO: add new node to linked list
void Polynomial::addTerm(Term t)
{
	this->term.push_back(t);
}

//TODO: Given every variables, return the solution number.
//Expection: variables not in map.
double Polynomial::Solution(std::map<std::string, double> m)
{
	double sum = 0;
	for (int i = 0; i < (int)this->term.size(); i++)
	{
		Term t = this->term[i];
		double temp = t.coef;
		for (int j = 0; j < (int)this->term[i].vars.size(); j++)
		{
			temp *= pow(m[t.vars[j].name], t.vars[j].exp);
		}
		sum += temp;
	}

	return sum;
}

//TODO: Can only use when only one variable.
//ERROR: Variables more than one, return number will be wrong.
double Polynomial::Solution(double x)
{
	double sum = 0;
	for (int i = 0; i < (int)this->term.size(); i++)
	{
		Term t = this->term[i];
		double temp = t.coef;
		for (int j = 0; j < (int)this->term[i].vars.size(); j++)
		{
			temp *= pow(x, t.vars[j].exp);
		}
		sum += temp;
	}
	return sum;
}

Polynomial Polynomial::GivenNum(std::map<std::string, double> m)
{
	Polynomial ans = *this;
	for (int i = 0; i < (int)ans.term.size(); i++)
	{
		for (int j = 0; j < ans.term[i].vars.size(); j++)
		{
			if (m.find(ans.term[i].vars[j].name) != m.end())
			{
				ans.term[i].coef *= pow(m[ans.term[i].vars[j].name], ans.term[i].vars[j].exp);
				ans.term[i].vars.erase(ans.term[i].vars.begin() + j);
			}
		}
	}
	return ans;
}

Polynomial Polynomial::VartoPoly(char name, Polynomial p)
{
	for (int i = 0; i < this->term.size(); i++)
	{
		for (int j = 0; j < this->term[i].vars.size(); j++)
		{

		}
	}
}