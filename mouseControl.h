#ifndef MOUSECONTROL_H
#define MOUSECONTROL_H

void mouseControl(GLint button, GLint state, int x, int y)
{
    // Update Mouse position & object area
    updateMouse(x, y);
    updateObjArea();
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
        {
            // Dial Area
            if (mouseInArea(Mouse.mouseX, Mouse.mouseY, ObjArea.dialX, ObjArea.dialY))
            {
                cout << "Watch dial pressed..." << endl;
                // Toggle dial state
                // ObjWatch.Dial.isPressed = !ObjWatch.Dial.isPressed;
            }

            // Dock Area, !Button Area, !Body Area
            if (mouseInArea(Mouse.mouseX, Mouse.mouseY, ObjArea.dockX, ObjArea.dockY) && !mouseInArea(Mouse.mouseX, Mouse.mouseY, ObjArea.btnX, ObjArea.btnY) && !mouseInArea(Mouse.mouseX, Mouse.mouseY, ObjArea.bodyX, ObjArea.bodyY))
            {
                cout << "Charging dock pressed..." << endl;
                // Toggle charging state
                Mouse.leftDown = true;
                ObjCharging.isDragging = true;
                Mouse.lastMouseX = Mouse.mouseX;
                Mouse.lastMouseY = Mouse.mouseY;
                ObjCharging.dockInitialX = ObjCharging.dock.anchorX;
                ObjCharging.dockInitialY = ObjCharging.dock.anchorY;
            }

            // Button Area
            if (mouseInArea(Mouse.mouseX, Mouse.mouseY, ObjArea.btnX, ObjArea.btnY))
            {
                cout << "Watch button pressed..." << endl;
                // Check if the button is animating
                switch (System.currentScreen)
                {
                case Screen::POWER_OFF_CONFIRMATION:
                    ObjPowerOff.pOffConfirmation = PowerOffConfirmation::NO;
                    if (!isBusyAnimating(ObjWatch.button))
                    {
                        Mouse.leftDown = true;
                        ObjWatch.Button.isDown = true;
                        toggleAnimationFlag(ObjWatch.button, true, false, false, false, false);
                        ObjWatch.Button.downStartTime = chrono::high_resolution_clock::now();
                    }
                    break;
                case Screen::NONE:
                case Screen::MAIN:
                case Screen::POWERING_ON:
                case Screen::POWERING_OFF:
                default:
                    if (!isBusyAnimating(ObjWatch.button))
                    {
                        Mouse.leftDown = true;
                        ObjWatch.Button.isDown = true;
                        toggleAnimationFlag(ObjWatch.button, true, false, false, false, false);
                        ObjWatch.Button.downStartTime = chrono::high_resolution_clock::now();
                    }

                    break;
                }
            }

            if (System.currentScreen == Screen::MAIN)
            {
                // Comp 4 Area
                GLfloat comp4X[2] = {COMPLICATION_X_POS - COMPLICATION_RADIUS,
                                     COMPLICATION_X_POS + COMPLICATION_RADIUS};
                GLfloat comp4Y[2] = {COMPLICATION_Y_POS_4 - COMPLICATION_RADIUS,
                                     COMPLICATION_Y_POS_4 + COMPLICATION_RADIUS};

                if (mouseInArea(Mouse.mouseX, Mouse.mouseY, comp4X, comp4Y))
                {
                    cout << "Complication 4 pressed..." << endl;
                    // Toggle 24Hr format
                    System.is24HrFormat = !System.is24HrFormat;
                }

                // Heart Rate Monitor Area
                GLfloat hrX[2] = {10, 190};
                GLfloat hrY[2] = {140, 210};
                if (mouseInArea(Mouse.mouseX, Mouse.mouseY, hrX, hrY))
                {
                    cout << "Heart Rate Monitor pressed..." << endl;
                    // Toggle Heart Beat Animation
                    ObjUI.isHeartBeating = !ObjUI.isHeartBeating;
                }
            }

            // Define Yes No area
            GLfloat yesX[2] = {0, 180};
            GLfloat noX[2] = {-180, 0};
            GLfloat yesNoY[2] = {-170, -70};

            // Check if Mouse is within the Yes No area
            if (System.currentScreen == Screen::POWER_OFF_CONFIRMATION)
            {
                if (mouseInArea(Mouse.mouseX, Mouse.mouseY, yesX, yesNoY))
                {
                    cout << "Yes pressed..." << endl;
                    ObjPowerOff.pOffConfirmation = PowerOffConfirmation::YES;
                }
                else if (mouseInArea(Mouse.mouseX, Mouse.mouseY, noX, yesNoY))
                {
                    cout << "No pressed..." << endl;
                    ObjPowerOff.pOffConfirmation = PowerOffConfirmation::NO;
                }
            }
        }
        if (state == GLUT_UP)
        {
            Mouse.leftDown = false;
            // Reset button state
            ObjWatch.Button.isDown = false;
            toggleAnimationFlag(ObjWatch.button, true, false, false, false, false);

            // Charging dock area
            ObjCharging.isDragging = false;
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
    // Update Mouse position & object area
    updateMouse(x, y);
    updateObjArea();
    if (Mouse.leftDown && ObjCharging.isDragging)
    {
        int dX = Mouse.mouseX - Mouse.lastMouseX;
        int dY = Mouse.mouseY - Mouse.lastMouseY;
        ObjCharging.dock.translateTo(ObjCharging.dockInitialX + dX, ObjCharging.dockInitialY + dY);

        // Check if out of bound
        if ((ObjCharging.dock.anchorX < -WINDOWS_WIDTH / 2))
            ObjCharging.dock.translateTo(-WINDOWS_WIDTH / 2, ObjCharging.dock.anchorY);
        if ((ObjCharging.dock.anchorX > WINDOWS_WIDTH / 2))
            ObjCharging.dock.translateTo(WINDOWS_WIDTH / 2, ObjCharging.dock.anchorY);
        if ((ObjCharging.dock.anchorY < -WINDOWS_HEIGHT / 2))
            ObjCharging.dock.translateTo(ObjCharging.dock.anchorX, -WINDOWS_HEIGHT / 2);
        if ((ObjCharging.dock.anchorY > WINDOWS_HEIGHT / 2))
            ObjCharging.dock.translateTo(ObjCharging.dock.anchorX, WINDOWS_HEIGHT / 2);

        // Toggle charging state
        if (objInArea(ObjArea.bodyX, ObjArea.bodyY, ObjArea.dockX, ObjArea.dockY))
            System.isCharging = true;
        else
            System.isCharging = false;
    }

    glutPostRedisplay();
}

#endif