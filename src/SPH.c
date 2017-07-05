#include "SPH.h"

void initSPH( SPH *_sph )
{
	clearVec3( &_sph->gravity );
	_sph->gravity.y = SPH_GRAVITY;
	_sph->time = 0;
	_sph->nt = 0;
	_sph->num_particles = 0;
}

void loadSPHParameters( char *_filename, SPH *_sph )
{
	FILE *file;
	char buf[256];
	if( (file=fopen( _filename, "r" ) ) != NULL ){
		while(! feof( file ) ){
			fgets( buf, 256, file );
			if( strstr( buf, "DT" ) ){
				sscanf( buf, "DT:%lf", &_sph->dt);
			}
			else if( strstr( buf, "CGAS" ) ){
				sscanf( buf, "CGAS:%lf", &_sph->cgas);
			}
			else if( strstr( buf, "PMASS" ) ){
				sscanf( buf, "PMASS:%lf", &_sph->pmass);
			}
			else if( strstr( buf, "EFFRADIUS" ) ){
				sscanf( buf, "EFFRADIUS:%lf", &_sph->effradius);
			}
			else if( strstr( buf, "RADIUS" ) ){
				sscanf( buf, "RADIUS:%lf", &_sph->radius);
			}
			else if( strstr( buf, "DENSITY" ) ){
				sscanf( buf, "DENSITY:%lf", &_sph->density);
			}
			else if( strstr( buf, "VISCOSITY" ) ){
				sscanf( buf, "VISCOSITY:%lf", &_sph->viscosity);
			}
			else if( strstr( buf, "RESTITUTION" ) ){
				sscanf( buf, "RESTITUTION:%lf", &_sph->restitution);
			}
			else if( strstr( buf, "FRICTION" ) ){
				sscanf( buf, "FRICTION:%lf", &_sph->friction);
			}
		}
		_sph->MxPoly6Kern = _sph->pmass * 315.0 / (64.0 * M_PI * pow( _sph->effradius, 9 ));
		_sph->MxdSpikyKern = -_sph->pmass * 45.0 / (M_PI * pow( _sph->effradius, 6 ));
		_sph->Mxd2ViscKern = _sph->pmass * 45.0 / (M_PI * pow( _sph->effradius, 6 ));
	}
}

void setLiquid( Mesh *_liquidMesh, SPH *_sph, int _isMemmoryAllocated )
{
	int i;
	_sph->time = 0;
	_sph->nt = 0;

	//Memory allocation for particles and neighbors
	if( _isMemmoryAllocated == 0 ){
		_sph->num_particles = _liquidMesh->num_node;
		_sph->particles = ( Particle* )calloc( _sph->num_particles, sizeof( Particle ) );
		_sph->neighbors = ( Neighbor* )calloc( _sph->num_particles, sizeof( Neighbor ) );
	}

	//Parameter initialization
	for( i = 0; i < _sph->num_particles; i++){
		_sph->neighbors[i].num_particles = 0;
	}
	for( i = 0; i < _sph->num_particles; i++){
		//Set all node position of the mesh to the initial position of the particles 
		setVec3toVec3( &_liquidMesh->node[i].position, &_sph->particles[i].position );
		clearVec3( &_sph->particles[i].force );
		clearVec3( &_sph->particles[i].velocity );
		_sph->particles[i].rho = 0;
		_sph->particles[i].pressure = 0;
	}
}

void genNeighborMap( SPH *_sph )
{
	int i, j;
	Vec3d dir;
#ifdef _OPENMP
#pragma omp parallel private( i, j, dir )
#pragma omp for
#endif
	for( i = 0; i < _sph->num_particles; i++){
		_sph->neighbors[i].num_particles = 0;
		for( j = 0; j < _sph->num_particles; j++){
				//If the distance between the i-th particle and the j-th particle is less than H,
				subVec3andVec3( &_sph->particles[i].position, &_sph->particles[j].position, &dir );
				if( /* [TODO] */ ){
					//Stack index of the neibor particle and count up the number of neibor particles
					_sph->neighbors[i].index[_sph->neighbors[i].num_particles] = j;
					_sph->neighbors[i].num_particles ++;
				}
		}
	}
}

void rotateSPHGravity( Vec3d *_rot, SPH *_sph )
{
	// [TODO]


}

void runSPH( SPH *_sph )
{
	genNeighborMap( _sph );
	calDensityAndPressure( _sph );
	calForce( _sph );
	updatePosition( _sph );
}

void calDensityAndPressure( SPH *_sph )
{
    double Wi, Rji2, R2effji;
    Vec3d rji;
	int i, j;
#ifdef _OPENMP
#pragma omp parallel private( i, j, Wi, R2effji, Rji2, rji )
#pragma omp for
#endif
	for( i = 0; i < _sph->num_particles; i++ ){
		Wi = 0.0;
		for( j = 0; j < _sph->neighbors[i].num_particles; j++ ){
			// [TODO]

		
		
		
		
		}
			// [TODO]

	}
}

