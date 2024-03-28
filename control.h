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

string getTimeNow()
{
    time_t now = time(nullptr);
    tm *local_time = localtime(&now);

    stringstream time;
    time << setfill('0') << setw(2) << local_time->tm_hour;
    time << ":" << setw(2) << local_time->tm_min;
    return time.str();
}

string get_formatted_date()
{
    time_t now = time(nullptr);
    tm *local_time = localtime(&now);

    stringstream date, day;
    date << setfill('0') << setw(2) << local_time->tm_mday;
    date << " " << asctime(local_time)[4] << asctime(local_time)[5] << asctime(local_time)[6];
    day << asctime(local_time)[0] << asctime(local_time)[1] << asctime(local_time)[2];
    return date.str() + ", " + day.str();
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