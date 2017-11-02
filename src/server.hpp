#pragma once

#include <SDL2/SDL_net.h>
#include <vector>

#include "database.hpp"
#include "modulemanager.hpp"

class DaffodilServer
{
	const unsigned int DEFAULT_PORT = 1234;
	const unsigned int DEFAULT_SERVER_SIZE = 32;

	unsigned int port_ = DEFAULT_PORT;
	unsigned int serverSize_ = DEFAULT_SERVER_SIZE;

	bool serverIsRunning_ = false;
	TCPsocket socket_;
	SDLNet_SocketSet allSockets_;
	void StartServer();

	Database db;
	ModuleManager modules;

	void MainLoop();

	public:

	void SetPort( const unsigned int & );
	void SetServerSize( const unsigned int & );
	void Start();
	void Quit();

	~DaffodilServer()
	{
		SDLNet_FreeSocketSet( allSockets_ );
		SDLNet_TCP_Close( socket_ );
		SDLNet_Quit();

	}
};
