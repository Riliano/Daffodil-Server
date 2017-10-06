#pragma once

#include <chrono>
#include <iostream>
#include <vector>
#include <dlfcn.h>

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

class ModuleManager
{
	private:
	std::vector< Module* > modules;
	public:
	void AddExternal( const char * );
	void AddLocal( Module* );
	size_t Size();
	double TimeToCall( size_t );
	//void Remove();
	void Execute( size_t );
};
