#include "Polynomial.h"
#include <sstream>
#include <vector>


Polynomial::Polynomial()
{
}

Polynomial::Polynomial(std::string str)
{
	//replace sin and cos to % and $
	for (std::size_t found = str.find("sin"); found != std::string::npos; found = str.find("sin"))
	{
		str.replace(str.begin() + found, str.begin() + found + 3, "$");
	}
	for (std::size_t found = str.find("cos"); found != std::string::npos; found = str.find("cos"))
	{
		str.replace(str.begin() + found, str.begin() + found + 3, "%");
	}
	this->data = str;
	//std::cout << Postorder(str) << std::endl;
}

//TODO: Recursion to get differnetial. Should used only in diff().
double diff_Solution(std::string target,std::map<std::string, std::string> &mem)
{
	std::string str = Postorder(mem[target]);
	std::vector<double> stackNumber;	//�@��stack�Ω�s��B�⤸
	std::string temp = "";	//�@�ӼȦs�Ŷ�
	for (int i = 0; i < (int)str.length(); i++)
	{
		//���p�J�W���j�r��...
		if (str[i] == ' ')
		{
			//�P�_��O�_���B��l
			if ((int)temp.length() == 1 && (isOperator(temp[0]) || temp == "@"))
			{
				int size = (int)stackNumber.size();
				//�q���|���X��Ӽư��[�k
				if (temp == "+")
				{
					if (size < 2)
					{
						//���~�A�B�⦡�����~
					}
					stackNumber[size - 2] += stackNumber[size - 1];
					stackNumber.pop_back();
					size--;
				}
				//�q���|���X��Ӽư���k
				else if (temp == "-")
				{
					if (size < 2)
					{
						//���~�A�B�⦡�����~
					}
					stackNumber[size - 2] -= stackNumber[size - 1];
					stackNumber.pop_back();
					size--;
				}
				//�q���|���X��Ӽư����k
				else if (temp == "*")
				{
					if (size < 2)
					{
						//���~�A�B�⦡�����~
					}
					stackNumber[size - 2] *= stackNumber[size - 1];
					stackNumber.pop_back();
					size--;
				}
				//�q���|���X��Ӽư����k
				else if (temp == "/")
				{
					if (size < 2)
					{
						//���~�A�B�⦡�����~
					}
					stackNumber[size - 2] /= stackNumber[size - 1];
					stackNumber.pop_back();
					size--;
				}
				//�q���|���X�@�Ӽƥ[�t��
				else if (temp == "@")
				{
					if (size < 1)
					{
						//���~�A�B�⦡�����~
					}
					stackNumber[size - 1] *= -1;
				}
				//�q���|���X��Ӽư�����
				else if (temp == "^")
				{
					if (size < 2)
					{
						//���~�A�B�⦡�����~
					}
					stackNumber[size - 2] = pow(stackNumber[size - 2], stackNumber[size - 1]);
					stackNumber.pop_back();
					size--;
				}
				//�q���|���X�@�Ӽư����h
				else if (temp == "!")
				{
					//���~�A�B�⦡�����~
				}
			}
			//���O�B��Ÿ��A�N��䬰�B�⤸
			//�N���Ʃ�J���|��
			else
			{
				if ((temp[0] >= 'a'&&temp[0] <= 'z') || (temp[0] >= 'A'&&temp[0] <= 'Z') || temp[0] == '\'')
				{
					if(temp == "\'X")
						stackNumber.push_back(1);
					else if (temp[0] == '\'' && mem.find(temp) == mem.end())
					{
						stackNumber.push_back(0);
					}
					else
					{
						if (mem.find(temp) == mem.end())
						{
							//���~
						}
						stackNumber.push_back(diff_Solution(temp,mem));
					}
				}
				//���O�ܼơA�P�_�䬰�p���٬O���
				else
				{
					int isPoint = 0;
					for (int i = 0; i < (int)temp.length(); i++)
					{
						if (temp[i] == '.')
						{
							if (isPoint++ > 0)
							{
								//���~�A�B�⦡�����~
							}
						}
						else if (temp[i] > '9' || temp[i] < '0')
						{
							//���~�A�B�⦡�����~
						}
					}
					stackNumber.push_back(std::stod(temp));
				}

			}
			temp = "";
		}
		else
		{
			//�٨S�J����j�Ÿ��A�N��Ӧr���P�e���O�@�骺
			temp += str[i];
		}
	}
	std::ostringstream strs;
	strs << stackNumber[0];
	mem[target] = strs.str();
	return stackNumber[0];
}

