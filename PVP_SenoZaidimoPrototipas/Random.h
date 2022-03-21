#pragma once

#include <stdlib.h>

class Random
{
public:
	static double RandZeroToOne()
	{
		return ((double)rand() / (double)RAND_MAX);
	}

	static double RandOneToOne()
	{
		return RandZeroToOne() * 2. - 1.;
	}
};

