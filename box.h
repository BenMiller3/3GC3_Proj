#ifndef __BOX_H__
#define __BOX_H__

#include "header.h"

class Box{

public:
	Box();
	void drawCollect(int x, int z);
	void drawAvoid(int x, int z);
	int genX(int range);
	int genZ(int range);
};

#endif