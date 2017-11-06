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

size_t ModuleManager::Size()
{
	return modules.size();
}
double ModuleManager::TimeToCall( size_t m )
{
	return modules[m]->module->TimeToCall();
}
void ModuleManager::Execute( size_t m, Database *db )
{
	modules[m]->module->Action( db );
}
void ModuleManager::AddExternal( const char *filename )
{
	ExternalModule *newModule = new ExternalModule;
	bool success = newModule->Load( filename );
	if( success )
		modules.push_back( newModule );
	else
		delete newModule;
}
void ModuleManager::Remove( size_t m )
{
	modules[m]->Unload();
	delete modules[m];
	for( size_t i=m;i<modules.size()-1;i++ )
		modules[i] = modules[i+1];
	modules.pop_back();
}
void ModuleManager::AddLocal( Module *module )
{
//	modules.push_back( module );
}
ModuleManager::~ModuleManager()
{
	if( modules.size() > 0 )
		while( !modules.empty() )
			Remove( 0 );
}
