#include "MathTool.h"

void clearVec3( Vec3d *_A )
{
	memset( _A->X, 0, sizeof( double ) * 3 );
}

void setVec3toVec3( Vec3d *_A,  Vec3d *_B )
{
	memcpy( _B->X, _A->X, sizeof( double ) * 3 );
}

void sumVec3andVec3( Vec3d *_A, Vec3d *_B, Vec3d *_dst )
{
	unsigned int i;
	//[TODO]



}

void subVec3andVec3( Vec3d *_A, Vec3d *_B, Vec3d *_dst )
{
	unsigned int i;
	//[TODO]



}

void scalingVec3( double _s, Vec3d *_A, Vec3d *_dst )
{
	unsigned int i;
	//[TODO]



}

double dotVec3andVec3( Vec3d *_A, Vec3d *_B )
{
	unsigned int i;
	double dst = 0;
	//[TODO]



	return dst;
}

void crossVec3andVec3(Vec3d *_A, Vec3d *_B, Vec3d *_dst)
{
	//[TODO]



}

double absVec3( Vec3d *_A )
{
	return //[TODO]
}

int isEqualVec3andVec3( Vec3d *_A, Vec3d *_B )
{
	return //[TODO]
}

void printVec3( Vec3d *_A )
{
	unsigned int i;
	for( i = 0; i < 3; i++ ){
		printf( "%2.2f", _A->X[ i ] );
		if( i < 2){
			printf( " ");
		}
		else{
			printf( "\n");
		}
	}
}