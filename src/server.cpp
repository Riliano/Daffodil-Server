#include <iostream>

#include <SDL2/SDL.h>

#include "server.hpp"
#include "modules.hpp"

void DaffodilServer::MainLoop()
{
	while( serverIsRunning_ )
	{
		modules.ExecuteTimed( &st );
		double downtime = modules.GetDowntime();
		// convert from seconds to miliseconds
		SDL_Delay( downtime*1000 );
	}
}

void DaffodilServer::LoadModule( const char *name )
{
	modules.Add( name );
}
void DaffodilServer::RemoveModule( const char *name )
{
    modules.Remove( name );
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
