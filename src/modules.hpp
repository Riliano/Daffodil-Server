#pragma once

#include <chrono>
#include <iostream>
#include <vector>
#include <dlfcn.h>

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
