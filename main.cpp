#include <chrono>
#include <cmath>
#include <ctime>
#include <iostream>
#include <math.h>
#include <ratio>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <thread>
#include <vector>
#include <windows.h>

// custom headers7
#include "system.h"
#include "dimen.h"
#include "color.h"
#include "easing.h"
#include "object.cpp"
#include "animate.h"

// renders and controls
#include "control.h"
#include "renderMaster.h"
#include "kbControl.h"
#include "mouseControl.h"

void init()
{
	// Initialize the windows
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);						  // Set the display mode to single buffer and RGBA.
	glutInitWindowSize(WINDOWS_WIDTH, WINDOWS_HEIGHT);					  // Set the windows size.
	glutInitWindowPosition(WINDOWS_INITIAL_POS_X, WINDOWS_INITIAL_POS_Y); // Set the windows position.
	glutCreateWindow("Assignment 2");									  // Set the windows title.

	// Context Settings
	glEnable(GL_LINE_SMOOTH);						   // Enables line anti-aliasing.
	glEnable(GL_BLEND);								   // Enable for proper transparency render.
	glDisable(GL_DEPTH_TEST);						   // Disable depth testing for overlap object. Use for transparency object involved.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Enable transparency.

	// Control Settings
	// glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF); // Disable key repeat.
}

int main()
{
	init(); // Load settings.

	glutDisplayFunc(renderMaster);	  // Load render function.
	glutMouseFunc(mouseControl);	  // Enable mouse button function.
	glutMotionFunc(mouseMoveControl); // Enable mouse move function.
	// glutKeyboardFunc(kbControl_Debug_Control); // For debugging only
	glutKeyboardFunc(kbControl_Main); // Enable keyboard function.
	// glutSpecialFunc(kbControl);				   // Enable special key function.
	glutMainLoop(); // Loop frame forever.

	system("PAUSE");
	return 0;
}