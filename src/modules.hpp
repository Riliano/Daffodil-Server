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
	public:
	double interval = -1;
	double TimeToCall();
	virtual void Func() = 0;
	void Action();
};

typedef Module* import();

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

	~ModuleManager()
	{
		modules.clear();
	}
};
