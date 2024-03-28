#ifndef MOUSECONTROL_H
#define MOUSECONTROL_H


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
                if (!isBusyAnimating(ObjWatch.button))
                {
                    mouse.leftDown = true;
                    // !remove after this
                    cout << "Watch button pressed..." << "mouse.leftDown = " << mouse.leftDown << endl;
                    // watchButtonPressed = true;
                    ObjWatch.Button.isDown = true;
                    toggleAnimationFlag(ObjWatch.button, true, false, false, false, false);
                    // buttonPressStartTime = chrono::high_resolution_clock::now(); // Catch the start time
                    ObjWatch.Button.downTime = chrono::high_resolution_clock::now();
                }
            }
        }
        if (state == GLUT_UP)
        {
            // Reset button state
            mouse.leftDown = false;
            // watchButtonPressed = false;
            ObjWatch.Button.isDown = false;
            toggleAnimationFlag(ObjWatch.button, true, false, false, false, false);
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