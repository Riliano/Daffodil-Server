#pragma once

#include <chrono>
#include <iostream>

#include <SDL2/SDL.h>

class Module
{
	private:
	std::chrono::steady_clock::time_point lastCall = std::chrono::steady_clock::now();
	protected:
	double interval;
	public:
	double TimeToCall();
	virtual void Func() = 0;
	void Action();
};
