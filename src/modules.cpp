#include "modules.hpp"

void Module::Action( Database &db )
{
	Func( db );
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
