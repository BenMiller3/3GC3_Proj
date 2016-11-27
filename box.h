#ifndef __BOX_H__
#define __BOX_H__

#include "header.h"

class Box{

public:
	Box();
	void drawSpeedPU(int x, int z);
	void drawShieldPU(int x, int z);
	int genLocation(int range);
};

#endif