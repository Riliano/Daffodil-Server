#pragma once

#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <dlfcn.h>
#include <map>

#include "modules.hpp"
#include "database.hpp"

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
	double downTime;
	const double DEFAULT_DOWN_TIME = 0.2;
	public:
	void Add( const char * );
	void Remove( const char * );
	void Execute( Database *, const char * );
	void ExecuteTimed( Database * );
	double GetDowntime();

	~ModuleManager();
};