void calForce( SPH *_sph )
{
    double p_alpha, v_alpha, Rji, Reffji;
    Vec3d rji, force, t_force, vji, p_force, v_force;
	int i, j;
	v_alpha = _sph->Mxd2ViscKern * _sph->viscosity;
#ifdef _OPENMP
#pragma omp parallel private( i, j, force, rji, Rji, Reffji, p_force, v_force, t_force, vji)
#pragma omp for
#endif
	for( i = 0; i < _sph->num_particles; i++ ){
	    force.x = 0; force.y =0; force.z=0;
		for( j = 0; j < _sph->neighbors[i].num_particles; j++ ){
			//The i-th particle and j-th particle are not at the same position
			if(  isEqualVec3andVec3( &_sph->particles[i].position, &_sph->particles[_sph->neighbors[i].index[j]].position ) == 0 ){
				// [TODO]




				
				
				

				
				

				
			
			}
		}
		setVec3toVec3( &force, &_sph->particles[i].force );
    }
}

void updatePosition( SPH *_sph )
{
	Vec3d accel;
	Vec3d dr,tvec;
	double dist, length;
	int i, j;
#ifdef _OPENMP
#pragma omp parallel private( i, j, dist, length, accel, tvec, dr )
#pragma omp for
#endif
	for( i = 0; i < _sph->num_particles; i++ ){
		sumVec3andVec3( &_sph->particles[i].force, &_sph->gravity, &accel );
		scalingVec3( _sph->dt, &accel, &tvec);
		sumVec3andVec3( &_sph->particles[i].velocity, &tvec, &_sph->particles[i].velocity );
		scalingVec3( _sph->dt, &_sph->particles[i].velocity, &tvec);
		sumVec3andVec3( &_sph->particles[i].position, &tvec, &_sph->particles[i].position );
		for( j = 0; j < _sph->container.num_facet; j++ ){
			// [TODO]



			
			
			
			

			
			
		}
	}
	_sph->nt ++;
    _sph->time = _sph->nt * _sph->dt;
}

void releaseSPH( SPH *_sph )
{
	int i;
	for( i = 0; i < _sph->num_particles; i++){
		_sph->neighbors[i].num_particles = 0;
	}
	_sph->num_particles = 0;
	free( _sph->particles );
	free( _sph->neighbors );
}

void renderSPH( SPH *_sph )
{
	int i;
	Materialf material;
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	for( i = 0; i < _sph->num_particles; i++){
		glPushMatrix();
		glTranslated( _sph->particles[i].position.x, _sph->particles[i].position.y, _sph->particles[i].position.z );
		glutSolidSphere( _sph->radius, 10, 5 );
		glPopMatrix();
	}

	setVec4f( material.ambient, 0.0, 0.2, 0.0, 0.1 );
	setVec4f( material.diffuse, 0.0, 1.0, 0.0, 0.1 );
	setVec4f( material.specular, 0.2, 0.2, 0.2, 0.1 );
	setMaterial( &material );
	renderSTLMesh( &_sph->container );
}

void savePovData( SPH *_sph, const char *_filename)
{
	FILE *file;
    char filename[256];
	int i;
	sprintf(filename, "%s%08f.pov", _filename, _sph->time);
	if( (file=fopen( filename, "w" ) ) != NULL ){
		fprintf( file, "#include \"colors.inc\"\n" );
		fprintf( file, "#include \"shapes.inc\"\n" );
		fprintf( file, "#include \"textures.inc\"\n" );
		fprintf( file, "#include \"glass.inc\"\n" );
		fprintf( file, "camera {perspective \n" );
		fprintf( file, "location <0, 50, 100>" );
		fprintf( file, "look_at <0, -20, 0.0> up <0,1,0> right<1,0,0>\n" );
		fprintf( file, "}\n" );
		fprintf( file, "light_source { <0, 100, 100> color White }\n" );
		fprintf( file, "object{Plane_XY pigment{ checker color rgb<1.0,1.0,1.0>, color rgb<0.8,0.8,0.8> scale 6} translate <0,0,-100> }\n" );
		fprintf( file, "object{Plane_XZ pigment{ checker color rgb<1.0,1.0,1.0>, color rgb<0.8,0.8,0.8> scale 6} translate <0,-50,0> }" );
		fprintf( file, "blob {\n" );
		fprintf( file, "threshold 5\n" );
	}
	for( i = 0; i < _sph->num_particles; i++ ){
		fprintf( file, "sphere {\n" );
		fprintf( file, "<%f,%f,%f>, 2, 2\n", _sph->particles[i].position.x, _sph->particles[i].position.y, _sph->particles[i].position.z );
		fprintf( file, "}\n" );
    }
	fprintf( file, "pigment {color Clear}\n" );
	fprintf( file, "finish { F_Glass1 }\n" );
	fprintf( file, "interior {\n" );
	fprintf( file, "  I_Glass1\n" );
	fprintf( file, "  fade_color Col_Emerald_03\n" );
	fprintf( file, "  ior 1.33\n" );
	fprintf( file, "}\n" );
	fprintf( file, "}\n" );
}