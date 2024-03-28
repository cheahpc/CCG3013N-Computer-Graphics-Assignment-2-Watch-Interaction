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
            GLfloat btnY[2] = {WATCH_BUTTON_CENTER_Y - WATCH_BUTTON_HEIGHT / 2,
                               WATCH_BUTTON_CENTER_Y + WATCH_BUTTON_HEIGHT / 2};
            //    Check if mouse is within the button
            if (inArea(mouse.mouseX, mouse.mouseY, btnX, btnY))
            {
                cout << "Watch button pressed..." << endl;
                // Check if the button is animating
                if (!isBusyAnimating(ObjWatch.button))
                {
                    mouse.leftDown = true;
                    ObjWatch.Button.isDown = true;
                    toggleAnimationFlag(ObjWatch.button, true, false, false, false, false);
                    ObjWatch.Button.downStartTime = chrono::high_resolution_clock::now();
                }
            }

            // Define comp 4 area
            GLfloat comp4X[2] = {COMPLICATION_X_POS - COMPLICATION_RADIUS,
                                 COMPLICATION_X_POS + COMPLICATION_RADIUS};
            GLfloat comp4Y[2] = {COMPLICATION_Y_POS_4 - COMPLICATION_RADIUS,
                                 COMPLICATION_Y_POS_4 + COMPLICATION_RADIUS};

            // Check if mouse is within the complication 4
            if (System.currentScreen == Screen::MAIN)
            {
                if (inArea(mouse.mouseX, mouse.mouseY, comp4X, comp4Y))
                {
                    cout << "Complication 4 pressed..." << endl;
                    // Toggle 24Hr format
                    System.is24HrFormat = !System.is24HrFormat;
                }
            }
        }
        if (state == GLUT_UP)
        {
            // Reset button state
            mouse.leftDown = false;
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