//
// Viewport.cpp
// TinyCS
//

#include "Viewport.h"

int Viewport::width = 0;
int Viewport::height = 0;

bool Viewport::grabbed = false;

void Viewport::init()	{

	// set GLUT call back function
	glutReshapeFunc( Viewport::reshape );
	glutDisplayFunc( Viewport::display );
	glutIdleFunc( Viewport::display );

	// start using deepth test, auto hide coverd graph from distance of coord
	glEnable( GL_DEPTH_TEST );

	// starting using 2D texture
	glEnable( GL_TEXTURE_2D );

	// profile mouse is directly global catching and showing by OpenGL
	if( grabbed ){
		Viewport::setGrabbed( true );
	}
	else{
		Viewport::setGrabbed( false );
	}

}

void Viewport::setGrabbed( bool value ) {
	grabbed = value;

	if( grabbed ) {
		// set windows cursor and that useless
		glutSetCursor( GLUT_CURSOR_NONE );
	} else {
		// inherit system cursor
		glutSetCursor( GLUT_CURSOR_INHERIT );
	}
}


// apply colours to drawing when window width and height were changed

void Viewport::reshape( int w, int h ) {
	width = w;
	height = h;

	if( h <= 0 ) h = 1;

	// calculate rate of width and height
	float ratio = ( float )w / h;

	// swtich matrix mode when viewport was changed
	glMatrixMode( GL_PROJECTION );
	// meke projection matrix is unit matrix
	glLoadIdentity();
	glViewport( 0, 0, w, h );

	// properly adjust the angle of view
	gluPerspective( 45, ratio, 0.01, 1000 );

	// return GL_MODELVIEW
	glMatrixMode( GL_MODELVIEW );
}

void Viewport::display() {

	// clear buffer in the viewport
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// change it to unit matrix
	glLoadIdentity();

	// drawing a trianlge
	glBegin( GL_TRIANGLES );
		glColor3f( 1.0, 1.0, 0.0 );
		glVertex3f( -1, 0, -3 );
		glColor3f( 0.0, 1.0, 0.0 );
		glVertex3f( 0, 2, -3 );
		glColor3f( 0.0, 0.0, 1.0 );
		glVertex3f( 1, 0, -3 );
	glEnd();

	// binding texture
	glBindTexture( GL_TEXTURE_2D, 0 );

	// send buffer of graph to graphics card that drawing
	// we will register showing mode that can show double buffer GLUT_DOUBLE in main.cpp
	glutSwapBuffers();
}


