#include <thread>
#include <iostream>
#include <string>

#include "server.hpp"

int main()
{
	DaffodilServer server;

	server.SetPort( 3333 );
	server.SetServerSize( 64 );

	std::thread t1( &DaffodilServer::Start, &server );
	while( true )
	{
		char ch = getchar();
		if( ch == 'q' )
		{
			server.Quit();
			break;
		}
		if( ch == 'l' )
		{
			std::string name;
			std::cin>>name;
			server.LoadModule( name.data() );
		}
	}
	/*
	SDL_Delay( 10000 );
	server.SetPort( 3332 );
	server.Quit();
	server.SetPort( 3332 );
	server.Start();
	SDL_Delay( 2000 );
	server.Quit();
*/
	t1.join();
}
