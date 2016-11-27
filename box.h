#ifndef __BOX_H__
#define __BOX_H__

#include "header.h"

class Box{

public:
	Box(int type);
	void drawSpeed(int x, int z);
	void drawShield(int x, int z);
	int genLocation(int range);
};

#endif