#include "header.h"
#include "box.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

// Number of powerups generated per loop (treadmill reset)
int n = 10;

Box::Box(){
	
}

void drawPolygon(int a, int b, int c, int d, float v[8][3]){
	glBegin(GL_POLYGON);
		glVertex3fv(v[a]);
		glVertex3fv(v[b]);
		glVertex3fv(v[c]);
		glVertex3fv(v[d]);
	glEnd();
}


void cube(float v[8][3]){
	drawPolygon(0, 3, 2, 1, v);
	drawPolygon(1, 0, 4, 5, v);
	drawPolygon(5, 1, 2, 6, v);
	drawPolygon(2, 3, 7, 6, v);
	drawPolygon(6, 5, 4, 7, v);
	drawPolygon(4, 0, 3, 7, v);
}


void drawBox(float* c, float w, float h, float d){
	float vertices[8][3] = { {c[0]-w/2, c[1]-h/2, c[2]+d/2},
							 {c[0]-w/2, c[1]+h/2, c[2]+d/2},
							 {c[0]+w/2, c[1]+h/2, c[2]+d/2},
							 {c[0]+w/2, c[1]-h/2, c[2]+d/2}, 
							 {c[0]-w/2, c[1]-h/2, c[2]-d/2}, 
							 {c[0]-w/2, c[1]+h/2, c[2]-d/2}, 
							 {c[0]+w/2, c[1]+h/2, c[2]-d/2},
							 {c[0]+w/2, c[1]-h/2, c[2]-d/2} };
	cube(vertices);
}

int Box::genLocation(int range){
	int x1 = rand()%(range)+1;
	int x2 = (rand()%range + 1) * (-1);

	return x2 + x1;
}

// Speed powerup
void Box::drawSpeedPU(int xLocation, int zLocation){
	glColor3f(0, 0, 1);
	float origin[3] = {xLocation, 0, zLocation};
	drawBox(origin, 1, 1, 1);
	
}

// Shield powerup
void Box::drawShieldPU(int xLocation, int zLocation){
	glColor3f(1, 1, 0);
	float origin[3] = {xLocation, 0, zLocation};
	drawBox(origin, 1, 1, 1);
}
