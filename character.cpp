#include "header.h"
#include "character.h"


//Colours
float blue[] = {0.132, 0.112, 0.255};
float red[] = {0.205, 0.091, 0.069};
float black[] = {0, 0, 0};
float skin[] = {0.96, 0.80, 0.69};
float wood[] = {0.52, 0.37, 0.26};


//Empty constructor
Character::Character(){ }


void Character::drawCharacter(float* pos, float gameSpeed, bool blend){
    glPushMatrix();
    pos[2] = pos[2] - gameSpeed;
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    //Character
    glTranslatef(pos[0], pos[1], pos[2]); //Starting postion
    glRotatef(90, 0, 1, 0); //Turned around
    glScalef(1, 0.75, 1);
    
    //Skateboard
    glPushMatrix();
    
    //Wheel 1
    glPushMatrix();
    if(blend){
        glColor4f(0,0,0,0.2);
    }
    else{
        glColor4f(0,0,0,1);    //black
    }
    glTranslatef(-0.5, -3.1, 0.1);
    glScalef(0.1, 0.1, 0.1);
    glutSolidSphere(1, 10, 10);
    glPopMatrix();
    
    //Wheel 2
    glPushMatrix();
    if(blend){
        glColor4f(0,0,0,0.2);
    }
    else{
        glColor4f(0,0,0,1);    //black
    }
    glTranslatef(0.5, -3.1, 0.1);
    glScalef(0.1, 0.1, 0.1);
    glutSolidSphere(1, 10, 10);
    glPopMatrix();
    
    //Wheel 3
    glPushMatrix();
    if(blend){
        glColor4f(0,0,0,0.2);
    }
    else{
        glColor4f(0,0,0,1);    //black
    }
    glTranslatef(-0.5, -3.1, -0.33);
    glScalef(0.1, 0.1, 0.1);
    glutSolidSphere(1, 10, 10);
    glPopMatrix();
    
    //Wheel 4
    glPushMatrix();
    if(blend){
        glColor4f(0,0,0,0.2);
    }
    else{
        glColor4f(0,0,0,1);    //black
    }
    glTranslatef(0.5, -3.1, -0.33);
    glScalef(0.1, 0.1, 0.1);
    glutSolidSphere(1, 10, 10);
    glPopMatrix();
    
    //Board
    glPushMatrix();
    if(blend){
        glColor4f(0.52, 0.37, 0.26,0.2);
    }
    else{
        glColor4f(0.52, 0.37, 0.26,1);    //wood
    }
    glTranslatef(0, -3, -0.1);
    glScalef(1.4, 0.2, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
    
    //Right leg
    glPushMatrix();
    if(blend){
        glColor4f(0.132, 0.112, 0.255,0.2);
    }
    else{
        glColor4f(0.132, 0.112, 0.255,1);    //blue
    }
    glTranslatef(0.3, -1.8 , 0);
    glScalef(0.2, 2.5, 0.2);
    glutSolidCube(1);
    glPopMatrix();
    
    //Right shoe
    glPushMatrix();
    if(blend){
        glColor4f(0,0,0,0.2);
    }
    else{
        glColor4f(0,0,0,1);    //black
    }
    glTranslatef(0.3, -3 , -0.1);
    glScalef(0.3, 0.2, 0.4);
    glutSolidCube(1);
    glPopMatrix();
    
    //Left leg
    glPushMatrix();
    if(blend){
        glColor4f(0.132, 0.112, 0.255,0.2);
    }
    else{
        glColor4f(0.132, 0.112, 0.255,1);    //blue
    }
    glTranslatef(-0.3, -1.8 , 0);
    glScalef(0.2, 2.5, 0.2);
    glutSolidCube(1);
    glPopMatrix();
    
    //Left shoe
    glPushMatrix();
    if(blend){
        glColor4f(0,0,0,0.2);
    }
    else{
        glColor4f(0,0,0,1);    //black
    }
    glTranslatef(-0.3, -3 , -0.1);
    glScalef(0.3, 0.2, 0.4);
    glutSolidCube(1);
    glPopMatrix();
    
    //Right arm
    glPushMatrix();
    if(blend){
        glColor4f(0.205, 0.091, 0.069,0.2);
    }
    else{
        glColor4f(0.205, 0.091, 0.069,1);    //red
    }
    glTranslatef(0.8, 0 ,0);
    glRotatef(45, 0, 0 , 1);
    glScalef(0.2, 1.5, 0.2);
    glutSolidCube(1);
    glPopMatrix();
    
    //Body
    glPushMatrix();
    if(blend){
        glColor4f(0.205, 0.091, 0.069,0.2);
    }
    else{
        glColor4f(0.205, 0.091, 0.069,1);    //red
    }
    glScalef(0.6, 1.5, 0.3);
    glutSolidCube(1);
    glPopMatrix();
    
    //Left arm
    glPushMatrix();
    if(blend){
        glColor4f(0.205, 0.091, 0.069,0.2);
    }
    else{
        glColor4f(0.205, 0.091, 0.069,1);    //red
    }
    glTranslatef(-0.8, 0 , 0.0);
    glRotatef(-45, 0, 0 , 1);
    glScalef(0.2, 1.5, 0.2);
    glutSolidCube(1);
    glPopMatrix();
    
    //Head
    glPushMatrix();
    glTranslatef(0, 1.5, 0);
    if(blend){
        glColor4f(0.96, 0.80, 0.69,0.2);
    }
    else{
        glColor4f(0.96, 0.80, 0.69,1);    //skin
    }
    glScalef(1, 1, 0.5);
    glutSolidSphere(0.5, 10, 10);
    glPopMatrix();
    
    //Hat top
    glPushMatrix();
    if(blend){
        glColor4f(0.205, 0.091, 0.069,0.2);
    }
    else{
        glColor4f(0.205, 0.091, 0.069,1);    //red
    }
    glTranslatef(0, 1.9, -0.3);
    glScalef(0.6, 0.2, 0.4);
    glutSolidCube(1);
    glPopMatrix();
    
    //Hat base
    glPushMatrix();
    if(blend){
        glColor4f(0.205, 0.091, 0.069,0.2);
    }
    else{
        glColor4f(0.205, 0.091, 0.069,1);    //red
    }
    glTranslatef(0, 2 , 0);
    glScalef(0.6, 0.4, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    
    glPopMatrix();
}