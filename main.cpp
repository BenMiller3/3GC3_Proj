#include "header.h"
#include "character.h"
#include "box.h"
#include "scene.h"
#include "menu.h"

// Different compile issue fix
#ifdef __APPLE__
float charSpeed = 0.13f;
float gameSpeed = 0.15f;
float acceleration = 0.015f;
float speedIncrease = 0.075;
#else
float charSpeed = 0.002f;
float gameSpeed = 0.01f;
float acceleration = 0.0001f;
float speedIncrease = 0.005f;
#endif


//Game Speed
float boxSpeed = gameSpeed;


//Character Position
float charPos[] = {0, 0, 10};


//Character Movement
float charAngle = 0.0f;
float charLeftAcc = 0.0f;
float charRightAcc = 0.0f;


//Clock for score
float pauseClock = 0;
float currentClock = 0;
float gameOverClock = 0;


//Initial Powerup location
bool setPowerups = false;
int currentLevel = 1;

//World Position
float zLocation = -5.0f;


//Camera Position
float camPos[] = {0, 10, 15};
int camera = 1;

//Smooth Character Movement Animation
bool leftPressed = false;
bool rightPressed = false;

//Score Variable
int playerHealth = 1000;
int playerScore = 0;

//Game variables
bool gamePause = false;
bool resetGame = false;
bool gameEnded = false;
float gameOverScore = 0;

// Levels
int increaseSpeed = 0;

Scene theWorld = Scene();
Character mainCharacter = Character();

//Boxes
Box collect = Box();
Box avoid = Box();

// Main Menu
Menu mainMenu = Menu();
bool gameStart = false;

//Boxes to collect
int totalCollectBoxes = 10; //Total number of boxes per loop
int collectX[10]; //X coordinate of the box (MUST be the same as the total number of boxes)
int collectZ[10]; //Z coordinate of the box (MUST be the same as the total number of boxes)
float actualCollectZ[10]; //Updated Z coordinate of the box (MUST be the same as the total number of boxes)


//Boxes to avoid
int totalAvoidBoxes = 90; //Total number of boxes per loop
int avoidX[90]; //X coordinate of the box (MUST be the same as the total number of boxes)
int avoidZ[90]; //Z coordinate of the box (MUST be the same as the total number of boxes)
float actualAvoidZ[90]; //Updated Z coordinate of the box (MUST be the same as the total number of boxes)

// Output the game instructions to the commandline
void introduction(){
    cout << "\n\n\nBlock Boarding\n" << endl;
    cout << "by Victoria Graff, 001401451, graffve\n" << endl;
    cout << "and Emily Ashworth, 001402976, ashworel \n" << endl;
    cout << "and Kareem Abdel Mesih, 001407633, abdelk2 \n" << endl;
    cout << "and Ben Miller, 001416516, millebd  \n\n" << endl;
    cout << "INSTRUCTIONS:\n\n" << endl;
    cout << "Use the arrow keys or A and D to move the character left and right\n" << endl;
    cout << "Avoid black boxes and collect green boxes\n" << endl;
    cout << "Your score is based on the distance you are able to go\n" << endl;
    cout << "The green boxes give you health while the black ones take away health\n" << endl;
    cout << "Press the spacebar to pause and unpause the game\n" << endl;
    cout << "Keys 1,2, and 3 can be used to try different camera angles: " << endl;
    cout << "1 = Normal view, 2 = First Person View, 3 = Bird's eye view\n" << endl;
    cout << "Press the r key to reset the game\n\n" << endl;
 }

// Function to display text on screen
void displayText(float x, float y, float z, const char *string){
	int j = strlen(string);
	glColor3f(0, 0, 0);
	glRasterPos3f(x, y, z);
	for(int i=0;i<j;i++) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
}
// Pauses the game when the SPACE BAR key is hit
void pauseGame(){
	if(gamePause==true) gamePause = false;
	else gamePause = true;
}

// Collision detection
bool hitTest(int x, int z){
	int dx = charPos[0] - x;
	if(abs(dx) <= 0.7 && (z > 9 && z < 12.5)) return true;
	else return false;
}

