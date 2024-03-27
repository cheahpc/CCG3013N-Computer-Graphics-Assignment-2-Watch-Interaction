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

// anchorX, anchorY, scaleFactor, orientation, *color, opacity, orbitRadius, orbitAngle

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

Object bg = Object();
void renderBackground()
{
    // Coordinates
    GLint x[4] = {-WINDOWS_WIDTH / 2, -WINDOWS_WIDTH / 2, WINDOWS_WIDTH / 2, WINDOWS_WIDTH / 2};
    GLint y[4] = {-WINDOWS_HEIGHT / 2, WINDOWS_HEIGHT / 2, WINDOWS_HEIGHT / 2, -WINDOWS_HEIGHT / 2};

    // Draw the background
    bg.setColor(COLOR_THEME_GREEN_1, 100);
    bg.drawQuad_Fill(x, y);
}

void renderMaster()
{
    renderInit(); // Initialize the canvas

    // Debugging
    // renderDebug(); // For debugging only
    // renderDebugControlTest(); // For debugging only

    // Background
    renderBackground(); // Draw the background
    renderGrid();       // Draw the grid

    glutSwapBuffers();   // Swap foreground and background frames.
    glutPostRedisplay(); // Update the canvas display.
    glFlush();
    glFinish();
}
