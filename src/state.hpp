#pragma once

#include <vector>
#include <SDL2/SDL_net.h>

#include "user.hpp"

struct State
{
    SDLNet_SocketSet allSockets;
    std::vector< User > users;
    ~State()
    {
	    SDLNet_FreeSocketSet( allSockets );
    }
};
