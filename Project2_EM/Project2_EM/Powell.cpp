#include "Powell.h"
#include "Polynomial.h"

std::map<char, double> Powell(Polynomial p, std::map<char, double> m)
{
	for (int i = 0; i < m.size(); i++)
	{
		double sum = 0;
		sum = p.Solution(m);

	}
}