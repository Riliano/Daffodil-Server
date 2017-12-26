#include <SDL2/SDL_net.h>
#include <iostream>

#include "../modules.hpp"
#include "../state.hpp"
#include "../user.hpp"

class ClientHandling : public Module
{
    public:
    virtual void Func( State *st )
    {
	int active = SDLNet_CheckSockets( st->allSockets, 0 );
	if( !st->users.empty() )
	    std::cout<<"Active users: "<<st->users.size()<<std::endl;
	if( active <= 0 )
	    return;
	if( SDLNet_SocketReady( st->serverSocket ) )
	{
	    active--;
	    std::cout<<"New client"<<std::endl;
	    TCPsocket socket = SDLNet_TCP_Accept( st->serverSocket );
	    User newUser( st->users.size(), socket );
	    st->users.push_back( newUser );
	}
    }

    ClientHandling()
    {
	interval = 0.10;
    }
};

extern "C" Module *import()
{
    return new ClientHandling;
}
extern "C" void destroy( Module *m )
{
    delete m;
}