//TODO: Differential for varable target. Need to give all number of variables
double Polynomial::diff(std::string target, std::map<std::string, double> m)
{
	double ans;
	Polynomial p = *this;

	//replace varables, if not target then change to const.
	for (auto i = m.begin(); i != m.end(); i++)
	{
		if (i->first != target)
		{
			std::ostringstream strs;
			strs << i->second;
			p.data = p.Replace(i->first, strs.str());
		}
		else
		{
			p.data = p.Replace(i->first,"X");
		}
	}

	std::string str = Postorder(p.data);
	std::map<std::string, std::string> mem;
	int count = 0;
	std::vector<std::string> stackNumber;	//�@��stack�Ω�s��B�⤸
	std::string temp = "";	//�@�ӼȦs�Ŷ�
	for (int i = 0; i < (int)str.length(); i++)
	{
		std::string count_s = "X";
		//���p�J�W���j�r��...
		if (str[i] == ' ')
		{
			//�P�_��O�_���B��l
			if ((int)temp.length() == 1 && (isOperator(temp[0]) || temp == "@"))
			{
				int size = (int)stackNumber.size();
				std::string var;
				//�q���|���X��Ӽư��[�k
				if (temp == "+")
				{
					if (size < 2)
					{
						//���~�A�B�⦡�����~
					}
					var = stackNumber[size - 2] + " + " + stackNumber[size - 1];
					std::ostringstream strs;
					strs << count++;
					count_s += strs.str();
					mem[count_s] = var;
					stackNumber.pop_back();
					stackNumber.pop_back();
					stackNumber.push_back(count_s);
					size--;
				}
				//�q���|���X��Ӽư���k
				else if (temp == "-")
				{
					if (size < 2)
					{
						//���~�A�B�⦡�����~
					}
					var = stackNumber[size - 2] + " - " + stackNumber[size - 1];
					std::ostringstream strs;
					strs << count++;
					count_s += strs.str();
					mem[count_s] = var;
					stackNumber.pop_back();
					stackNumber.pop_back();
					stackNumber.push_back(count_s);
					size--;
				}
				//�q���|���X��Ӽư����k
				else if (temp == "*")
				{
					if (size < 2)
					{
						//���~�A�B�⦡�����~
					}
					var = stackNumber[size - 2] + " * " + stackNumber[size - 1];
					std::ostringstream strs;
					strs << count++;
					count_s += strs.str();
					mem[count_s] = var;
					stackNumber.pop_back();
					stackNumber.pop_back();
					stackNumber.push_back(count_s);
					size--;
				}
				//�q���|���X��Ӽư����k
				else if (temp == "/")
				{
					if (size < 2)
					{
						//���~�A�B�⦡�����~
					}
					var = stackNumber[size - 2] + " / " + stackNumber[size - 1];
					std::ostringstream strs;
					strs << count++;
					count_s += strs.str();
					mem[count_s] = var;
					stackNumber.pop_back();
					stackNumber.pop_back();
					stackNumber.push_back(count_s);
					size--;
				}
				//�q���|���X�@�Ӽƥ[�t��
				else if (temp == "@")
				{
					if (size < 1)
					{
						//���~�A�B�⦡�����~
					}
					var = " -1 * " + stackNumber[size - 1];
					std::ostringstream strs;
					strs << count++;
					count_s += strs.str();
					mem[count_s] = var;
					stackNumber.pop_back();
					stackNumber.push_back(count_s);
				}
				//�q���|���X��Ӽư�����
				else if (temp == "^")
				{
					if (size < 2)
					{
						//���~�A�B�⦡�����~
					}
					var = stackNumber[size - 2] + " ^ " + stackNumber[size - 1];
					std::ostringstream strs;
					strs << count++;
					count_s += strs.str();
					mem[count_s] = var;
					stackNumber.pop_back();
					stackNumber.pop_back();
					stackNumber.push_back(count_s);
					size--;
				}
				//�q���|���X�@�Ӽư����h
				else if (temp == "!")
				{
					//���~�A�B�⦡�����~
				}
				else if (temp == "$")
				{
					if (size < 1)
					{
						//���~�A�B�⦡�����~
					}
					var = " $ " + stackNumber[size - 1];
					std::ostringstream strs;
					strs << count++;
					count_s += strs.str();
					mem[count_s] = var;
					stackNumber.pop_back();
					stackNumber.push_back(count_s);
				}
				else if (temp == "%")
				{
					if (size < 1)
					{
						//���~�A�B�⦡�����~
					}
					var = " % " + stackNumber[size - 1];
					std::ostringstream strs;
					strs << count++;
					count_s += strs.str();
					mem[count_s] = var;
					stackNumber.pop_back();
					stackNumber.push_back(count_s);
				}
			}
			//���O�B��Ÿ��A�N��䬰�B�⤸
			//�N���Ʃ�J���|��
			else
			{
				//�ܼƲĤ@�Ӧr���^��
				if ((temp[0] >= 'a'&&temp[0] <= 'z') || (temp[0] >= 'A'&&temp[0] <= 'Z'))
				{
					stackNumber.push_back(temp);
				}
				//���O�ܼơA�P�_�䬰�p���٬O���
				else
				{
					int isPoint = 0;
					for (int i = 0; i < (int)temp.length(); i++)
					{
						if (temp[i] == '.')
						{
							if (isPoint++ > 0)
							{
								//���~�A�B�⦡�����~
							}
						}
						else if (temp[i] > '9' || temp[i] < '0')
						{
							//���~�A�B�⦡�����~
						}
					}
					stackNumber.push_back(temp);
				}

			}
			temp = "";
		}
		else
		{
			//�٨S�J����j�Ÿ��A�N��Ӧr���P�e���O�@�骺
			temp += str[i];
		}
	}

	//Build differential tree
	for (auto i = mem.begin(); i != mem.end(); i++)
	{
		std::string parsho = "\'";
		std::string parts[3] = {"","",""};
		std::string var = "";
		for (int j = 0,k = 0; j < (int)i->second.length(); j++)
		{
			if (i->second[j] == ' ')
				k++;
			else
				parts[k] += i->second[j];
		}
		parsho += i->first;

		if (parts[1] == "+")
		{
			var = "\'" + parts[0] + " + " + "\'" + parts[2];
			mem[parsho] = var;
		}
		else if (parts[1] == "-")
		{
			var = "\'" + parts[0] + " - " + "\'" + parts[2];
			mem[parsho] = var;
		}
		else if (parts[1] == "*")
		{
			var = "\'" + parts[0] + " * " + parts[2] + " + " + parts[0] + " * " + "\'" + parts[2];
			mem[parsho] = var;
		}
		else if (parts[1] == "^")
		{
			var = parts[2] + " * \'" + parts[0] + " * " + parts[0] + " ^ (" + parts[2] + "- 1 )";
			mem[parsho] = var;
		}
		else if (parts[1] == "$")
		{
			var = "%(" + parts[2] + ")" + " + \'" + parts[2];
			mem[parsho] = var;
		}
		else if (parts[1] == "%")
		{
			var = "-1 * $(" + parts[2] + ")" + " + \'" + parts[2];
		}
	}
	std::string count_s = "\'X";
	std::ostringstream strs;
	strs << count-1;
	count_s += strs.str();
	std::ostringstream strs2;
	strs2 << m[target];
	mem["X"] = strs2.str();
	//Automatic differentiation.
	ans = diff_Solution(count_s, mem);
	return ans;
}

