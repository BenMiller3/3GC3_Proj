#include "header.h"
#include "character.h"


/* Colours */
float blue[] = {0.132, 0.112, 0.255};
float red[] = {0.205, 0.091, 0.069};
float black[] = {0, 0, 0};
float skin[] = {0.96, 0.80, 0.69};
float wood[] = {0.52, 0.37, 0.26};


Character::Character(){ }


void Character::drawCharacter(float* pos, float gameSpeed){
    glPushMatrix();
    pos[2] = pos[2] - gameSpeed;
    
    //Character
    glTranslatef(pos[0], pos[1], pos[2]); //Starting postion
    glRotatef(90, 0, 1, 0); //Turned around
    glScalef(1, 0.75, 1);
    
    //Skateboard
    glPushMatrix();
    
    //Wheel 1
    glPushMatrix();
    glColor3fv(black);
    glTranslatef(-0.5, -3.1, 0.1);
    glScalef(0.1, 0.1, 0.1);
    glutSolidSphere(1, 10, 10);
    glPopMatrix();
    
    //Wheel 2
    glPushMatrix();
    glColor3fv(black);
    glTranslatef(0.5, -3.1, 0.1);
    glScalef(0.1, 0.1, 0.1);
    glutSolidSphere(1, 10, 10);
    glPopMatrix();
    
    //Wheel 3
    glPushMatrix();
    glColor3fv(black);
    glTranslatef(-0.5, -3.1, -0.33);
    glScalef(0.1, 0.1, 0.1);
    glutSolidSphere(1, 10, 10);
    glPopMatrix();
    
    //Wheel 4
    glPushMatrix();
    glColor3fv(black);
    glTranslatef(0.5, -3.1, -0.33);
    glScalef(0.1, 0.1, 0.1);
    glutSolidSphere(1, 10, 10);
    glPopMatrix();
    
    //Board
    glPushMatrix();
    glColor3fv(wood);
    glTranslatef(0, -3, -0.1);
    glScalef(1.4, 0.2, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
    
    //Right leg
    glPushMatrix();
    glColor3fv(blue);
    glTranslatef(0.3, -1.8 , 0);
    glScalef(0.2, 2.5, 0.2);
    glutSolidCube(1);
    glPopMatrix();
    
    //Right shoe
    glPushMatrix();
    glColor3fv(black);
    glTranslatef(0.3, -3 , -0.1);
    glScalef(0.3, 0.2, 0.4);
    glutSolidCube(1);
    glPopMatrix();
    
    //Left leg
    glPushMatrix();
    glColor3fv(blue);
    glTranslatef(-0.3, -1.8 , 0);
    glScalef(0.2, 2.5, 0.2);
    glutSolidCube(1);
    glPopMatrix();
    
    //Left shoe
    glPushMatrix();
    glColor3fv(black);
    glTranslatef(-0.3, -3 , -0.1);
    glScalef(0.3, 0.2, 0.4);
    glutSolidCube(1);
    glPopMatrix();
    
    //Right arm
    glPushMatrix();
    glColor3fv(red);
    glTranslatef(0.8, 0 ,0);
    glRotatef(45, 0, 0 , 1);
    glScalef(0.2, 1.5, 0.2);
    glutSolidCube(1);
    glPopMatrix();
    
    //Body
    glPushMatrix();
    glColor3fv(red);
    glScalef(0.6, 1.5, 0.3);
    glutSolidCube(1);
    glPopMatrix();
    
    //Left arm
    glPushMatrix();
    glColor3fv(red);
    glTranslatef(-0.8, 0 , 0.0);
    glRotatef(-45, 0, 0 , 1);
    glScalef(0.2, 1.5, 0.2);
    glutSolidCube(1);
    glPopMatrix();
    
    //Head
    glPushMatrix();
    glTranslatef(0, 1.5, 0);
    glColor3fv(skin);
    glScalef(1, 1, 0.5);
    glutSolidSphere(0.5, 10, 10);
    glPopMatrix();
    
    //Hat top
    glPushMatrix();
    glColor3fv(red);
    glTranslatef(0, 1.9, -0.3);
    glScalef(0.6, 0.2, 0.4);
    glutSolidCube(1);
    glPopMatrix();
    
    //Hat base
    glPushMatrix();
    glColor3fv(red);
    glTranslatef(0, 2 , 0);
    glScalef(0.6, 0.4, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    
    glPopMatrix();
}