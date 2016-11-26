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
float spd = 0.003f;

// @Karim rather than shift for speed when player
// hits the box we will make them fast and 
// not have them have to use the shift bar at all
float slow = 0.3f;
float fast = 0.5f;

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

// Total Speed and Shield boxes per loop
int totalSpeed = 20;
int totalShield = 20;

// X and Z locations of all speed blocks ** MUST be the same as totalSpeed & totalShield 
int speedX [20];
int speedZ [20];

int shieldX [20];
int shieldZ [20];

// Sets initial powerup locations
bool setPowerups = false;

//Smooth Keyboard movements
bool leftPressed = false;
bool rightPressed = false;

void keyboard(unsigned char key, int xIn, int yIn){
	switch(key){
		case 'q':
			exit(0);
		case 27:
			exit(0);
		case 'a':
			leftPressed = true;
			break;
		case 'd':
			rightPressed = true;
			break;
	}

	glutPostRedisplay();	
}

// Needed for smooth keyboard callbacks
void keyUp(unsigned char key, int x, int y){
	if(key=='a'){
		leftPressed = false;
	}
	else if(key=='d'){
		rightPressed = false;
	}
}

void special(int key, int x, int y){
	int mod = glutGetModifiers();

	switch(key){
		case GLUT_KEY_LEFT:
			leftPressed = true;
			break;

		case GLUT_KEY_RIGHT:
			rightPressed = true;
			break;
	}
	glutPostRedisplay();
}

void specialUp(int key, int x, int y){
	if(key == GLUT_KEY_RIGHT){
		rightPressed = false;
	}
	else if(key == GLUT_KEY_LEFT){
		leftPressed = false;
	}
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

	glTranslatef(0.0f, 0.0f, zLocation);

	zLocation += gameSpeed;

	if(zLocation >= 205.0f || setPowerups == false){
		zLocation = -5.0f;

		// Generate new locations for speed blocks
		for(int i = 0; i<totalSpeed; i++){
			speedX[i] = items.genLocation(9);
			speedZ[i] = items.genLocation(200);
		}

		// Generate new locations for shield blocks
		for(int i = 0; i<totalShield; i++){
			shieldX[i] = items.genLocation(9);
			shieldZ[i] = items.genLocation(200);
		}
		if(setPowerups==false){
			setPowerups = true;
			mainCharacter.drawCharacter(pos,rot,+210.0f);
		}

        glPushMatrix();
            mainCharacter.drawCharacter(pos,rot,-210.0f);
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
    	// Draw speed and shield blocks from random locations
        for(int i = 0; i<totalShield; i++){
        	items.drawSpeedPU(speedX[i],speedZ[i]);
        }

    	for(int i = 0; i<totalSpeed; i++){
    		items.drawShieldPU(shieldX[i],shieldZ[i]);
    	}
    glPopMatrix();

    // Move the character
    if(leftPressed == true && pos[0] > -4.4){
    	pos[0] -= spd;
		rot[1] = -90;
    }
    
    if(rightPressed == true && pos[0] < 4.4){
    	pos[0] += spd;
    	rot[1] = 90;
    }
    
    //lighting
    glPushMatrix();
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
        float pos1[] = {10,1,1,0};
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
    
    glutSwapBuffers();
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
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(special);
	glutSpecialUpFunc(specialUp);

	init();
	glutMainLoop();	

	return(0);
}
