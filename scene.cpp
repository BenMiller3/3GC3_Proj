#include "header.h"
#include "scene.h"

Scene::Scene(){
	
}

unsigned int texture[1];

// Structure for holding bitmap info
struct Image{
long SizeX;
long SizeY;
char *data;
};
typedef struct Image Image;

void LoadBMP(char *filename, Image *image){
FILE *file;
short int bpp;
short int planes;
long i;
long size;
char temp;

file = fopen(filename, "rb");
fseek(file, 18, SEEK_CUR);
i = fread(&image->SizeX, 4, 1, file);
i = fread(&image->SizeY, 4, 1, file);
size = image->SizeX * image->SizeY * 3;
i = fread(&bpp, 2, 1, file);
i = fread(&planes, 2, 1, file);
fseek(file, 24, SEEK_CUR);
image->data = (char *)malloc(size);
i = fread(image->data, size, 1, file);
for(i = 0; i < size; i+=3){
temp = image->data[i];
image->data[i] = image->data[i+2];
image->data[i+2] = temp;
}
fclose(file);
free(image);
}

void LoadTextures(void){
Image *image1;

image1 = (Image *)malloc(sizeof(Image));
LoadBMP("Textures/path.bmp", image1);
glGenTextures(1, &texture[0]);
glBindTexture(GL_TEXTURE_2D, texture[0]);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image1->SizeX, image1->SizeY, GL_RGB, GL_UNSIGNED_BYTE, image1->data);
}

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
