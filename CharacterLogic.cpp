#include "header.h"


float pos[] = {0,0,5};
float rot[] = {0, 0, 0};
float camPos[] = {0, 10, 15};
float angle = 0.0f;
float spd = 0.3;
bool spdPowerUp = true;
bool shieldPowerUp = true;


void special(int key, int x, int y){
	int mod = glutGetModifiers();
	if(spdPowerUp && mod == GLUT_ACTIVE_SHIFT) spd = 0.5;
	else spd = 0.3;

	switch(key){
		case GLUT_KEY_LEFT:
			if(pos[0] > -4.4) pos[0] -= spd;
			rot[1] = -90;
			break;

		case GLUT_KEY_RIGHT:
			if(pos[0] < 4.4) pos[0] += spd;
			rot[1] = 90;
			break;
	}
	glutPostRedisplay();
}


void init(void){
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);
}


void DrawSnowman(float* pos, float* rot){
	glPushMatrix();

	glTranslatef(pos[0], pos[1], pos[2]);
	glRotatef(rot[1], 0, 1, 0);

	//draw body
	glColor3f(1,1,1);
	glutSolidSphere(1, 16, 16);

	//draw buttons
	glPushMatrix();
	glTranslatef(0, 0.35, 0.9);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.15, 0.95);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -0.05, 0.95);
	glColor3f(0, 0, 0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();


	glPushMatrix();
	//translate relative to body, and draw head
	glTranslatef(0, 1.25, 0);
	glColor3f(1,1,1);
	glutSolidSphere(0.5, 16, 16);
	
	//translate and draw right eye
	glPushMatrix();
	glTranslatef(0.2, 0.15, 0.45);
	glColor3f(0,0,0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	//translate and draw left eye
	glPushMatrix();
	glTranslatef(-0.2, 0.15, 0.45);
	glColor3f(0,0,0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	//translate and draw nose
	glPushMatrix();
	glTranslatef(0, 0, 0.5);
	glColor3f(1,0.4,0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	glPopMatrix();//body
	glPopMatrix();//snowman
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

void drawSPDPU(){
	glColor3f(0, 0, 1);
	float origin[3] = {-3, 0, 0};
	drawBox(origin, 1, 1, 1);
}


void drawShieldPU(){
	glColor3f(0, 1, 0);
	float origin[3] = {3, 0, 0};
	drawBox(origin, 1, 1, 1);
}


void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camPos[0], camPos[1], camPos[2], 0,0,0, 0,1,0);
	glColor3f(1,1,1);
	DrawSnowman(pos, rot);
	drawSPDPU();
	drawShieldPU();
	glutSwapBuffers();
}


int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("Final");

	glutDisplayFunc(display);
	glutSpecialFunc(special);

	glEnable(GL_DEPTH_TEST);
	init();

	glutMainLoop();
	return(0);
}
