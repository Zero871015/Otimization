#include "Exceptions.h"



Exceptions::Exceptions()
{

}

int Exceptions::getType()
{
	return type;
}

Exceptions::Exceptions(int type)
{
	this->type = type;
}
