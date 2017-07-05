#include "MathTool.h"
#include "Mesh.h"
#include "SPH.h"
#include "GLTool.h"
#include <GL/glut.h>

//Window settings
#define WINDOW_POSITION_X	100
#define WINDOW_POSITION_Y	100
#define WINDOW_SIZE_X			640
#define WINDOW_SIZE_Y			480

//A gain for rotation relative to mouse motion
#define ANGLE_GAIN					0.2

//Light source
Lightf light;
//Material
Materialf material;
//Object mesh to initialize particle position
Mesh mesh;
//Liquid simulation solver
SPH sph;
//Window width
int width;
//Window height
int height;
//Previous mouse position
int pre_x;
int pre_y;
//Camera rotational angle
Vec3d camera_rot_angle;
//A flag presents whether simulation is started or not
int isStarted;
//A flag presents whether simulation result will be saved or not
int isSaveResult;

//Display callback function
void glDisplay( void )
{
	//Reset draw buffer
	glClearColor( 1.0, 1.0, 1.0, 1.0 );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//Set camera parameters
	setCamera( width, height );
	glRotated( camera_rot_angle.x, 0, 1, 0 );
	glRotated( camera_rot_angle.y, 1, 0, 0 );

	//Set light source
	setLight( &light );
	//Enable lighting and depth buffer
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 + light.id );
	glEnable( GL_DEPTH );
	//Set material
	setMaterial( &material );

	//Draw particle and container
	renderSPH( &sph );
	glDisable( GL_DEPTH );
	glDisable( GL_LIGHTING );
	glDisable( GL_LIGHT0 + light.id );

	//Swap flame buffer
	glutSwapBuffers();
}

//Idle callback function
void glIdle( void )
{
	if( isStarted ){//If simulation is started
		if( isSaveResult){//If save pov-ray flag is on
			//save current secene as pov-ray file
			savePovData( &sph, "../data/dst/img" );
			printf( "../data/dst/img%.6f.pov was saved\n", sph.time );
		}
		//execute SPH solver
		runSPH( &sph );
	}
	glutPostRedisplay();
}

//Mouse click callback function
void glMouse( int _button, int _state, int _x, int _y )
{
	if( _state == GLUT_DOWN ){//When you click within the window
		pre_x = _x;
		pre_y = _y;
	}
}

//Mouse motion callback function
void glMotion( int _x, int _y)
{
	//Set camera rotation
	//[TODO]






	//Rotate gravity direction
	//[TODO]

}

//Keyboard callback function
void glKeyboard( unsigned char _key, int _x, int _y )
{
	switch (_key) {
		case 'q':
		case 'Q':
		case '\033':	//Exit program
			exit(0);
			break;
		case 'r':		//Start simulation
			isStarted = 1;
			break;
		case 'i':		//Reset particle position
			setLiquid( &mesh, &sph, 1 );
			isStarted = 0;
			break;
		case 's':		//Save simulation result
			isSaveResult = 1;
			break;
		case 'n':		//Not to save simulation result
			isSaveResult = 0;
			break;
		default:
			break;
	}
}

//Resize callback function
void glResize( int _width, int _height )
{
	width = _width;
	height = _height;
	setCamera( width, height );
}

int main( int _argc, char *_argv[] )
{
	char filename[256];

	//Command line input
	if( //[TODO]


	}else{
		sprintf( filename, "../data/bunny.stl" );
	}

	//Initialization of mesh
	initMesh( &mesh );
	//load mesh data
	if(	loadSTLMesh( &mesh, filename ) == -1 ){
		printf( "ERROR: fail to load %s\n", filename );
		return -1;
	}

	//Initialization of SPH
	initSPH( &sph );
	//Load SPH parameters
	loadSPHParameters( "../data/param.ini", &sph);
	//Generate the initial position of the particles using mesh
	setLiquid( &mesh, &sph, 0 );
	//Load container data
	loadSTLMesh( &sph.container, "../data/container.stl" );

	isStarted = 0;
	isSaveResult = 0;

	//Set initial window size
	width = WINDOW_SIZE_X;
	height = WINDOW_SIZE_Y;

	//Set lighting
	light.id = 0;
	setVec4f( light.position, 0, 0, 100, 1.0 );
	setVec4f( light.ambient, 0.0, 0.0, 0.0, 1.0 );
	setVec4f( light.diffuse, 1.0, 1.0, 1.0, 1.0 );
	setVec4f( light.specular, 0.0, 0.0, 0.0, 1.0 );

	//Set material
	setVec4f( material.ambient, 0.0, 0.0, 0.0, 1.0 );
	setVec4f( material.diffuse, 0.0, 1.0, 1.0, 1.0 );
	setVec4f( material.specular, 0.0, 0.0, 0.0, 1.0 );

	//Set the initial angle of the camera
	clearVec3( &camera_rot_angle );

	glutInit( &_argc, _argv );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowPosition( WINDOW_POSITION_X, WINDOW_POSITION_Y );
	glutInitWindowSize( WINDOW_SIZE_X, WINDOW_SIZE_Y );
	glutCreateWindow( _argv[ 0 ] );
	glutDisplayFunc( glDisplay );
	glutReshapeFunc( glResize );
	glutMouseFunc( glMouse );
	glutMotionFunc( glMotion );
	glutKeyboardFunc( glKeyboard );
	glutIdleFunc( glIdle );
	glInit();
	glutMainLoop();

	//Release mesh memory
	releaseMesh( &mesh );
	//Release SPH memory
	releaseSPH( &sph );

	return 0;
}