#ifndef SPH_H
#define SPH_H

#ifdef _OPENMP
#include <omp.h>
#endif

#include "MathTool.h"
#include "Mesh.h"
#include "GLTool.h"

#define MAX_NUM_INDEX 1000
#define SPH_GRAVITY -9806.65			//[mm/s^2]

typedef struct{
    Vec3d position;
    Vec3d velocity;
    Vec3d force;
    double rho;
	double pressure;
}Particle;

typedef struct{
	int num_particles;
	int index[MAX_NUM_INDEX];
}Neighbor;

typedef struct{
	double dt;
	int nt;
	double time;
	Vec3d gravity;
	double cgas;
	double pmass;
	double effradius;
	double radius;
	double density;
	double viscosity;
	double restitution;
	double friction;
	double MxPoly6Kern;
	double MxdSpikyKern;
	double Mxd2ViscKern;
	Mesh container;
	int num_particles;
	Particle *particles;
	Neighbor *neighbors;
}SPH;

//Initialization
void initSPH( SPH *_sph );
//Load SPH parameters
void loadSPHParameters( char *_filename, SPH *_sph );
//Set initial position of liquid particles and container based on mesh data
void setLiquid( Mesh *_liquidMesh, SPH *_sph, int _isMemmoryAllocated );
//Generate index lists of the neighbor particles
void genNeighborMap( SPH *_sph );
//Interactive gravity setting
void rotateSPHGravity( Vec3d *_rot, SPH *_sph );
//Run simulation
void runSPH( SPH *_sph );
//Calculate density and pressure
void calDensityAndPressure( SPH *_sph );
//Calculate force
void calForce( SPH *_sph );
//Update particle position
void updatePosition( SPH *_sph );
//Release memory for SPH pointer
void releaseSPH( SPH *_sph );
//Rendering function of the particles and container
void renderSPH( SPH *_sph );
//Save current scene as Pov-Ray file
void savePovData( SPH *_sph, const char *_filename);

#endif