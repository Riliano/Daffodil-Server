#pragma once

#include <iostream>

#include <SDL2/SDL.h>

class Module
{
	public:
	long long interval;
	long long lastCall = 0;
	long long TimeToCall()
	{
		return (lastCall + interval) - SDL_GetTicks();
	}

	virtual void Action(){};
};

class Info: public Module
{
	public:
	
	virtual void Action()
	{
		std::cout<<"Hi\n";
		lastCall = SDL_GetTicks();
	}
	Info()
	{
		interval = 1000;
	}
}info;

class Info2: public Module
{
	public:
	
	virtual void Action()
	{
		std::cout<<"Hi;)\n";
		lastCall = SDL_GetTicks();
	}
	Info2()
	{
		interval = 300;
	}
} info2;
