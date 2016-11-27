#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "header.h"
#include "box.h"

class Character{

public:
	Character();
	void drawCharacter(float* pos, float* rot, float gameSpeed);
	bool hitTest(Box box);

};

#endif