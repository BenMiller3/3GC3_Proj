#include "header.h"
#include "character.h"
#include "powerup.h"
#include "scene.h"

#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

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

    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], 0, 0, 0, 0, 1, 0);
	glColor3f(0, 0, 0);
    
    //lighting
    glPushMatrix();
        glLoadIdentity();
        glEnable(GL_COLOR_MATERIAL);
        float pos1[] = {1,1,0};
        float amb1[4] = {0.4f,0.4f,0.4f,1};
        float diff1[4] = {1, 1, 1, 1};
        float spec1[4] = {1, 1, 1, 1};
        glEnable(GL_LIGHTING);
        //turn on light bulb 0
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diff1);
        glLightfv(GL_LIGHT0, GL_POSITION, pos1);
        glLightfv(GL_LIGHT0, GL_SPECULAR, spec1);
        glLightfv(GL_LIGHT0, GL_AMBIENT, amb1);
    glPopMatrix();

	glTranslatef(0.0f, 0.0f, zLocation);

	zLocation += gameSpeed;

	if(zLocation >= 10.0f){
		zLocation = -5.0f;
        glPushMatrix();
            mainCharacter.drawCharacter(pos,rot,-15.0f);
        glPopMatrix();
	}

	// Draw road
    glPushMatrix();
        theWorld.drawRoad(zLocation);
    glPopMatrix();

	// Draw Assets
    glPushMatrix();
        mainCharacter.drawCharacter(pos,rot,gameSpeed);
    glPopMatrix();
    glPushMatrix();
        items.drawShieldPU();
    glPopMatrix();
    glPushMatrix();
        items.drawSpeedPU();
    glPopMatrix();
    

	glutPostRedisplay();
	glFlush();
}


int main(int argc, char** argv){
	glutInit(&argc, argv); 	
	glutInitDisplayMode(GLUT_RGBA);	

	glutInitWindowPosition(50,50);
	glutInitWindowSize(640,480);

	glutCreateWindow("3GC3 Final Project");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	init();
	glutMainLoop();	

	return(0);
}
