#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <stdarg.h>
// custom
#include "animate.cpp"
#include "dimen.h"
#include "color.h"
#include "easing.h"
#include "object.cpp"
// #include "animate.cpp"
#include "renderdebug.cpp"

Object obj1 = Object(100, 100);
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

void renderBackground()
{
    // Draw the background
}

void renderMaster()
{
    renderInit(); // Initialize the canvas

    // Debugging
    renderGrid(); // For references only
    // renderDebug(); // For debugging only

    GLint x[4] = {-50, -50, 50, 50};
    GLint y[4] = {-50, 50, 50, -50};
    obj1.setColor(COLOR_RED, 100);

    obj1.drawQuad_Fill(x, y);
    // animateTranslate(obj1, 500, bezierLinear, 100, 100);
    animateTranslate(obj1, 1000, bezier, 100, 100);

    // todo implement speed interpolation

    glutSwapBuffers();   // Swap foreground and background frames.
    glutPostRedisplay(); // Update the canvas display.
    glFlush();
    glFinish();
}
