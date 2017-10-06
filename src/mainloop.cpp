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
	ModuleManager modules;
	modules.AddLocal( &info );
	modules.AddLocal( &info2 );
	modules.AddExternal( "./test.so" );

	while( serverIsRunning_ )
	{
		for( unsigned int i=0;i<modules.Size();i++ )
			if( modules.TimeToCall(i) <= 0 )
				modules.Execute(i);

		double downtime = modules.TimeToCall(0);
		for( unsigned int i=1;i<modules.Size();i++ )
			downtime = std::min( downtime, modules.TimeToCall(i) );

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
