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
                switch (System.currentScreen)
                {
                case Screen::NONE:
                case Screen::MAIN:
                    if (!isBusyAnimating(ObjWatch.button))
                    {
                        mouse.leftDown = true;
                        ObjWatch.Button.isDown = true;
                        toggleAnimationFlag(ObjWatch.button, true, false, false, false, false);
                        ObjWatch.Button.downStartTime = chrono::high_resolution_clock::now();
                    }
                    break;
                case Screen::POWER_OFF_CONFIRMATION:
                    ObjPowerOff.pOffConfirmation = PowerOffConfirmation::NO;
                    if (!isBusyAnimating(ObjWatch.button))
                    {
                        mouse.leftDown = true;
                        ObjWatch.Button.isDown = true;
                        toggleAnimationFlag(ObjWatch.button, true, false, false, false, false);
                        ObjWatch.Button.downStartTime = chrono::high_resolution_clock::now();
                    }
                    break;
                default:
                    break;
                }
            }

            // Define comp 4 area
            GLfloat comp4X[2] = {COMPLICATION_X_POS - COMPLICATION_RADIUS,
                                 COMPLICATION_X_POS + COMPLICATION_RADIUS};
            GLfloat comp4Y[2] = {COMPLICATION_Y_POS_4 - COMPLICATION_RADIUS,
                                 COMPLICATION_Y_POS_4 + COMPLICATION_RADIUS};

            if (System.currentScreen == Screen::MAIN)
            {
                // Check if mouse is within the complication 4
                if (inArea(mouse.mouseX, mouse.mouseY, comp4X, comp4Y))
                {
                    cout << "Complication 4 pressed..." << endl;
                    // Toggle 24Hr format
                    System.is24HrFormat = !System.is24HrFormat;
                }
            }

            // Define Yes No area
            GLfloat yesX[2] = {0, 180};
            GLfloat noX[2] = {-180, 0};
            GLfloat yesNoY[2] = {-170, -70};

            // Check if mouse is within the Yes No area
            if (System.currentScreen == Screen::POWER_OFF_CONFIRMATION)
            {
                if (inArea(mouse.mouseX, mouse.mouseY, yesX, yesNoY))
                {
                    cout << "Yes pressed..." << endl;
                    ObjPowerOff.pOffConfirmation = PowerOffConfirmation::YES;
                }
                else if (inArea(mouse.mouseX, mouse.mouseY, noX, yesNoY))
                {
                    cout << "No pressed..." << endl;
                    ObjPowerOff.pOffConfirmation = PowerOffConfirmation::NO;
                }
            }
        }
        if (state == GLUT_UP)
        {
            // Reset button state
            mouse.leftDown = false;
            ObjWatch.Button.isDown = false;
            toggleAnimationFlag(ObjWatch.button, true, false, false, false, false);
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