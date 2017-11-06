#pragma once

#include <vector>
#include <SDL2/SDL_net.h>

#include "user.hpp"

struct Database
{
	SDLNet_SocketSet allSockets;
    std::vector< User > users;
	~Database()
	{
		SDLNet_FreeSocketSet( allSockets );
	}
};
