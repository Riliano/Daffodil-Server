#include <iostream>

#include "server.hpp"

void DaffodilServer::SetPort( const unsigned int &port )
{
	if( !serverIsRunning_ )
	{
		port_ = port;
		std::cout<<"Port set to "<<port<<"\n";
	}else
	{
		std::cout<<"Error setting port: server is already running\n";
	}
}

void DaffodilServer::SetServerSize( const unsigned int &serverSize )
{
	if( !serverIsRunning_ )
	{
		serverSize_ = serverSize;
		std::cout<<"Server size set to "<<serverSize<<"\n";
	}else
	{
		std::cout<<"Error setting server size: server is already running\n";
	}
}

void DaffodilServer::StartServer()
{
	IPaddress ip;
	SDLNet_Init();
	std::cout<<"Starting server on port: "<<port_<<" with size: "<<serverSize_<<"\n";
	SDLNet_ResolveHost( &ip, NULL, port_ );
	st.allSockets = SDLNet_AllocSocketSet( serverSize_ );
	socket_ = SDLNet_TCP_Open( &ip );
	SDLNet_TCP_AddSocket( st.allSockets, socket_ );
	serverIsRunning_ = true;
}
