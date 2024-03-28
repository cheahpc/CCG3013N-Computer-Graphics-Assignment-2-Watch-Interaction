#ifndef RENDERMASTER_H
#define RENDERMASTER_H

// Renders
#include "renderdebug.h"
#include "renderBackdrop.h"
#include "renderLegend.h"
#include "renderWatch.h"
#include "renderPowerOn.h"
#include "renderPowerOff.h"
#include "renderUI.h"

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

void renderFinish()
{
    glutSwapBuffers();   // Swap foreground and background frames.
    glutPostRedisplay(); // Update the canvas display.
    glFlush();
    glFinish();
}

void renderMaster()
{
    renderInit(); // Initialize the canvas

    // Debugging
    // renderDebug(); // For debugging only
    // renderDebugControlTest(); // For debugging only

    // UI
    renderBackground(); // Draw the background

    // Watch
    renderWatchStrap();
    renderWatchDial();   // Draw the watch dial
    renderWatchButton(); // Draw the watch button
    renderWatchBody();   // Draw the watch body

    // Power On
    renderPowerOn(); // Draw the booting up UI

    // UI
    renderUI_BG();

// Power Off
    // renderPowerOff(); // Draw the power off UI

    // Legend
    renderLegend(); // Draw the legend

    // Grid Overlay
    renderGrid(); // Draw the grid

    renderFinish(); // Finish the rendering
}

#endif