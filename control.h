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

struct Mouse
{
    GLint mouseX, mouseY;
    chrono::high_resolution_clock::time_point leftDownTime, rightDownTime;
    bool leftDown, rightDown;
} mouse;

void updateMouse(int x, int y)
{
    // Get mouse position, convert to canvas position
    mouse.mouseX = x - WINDOWS_WIDTH / 2;
    mouse.mouseY = -y + WINDOWS_HEIGHT / 2;
}

bool inArea(GLint x, GLint y, GLfloat *areaX, GLfloat *areaY)
{
    if (x >= areaX[0] && x <= areaX[1] && y >= areaY[0] && y <= areaY[1])
        return true;
    return false;
}
#endif