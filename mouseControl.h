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

                switch (System.currentScreen)
                {
                case ScreenState::STOPWATCH:

                    switch (ObjStopwatch.stopwatchState)
                    {
                    case StopwatchState::IDLE:
                        cout << "Stopwatch started..." << endl;
                        ObjStopwatch.stopwatchState = StopwatchState::RUNNING;
                        ObjStopwatch.stopwatchStartTime = chrono::high_resolution_clock::now();
                        break;
                    case StopwatchState::RUNNING:
                        cout << "Stopwatch paused..." << endl;
                        ObjStopwatch.stopwatchState = StopwatchState::PAUSED;

                        break;
                    case StopwatchState::PAUSED:
                        cout << "Stopwatch resumed..." << endl;
                        ObjStopwatch.stopwatchState = StopwatchState::IDLE;
                        ObjStopwatch.elapsedMinSec = "00:00";
                        ObjStopwatch.elapsedMilli = "000";
                    }
                }
            }

            // Button Area
            if (mouseInArea(Mouse.mouseX, Mouse.mouseY, ObjArea.btnX, ObjArea.btnY))
            {

                Mouse.leftDown = true;
                ObjWatch.Button.isDown = true;
                ObjWatch.Button.downStartTime = chrono::high_resolution_clock::now();

                cout << "Watch button pressed..." << endl;
                switch (System.currentScreen)
                {
                case ScreenState::POWER_OFF_CONFIRMATION:
                    ObjPowerOff.pOffConfirmation = PowerOffConfirmationState::NO;
                    break;
                case ScreenState::STOPWATCH:
                    cout << "Stopwatch app closed..." << endl;
                    ObjStopwatch.stopwatchState = StopwatchState::IDLE;
                    System.currentScreen = ScreenState::MAIN;

                    ObjStopwatch.bg.setOpacity(0);
                    ObjStopwatch.stopwatchIcon.setOpacity(0);
                    ObjStopwatch.stopwatchLabel.setOpacity(0);
                    ObjStopwatch.elapsedTimeText.setOpacity(0);
                    ObjStopwatch.elapsedTimeMilliText.setOpacity(0);
                    ObjStopwatch.elapsedMinSec = "00:00";
                    ObjStopwatch.elapsedMilli = "000";
                    ObjStopwatch.animState = AnimState::IDLE;
                    break;
                case ScreenState::NONE:
                case ScreenState::MAIN:
                case ScreenState::POWERING_ON:
                case ScreenState::POWERING_OFF:
                default:
                    break;
                }
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

            // Complication Area
            if (System.currentScreen == ScreenState::MAIN)
            {
                // Comp 1 Area
                if (mouseInArea(Mouse.mouseX, Mouse.mouseY, ObjArea.compX, ObjArea.comp1Y))
                {
                    cout << "Complication 1 pressed, Switching battery percentage..." << endl;
                    ObjUI.isBatteryPercentageVisible = !ObjUI.isBatteryPercentageVisible;
                }
                // Comp 2 Area
                if (mouseInArea(Mouse.mouseX, Mouse.mouseY, ObjArea.compX, ObjArea.comp2Y))
                {
                    cout << "Complication 2 pressed, starting stopwatch app..." << endl;
                    System.currentScreen = ScreenState::STOPWATCH;
                }
                // Comp 3 Area
                if (mouseInArea(Mouse.mouseX, Mouse.mouseY, ObjArea.compX, ObjArea.comp3Y))
                {
                    cout << "Complication 3 pressed, starting timer app..." << endl;
                    System.currentScreen = ScreenState::TIMER;
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
            if (System.currentScreen == ScreenState::POWER_OFF_CONFIRMATION)
            {
                if (mouseInArea(Mouse.mouseX, Mouse.mouseY, ObjArea.yesX, ObjArea.yesNoY))
                {
                    cout << "Yes pressed..." << endl;
                    ObjPowerOff.pOffConfirmation = PowerOffConfirmationState::YES;
                }
                else if (mouseInArea(Mouse.mouseX, Mouse.mouseY, ObjArea.noX, ObjArea.yesNoY))
                {
                    cout << "No pressed..." << endl;
                    ObjPowerOff.pOffConfirmation = PowerOffConfirmationState::NO;
                }
            }
        }

        if (state == GLUT_UP)
        {
            Mouse.leftDown = false;
            ObjWatch.Button.isDown = false;
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