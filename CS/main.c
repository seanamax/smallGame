#include <stdio.h>
#include "common.hpp"
#include "Viewport.hpp"

using namespace std;

const int WINDOW_WIDTH = 500;

const int WINDOW_HEIGHT = 500;

const char * WINDOW_TITLE = "Shiyanglou Tiny CS";

int main( int argc, char * argv[] ){

	// initliaze GLUT and OpenGL
	glutInit( &argc, argv );
	glutInitWindowPosition( 0, 0 );
	glutInitWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );

	// create OpenGL
	glutCreateWindow( WINDOW_TITLE );

	// initilize viewport
	Viewport::init();

	// Enter Main Loop
	glutMainLoop();

	return 0;
}

