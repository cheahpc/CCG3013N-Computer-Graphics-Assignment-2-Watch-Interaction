#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <stdarg.h>
#include "dimen.h"
#include "color.h"
#include "renderdebug.cpp"

Object obj1 = Object();
Object obj2 = Object();
Object obj3 = Object();

void renderInit()
{
    // Initialize the rendering context
    glClearColor(1, 1, 1, 1);    // Set the background color to white, any area not rendered will be white.
    glMatrixMode(GL_PROJECTION); // Set the matrix mode to projection.
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT); // Load frame buffer.
    glMatrixMode(GL_MODELVIEW);   // Set matrix to
    glLoadIdentity();
    gluOrtho2D(-(WINDOWS_WIDTH / 2), WINDOWS_WIDTH / 2, -(WINDOWS_HEIGHT / 2), WINDOWS_HEIGHT / 2); // Set canvas to windows width and height.
}

void animateTranslate(Object obj, GLfloat duration, GLfloat *initialPos, GLfloat *finalPos)
{
    // First check object animation flag
    // If true, then animate
    // If false, then do nothing
    // If animation is done, set flag to false
    if (obj.translateFlag)
    {
        // Check if object already started animation, if not then set the start time, else continue the animation
    }
    else
    {
        return;
    }
}

void renderMaster()
{
    renderInit();  // Initialize the canvas
    
    // Debugging
    renderGrid();  // For references only
    renderDebug(); // For debugging only

    // todo implement speed interpolation

    glutSwapBuffers();   // Swap foreground and background frames.
    glutPostRedisplay(); // Update the canvas display.
    glFlush();
    glFinish();
}
