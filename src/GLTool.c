#include "GLTool.h"

void glInit( void )
{
	glClearColor( 0.0, 0.0, 0.0, 1.0 );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_LINE_SMOOTH );
	glShadeModel( GL_SMOOTH );
}

void setCamera( int _width, int _height )
{
	glViewport( 0, 0, _width, _height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 30.0, (double)_width / (double)_height, 0.1, 1000 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 150.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void setLight( Lightf *_light )
{
	glLightfv( GL_LIGHT0+_light->id, GL_POSITION, _light->position );
	glLightfv( GL_LIGHT0+_light->id, GL_AMBIENT, _light->ambient );
	glLightfv( GL_LIGHT0+_light->id, GL_DIFFUSE, _light->diffuse );
	glLightfv( GL_LIGHT0+_light->id, GL_SPECULAR, _light->specular );
}

void setMaterial( Materialf *_material )
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _material->ambient );
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _material->diffuse );
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _material->specular );
}
void setVec4f( float *_vec, float _x, float _y, float _z, float _w)
{
	_vec[ 0 ] = _x;
	_vec[ 1 ] = _y;
	_vec[ 2 ] = _z;
	_vec[ 3 ] = _w;
}