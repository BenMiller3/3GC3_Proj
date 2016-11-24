#include "header.h"
#include "character.h"
#include "powerup.h"
#include "scene.h"

// Camera Values
float pos[] = {0,0,5};
float rot[] = {0, 0, 0};
float camPos[] = {0, 10, 15};

//Character Movement
float angle = 0.0f;
float spd = 0.3;

//Location of the world
float zLocation = -5.0f;
float gameSpeed = 0.002f;

// Not needed for now
//bool spdPowerUp = true;
//bool shieldPowerUp = true;

// World
Scene theWorld = Scene();

// Character
Character mainCharacter = Character();

//Powerups
Powerup items = Powerup();

void keyboard(unsigned char key, int xIn, int yIn){

	switch(key){
		case 'q':
			exit(0);
		case 27:
			exit(0);

		// Movement controls
		case 'a':
			if(pos[0] > -4.4) pos[0] -= 0.3;
			rot[1] = -90;
			break;

		case 'd':
			if(pos[0] < 4.4) pos[0] += 0.3;
			rot[1] = 90;
			break;

		//Look at camera or away from camera -- no movement
		case 'w':
			rot[1] = -180;
			break;
		case 's':
			rot[1] = 0;
			break;
	}

	// Update the display
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

	init();
	glutMainLoop();	

	return(0);
}
