#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "header.h"

class Character{

public:
	Character();
	void drawCharacter(float* pos, float gameSpeed, bool blend);
};

#endif