void gameOver(){
	gamePause = true;

	// Resetting Values
	playerHealth = 1000;
	gameOverClock = clock() - pauseClock;
	setPowerups = false;
	charPos[0] = 0;
	charPos[1] = 0;
	charPos[2] = 10;

	// Reset initial game speeds
	#ifdef __APPLE__
	gameSpeed = 0.15f;
	speedIncrease = 0.075f;
	#else
	gameSpeed = 0.01f;
	speedIncrease = 0.005f;
	#endif

	camera = 1;
}


// Updates the score based on the player's current time spent in the game
int updateScore(int score, bool effect){
	if(effect and score > 0){
		if(score >= 1000) return score;
		else return score += 1;
	}
	else{
		if(score <= 0){
			gamePause = true;
			gameEnded = true;
		} 
		else return score -= 1;
	}
}

// Keyboard function
void keyboard(unsigned char key, int xIn, int yIn){
	switch(key){
		case 'q': exit(0);
		case 27: exit(0);
		case '1':
			camera = 1;
			break;
		case '2':
			camera = 2;
			break;
		case '3':
			camera = 3;
			break;
		case 'a':
			if(!gamePause) leftPressed = true;
			break;
		case 'd':
			if(!gamePause) rightPressed = true;
			break;
		case 'r':
			gameOver();
			gamePause = false;
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

// Special keys -- The arrow keys
void special(int key, int x, int y){
	if(!gamePause){
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

void mouse(int btn, int state, int mouseX, int mouseY)
{
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
				gameStart = true;
				gamePause = false;
		}
}


//Smooth Character Movement Animation
void specialUp(int key, int x, int y){
	if(key == GLUT_KEY_RIGHT) rightPressed = false;
	else if(key == GLUT_KEY_LEFT) leftPressed = false;
}

// Game initialization
void init(void){
	glClearColor(0, 0.68, 0.146, 0);			
	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();			
	gluPerspective(45, 1, 1, 100);
}

// Main display function
void display(void){

	if(camera == 1){
	
	camPos[0] = 0;
	camPos[1] =  10;
	camPos[2] = 15;
	}
	else if (camera == 2){
		camPos[0] = charPos[0];
		camPos[1] = 3;
		camPos[2] = 9;
	}
	else if(camera == 3){
		camPos[0] = 0;
		camPos[1] = 25;
		camPos[2] = 15;
	}

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camPos[0], camPos[1], camPos[2], 0, 0, 0, 0, 1, 0);

	if(gameEnded == true){
		gameOver();
		gameEnded = false;
	}

	if(!gamePause) gameOverScore = playerScore;

	if(!gamePause) boxSpeed = gameSpeed;
	else boxSpeed = 0.0f;

	glTranslatef(0.0f, 0.0f, zLocation);
	zLocation += boxSpeed;

	if(zLocation >= 240.0f || !setPowerups){
		zLocation = -5.0f;

		//Generate new locations for collect blocks
		for(int i=0;i<totalCollectBoxes;i++){
			collectX[i] = collect.genX(7);
			collectZ[i] = collect.genZ(200);
			actualCollectZ[i] = collectZ[i];
		}

		//Generate new locations for avoid blocks
		for(int i=0;i<totalAvoidBoxes;i++){
			avoidX[i] = avoid.genX(7);
			avoidZ[i] = avoid.genZ(200);
			actualAvoidZ[i] = avoidZ[i];
		}

		if(!setPowerups){
			setPowerups = true;
			mainCharacter.drawCharacter(charPos, 245.0f, false);
		}

        glPushMatrix();
            mainCharacter.drawCharacter(charPos, -245.0f, false);
        glPopMatrix();

        //Speed increases every level up
        gameSpeed += speedIncrease;
	}

	//Draw road
    glPushMatrix();
        theWorld.drawRoad(zLocation);
    glPopMatrix();

    //Score calculated by time
    playerScore = (clock() - pauseClock - gameOverClock) / 100000;

    if(gamePause) pauseClock = clock() - currentClock;
    else currentClock = clock() - pauseClock;

    //Parsing text
    char buffer[100];
	snprintf(buffer, 100, "Score: %d", playerScore);  

	char healthBuffer[100];
	snprintf(healthBuffer, 100, "Health: %d %%", playerHealth/10);

	char finalScoreBuffer[100];
	snprintf(finalScoreBuffer, 100, "FINAL SCORE = %f", gameOverScore);

	if(gameStart == true){


	// Draw text
	glPushMatrix();
	if(camera != 2){
		displayText(-6, 6, -zLocation, healthBuffer);
    	displayText(2.8, 6.0, -zLocation, buffer);
	}
	else{
		displayText(-1 + charPos[0], 3, -zLocation+5, healthBuffer);
		displayText(1 + charPos[0], 3, -zLocation+5, buffer);
	}
    	
    	if(gamePause & charPos[0] == 0 & charPos[1] == 0  & charPos[2] == 10 || gamePause & playerScore != gameOverScore) displayText(-2, 3, -zLocation, finalScoreBuffer);
    	if(gamePause & charPos[0] == 0 & charPos[1] == 0  & charPos[2] == 10 || gamePause & playerScore != gameOverScore) displayText(-4, 2, -zLocation, "PRESS SPACE BAR TO PLAY AGAIN");
    glPopMatrix();
}

    //Draw collect and avoid boxes at random locations
    glPushMatrix();
        for(int i=0;i<totalCollectBoxes;i++) collect.drawCollect(collectX[i], collectZ[i]);
    	for(int i=0;i<totalAvoidBoxes;i++) avoid.drawAvoid(avoidX[i], avoidZ[i]);
    glPopMatrix();

	//Draw Assets
    glPushMatrix();
        if(playerHealth < 200){
            //alpha blend
            mainCharacter.drawCharacter(charPos, boxSpeed, true);
        }
        else{
            mainCharacter.drawCharacter(charPos, boxSpeed, false);
        }
    glPopMatrix();

    //Move the character
    if(!leftPressed) charLeftAcc = 0.0f;
    if(!rightPressed) charRightAcc = 0.0f;

    if(leftPressed && charPos[0] > -4.8){
    	charLeftAcc -= acceleration;
    	charPos[0] -= (charSpeed - charLeftAcc);
    }
    
    if(rightPressed && charPos[0] < 4.8){
    	charRightAcc += acceleration;
    	charPos[0] += (charSpeed + charRightAcc);
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
    
    //Collision detection
    if(!gamePause){
	    for(int i=0;i<totalCollectBoxes;i++){
	    	actualCollectZ[i] += boxSpeed;
	    	if(hitTest(collectX[i], actualCollectZ[i])){
	    		collectZ[i] = 100;
	    		playerHealth = updateScore(playerHealth, true);
	    	}
	    }

	    for(int i=0;i<totalAvoidBoxes;i++){
	    	actualAvoidZ[i] += boxSpeed;
	    	if(hitTest(avoidX[i], actualAvoidZ[i])){
	    		avoidZ[i] = 100;
	    		playerHealth = updateScore(playerHealth, false);
	    	}
	    }
	

}

	if(gameStart == false){

		gamePause = true;
		camPos[0] = 0;
		camPos[1] = 0;
		camPos[2] = 5;
		glColor3f(1,1,1);
		glutSolidCube(17);

		//Easy (Green)
		glPushMatrix();
			glTranslatef(-6.5,2,0);
			glColor3f(0,1,0);
			glutSolidCube(2.5);
		glPopMatrix();

		// Medium (Yellow)
		glPushMatrix();
			glTranslatef(0,2,0);
			glColor3f(1,1,0);
			glutSolidCube(2.5);
		glPopMatrix();

		// Hard (Red)
		glPushMatrix();
			glTranslatef(6.5,2,0);
			glColor3f(1,0,0);
			glutSolidCube(2.5);
		glPopMatrix();

		glColor3f(0,0,0);
		displayText(-3.5, 3.5, -zLocation+5, "** BLOCK BOARDING **");
		displayText(-3, 2, -zLocation+5, "Click green for easy");
		displayText(-3.1, 0, -zLocation+5, "Click yellow for medium");
		displayText(-3.2, -2, -zLocation+5, "Click red for hard");
	}

    glutSwapBuffers();
	glutPostRedisplay();
    glFlush();
}

// Main game loop
int main(int argc, char** argv){
	srand(time(NULL));
	glutInit(&argc, argv); 	
	glutInitDisplayMode(GLUT_RGBA);	

	glutInitWindowPosition(50, 50);
	glutInitWindowSize(640, 480);

	glutCreateWindow("Block Boarding");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(special);
	glutSpecialUpFunc(specialUp);

	glutMouseFunc(mouse);

	introduction();

	init();
	glutMainLoop();	
	return(0);
}
