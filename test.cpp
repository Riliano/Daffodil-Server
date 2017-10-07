#include <iostream>

#include "src/modules.hpp"

class Info3 : public Module
{
	public:
	virtual void Func()
	{
		std::cout<<"Hello :D\n";
	}
	Info3()
	{
		interval = 2;
	}
}info3;

extern "C" Module* import()
{
	return &info3;
}

extern "C" void destroy()
{
//	delete &info3;
}
