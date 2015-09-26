#include "helper_func.h"
#include "house.h"

#include <iostream>

using namespace std;

namespace rt	{

	house_t house;

	void setup_rt()	{
		house.setup();
	}

	void begin_rt()	{
		house.play();
	}	
}
