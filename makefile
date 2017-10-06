default:
	g++ -c src/main.cpp src/mainloop.cpp src/netcode.cpp src/modules.cpp -Wall -Wpedantic
	g++ main.o mainloop.o netcode.o modules.o -pthread -lSDL2 -lSDL2_net -ldl
