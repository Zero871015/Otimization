#include "Polynomial.h"

#include <vector>


Polynomial::Polynomial()
{
}

Polynomial::Polynomial(std::string str)
{
	for (std::size_t found = str.find("sin"); found != std::string::npos; found = str.find("sin"))
	{
		str.replace(str.begin() + found, str.begin() + found + 3, "%");
	}
	for (std::size_t found = str.find("cos"); found != std::string::npos; found = str.find("cos"))
	{
		str.replace(str.begin() + found, str.begin() + found + 3, "$");
	}
	this->data = str;
	//std::cout << Postorder(str) << std::endl;
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