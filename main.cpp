#include <chrono>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <ratio>
#include <random>
#include <sstream>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <thread>
#include <vector>
#include <windows.h>

// custom headers7
#include "dimen.h"
#include "color.h"
#include "easing.h"
#include "object.cpp"
#include "animate.h"

// Structs
#include "globalStruct.h"

// renders and controls
#include "control.h"
#include "renderMaster.h"
#include "controlKeyboard.h"
#include "controlMouse.h"

void init()
{
	// Initialize the windows
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);								 // Set the display mode to single buffer and RGBA.
	glutInitWindowSize(WINDOWS_WIDTH, WINDOWS_HEIGHT);							 // Set the windows size.
	glutInitWindowPosition(WINDOWS_INITIAL_POS_X, WINDOWS_INITIAL_POS_Y);		 // Set the windows position.
	glutCreateWindow("CCG3013N Assignment 2 (OppsOS Simulator) by: Group Opps"); // Set the windows title.

	// Context Settings
	glEnable(GL_LINE_SMOOTH);						   // Enables line anti-aliasing.
	glEnable(GL_BLEND);								   // Enable for proper transparency render.
	glDisable(GL_DEPTH_TEST);						   // Disable depth testing for overlap object. Use for transparency object involved.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Enable transparency.
}

int main()
{
	init(); // Load settings.

	glutDisplayFunc(renderMaster);	  // Load render function.
	glutMouseFunc(ctrlMouse);		  // Enable mouse button function.
	glutMotionFunc(mouseMoveControl); // Enable mouse move function.
	glutKeyboardFunc(ctrlKeyboard);	  // Enable keyboard function.
	glutMainLoop();					  // Loop frame forever.

	system("PAUSE");
	return 0;
}