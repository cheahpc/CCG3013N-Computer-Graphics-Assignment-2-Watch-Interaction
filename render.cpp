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

// Object  anchorX, anchorY, scaleFactor, orientation, *color, opacity, orbitRadius, orbitAngle
Object obj1 = Object(100, 100, 1, -45, COLOR_BLUE, 100, 100, 120);
Object obj2 = Object(100, 100, 1, -45, COLOR_BLUE, 0);
Object obj3 = Object();

GLfloat xVal, yVal, rotateVal, scaleVal, opacityVal, orbitVal;

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

Object backgroundObj1 = Object();
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

    // obj1.drawQuad_Fill(x, y);
    obj1.drawCircle_Line(50, 25, 330,80);
    obj2.drawPoint(10);

    if (obj2.anchorX == 100 && obj2.anchorY == 100)
        xVal = yVal = -200;
    else if (obj2.anchorX == -100 && obj2.anchorY == -100)
        xVal = yVal = 200;

    if (obj1.orientation == -45)
        rotateVal = 90;
    else if (obj1.orientation == 45)
        rotateVal = -90;
    if (obj1.scaleFactor == 1)
        scaleVal = 4;
    else if (obj1.scaleFactor == 5)
        scaleVal = -4;

    if (obj1.opacity == 100)
        opacityVal = -80;
    else if (obj1.opacity == 20)
        opacityVal = 80;

    // if (obj1.clockWiseFlag)
    //     orbitVal = 1;
    // else if (!obj1.clockWiseFlag)
    //     orbitVal = -1;

    if (obj1.clockWiseFlag)
        orbitVal = 180;
    else if (!obj1.clockWiseFlag)
        orbitVal = -180;

    // animateTranslate(obj1, 1000, EASEOUT5, 100, 100);
    animateTranslate(obj2, 1000, EASEOUT5, xVal, yVal);
    animateTranslate(obj1, 1000, EASEOUT5, xVal, yVal);
    animateRotate(obj1, 1000, EASEOUT5, rotateVal);
    animateScale(obj1, 1000, EASEOUT5, scaleVal);
    animateOpacity(obj1, 1000, EASEOUT5, opacityVal);
    // obj1.orbit(obj2.anchorX, obj2.anchorY, 100, orbitVal);
    animateOrbit(obj1, 1000, EASEINOUT1, obj2.anchorX, obj2.anchorY, 100, orbitVal);

    glutSwapBuffers();   // Swap foreground and background frames.
    glutPostRedisplay(); // Update the canvas display.
    glFlush();
    glFinish();
}