//TODO: Given every variables, return the solution number.
//Expection: variables not in map.
double Polynomial::Solution(std::map<std::string, double> m)
{
	std::string str = Postorder(this->data);
	std::vector<double> stackNumber;	//�@��stack�Ω�s��B�⤸
	std::string temp = "";	//�@�ӼȦs�Ŷ�
	for (int i = 0; i < (int)str.length(); i++)
	{
		//���p�J�W���j�r��...
		if (str[i] == ' ')
		{
			//�P�_��O�_���B��l
			if ((int)temp.length() == 1 && (isOperator(temp[0]) || temp == "@"))
			{
				int size = (int)stackNumber.size();
				//�q���|���X��Ӽư��[�k
				if (temp == "+")
				{
					if (size < 2)
					{
						//���~�A�B�⦡�����~
					}
					stackNumber[size - 2] += stackNumber[size - 1];
					stackNumber.pop_back();
					size--;
				}
				//�q���|���X��Ӽư���k
				else if (temp == "-")
				{
					if (size < 2)
					{
						//���~�A�B�⦡�����~
					}
					stackNumber[size - 2] -= stackNumber[size - 1];
					stackNumber.pop_back();
					size--;
				}
				//�q���|���X��Ӽư����k
				else if (temp == "*")
				{
					if (size < 2)
					{
						//���~�A�B�⦡�����~
					}
					stackNumber[size - 2] *= stackNumber[size - 1];
					stackNumber.pop_back();
					size--;
				}
				//�q���|���X��Ӽư����k
				else if (temp == "/")
				{
					if (size < 2)
					{
						//���~�A�B�⦡�����~
					}
					stackNumber[size - 2] /= stackNumber[size - 1];
					stackNumber.pop_back();
					size--;
				}
				//�q���|���X�@�Ӽƥ[�t��
				else if (temp == "@")
				{
					if (size < 1)
					{
						//���~�A�B�⦡�����~
					}
					stackNumber[size - 1] *= -1;
				}
				//�q���|���X��Ӽư�����
				else if (temp == "^")
				{
					if (size < 2)
					{
						//���~�A�B�⦡�����~
					}
					stackNumber[size - 2] = pow(stackNumber[size - 2], stackNumber[size - 1]);
					stackNumber.pop_back();
					size--;
				}
				//�q���|���X�@�Ӽư����h
				else if (temp == "!")
				{
					//���~�A�B�⦡�����~
				}
				else if (temp == "$")
				{
					if (size < 1)
					{
						//���~�A�B�⦡�����~
					}
					stackNumber[size - 1] = sin(stackNumber[size - 1]);
				}
				else if (temp == "%")
				{
					if (size < 1)
					{
						//���~�A�B�⦡�����~
					}
					stackNumber[size - 1] = cos(stackNumber[size - 1]);
				}
			}
			//���O�B��Ÿ��A�N��䬰�B�⤸
			//�N���Ʃ�J���|��
			else
			{
				//�ܼƲĤ@�Ӧr���^��
				if ((temp[0] >= 'a'&&temp[0] <= 'z') || (temp[0] >= 'A'&&temp[0] <= 'Z'))
				{
					if (m.find(temp) == m.end())
					{
						//���~
					}
					stackNumber.push_back(m[temp]);
				}
				//���O�ܼơA�P�_�䬰�p���٬O���
				else
				{
					int isPoint = 0;
					for (int i = 0; i < (int)temp.length(); i++)
					{
						if (temp[i] == '.')
						{
							if (isPoint++ > 0)
							{
								//���~�A�B�⦡�����~
							}
						}
						else if (temp[i] > '9' || temp[i] < '0')
						{
							//���~�A�B�⦡�����~
						}
					}
					stackNumber.push_back(std::stod(temp));
				}

			}
			temp = "";
		}
		else
		{
			//�٨S�J����j�Ÿ��A�N��Ӧr���P�e���O�@�骺
			temp += str[i];
		}
	}
	return stackNumber[0];
}

