#include "modules.hpp"

void Module::Action()
{
	Func();
	lastCall = std::chrono::steady_clock::now();
}
double Module::TimeToCall()
{
	std::chrono::steady_clock::time_point timeNow = std::chrono::steady_clock::now();
	std::chrono::duration < double > timeSpan =
		std::chrono::duration_cast < std::chrono::duration < double > >(timeNow - lastCall);

	return interval - timeSpan.count();
}
Module::~Module(){}

void ExternalModule::Load( const char *filename )
{
	externalClass = dlopen( filename, RTLD_NOW );
	const char *dlsym_error = dlerror();
	if( dlsym_error )
	{
		std::cerr << "Cannot load module " << filename << " : " << dlsym_error << "/n";
		return;
	}

	constructor = (Import*) dlsym( externalClass, "import" );
	dlsym_error = dlerror();
	if( dlsym_error )
	{
		std::cerr << "Cannot find constructor in " << filename << " : " << dlsym_error << "/n";
		return;
	}
	module = constructor();
}
void ExternalModule::Unload()
{
	delete module;
	dlclose( externalClass );
}

size_t ModuleManager::Size()
{
	return modules.size();
}
double ModuleManager::TimeToCall( size_t m )
{
	return modules[m]->module->TimeToCall();
}
void ModuleManager::Execute( size_t m )
{
	modules[m]->module->Action();
}
void ModuleManager::AddExternal( const char *filename )
{
	ExternalModule *newModule = new ExternalModule;
	newModule->Load( filename );
	modules.push_back( newModule );
}
void ModuleManager::Remove( size_t m )
{
	modules[m]->Unload();
	for( size_t i=m;i<modules.size()-1;i++ )
		modules[i] = modules[i+1];
	modules.pop_back();
}
void ModuleManager::AddLocal( Module *module )
{
//	modules.push_back( module );
}
