#include "header.h"
#include "character.h"
#include "box.h"
#include "scene.h"

//Character Position
float charPos[] = {0, 0, 10};
float charRot[] = {0, 0, 0};


//Character Movement
float charAngle = 0.0f;
float charSpeed = 0.15f; //@Ben: 0.008f

//Speed
float boxSpeed = 0.06f;//0.2f; //@Ben: 0.06f

// CLOCK -- for scoring
float pauseClock = 0;
float currentClock = 0;

//Boxes to collect
int totalCollectBoxes = 20; //Total number of boxes per loop
int collectX [20]; //X coordinate of the box (MUST be the same as the total number of boxes)
int collectZ [20]; //Z coordinate of the box (MUST be the same as the total number of boxes)
float actualCollectZ [20]; //Updated Z coordinate of the box (MUST be the same as the total number of boxes)


//Boxes to avoid
int totalAvoidBoxes = 40; //Total number of boxes per loop
int avoidX [40]; //X coordinate of the box (MUST be the same as the total number of boxes)
int avoidZ [40]; //Z coordinate of the box (MUST be the same as the total number of boxes)
float actualAvoidZ [40]; //Updated Z coordinate of the box (MUST be the same as the total number of boxes)


//Initial Powerup location
bool setPowerups = false;


//World Position
float zLocation = -5.0f;


//Camera Position
float camPos[] = {0, 10, 15};

//Smooth Character Movement Animation
bool leftPressed = false;
bool rightPressed = false;

//Score Variable
int score = 300;
int playerScore = 0;

//Game variables
bool gamePause = false;
bool resetGame = false;


Scene theWorld = Scene();
Character mainCharacter = Character();
Box collect = Box();
Box avoid = Box();

// 2nd wave of boxes
Box collect2 = Box();
Box avoid2 = Box();

int totalCollectBoxes2 = 10; //Total number of boxes per loop
int collectX2 [10]; //X coordinate of the box (MUST be the same as the total number of boxes)
int collectZ2 [10]; //Z coordinate of the box (MUST be the same as the total number of boxes)
float actualCollectZ2 [10]; //Updated Z coordinate of the box (MUST be the same as the total number of boxes)

int totalAvoidBoxes2 = 20; //Total number of boxes per loop
int avoidX2 [20]; //X coordinate of the box (MUST be the same as the total number of boxes)
int avoidZ2 [20]; //Z coordinate of the box (MUST be the same as the total number of boxes)
float actualAvoidZ2 [20]; //Updated Z coordinate of the box (MUST be the same as the total number of boxes)

// End of second wave boxes