//TODO: Can only use when only one variable.
//ERROR: Variables more than one, return number will be wrong.
double Polynomial::Solution(double x)
{
	std::string str = Postorder(this->data);
	std::vector<double> stackNumber;	//�@��stack�Ω�s��B�⤸
	std::string temp = "";	//�@�ӼȦs�Ŷ�
	for (int i = 0; i < (int)str.length(); i++)
	{
		//���p�J�W���j�r��...
		if (str[i] == ' ')
		{
			//�P�_��O�_���B��l
			if ((int)temp.length() == 1 && (isOperator(temp[0]) || temp == "@"))
			{
				int size = (int)stackNumber.size();
				//�q���|���X��Ӽư��[�k
				if (temp == "+")
				{
					if (size < 2)
					{
						//���~�A�B�⦡�����~
					}
					stackNumber[size - 2] += stackNumber[size - 1];
					stackNumber.pop_back();
					size--;
				}
				//�q���|���X��Ӽư���k
				else if (temp == "-")
				{
					if (size < 2)
					{
						//���~�A�B�⦡�����~
					}
					stackNumber[size - 2] -= stackNumber[size - 1];
					stackNumber.pop_back();
					size--;
				}
				//�q���|���X��Ӽư����k
				else if (temp == "*")
				{
					if (size < 2)
					{
						//���~�A�B�⦡�����~
					}
					stackNumber[size - 2] *= stackNumber[size - 1];
					stackNumber.pop_back();
					size--;
				}
				//�q���|���X��Ӽư����k
				else if (temp == "/")
				{
					if (size < 2)
					{
						//���~�A�B�⦡�����~
					}
					stackNumber[size - 2] /= stackNumber[size - 1];
					stackNumber.pop_back();
					size--;
				}
				//�q���|���X�@�Ӽƥ[�t��
				else if (temp == "@")
				{
					if (size < 1)
					{
						//���~�A�B�⦡�����~
					}
					stackNumber[size - 1] *= -1;
				}
				//�q���|���X��Ӽư�����
				else if (temp == "^")
				{
					if (size < 2)
					{
						//���~�A�B�⦡�����~
					}
					stackNumber[size - 2] = pow(stackNumber[size - 2], stackNumber[size - 1]);
					stackNumber.pop_back();
					size--;
				}
				//�q���|���X�@�Ӽư����h
				else if (temp == "!")
				{
					//���~�A�B�⦡�����~
				}
				else if (temp == "$")
				{
					if (size < 1)
					{
						//���~�A�B�⦡�����~
					}
					stackNumber[size - 1] = sin(stackNumber[size - 1]);
				}
				else if (temp == "%")
				{
					if (size < 1)
					{
						//���~�A�B�⦡�����~
					}
					stackNumber[size - 1] = cos(stackNumber[size - 1]);
				}
			}
			//���O�B��Ÿ��A�N��䬰�B�⤸
			//�N���Ʃ�J���|��
			else
			{
				//�ܼƲĤ@�Ӧr���^��
				if ((temp[0] >= 'a'&&temp[0] <= 'z') || (temp[0] >= 'A'&&temp[0] <= 'Z'))
				{
					stackNumber.push_back(x);
				}
				//���O�ܼơA�P�_�䬰�p���٬O���
				else
				{
					int isPoint = 0;
					for (int i = 0; i < (int)temp.length(); i++)
					{
						if (temp[i] == '.')
						{
							if (isPoint++ > 0)
							{
								//���~�A�B�⦡�����~
							}
						}
						else if (temp[i] > '9' || temp[i] < '0')
						{
							//���~�A�B�⦡�����~
						}
					}
					stackNumber.push_back(std::stod(temp));
				}

			}
			temp = "";
		}
		else
		{
			//�٨S�J����j�Ÿ��A�N��Ӧr���P�e���O�@�骺
			temp += str[i];
		}
	}
	return stackNumber[0];
}

//TODO: Automatic replace all string a to b
std::string Polynomial::Replace(std::string find, std::string target)
{
	std::string str;
	str = this->data;
	for (std::size_t found = str.find(find); found != std::string::npos; found = str.find(find))
	{
		str.replace(str.begin() + found, str.begin() + found + find.size(), target);
	}
	return str;
}

void ShowVars(std::map<std::string, double> m)
{
	for (auto i = m.begin(); i != m.end(); i++)
	{
		std::cout << i->first << " = " << i->second << std::endl;
	}
}