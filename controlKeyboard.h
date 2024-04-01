#ifndef CONTROLKEYBOARD_H
#define CONTROLKEYBOARD_H

void ctrlKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'g': // Toggle grid
        ObjDebug.grid.opacity = (ObjDebug.grid.opacity == 100) ? 0 : 100;
        break;
        
    case 'h': // Help - legend
        if (!isBusyAnimating(ObjHelp.hintText) || !isBusyAnimating(ObjHelp.bg))
        {
            ObjHelp.isHelpVisible = ObjHelp.isHelpVisible ? false : true;
            toggleAnimationFlag(ObjHelp.hintText, true, false, false, true, false);
            toggleAnimationFlag(ObjHelp.bg, true, false, false, true, false);
        }
        break;

    case 'a':
        if (System.state != SystemState::OFF && System.state != SystemState::POWERING_OFF)
        {
            if (!ObjUI.lastStepIsLeft)
            {
                ObjUI.stepCount++;
                ObjUI.lastStepIsLeft = true;
            }
        }
        break;
    case 'd':
        if (System.state != SystemState::OFF && System.state != SystemState::POWERING_OFF)
        {
            if (ObjUI.lastStepIsLeft)
            {
                ObjUI.stepCount++;
                ObjUI.lastStepIsLeft = false;
            }
        }
        break;
    case 'q': // Testing
        // ---- Test Power On Animation
        // System.state = SystemState::POWERING_ON;

        // ---- Test After Power On Animation
        // System.state = SystemState::ON;

        // Test timer
        System.currentScreen = ScreenState::TIMER;

        // Test Charging
        // System.isCharging = !System.isCharging;

        // Test Yes on Power Off Confirmation
        // System.state = SystemState::POWERING_OFF_TRIGGERED;
        // Stopwatch test
        // System.currentScreen = ScreenState::STOPWATCH;
        break;

    case 27: // Escape key
        exit(0);
        break;
    }
}

#endif