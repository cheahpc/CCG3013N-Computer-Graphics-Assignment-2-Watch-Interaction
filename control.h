#ifndef CONTROL_H
#define CONTROL_H

void toggleAnimationFlag(Object &obj, bool translate, bool rotate, bool scale, bool opacity, bool orbit)
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

bool isBusyAnimating(Object &obj)
{
    if (obj.aTranslateState == obj.BUSY || obj.aRotateState == obj.BUSY || obj.aScaleState == obj.BUSY || obj.aOpacityState == obj.BUSY || obj.aOrbitState == obj.BUSY)
        return true;
    else
        return false;
}

#endif