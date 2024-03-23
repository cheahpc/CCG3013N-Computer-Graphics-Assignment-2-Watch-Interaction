#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <stdarg.h>
#include "dimen.h"
#include "object.cpp"
#include "color.h"

void setColor(const GLfloat *color, GLint alpha)
{
    GLfloat value = (GLfloat)alpha / 100;
    glColor4f(color[0], color[1], color[2], value);
}

GLfloat angle = 0.0;
GLfloat scale = 1.0;

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

Object debugGrid = Object();

void renderGrid()
{
    // Draw the grid
    debugGrid.scaleTo(1);
    debugGrid.translateTo(0, 0);
    debugGrid.setColor(COLOR_SILVER, 100);
    debugGrid.drawGrid(10, 1, 0);
    debugGrid.setColor(COLOR_GRAY, 100);
    debugGrid.drawGrid(50, 1, 0);
    debugGrid.setColor(COLOR_BLACK, 100);
    debugGrid.drawGrid(100, 1, 0);

    debugGrid.setColor(COLOR_RED, 100);
    // Center Line
    debugGrid.drawLine(-WINDOWS_WIDTH / 2, 0, WINDOWS_WIDTH / 2, 0, 2);
    debugGrid.drawLine(0, -WINDOWS_HEIGHT / 2, 0, WINDOWS_HEIGHT / 2, 2);

    // Center point
    debugGrid.drawCircle_Fill(5, 0, 360);
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
    renderInit(); // Initialize the canvas
    renderGrid(); // For references only

    GLint x[4] = {-150, 150, 150, -150};
    GLint y[4] = {150, 150, -150, -150};
    // obj3.setColor(COLOR_RED, 100);
    // obj3.setOpacity(40);
    obj3.scaleTo(2.4);
    obj3.rotateTo(45);
    obj3.translateTo(100, 0);

    // obj3.setColor(COLOR_ORANGE, 50);
    obj3.drawPoint(0, 0, 20);
    // obj3.drawLine(x, y, 10);
    // obj3.drawTriangle_Fill(x, y);
    // obj3.drawTriangle_Line(x, y, 10);
    // obj3.drawQuad_Fill(x, y);
    // obj3.drawQuad_Line(x, y, 10);
    // obj3.drawCircle_Fill(200, 270, 340);
    // obj3.drawCircle_Line(100, 0, 270, 10);
    // obj3.setColor(COLOR_BRONZE, 30);
    // obj3.drawRoundedRect_Fill(200, 200, 40);
    obj3.drawRoundedRect_Line(200, 200, 40, 40);

    // setColor(COLOR_BLACK, 100);
    // obj3.scaleTo(2);
    // obj3.drawCircle_Fill(100, 0, 90);

    // setColor(COLOR_RED, 90);
    // obj3.scaleTo(1.0);
    // obj3.drawCircle_Line(100, 0, 90, 25);
    // Translate object
    // float offsetX = obj2.anchorX;
    // float offsetY = obj2.anchorY;
    // float speeda = 1;
    // if (obj2.anchorX > 150)
    //     obj2.translateFlag = false;
    // else if (obj2.anchorX <= 0)
    //     obj2.translateFlag = true;

    // if (obj2.translateFlag)
    //     obj2.translate(speeda, speeda);
    // else
    //     obj2.translate(-speeda, -speeda);

    // setColor(COLOR_BLUE, 20);
    // obj2.drawCircle_Fill(20, 270, 360);

    // Scale object

    // Orbit object
    // float radius = 100;
    // float speed = 0;
    // if (obj1.orbitAngle >= 180)
    //     obj1.orbitFlag = false;
    // else if (obj1.orbitAngle <= 0)
    //     obj1.orbitFlag = true;

    // if (obj1.orbitFlag)
    //     obj1.orbit(obj2.anchorX, obj2.anchorY, radius, speed);
    // else
    //     obj1.orbit(obj2.anchorX, obj2.anchorY, radius, -speed);

    // obj1.drawCircle_Fill(100, 0, 60);

    // setColor(COLOR_GREEN, 50);
    // // rotate object
    // if (obj1.orientation >= 180)
    //     obj1.rotateFlag = false;
    // else if (obj1.orientation <= 0)
    //     obj1.rotateFlag = true;

    // if (obj1.rotateFlag)
    //     obj1.rotate(1);
    // else
    //     obj1.rotate(-1);

    // obj1.drawCircle_Fill(50, 0, 300);

    // todo implement speed interpolation

    // obj3.drawSineCurve(0, 360 * 2); // for fun...

    glutSwapBuffers();   // Swap foreground and background frames.
    glutPostRedisplay(); // Update the canvas display.
    glFlush();
    glFinish();
}
