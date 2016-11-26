#ifndef __POWERUP_H__
#define __POWERUP_H__

#include "header.h"

class Powerup{

public:
	Powerup();
	void drawSpeedPU(int x, int z);
	void drawShieldPU(int x, int z);
	int genLocation(int range);
};

#endif