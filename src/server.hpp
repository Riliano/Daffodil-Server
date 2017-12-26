#pragma once

#include <SDL2/SDL_net.h>
#include <vector>

#include "state.hpp"
#include "modulemanager.hpp"

class DaffodilServer
{
	const unsigned int DEFAULT_PORT = 1234;
	const unsigned int DEFAULT_SERVER_SIZE = 32;

	unsigned int port_ = DEFAULT_PORT;
	unsigned int serverSize_ = DEFAULT_SERVER_SIZE;

	bool serverIsRunning_ = false;
	TCPsocket socket_;
	void StartServer();

	State st;
	ModuleManager modules;

	void MainLoop();

	public:
	void LoadModule( const char * );

	void SetPort( const unsigned int & );
	void SetServerSize( const unsigned int & );
	void Start();
	void Quit();

	~DaffodilServer()
	{
		SDLNet_TCP_Close( socket_ );
		SDLNet_Quit();
	}
};
