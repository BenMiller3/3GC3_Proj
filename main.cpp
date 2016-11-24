#include "header.h"
#include "character.h"
#include "powerup.h"
#include "scene.h"

// Camera Values
float pos[] = {0,0,10};
float rot[] = {0, 0, 0};
float camPos[] = {0, 10, 15};

//Character Movement
float angle = 0.0f;
float spd = 0.3;

//Location of the world
float zLocation = -5.0f;
float gameSpeed = 0.05f;

// World
Scene theWorld = Scene();

// Character
Character mainCharacter = Character();

//Powerups
Powerup items = Powerup();
bool spdPowerup = true;
bool shieldPowerup = true;

void keyboard(unsigned char key, int xIn, int yIn){
	switch(key){
		case 'q':
			exit(0);
		case 27:
			exit(0);
	}
	glutPostRedisplay();	
}


void special(int key, int x, int y){
	int mod = glutGetModifiers();
	if(spdPowerup && mod == GLUT_ACTIVE_SHIFT) spd = 0.5;
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
	glClearColor(0, 0.68, 0.146, 0);	
	glColor3f(1, 1, 1);			
	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();			
	gluPerspective(45, 1, 1, 100);	
}

void display(void){

	glClear(GL_COLOR_BUFFER_BIT); 

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], 0, 0, 0, 0, 1, 0);
	glColor3f(0, 0, 0);

	glTranslatef(0.0f, 0.0f, zLocation); 

	zLocation += gameSpeed;

	if(zLocation >= 10.0f){
		zLocation = -5.0f;
		mainCharacter.drawCharacter(pos,rot,-15.0f);
	}

	// Draw road
	theWorld.drawRoad(zLocation);

	// Draw Assets
	mainCharacter.drawCharacter(pos,rot,gameSpeed);
	items.drawShieldPU();
	items.drawSpeedPU();

	glutPostRedisplay();
	glFlush();	
}


int main(int argc, char** argv){
	glutInit(&argc, argv); 	
	glutInitDisplayMode(GLUT_RGBA);	

	glutInitWindowPosition(50,50);
	glutInitWindowSize(640,480);

	glutCreateWindow("3GC3 Final Project");	

	glutDisplayFunc(display);	
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	init();
	glutMainLoop();	

	return(0);
}
