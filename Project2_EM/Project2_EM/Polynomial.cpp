#include "Polynomial.h"
#include <vector>


Polynomial::Polynomial()
{
}

Polynomial::Polynomial(std::string str)
{
	std::string coef_s = "";
	std::string exp_s = "";
	
	Variable *v_new, *v_last;
	v_new = new Variable[1];


	std::vector<std::string> terms;

	int level = 0;
	/*
	for (int i = 0; i <= (int)str.size(); i++)
	{
		if (level == 0)	//coef
		{
			if (str[i] == '*')
			{
				if (coef_s == "" || coef_s == "-")
					coef_s += "1";
				term.coef = std::stod(coef_s);
				level = 1;
				coef_s = "";
			}
			else
			{
				coef_s += str[i];
			}
		}
		else if (level == 1)	//name
		{
			v_new->name = str[i];
			level = 2;
		}
		else if (level == 2)	//exp
		{
			if (str[i] == '^');
			else if ((str[i] >= '0'&&str[i] <= '9') || str[i] == '.')
			{
				exp_s += str[i];
			}
			else if (str[i] == '*')
			{
				if (exp_s == "")
					exp_s = "1";
				v_new->exp = std::stod(exp_s);
				exp_s = "";
				level = 1;
				v_last->next = v_new;
				v_last = v_new;
				v_new = new Variable[1];
			}
			else
			{
				if (exp_s == "")
					exp_s = "1";
				v_new->exp = std::stod(exp_s);
				exp_s = "";
				level = 0;
				v_last->next = v_new;
				v_last = v_new;
				v_new = new Variable[1];
			}
		}

	}
	term.vars = term.vars->next;
	*/
	std::string temp;
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


	for (int i = 0; i < (int)terms.size(); i++)
	{
		Term term;
		temp = "";
		bool isVarPart = false;
		for (int j = 0; j < (int)terms[i].length(); j++)
		{
			Variable *var = new Variable;
			if (!isVarPart)
			{
				if ((terms[i][j] < '0' || terms[i][j] > '9') &&
					terms[i][j] != '+' &&
					terms[i][j] != '-' &&
					terms[i][j] != '.')
				{
					if (temp == "" || temp == "-" || temp == "+")
					{
						temp += '1';
					}
					term.coef = std::stod(temp);
					//if (terms[i][j] != '*')j--;
					isVarPart = true;
				}
				else
				{
					temp += terms[i][j];
				}
			}
			if(isVarPart)
			{

				if (terms[i][j] == '*')j++;
				//vars handle
				var->name = terms[i][j];
				if (j + 1 == terms[i].length())
				{
					var->exp = 1;
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
					var->exp = std::stod(temp);
				}
				else
					var->exp = 1;

				term.addVar(var);
			}
			

			
		}

		std::cout << std::endl;
	}
}
