#include "header.h"
#include "character.h"
#include "powerup.h"

// Camera Values
float pos[] = {0,0,5};
float rot[] = {0, 0, 0};
float camPos[] = {0, 10, 15};

//Character Movement
float angle = 0.0f;
float spd = 0.3;
bool spdPowerUp = true;
bool shieldPowerUp = true;

// Character
Character bob = Character();

//Powerups
Powerup items = Powerup();

// END OF THE GLOBAL VARIABLES

void keyboard(unsigned char key, int xIn, int yIn){

	switch(key){
		case 'q':
			exit(0);
		case 27:
			exit(0);
	}

}

void init(void){

	glClearColor(0.8, 0.8, 0.8, 0);	// Clear the screen
	glColor3f(1, 1, 1);			// Sets the curent drawing colour

	glMatrixMode(GL_PROJECTION);	// Specify the current matrix
	glLoadIdentity();			// Replace current Matrix w/ identity matrix
	gluPerspective(45, 1, 1, 100);	// Sets a perspective projection matrix
}

void display(void){

	glClear(GL_COLOR_BUFFER_BIT); // Clear buffers to preset vals

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], 0, 0, 0, 0, 1, 0);
	glColor3f(0, 0, 0);

	glTranslatef(0.0f, 0.0f, -5.0f); 

	//glutWireCube(2.0f);

	bob.drawCharacter(pos,rot);
	items.drawShieldPU();
	items.drawSpeedPU();
	// Flush out to a single buffer
	glFlush();	// Forces execution of GL commands in finite time
}

/*
Main function -- the program entry point!
*/
int main(int argc, char** argv){

	glutInit(&argc, argv); 	// Initializes the GLUT library
	glutInitDisplayMode(GLUT_RGBA);	// Sets the initial display mode

	glutInitWindowPosition(50,50);
	glutInitWindowSize(640,480);

	glutCreateWindow("Intro to 3D Objects");	// Creates window and title!

	glutDisplayFunc(display);	// Registers f'n display as callback f'n
	glutKeyboardFunc(keyboard);

	init();

	//OtherCall b -- Would take another H file and call it b
	//b.hello(); call another function from another prog. but why
	// I guess to make building blocks that would help to build
	// A HOUSE! :)

	glutMainLoop();	// Enters the GLUT event processing loop

	return(0);
}
