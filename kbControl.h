#ifndef KBCONTROL_H
#define KBCONTROL_H
#include "object.cpp"
#include "color.h"
#include "dimen.h"
#include "renderMaster.h"
#include "renderLegend.h"

void toggle(Object &obj, bool translate, bool rotate, bool scale, bool opacity, bool orbit)
{
    if (translate)
        obj.translateFlag = !obj.translateFlag;
    if (rotate)
        obj.rotateFlag = !obj.rotateFlag;
    if (scale)
        obj.scaleFlag = !obj.scaleFlag;
    if (opacity)
        obj.opacityFlag = !obj.opacityFlag;
    if (orbit)
        obj.orbitFlag = !obj.orbitFlag;
}

bool isBusy(Object &obj)
{
    if (obj.aTranslateState == obj.BUSY || obj.aRotateState == obj.BUSY || obj.aScaleState == obj.BUSY || obj.aOpacityState == obj.BUSY || obj.aOrbitState == obj.BUSY)
        return true;
    else
        return false;
}

void kbControl_Debug_Control(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'v':
        debugObj2.translateFlag = !debugObj2.translateFlag;
        break;
    case 'r':
        debugObj1.rotateFlag = !debugObj1.rotateFlag;
        break;
    case 's':
        debugObj1.scaleFlag = !debugObj1.scaleFlag;
        break;
    case 't':
        debugObj1.opacityFlag = !debugObj1.opacityFlag;
        break;
    case 'o':
        debugObj1.orbitFlag = !debugObj1.orbitFlag;
        break;
    case 'c':
        debugObj1.clockWiseFlag = !debugObj1.clockWiseFlag;
        break;
    case 'a': // All
        debugObj2.translateFlag = !debugObj2.translateFlag;
        debugObj1.rotateFlag = !debugObj1.rotateFlag;
        debugObj1.scaleFlag = !debugObj1.scaleFlag;
        debugObj1.opacityFlag = !debugObj1.opacityFlag;
        debugObj1.orbitFlag = !debugObj1.orbitFlag;
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
        if (debugGrid.opacity == 0)
            debugGrid.opacity = 100;
        else
            debugGrid.opacity = 0;

        break;
    case 'h': // Help - legend
        if (!isBusy(legendHelpText) || !isBusy(legendBg))
        {
            legendShow = !legendShow;
            toggle(legendHelpText, true, false, false, true, false);
            toggle(legendBg, true, false, false, true, false);
        }
        break;
    case 27: // Escape key
        exit(0);
        break;
    }
}

#endif