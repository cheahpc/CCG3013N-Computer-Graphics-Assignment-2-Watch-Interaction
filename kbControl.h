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
        if (ObjDebug.grid.opacity == 0)
            ObjDebug.grid.opacity = 100;
        else
            ObjDebug.grid.opacity = 0;

        break;
    case 'h': // Help - legend
        if (!isBusyAnimating(ObjLegend.hintText) || !isBusyAnimating(ObjLegend.bg))
        {
            legendShow = !legendShow;
            toggleAnimationFlag(ObjLegend.hintText, true, false, false, true, false);
            toggleAnimationFlag(ObjLegend.bg, true, false, false, true, false);
        }
        break;
    case 'q': // Testing
        System.poweringUp = true;
        bootStartTime = chrono::high_resolution_clock::now();
        System.poweringUpStartTime = chrono::high_resolution_clock::now();
        break;
    case 27: // Escape key
        exit(0);
        break;
    }
}

#endif