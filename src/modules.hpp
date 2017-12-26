#pragma once

#include <chrono>
#include <iostream>
#include <vector>
#include <dlfcn.h>

#include "state.hpp"

class Module
{
	private:
	std::chrono::steady_clock::time_point lastCall = std::chrono::steady_clock::now();
	protected:
	public:
	double interval = -1;
	double TimeToCall();
	virtual void Func( State * ) = 0;
	void Action( State * );

	virtual ~Module();
};

typedef Module *Import();
typedef Module *Destroy( Module * );
