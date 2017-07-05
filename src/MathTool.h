#ifndef MATHTOOL_H
#define MATHTOOL_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Union for 3D vector
typedef union
{
	//x,y,z are corresponding to X[0],X[1],X[2], respectively
	struct{double x,y,z;};
	double X[3];
}Vec3d;

//Set zero value to the vector
void clearVec3( Vec3d *_A );
//Copy vector A to vector B
void setVec3toVec3( Vec3d *_A,  Vec3d *_B );
//Summation of the vectors
void sumVec3andVec3( Vec3d *_A, Vec3d *_B, Vec3d *_dst );
//Subtraction of the vectors
void subVec3andVec3( Vec3d *_A, Vec3d *_B, Vec3d *_dst );
//Scaling vector
void scalingVec3( double _s, Vec3d *_A, Vec3d *_dst );
//Dot product of the vectors
double dotVec3andVec3( Vec3d *_A, Vec3d *_B );
//Cross product of the vectors
void crossVec3andVec3( Vec3d *_A, Vec3d *_B, Vec3d *_dst );
//Absolute value of the vector
double absVec3( Vec3d *_A );
//Equality operator
int isEqualVec3andVec3( Vec3d *_A, Vec3d *_B );
//Print vector value to console
void printVec3( Vec3d *_A );

#endif