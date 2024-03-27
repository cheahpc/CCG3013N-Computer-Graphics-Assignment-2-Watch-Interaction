#ifndef MOUSECONTROL_H
#define MOUSECONTROL_H
struct Mouse
{
    GLint mouseX, mouseY;
    int timerID;
    chrono::high_resolution_clock::time_point leftDownTime, rightDownTime;
    bool leftDown, rightDown;
} mouse;

void updateMouse(int x, int y)
{
    // Get mouse position, convert to canvas position
    mouse.mouseX = x - WINDOWS_WIDTH / 2;
    mouse.mouseY = -y + WINDOWS_HEIGHT / 2;
}

bool inArea(GLint x, GLint y, GLfloat *areaX, GLfloat *areaY)
{
    if (x >= areaX[0] && x <= areaX[1] && y >= areaY[0] && y <= areaY[1])
        return true;
    return false;
}

void mouseControl(GLint button, GLint state, int x, int y)
{
    // Get mouse position
    updateMouse(x, y);

    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
        {
            // Define button area
            GLfloat btnX[2] = {WATCH_BODY_WIDTH / 2,
                               (WATCH_BODY_WIDTH / 2) + WATCH_BUTTON_WIDTH / 2};
            GLfloat btnY[2] = { WATCH_BUTTON_CENTER_Y - WATCH_BUTTON_HEIGHT / 2,
                                WATCH_BUTTON_CENTER_Y + WATCH_BUTTON_HEIGHT / 2 };
            //    Check if mouse is within the button
            if (inArea(mouse.mouseX, mouse.mouseY, btnX, btnY))
            {
                // Check if the button is animating
                if (!isBusyAnimating(watchButton))
                {
                    cout << "Watch button pressed..." << endl;
                    mouse.leftDown = true;
                    watchButtonPressed = true;
                    toggleAnimationFlag(watchButton, true, false, false, false, false);
                    buttonPressStartTime = chrono::high_resolution_clock::now(); // Catch the start time
                }
            }
        }
        if (state == GLUT_UP)
        {
            // Reset button state
            mouse.leftDown = false;
            watchButtonPressed = false;
            toggleAnimationFlag(watchButton, true, false, false, false, false);
            cout << "Watch button released..." << endl;
        }
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
        {
        }
        if (state == GLUT_UP)
        {
        }
        break;
    }
}
void mouseMoveControl(GLint x, GLint y)
{
    // Update mouse position
    updateMouse(x, y);

    glutPostRedisplay();
}

#endif