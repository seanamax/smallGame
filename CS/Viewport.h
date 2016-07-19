//
// Viewport.hpp
// TinyCS
//

#ifndef Viewport_h
#define Viewport_h


#include "common.h"

class Viewport {
public:
	// mouse pointer is view
	static bool grabbed;

	// view width
	static int width;

	// view height
	static int height;

	// initilize basiced
	static void init();

	// can change of profile of windows
	static void reshape( int w, int h );

	// show the display
	static void display();

	// set mouse pointer is show
	static void setGrabbed( bool value );

};

#endif /* Viewport_hpp */


