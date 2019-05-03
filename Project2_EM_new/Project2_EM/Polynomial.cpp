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
	std::vector<double> stackNumber;	//一個stack用於存放運算元
	std::string temp = "";	//一個暫存空間
	for (int i = 0; i < (int)str.length(); i++)
	{
		//假如遇上分隔字元...
		if (str[i] == ' ')
		{
			//判斷其是否為運算子
			if ((int)temp.length() == 1 && (isOperator(temp[0]) || temp == "@"))
			{
				int size = (int)stackNumber.size();
				//從堆疊拿出兩個數做加法
				if (temp == "+")
				{
					if (size < 2)
					{
						//錯誤，運算式有錯誤
					}
					stackNumber[size - 2] += stackNumber[size - 1];
					stackNumber.pop_back();
					size--;
				}
				//從堆疊拿出兩個數做減法
				else if (temp == "-")
				{
					if (size < 2)
					{
						//錯誤，運算式有錯誤
					}
					stackNumber[size - 2] -= stackNumber[size - 1];
					stackNumber.pop_back();
					size--;
				}
				//從堆疊拿出兩個數做乘法
				else if (temp == "*")
				{
					if (size < 2)
					{
						//錯誤，運算式有錯誤
					}
					stackNumber[size - 2] *= stackNumber[size - 1];
					stackNumber.pop_back();
					size--;
				}
				//從堆疊拿出兩個數做除法
				else if (temp == "/")
				{
					if (size < 2)
					{
						//錯誤，運算式有錯誤
					}
					stackNumber[size - 2] /= stackNumber[size - 1];
					stackNumber.pop_back();
					size--;
				}
				//從堆疊拿出一個數加負號
				else if (temp == "@")
				{
					if (size < 1)
					{
						//錯誤，運算式有錯誤
					}
					stackNumber[size - 1] *= -1;
				}
				//從堆疊拿出兩個數做次方
				else if (temp == "^")
				{
					if (size < 2)
					{
						//錯誤，運算式有錯誤
					}
					stackNumber[size - 2] = pow(stackNumber[size - 2], stackNumber[size - 1]);
					stackNumber.pop_back();
					size--;
				}
				//從堆疊拿出一個數做階層
				else if (temp == "!")
				{
					//錯誤，運算式有錯誤
				}
			}
			//不是運算符號，代表其為運算元
			//將此數放入堆疊中
			else
			{
				//變數第一個字為英文
				if ((temp[0] >= 'a'&&temp[0] <= 'z') || (temp[0] >= 'A'&&temp[0] <= 'Z'))
				{
					if (m.find(temp) == m.end())
					{
						//錯誤
					}
					stackNumber.push_back(m[temp]);
				}
				//不是變數，判斷其為小數還是整數
				else
				{
					int isPoint = 0;
					for (int i = 0; i < (int)temp.length(); i++)
					{
						if (temp[i] == '.')
						{
							if (isPoint++ > 0)
							{
								//錯誤，運算式有錯誤
							}
						}
						else if (temp[i] > '9' || temp[i] < '0')
						{
							//錯誤，運算式有錯誤
						}
					}
					stackNumber.push_back(std::stod(temp));
				}

			}
			temp = "";
		}
		else
		{
			//還沒遇到分隔符號，代表該字元與前面是一體的
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
	std::vector<double> stackNumber;	//一個stack用於存放運算元
	std::string temp = "";	//一個暫存空間
	for (int i = 0; i < (int)str.length(); i++)
	{
		//假如遇上分隔字元...
		if (str[i] == ' ')
		{
			//判斷其是否為運算子
			if ((int)temp.length() == 1 && (isOperator(temp[0]) || temp == "@"))
			{
				int size = (int)stackNumber.size();
				//從堆疊拿出兩個數做加法
				if (temp == "+")
				{
					if (size < 2)
					{
						//錯誤，運算式有錯誤
					}
					stackNumber[size - 2] += stackNumber[size - 1];
					stackNumber.pop_back();
					size--;
				}
				//從堆疊拿出兩個數做減法
				else if (temp == "-")
				{
					if (size < 2)
					{
						//錯誤，運算式有錯誤
					}
					stackNumber[size - 2] -= stackNumber[size - 1];
					stackNumber.pop_back();
					size--;
				}
				//從堆疊拿出兩個數做乘法
				else if (temp == "*")
				{
					if (size < 2)
					{
						//錯誤，運算式有錯誤
					}
					stackNumber[size - 2] *= stackNumber[size - 1];
					stackNumber.pop_back();
					size--;
				}
				//從堆疊拿出兩個數做除法
				else if (temp == "/")
				{
					if (size < 2)
					{
						//錯誤，運算式有錯誤
					}
					stackNumber[size - 2] /= stackNumber[size - 1];
					stackNumber.pop_back();
					size--;
				}
				//從堆疊拿出一個數加負號
				else if (temp == "@")
				{
					if (size < 1)
					{
						//錯誤，運算式有錯誤
					}
					stackNumber[size - 1] *= -1;
				}
				//從堆疊拿出兩個數做次方
				else if (temp == "^")
				{
					if (size < 2)
					{
						//錯誤，運算式有錯誤
					}
					stackNumber[size - 2] = pow(stackNumber[size - 2], stackNumber[size - 1]);
					stackNumber.pop_back();
					size--;
				}
				//從堆疊拿出一個數做階層
				else if (temp == "!")
				{
					//錯誤，運算式有錯誤
				}
			}
			//不是運算符號，代表其為運算元
			//將此數放入堆疊中
			else
			{
				//變數第一個字為英文
				if ((temp[0] >= 'a'&&temp[0] <= 'z') || (temp[0] >= 'A'&&temp[0] <= 'Z'))
				{
					stackNumber.push_back(x);
				}
				//不是變數，判斷其為小數還是整數
				else
				{
					int isPoint = 0;
					for (int i = 0; i < (int)temp.length(); i++)
					{
						if (temp[i] == '.')
						{
							if (isPoint++ > 0)
							{
								//錯誤，運算式有錯誤
							}
						}
						else if (temp[i] > '9' || temp[i] < '0')
						{
							//錯誤，運算式有錯誤
						}
					}
					stackNumber.push_back(std::stod(temp));
				}

			}
			temp = "";
		}
		else
		{
			//還沒遇到分隔符號，代表該字元與前面是一體的
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