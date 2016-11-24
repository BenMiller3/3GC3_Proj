#include "scene.h"
#include "header.h"

Scene::Scene(){
	
}

void Scene::drawScene(float zPosition){
	float size = 9.6f;

	glColor3f(0.87f, 0.59f, 0.12f);

	glBegin(GL_QUADS);
		glVertex3f(-size, -size, (10.0f - zPosition));	// Bottom left corner
		glVertex3f(-size, size, (-50.0f - zPosition));	// Top left corner
		glVertex3f(size, size, (-50.0f - zPosition));	// Top right corner
		glVertex3f(size, -size, (10.0f - zPosition));	// Bottom right corner
	glEnd();
}
