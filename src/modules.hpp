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
	double interval;
	double TimeToCall();
	virtual void Func() = 0;
	void Action();

	virtual ~Module();
};

typedef Module *Import();
typedef Module *Destroy( Module * );

class ExternalModule
{
	public:
	Module* module;
	Import* Constructor;
	Destroy* Destructor;
	void* externalClass;

	bool Load( const char * );
	void Unload();
};

class ModuleManager
{
	private:
	std::vector< ExternalModule* > modules;
	public:
	void AddExternal( const char * );
	void AddLocal( Module* );
	size_t Size();
	double TimeToCall( size_t );
	void Remove( size_t );
	void Execute( size_t );

	~ModuleManager();
};
