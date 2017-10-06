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

size_t ModuleManager::Size()
{
	return modules.size();
}
double ModuleManager::TimeToCall( size_t m )
{
	return modules[m]->TimeToCall();
}
void ModuleManager::Execute( size_t m )
{
	modules[m]->Action();
}
void ModuleManager::AddExternal( const char * filename )
{
	void *externalModule = dlopen( filename, RTLD_NOW );
	Module *module = (Module*) dlsym( externalModule, "import" );

	modules.push_back( module );
}
void ModuleManager::AddLocal( Module *module )
{
	modules.push_back( module );
}
