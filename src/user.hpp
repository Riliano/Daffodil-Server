#pragma once

#include <SDL2/SDL_net.h>

class User
{
    public:
    int id;
    TCPsocket socket;
    int status;

    User( const int &myID, const TCPsocket &mySocket)
    {
        id = myID;
        socket = mySocket;
        status = -1;
    }
};
