#ifndef GLTOOL_H
#define GLTOOL_H

#include "MathTool.h"
#include <GL/glut.h>

typedef struct
{
	int id;
	float position[4];
	float ambient[4];
	float diffuse[4];
	float specular[4];
}Lightf;

typedef struct
{
	float ambient[4];
	float diffuse[4];
	float specular[4];
}Materialf;

//Initialization of OpenGL
void glInit( void );
//Camera settings
void setCamera( int _width, int _height );
//Light settings
void setLight( Lightf *_light );
//Material settings
void setMaterial( Materialf *_material );
void setVec4f( float *_vec, float _x, float _y, float _z, float _w);

#endif