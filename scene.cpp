#include "header.h"
#include "scene.h"


Scene::Scene(){ }

void Scene::drawRoad(float zPosition){
	float size = 9.6f;

	glColor3f(0.87f, 0.59f, 0.12f);

	glEnable(GL_TEXTURE_2D);
	//LoadTextures();

	glBegin(GL_QUADS);
		glTexCoord2f(0.0,0.0);
		glVertex3f(-size, -size, (10.0f - zPosition));	// Bottom left corner
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-size, size, (-50.0f - zPosition));	// Top left corner
		glTexCoord2f(1.0, 1.0);
		glVertex3f(size, size, (-50.0f - zPosition));	// Top right corner
		glTexCoord2f(1.0, 0.0);
		glVertex3f(size, -size, (10.0f - zPosition));	// Bottom right corner
	glEnd();
}