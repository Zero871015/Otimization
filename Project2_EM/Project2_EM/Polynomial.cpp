#include "Polynomial.h"
#include <vector>


Polynomial::Polynomial()
{
	this->last = NULL;
	this->term = NULL;
}

Polynomial::Polynomial(std::string str)
{
	//initialize linked list pointer
	this->last = NULL;
	this->term = NULL;

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
		Term *term = new Term;
		temp = "";
		bool isVarPart = false;

		//TODO: convert each string of term to term
		for (int j = 0; j < (int)terms[i].length(); j++)
		{
			Variable *var = new Variable;
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
					term->coef = std::stod(temp);
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
				var->name = terms[i][j];
				//hide number when exponent is 1 and j+1 over index
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
				//hide number when exponent is 1
				else
					var->exp = 1;

				term->addVar(var);
			}
			

		}
		//only const number
		if (!isVarPart)
		{
			if (temp == "" || temp == "-" || temp == "+")
			{
				temp += '1';
			}
			term->coef = std::stod(temp);
		}

		this->addTerm(term);
		std::cout << std::endl;
	}
}

//TODO: add new node to linked list
void Polynomial::addTerm(Term* t)
{
	if (term == NULL)
	{
		term = t;
		last = t;
	}
	else
	{
		last->next = t;
		last = last->next;
	}
}