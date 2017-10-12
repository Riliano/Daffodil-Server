#include <iostream>

#include "src/modules.hpp"

class Info3 : public Module
{
	int memory[2000];
	public:
	virtual void Func()
	{
		std::cout<<"Hello :D\n";
	}
	Info3()
	{
		interval = 2;
	}
};

extern "C" Module* import()
{
	return new Info3;
}

extern "C" void destroy( Module *m )
{
	delete m;
}
