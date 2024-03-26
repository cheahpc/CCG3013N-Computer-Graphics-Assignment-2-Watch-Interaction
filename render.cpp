#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <stdarg.h>
// custom
#include "dimen.h"
#include "color.h"
#include "easing.h"
#include "animate.cpp"
#include "object.cpp"
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

    GLint x[4] = {-10, -10, 10, 10};
    GLint y[4] = {-10, 10, 10, -10};
    obj1.setColor(COLOR_RED, 60);

    obj1.drawQuad_Fill(x, y);
    // animateTranslate(obj1, 1000, EASEOUT1, 50, 50);
    // animateTranslate(obj1, 1000, EASEOUT2, 50, 50);
    // animateTranslate(obj1, 1000, EASEOUT3, 50, 50);
    // animateTranslate(obj1, 1000, EASEOUT4, 50, 50);
    // animateTranslate(obj1, 1000, EASEOUT5, 50, 50);
    // animateTranslate(obj1, 1000, EASEOUT6, 50, 50);
    // animateTranslate(obj1, 1000, EASEOUT7, 50, 50);
    // animateTranslate(obj1, 1000, EASEOUT8, 50, 50);
    // animateTranslate(obj1, 1000, EASEOUT9, 50, 50);

    // animateTranslate(obj1, 1000, EASEIN1, 50, 50);
    // animateTranslate(obj1, 1000, EASEIN2, 50, 50);
    // animateTranslate(obj1, 1000, EASEIN3, 50, 50);
    // animateTranslate(obj1, 1000, EASEIN4, 50, 50);
    // animateTranslate(obj1, 1000, EASEIN5, 50, 50);
    // animateTranslate(obj1, 1000, EASEIN6, 50, 50);
    animateTranslate(obj1, 1000, EASEIN7, 50, 50);
    // animateTranslate(obj1, 1000, EASEIN8, 50, 50);
    // animateTranslate(obj1, 1000, EASEIN9, 50, 50);

    // animateTranslate(obj1, 1000, EASEINOUT1, 50, 50);
    // animateTranslate(obj1, 1000, EASEINOUT2, 50, 50);
    // animateTranslate(obj1, 1000, EASEINOUT3, 50, 50);
    // animateTranslate(obj1, 1000, EASEINOUT4, 50, 50);
    // animateTranslate(obj1, 1000, EASEINOUT5, 50, 50);
    // animateTranslate(obj1, 1000, EASEINOUT6, 50, 50);
    // animateTranslate(obj1, 1000, EASEINOUT7, 50, 50);
    // animateTranslate(obj1, 1000, EASEINOUT8, 50, 50);
    // animateTranslate(obj1, 1000, EASEINOUT9, 50, 50);

    // todo implement speed interpolation

    glutSwapBuffers();   // Swap foreground and background frames.
    glutPostRedisplay(); // Update the canvas display.
    glFlush();
    glFinish();
}
