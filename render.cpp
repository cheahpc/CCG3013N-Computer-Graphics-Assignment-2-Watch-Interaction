#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "dimen.h"
#include "object.cpp"
#include "color.h"

GLfloat angle = 0.0;
GLfloat scale = 1.0;

Object obj1 = Object(300, 200);
Object obj2 = Object();

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
    glColor4fv(COLOR_SILVER);
    debugGrid.drawGrid(10, 1, 0);
    glColor4fv(COLOR_GRAY);
    debugGrid.drawGrid(50, 2, 0);
    glColor4fv(COLOR_BLACK);
    debugGrid.drawGrid(100, 3, 0);

    // Labling the grid
    GLfloat length = 10;
    int thickness = 5;
    glColor4fv(COLOR_BLACK);
    debugGrid.moveTo(-13, -13);
    debugGrid.scale(0.25);
    debugGrid.drawText("0", thickness);
}

void renderMaster()
{
    // Clear the canvas
    renderInit(); // For references only

    renderGrid();

    glColor3fv(COLOR_BLUE);

    // Translate object
    float offsetX = obj2.anchorX;
    float offsetY = obj2.anchorY;
    float speeda = 1;
    if (obj2.anchorX >= 300)
        obj2.translateFlag = false;
    else if (obj2.anchorX <= 0)
        obj2.translateFlag = true;

    if (obj2.translateFlag)
        obj2.translate(speeda, speeda);
    else
        obj2.translate(-speeda, -speeda);

    glColor4f(1.0, 0.0, 0.0, 0.0);
    obj2.drawCircle_Fill(20, 0, 360);
    glColor4fv(COLOR_BLUE);

    // Scale object
    float upperBound = 1.5;
    float lowerBound = 0.2;
    float step = 0.01;
    if (obj1.scaleX > upperBound || obj1.scaleY > upperBound)
    {
        obj1.scaleFlag = false;
    }
    else if (obj1.scaleX < lowerBound || obj1.scaleY < lowerBound)
    {
        obj1.scaleFlag = true;
    }
    if (obj1.scaleFlag)
        obj1.scale(scale += step); // Enlarge
    else
        obj1.scale(scale -= step); // Shrink

    // Orbit object
    float radius = 100;
    float speed = 1;
    if (obj1.orbitAngle >= 180)
        obj1.orbitFlag = false;
    else if (obj1.orbitAngle <= 0)
        obj1.orbitFlag = true;

    if (obj1.orbitFlag)
        obj1.orbit(obj2.anchorX, obj2.anchorY, radius, speed);
    else
        obj1.orbit(obj2.anchorX, obj2.anchorY, radius, -speed);

    obj1.drawCircle_Fill(100, 0, 60);

    glColor3fv(COLOR_YELLOW);

    // rotate object
    if (obj1.orientation >= 180)
        obj1.rotateFlag = false;
    else if (obj1.orientation <= 0)
        obj1.rotateFlag = true;

    if (obj1.rotateFlag)
        obj1.rotate(1);
    else
        obj1.rotate(-1);

    obj1.drawCircle_Fill(50, 0, 300);

    glutSwapBuffers();   // Swap foreground and background frames.
    glutPostRedisplay(); // Update the canvas display.
    glFlush();
    glFinish();
}
