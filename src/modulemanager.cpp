#include "modulemanager.hpp"

bool ExternalModule::Load( const char *filename )
{
	externalClass = dlopen( filename, RTLD_NOW );
	const char *dlsym_error = dlerror();
	if( dlsym_error )
	{
		std::cerr << "Cannot load module " << filename << " : " << dlsym_error << "/n";
		return false;
	}

	Constructor = (Import*) dlsym( externalClass, "import" );
	dlsym_error = dlerror();
	if( dlsym_error )
	{
		std::cerr << "Cannot find constructor in " << filename << " : " << dlsym_error << "/n";
		dlclose( externalClass );
		return false;
	}

	Destructor = (Destroy*) dlsym( externalClass, "destroy" );
	dlsym_error = dlerror();
	if( dlsym_error )
	{
		std::cerr << "Cannot find destructor in " << filename << " : " << dlsym_error << "/n";
		dlclose( externalClass );
		return false;
	}

	module = Constructor();
	return true;
}
void ExternalModule::Unload()
{
	Destructor( module );
	dlclose( externalClass );
}

void ModuleManager::Add( const char *name )
{
	moduleMap[name].Load( name );
	if( moduleMap[name].module->interval != -1 )
		timedModules.push_back( &moduleMap[name] );
}
void ModuleManager::Remove( const char *name )
{
    moduleMap[name];
    if( moduleMap[name].module->interval != -1 )
    {
	for( size_t i=0;i<timedModules.size();i++ )
	{
	    if( timedModules[i] == &moduleMap[name] )
	    {
		timedModules[i] = nullptr;
		timedModules.erase( timedModules.begin()+i );
		break;
	    }
	}
    }

    moduleMap[name].Unload();
    moduleMap.erase( name );
}
void ModuleManager::Execute( State *st, const char *name )
{
	moduleMap[name].module->Action( st );
}
void ModuleManager::ExecuteTimed( State *st )
{
	for( size_t i=0;i<timedModules.size();i++ )
		if( timedModules[i]->module->TimeToCall() <= 0 )
			timedModules[i]->module->Action( st );
}
double ModuleManager::GetDowntime()
{
	if( timedModules.empty() )
		return DEFAULT_DOWN_TIME;
	double downtime = 0;
	for( size_t i=0;i<timedModules.size();i++ )
		downtime = std::min( downtime, timedModules[i]->module->TimeToCall() );
	return downtime;
}
ModuleManager::~ModuleManager()
{
	for( auto it=moduleMap.begin();it!=moduleMap.end();it++ )
		it->second.Unload();
	timedModules.clear();
}
