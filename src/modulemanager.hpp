#pragma once

#include <chrono>
#include <iostream>
#include <vector>
#include <dlfcn.h>

#include "modules.hpp"
#include "database.hpp"

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
	void Execute( size_t, Database * );

	~ModuleManager();
};
