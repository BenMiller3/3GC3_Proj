#include "scene.h"
#include "header.h"

Scene::Scene(){
	
}

/*
// BMP image loader
GLuint LoadTexture( const char * filename )
{

  GLuint texture;

  int width, height;

  unsigned char * data;

  FILE * file;

  file = fopen( filename, "rb" );

  if ( file == NULL ) return 0;
  width = 1024;
  height = 512;
  data = (unsigned char *)malloc( width * height * 3 );
  //int size = fseek(file,);
  fread( data, width * height * 3, 1, file );
  fclose( file );

 for(int i = 0; i < width * height ; ++i)
{
   int index = i*3;
   unsigned char B,R;
   B = data[index];
   R = data[index+2];

   data[index] = R;
   data[index+2] = B;

}


glGenTextures( 1, &texture );
glBindTexture( GL_TEXTURE_2D, texture );
glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );


glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
free( data );

return texture;
}
*/

void Scene::drawRoad(float zPosition){
	
	/*
	// texture enabled here
	GLuint texture;
	texture = LoadTexture("Textures/path.bmp");

	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 9, 9, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
	*/

	float size = 9.6f;

	glColor3f(0.87f, 0.59f, 0.12f);

	glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex3f(-size, -size, (10.0f - zPosition));	// Bottom left corner
		glVertex3f(-size, size, (-50.0f - zPosition));	// Top left corner
		glVertex3f(size, size, (-50.0f - zPosition));	// Top right corner
		glVertex3f(size, -size, (10.0f - zPosition));	// Bottom right corner
	glEnd();
}
