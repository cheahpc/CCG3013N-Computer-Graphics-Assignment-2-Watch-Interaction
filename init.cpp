#include <GL/glut.h>
#include "dimen.h"
#include "color.h"

void init()
{
    // Initialize the windows
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);                         // Set the display mode to single buffer and RGBA.
    glutInitWindowSize(WINDOWS_WIDTH, WINDOWS_HEIGHT);                    // Set the windows size.
    glutInitWindowPosition(WINDOWS_INITIAL_POS_X, WINDOWS_INITIAL_POS_Y); // Set the windows position.
    glutCreateWindow("Assignment 2");                                     // Set the windows title.

    // Context Settings
    glEnable(GL_LINE_SMOOTH);                          // Enables line anti-aliasing.
    glEnable(GL_BLEND);                                // Enable for proper transparency render.
    glDisable(GL_DEPTH_TEST);                          // Disable depth testing for overlap object. Use for transparency object involved.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Enable transparency.

    // Control Settings
    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF); // Disable key repeat.
}