void displayText(float x, float y, float z, const char *string){
	int j = strlen(string);
 
	glColor3f(0, 0, 0);
	glRasterPos3f(x, y, z);
	for(int i=0;i<j;i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void gameOver(){
	exit(0);
}

void pauseGame(){
	if(gamePause==true){
		gamePause = false;
	}
	else{
		gamePause = true;	
	}
}


bool hitTest(int x, int z){
	int dx = charPos[0] - x;
	if(abs(dx) <= 0.7 && (z > 9 && z < 13)) return true;
	else return false;
}


int updateScore(int score, bool effect){
	if(effect){
		if(score >= 300) return score;
		else return score += 1;
	}
	else{
		if(score <= 0) gameOver();
		else return score -= 1;
	}
}


void keyboard(unsigned char key, int xIn, int yIn){
	switch(key){
		case 'q':
			exit(0);
		case 27:
			exit(0);
		case 'a':
			if(gamePause == false) leftPressed = true;
			break;
		case 'd':
			if(gamePause == false) rightPressed = true;
			break;
		case ' ':
			pauseGame();
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
	
	if(gamePause == false){
	switch(key){
		case GLUT_KEY_LEFT:
			leftPressed = true;
			break;

		case GLUT_KEY_RIGHT:
			rightPressed = true;
			break;
	}
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

	if(gamePause==false){
		boxSpeed = 0.2f;
	}
	else{
		boxSpeed = 0.0f;
	}

	glTranslatef(0.0f, 0.0f, zLocation);
	zLocation += boxSpeed;
	

	if(zLocation >= 205.0f || setPowerups == false){
		zLocation = -5.0f;

		//Generate new locations for collect blocks
		for(int i=0;i<totalCollectBoxes;i++){
			collectX[i] = collect.genX(9);
			collectZ[i] = collect.genZ(200);
			actualCollectZ[i] = collectZ[i];
		}

		//Generate new locations for avoid blocks
		for(int i=0;i<totalAvoidBoxes;i++){
			avoidX[i] = avoid.genX(9);
			avoidZ[i] = avoid.genZ(200);
			actualAvoidZ[i] = avoidZ[i];
		}

		if(setPowerups == false){
			setPowerups = true;
			mainCharacter.drawCharacter(charPos, charRot, 210.0f);
		}

        glPushMatrix();
            mainCharacter.drawCharacter(charPos, charRot, -210.2f);
        glPopMatrix();
	}


	// Smooth the transition between the two waves
	if(zLocation >= 150.0f){

		//Generate new locations for collect blocks
		for(int i=0;i<totalCollectBoxes2;i++){
			collectX2[i] = collect2.genX(8);
			collectZ2[i] = collect2.genZ(75);
			actualCollectZ2[i] = collectZ2[i];
		}

		//Generate new locations for avoid blocks
		for(int i=0;i<totalAvoidBoxes2;i++){
			avoidX2[i] = avoid2.genX(8);
			avoidZ2[i] = avoid2.genZ(75);
			actualAvoidZ2[i] = avoidZ2[i];
		}

	}


	//Draw road
    glPushMatrix();
        theWorld.drawRoad(zLocation);
    glPopMatrix();

    // Score calculated by time
    playerScore = (clock() - pauseClock)/100000;

    
    if(gamePause==true){

    	pauseClock = clock() - currentClock;
    }
    else{
    	currentClock = clock() - pauseClock;
    }


    //Parsing text
    char buffer [100];
	snprintf(buffer,100,"Score: %d",playerScore);  

	char healthBuffer [100];
	snprintf(healthBuffer,100,"Health: %d %%",score/3);

	// Draw text
	glPushMatrix();
    	displayText(-6,6,-zLocation, healthBuffer);
    	displayText(2.8, 6.0, -zLocation, buffer);
    glPopMatrix();

    //Draw collect and avoid boxes at random locations
    glPushMatrix();
        for(int i=0;i<totalCollectBoxes;i++) collect.drawCollect(collectX[i], collectZ[i]);
    	for(int i=0;i<totalAvoidBoxes;i++) avoid.drawAvoid(avoidX[i], avoidZ[i]);
    glPopMatrix();

	//Draw Assets
    glPushMatrix();
        mainCharacter.drawCharacter(charPos, charRot, boxSpeed);
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
    
    // Collision detection
    if(gamePause == false){
    for(int i=0;i<totalCollectBoxes;i++){
    	actualCollectZ[i] += boxSpeed;
    	if(hitTest(collectX[i], actualCollectZ[i])){
    		collectZ[i] = 20;
    		score = updateScore(score, true);
    	}
    }

    for(int i=0;i<totalAvoidBoxes;i++){
    	actualAvoidZ[i] += boxSpeed;
    	if(hitTest(avoidX[i], actualAvoidZ[i])){
    		avoidZ[i] = 20;
    		score = updateScore(score, false);
    	}
    }
}

    glutSwapBuffers();
	glutPostRedisplay();
    glFlush();
}


int main(int argc, char** argv){
	glutInit(&argc, argv); 	
	glutInitDisplayMode(GLUT_RGBA);	

	glutInitWindowPosition(50, 50);
	glutInitWindowSize(640, 480);

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