#include <iostream>

#include <SDL2/SDL.h>

#include "server.hpp"
#include "modules.hpp"

class Info: public Module
{
	public:

	virtual void Func()
	{
		std::cout<<"Hi\n";
	}
	Info()
	{
		interval = 1;
	}
}info;

class Info2: public Module
{
	public:

	virtual void Func()
	{
		std::cout<<"Hi;)\n";
	}
	Info2()
	{
		interval = 0.3;
	}
} info2;


void DaffodilServer::MainLoop()
{

	Module *modules[] = {&info, &info2};
	size_t modulesSize = 2;

	while( serverIsRunning_ )
	{
		for( unsigned int i=0;i<modulesSize;i++ )
			if( modules[i]->TimeToCall() <= 0 )
				modules[i]->Action();

		double downtime = modules[0]->TimeToCall();
		for( unsigned int i=1;i<modulesSize;i++ )
			downtime = std::min( downtime, modules[i]->TimeToCall() );

		// convert from seconds to miliseconds
		SDL_Delay( downtime*1000 );
	}
}

void DaffodilServer::Start()
{
	StartServer();
	MainLoop();
}

void DaffodilServer::Quit()
{
	serverIsRunning_ = false;
	std::cout<<"Quitting...\n";
}
