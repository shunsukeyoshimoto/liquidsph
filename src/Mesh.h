#ifndef MESH_H
#define MESH_H

#include "MathTool.h"
#include "GLTool.h"

typedef struct{
	Vec3d position;
}Node;
typedef struct{
	Vec3d position[3];
	Vec3d normal;
}Facet;
typedef struct{
	unsigned int num_node;
	unsigned int num_facet;
	Node *node;
	Facet *facet;
}Mesh;

//Initialization of mesh
void initMesh( Mesh *_mesh );
//Memory allocation for the node and element of the mesh
void setMeshDim( Mesh *_mesh );
//Memory release of the mesh
void releaseMesh( Mesh *_mesh );
//Load the node position, surface index and normal of the mesh
int loadSTLMesh( Mesh *_mesh, const char *_filename );
//Rendering process of the mesh
void renderSTLMesh( Mesh *_mesh );

#endif