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
            if (mouseInArea(Mouse.mouseX, Mouse.mouseY, ObjArea.dockX, ObjArea.dockY) && !mouseInArea(Mouse.mouseX, Mouse.mouseY, ObjArea.btnX, ObjArea.btnY) && !mouseInArea(Mouse.mouseX, Mouse.mouseY, ObjArea.bodyX, ObjArea.bodyY) && !mouseInArea(Mouse.mouseX, Mouse.mouseY, ObjArea.dialX, ObjArea.dialY) && !mouseInArea(Mouse.mouseX, Mouse.mouseY, ObjArea.strapX, ObjArea.strapY))
            {
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

            // Complication Area
            if (System.currentScreen == Screen::MAIN)
            {
                // ! complication implementation for 2 and 3
                // Comp 1 Area
                if (mouseInArea(Mouse.mouseX, Mouse.mouseY, ObjArea.compX, ObjArea.comp1Y))
                {
                    cout << "Complication 1 pressed, Switching battery percentage..." << endl;
                    ObjUI.isBatteryPercentageVisible = !ObjUI.isBatteryPercentageVisible;
                }
                // Comp 2 Area
                if (mouseInArea(Mouse.mouseX, Mouse.mouseY, ObjArea.compX, ObjArea.comp2Y))
                {
                    cout << "Complication 2 pressed, switching screen..." << endl;
                    // System.currentScreen = Screen::ALARM;
                }
                // Comp 3 Area
                if (mouseInArea(Mouse.mouseX, Mouse.mouseY, ObjArea.compX, ObjArea.comp3Y))
                {
                    cout << "Complication 3 pressed, switching screen..." << endl;
                    // System.currentScreen = Screen::NONE;
                }

                // Comp 4 Area
                if (mouseInArea(Mouse.mouseX, Mouse.mouseY, ObjArea.compX, ObjArea.comp4Y))
                {
                    cout << "Complication 4 pressed, switching time format..." << endl;
                    System.is24HrFormat = !System.is24HrFormat;
                }

                // Heart Rate Monitor Area
                if (mouseInArea(Mouse.mouseX, Mouse.mouseY, ObjArea.heartRateX, ObjArea.heartRateY))
                {
                    cout << "Heart icon pressed, visualizing heart beat..." << endl;
                    ObjUI.isHeartBeating = !ObjUI.isHeartBeating;
                }
            }

            // Yes No area
            if (System.currentScreen == Screen::POWER_OFF_CONFIRMATION)
            {
                if (mouseInArea(Mouse.mouseX, Mouse.mouseY, ObjArea.yesX, ObjArea.yesNoY))
                    ObjPowerOff.pOffConfirmation = PowerOffConfirmation::YES;
                else if (mouseInArea(Mouse.mouseX, Mouse.mouseY, ObjArea.noX, ObjArea.yesNoY))
                    ObjPowerOff.pOffConfirmation = PowerOffConfirmation::NO;
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