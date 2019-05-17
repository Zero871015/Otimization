#include "Quasi.h"
#define threshold 1E-6

void DFP(Polynomial p, std::map<std::string, double>startpoint)
{
	MyMatrix PDM, dk,gk,signChange;
	MyVector temp_v;
	
	//create a indentity matrix
	for (int i = 0; i < startpoint.size(); i++)
	{
		std::vector < double >blank(startpoint.size());	
		blank[i] = 1;
		temp_v.data = blank;
		PDM.data.push_back(temp_v);
	}
	//bulid matrix for calculating
	temp_v.data.clear();
	temp_v.data.push_back(-1);
	signChange.data.push_back(temp_v);
	temp_v.data.clear();
	temp_v.data.push_back(0);
	gk.data.push_back(temp_v);


	while ((gk[0][0] = p.Solution(startpoint)) <= threshold)
	{
		dk = mul(mul(signChange, PDM), gk);
	}

}


System::String ^QuasiNewton(Polynomial p, std::map<std::string, double>startpoint)
{
	return "";
}