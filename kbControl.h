#ifndef KBCONTROL_H
#define KBCONTROL_H

void kbControl_Debug_Control(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'v':
        ObjDebug.ctrlTest2.translateFlag = !ObjDebug.ctrlTest2.translateFlag;
        break;
    case 'r':
        ObjDebug.ctrlTest1.rotateFlag = !ObjDebug.ctrlTest1.rotateFlag;
        break;
    case 's':
        ObjDebug.ctrlTest1.scaleFlag = !ObjDebug.ctrlTest1.scaleFlag;
        break;
    case 't':
        ObjDebug.ctrlTest1.opacityFlag = !ObjDebug.ctrlTest1.opacityFlag;
        break;
    case 'o':
        ObjDebug.ctrlTest1.orbitFlag = !ObjDebug.ctrlTest1.orbitFlag;
        break;
    case 'c':
        ObjDebug.ctrlTest1.clockWiseFlag = !ObjDebug.ctrlTest1.clockWiseFlag;
        break;
    case 'a': // All
        ObjDebug.ctrlTest2.translateFlag = !ObjDebug.ctrlTest2.translateFlag;
        ObjDebug.ctrlTest1.rotateFlag = !ObjDebug.ctrlTest1.rotateFlag;
        ObjDebug.ctrlTest1.scaleFlag = !ObjDebug.ctrlTest1.scaleFlag;
        ObjDebug.ctrlTest1.opacityFlag = !ObjDebug.ctrlTest1.opacityFlag;
        ObjDebug.ctrlTest1.orbitFlag = !ObjDebug.ctrlTest1.orbitFlag;
        break;

    case 27: // Escape key
        exit(0);
        break;
    }
}

void kbControl_Main(unsigned char key, int x, int y)
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
        System.state = SystemState::ON;
        ObjUI.animState = AnimState::IDLE;

        // Test Yes on Power Off Confirmation
        // ObjPowerOff.pOffConfirmation = PowerOffConfirmation::YES;

        // Test No on Power Off Confirmation
        // ObjPowerOff.pOffConfirmation = PowerOffConfirmation::NO;

        // Test Charging
        // System.isCharging = !System.isCharging;

        break;

    case 'w': // Testing

        // ---- Test Power On Animation
        // System.state = SystemState::POWERING_ON;

        // ---- Test Heart Beat Animation
        ObjUI.isHeartBeating = !ObjUI.isHeartBeating;
        toggleAnimationFlag(ObjUI.heartIcon, false, false, true, false, false); // Always animate the heart icon scale

        //   ---- Test Power Off Animation
        // System.state = SystemState::POWERING_OFF_TRIGGERED;

        // ---- Test After Power On Animation
        // System.state = SystemState::ON;

        // ---- Test Power Off Animation
        // System.state = SystemState::POWERING_OFF_TRIGGERED;

        // ---- Test complication 4
        // System.is24HrFormat = !System.is24HrFormat;

        // Test No on Power Off Confirmation
        // ObjPowerOff.pOffConfirmation = PowerOffConfirmation::NO;

        break;
    case 27: // Escape key
        exit(0);
        break;
    }
}

#endif