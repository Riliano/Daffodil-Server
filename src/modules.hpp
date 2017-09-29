#pragma once

#include <chrono>
#include <iostream>

#include <SDL2/SDL.h>

class Module
{
	public:
	double interval;
	std::chrono::steady_clock::time_point lastCall = std::chrono::steady_clock::now();
	double TimeToCall()
	{
		std::chrono::steady_clock::time_point timeNow = std::chrono::steady_clock::now();
		std::chrono::duration < double > timeSpan =
			std::chrono::duration_cast < std::chrono::duration < double > >(timeNow - lastCall);

		return interval - timeSpan.count();
	}

	virtual void Action(){};
};

class Info: public Module
{
	public:
	
	virtual void Action()
	{
		std::cout<<"Hi\n";
		lastCall = std::chrono::steady_clock::now();
	}
	Info()
	{
		interval = 1;
	}
}info;

class Info2: public Module
{
	public:
	
	virtual void Action()
	{
		std::cout<<"Hi;)\n";
		lastCall = std::chrono::steady_clock::now();
	}
	Info2()
	{
		interval = 0.3;
	}
} info2;
