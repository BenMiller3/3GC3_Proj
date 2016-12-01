#include "header.h"
#include "box.h"


int n = 10; //Number of boxes generated per loop (treadmill reset)
float boxLoc[] = {0, 0, 0};

Box::Box(){ }


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


void drawCuboid(float* c, float w, float h, float d){
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


int Box::genX(int range){
	int x1 = rand()%(range)+1;
	int x2 = (rand()%range + 1) * (-1);
	return x2 + x1;
}

int Box::genZ(int range){
	int x = (rand()%range + 1) * (-1);
	return x;
}


void Box::drawCollect(int xLocation, int zLocation){
	glColor3f(0, 1, 0);
	boxLoc[0] = xLocation;
	boxLoc[2] = zLocation;
	drawCuboid(boxLoc, 1, 1, 1);
}


void Box::drawAvoid(int xLocation, int zLocation){
	glColor3f(0, 0, 0);
	boxLoc[0] = xLocation;
	boxLoc[2] = zLocation;
	drawCuboid(boxLoc, 1, 1, 1);
}