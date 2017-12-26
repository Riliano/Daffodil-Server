#pragma once

#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <dlfcn.h>
#include <map>

#include "modules.hpp"
#include "state.hpp"

class ExternalModule
{
	public:
	std::string name;

	Module* module;
	Import* Constructor;
	Destroy* Destructor;
	void* externalClass;

	ExternalModule *next;

	bool Load( const char * );
	void Unload();
};

class ModuleManager
{
	private:
	std::map< std::string, ExternalModule > moduleMap;
	std::vector< ExternalModule* > timedModules;
	const double DEFAULT_DOWN_TIME = 0.2;
	double downTime;
	public:
	void Add( const char * );
	void Remove( const char * );
	void Execute( State *, const char * );
	void ExecuteTimed( State * );
	double GetDowntime();

	~ModuleManager();
};
