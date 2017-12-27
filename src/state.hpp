#pragma once

#include <vector>
#include <SDL2/SDL_net.h>

#include "user.hpp"

struct State
{
    SDLNet_SocketSet allSockets;
    TCPsocket serverSocket;
    std::vector< User > users;
    ~State()
    {
	SDLNet_TCP_Close( serverSocket );
	for( size_t i=0;i<users.size();i++ )
	    SDLNet_TCP_Close( users[i].socket );
	users.clear();
	SDLNet_FreeSocketSet( allSockets );
    }
};
