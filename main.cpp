#include "header.h"
#include "character.h"
#include "box.h"
#include "scene.h"


//Character Position
float charPos[] = {0, 0, 10};
float charRot[] = {0, 0, 0};


//Character Movement
float charAngle = 0.0f;
float charSpeed = 0.003f;


//Speed Powerup
bool speedActive = true; //True when it is active
int totalSpeedBoxes = 20; //Total number of boxes per loop
int speedX [20]; //X coordinate of the box (MUST be the same as the total number of boxes)
int speedZ [20]; //Z coordinate of the box (MUST be the same as the total number of boxes)


//Shield Powerup
bool shieldActive = true; //True when it is active
int totalShieldBoxes = 20; //Total number of boxes per loop
int shieldX [20]; //X coordinate of the box (MUST be the same as the total number of boxes)
int shieldZ [20]; //Z coordinate of the box (MUST be the same as the total number of boxes)


//Initial Powerup location
bool setPowerups = false;


//World Position
float zLocation = -5.0f;


//Camera Position
float camPos[] = {0, 10, 15};


//Speeds
float slow = 0.3f;
float fast = 0.5f;
float gameSpeed = 0.05f;


//Smooth Character Movement Animation
bool leftPressed = false;
bool rightPressed = false;


Scene theWorld = Scene();
Character mainCharacter = Character();
Box speed = Box(0);
Box shield = Box(1);


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


//Smooth Character Movement Animation
void keyUp(unsigned char key, int x, int y){
	if(key == 'a') leftPressed = false;
	else if(key == 'd') rightPressed = false;
}


void special(int key, int x, int y){
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


//Smooth Character Movement Animation
void specialUp(int key, int x, int y){
	if(key == GLUT_KEY_RIGHT) rightPressed = false;
	else if(key == GLUT_KEY_LEFT) leftPressed = false;
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

	glTranslatef(0.0f, 0.0f, zLocation);
	zLocation += gameSpeed;

	if(zLocation >= 205.0f || setPowerups == false){
		zLocation = -5.0f;

		//Generate new locations for speed blocks
		for(int i=0;i<totalSpeedBoxes;i++){
			speedX[i] = speed.genLocation(9);
			speedZ[i] = speed.genLocation(200);
		}

		//Generate new locations for shield blocks
		for(int i=0;i<totalShieldBoxes;i++){
			shieldX[i] = shield.genLocation(9);
			shieldZ[i] = shield.genLocation(200);
		}

		if(setPowerups == false){
			setPowerups = true;
			mainCharacter.drawCharacter(charPos, charRot, 210.0f);
		}

        glPushMatrix();
            mainCharacter.drawCharacter(charPos, charRot, -210.0f);
        glPopMatrix();
	}

	//Draw road
    glPushMatrix();
        theWorld.drawRoad(zLocation);
    glPopMatrix();

	//Draw Assets
    glPushMatrix();
        mainCharacter.drawCharacter(charPos,charRot,gameSpeed);
    glPopMatrix();

    //Draw speed and shield boxes at random locations
    glPushMatrix();
        for(int i=0;i<totalSpeedBoxes;i++) speed.drawSpeed(speedX[i], speedZ[i]);

    	for(int i=0;i<totalShieldBoxes;i++) shield.drawShield(shieldX[i], shieldZ[i]);
    glPopMatrix();

    //Move the character
    if(leftPressed == true && charPos[0] > -4.4){
    	charPos[0] -= charSpeed;
		charRot[1] = -90;
    }
    
    if(rightPressed == true && charPos[0] < 4.4){
    	charPos[0] += charSpeed;
    	charRot[1] = 90;
    }
    
    //lighting
    glPushMatrix();
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        float pos1[] = {10, 1, 1, 0};
        float amb1[4] = {0.4f, 0.4f, 0.4f, 1};
        float diff1[4] = {1, 1, 1, 1};
        float spec1[4] = {1, 1, 1, 1};
        glEnable(GL_LIGHTING);

        //Turn on light bulb 0
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
