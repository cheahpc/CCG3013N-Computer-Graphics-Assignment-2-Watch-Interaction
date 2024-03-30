#ifndef CONTROL_H
#define CONTROL_H

void toggleAnimationFlag(Object &obj, bool translate, bool rotate, bool scale, bool opacity, bool orbit)
{
    obj.translateFlag = translate;
    obj.rotateFlag = rotate;
    obj.scaleFlag = scale;
    obj.opacityFlag = opacity;
    obj.orbitFlag = orbit;
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

    if (!(System.is24HrFormat) && local_time->tm_hour == 0)
        time << setfill(' ') << setw(2) << local_time->tm_hour + 12;
    else if (!(System.is24HrFormat) && local_time->tm_hour > 12)
        time << setfill(' ') << setw(2) << local_time->tm_hour - 12;
    else
        time << setfill('0') << setw(2) << local_time->tm_hour;

    time << ":" << setfill('0') << setw(2) << local_time->tm_min;

    return time.str();
}

string getDate()
{
    time_t now = time(nullptr);
    tm *local_time = localtime(&now);

    stringstream date, day;
    date << setfill(' ') << setw(2) << local_time->tm_mday;
    date << " " << asctime(local_time)[4] << asctime(local_time)[5] << asctime(local_time)[6];
    day << asctime(local_time)[0] << asctime(local_time)[1] << asctime(local_time)[2];
    return date.str() + ", " + day.str();
}

string getAMPM()
{
    time_t now = time(nullptr);
    tm *local_time = localtime(&now);

    stringstream ampm;
    if (local_time->tm_hour >= 12)
        ampm << "PM";
    else
        ampm << "AM";
    return ampm.str();
}

string getHeartRate()
{
    default_random_engine rSeed(chrono::system_clock::now().time_since_epoch().count());

    uniform_int_distribution<int> distInterval(3000, 12000);
    int randomInterval = distInterval(rSeed);
    uniform_real_distribution<float> distBaseHeartRate(50, 85);
    int heartRate = distBaseHeartRate(rSeed);
    uniform_real_distribution<float> distHeartRateOffset(0, ObjUI.heartBeatOffset);
    int heartRateOffset = distHeartRateOffset(rSeed);
    uniform_real_distribution<float> distHeartRateOffsetDecay(0, ObjUI.heartBeatOffset / 2);
    int heartRateOffsetDecay = distHeartRateOffsetDecay(rSeed);

    GLfloat currentStep = 0;

    chrono::high_resolution_clock::time_point currentTime = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsedTimeStep = currentTime - ObjUI.stepLastSampleTime;

    if (elapsedTimeStep.count() > ObjUI.stepSamplePeriod)
    {
        System.batteryLevel = System.batteryLevel - System.depletedRate;
        ObjUI.stepLastSampleTime = currentTime;
        currentStep = ObjUI.stepCount - ObjUI.stepLastSampleCount;
        ObjUI.stepLastSampleCount = ObjUI.stepCount;
        if (ObjUI.heartBeatOffset < currentStep)
            ObjUI.heartBeatOffset = currentStep;
    }
    chrono::duration<double, milli> elapsedTimeHeart = currentTime - ObjUI.heartRateLastSampleTime;
    if (elapsedTimeHeart.count() > ObjUI.heartRateInterval)
    {
        cout << "Heart rate refreshed..." << endl;
        System.batteryLevel = System.batteryLevel - System.depletedRate;

        ObjUI.heartRateLastSampleTime = currentTime;
        ObjUI.heartRateInterval = randomInterval;

        ObjUI.heartRateValue = heartRate + ObjUI.heartBeatOffset;
        ObjUI.heartBeatOffset = ObjUI.heartBeatOffset - heartRateOffsetDecay;
        stringstream hr;
        hr << heartRate << " bpm";
        return hr.str();
    }
    else
    {
        stringstream hr;
        hr << ObjUI.heartRateValue << " bpm";
        return hr.str();
    }
}
struct Mouse
{
    int mouseX, mouseY;
    int lastMouseX, lastMouseY;

    chrono::high_resolution_clock::time_point leftDownTime, rightDownTime;
    bool leftDown, rightDown;
} Mouse;

void updateMouse(int x, int y)
{
    // Get Mouse position, convert to canvas position
    Mouse.mouseX = x - WINDOWS_WIDTH / 2;
    Mouse.mouseY = -y + WINDOWS_HEIGHT / 2;
}

struct ObjectArea
{
    GLfloat bodyX[2] = {-WATCH_BODY_WIDTH / 2, WATCH_BODY_WIDTH / 2};
    GLfloat bodyY[2] = {-WATCH_BODY_HEIGHT / 2, WATCH_BODY_HEIGHT / 2};

    // Button Area
    GLfloat btnX[2] = {WATCH_BODY_WIDTH / 2, (WATCH_BODY_WIDTH / 2) + WATCH_BUTTON_WIDTH / 2};
    GLfloat btnY[2] = {WATCH_BUTTON_CENTER_Y - WATCH_BUTTON_HEIGHT / 2, WATCH_BUTTON_CENTER_Y + WATCH_BUTTON_HEIGHT / 2};

    // Dial Area
    GLfloat dialX[2] = {WATCH_DIAL_CENTER_X - WATCH_DIAL_WIDTH / 2, WATCH_DIAL_CENTER_X + WATCH_DIAL_WIDTH / 2};
    GLfloat dialY[2] = {WATCH_DIAL_CENTER_Y - WATCH_DIAL_HEIGHT / 2, WATCH_DIAL_CENTER_Y + WATCH_DIAL_HEIGHT / 2};

    // Charging dock area
    GLfloat dockX[2] = {ObjCharging.dock.anchorX - DOCK_WIDTH / 2, ObjCharging.dock.anchorX + DOCK_WIDTH / 2};
    GLfloat dockY[2] = {ObjCharging.dock.anchorY - DOCK_HEIGHT / 2, ObjCharging.dock.anchorY + DOCK_HEIGHT / 2};

    // Strap Area
    GLfloat strapX[2] = {-WATCH_STRAP_WIDTH / 2, WATCH_STRAP_WIDTH / 2};
    GLfloat strapY[2] = {-WATCH_STRAP_HEIGHT / 2, WATCH_STRAP_HEIGHT / 2};
} ObjArea;

void updateObjArea()
{
    // Charging dock area
    ObjArea.dockX[0] = ObjCharging.dock.anchorX - DOCK_WIDTH / 2;
    ObjArea.dockX[1] = ObjCharging.dock.anchorX + DOCK_WIDTH / 2;
    ObjArea.dockY[0] = ObjCharging.dock.anchorY - DOCK_HEIGHT / 2;
    ObjArea.dockY[1] = ObjCharging.dock.anchorY + DOCK_HEIGHT / 2;
}

bool mouseInArea(GLint x, GLint y, GLfloat *areaX, GLfloat *areaY)
{
    if (x >= areaX[0] && x <= areaX[1] && y >= areaY[0] && y <= areaY[1])
        return true;
    return false;
}

bool objInArea(GLfloat *objX, GLfloat *objY, GLfloat *areaX, GLfloat *areaY)
{
    if (objX[0] >= areaX[0] && objX[1] <= areaX[1] && objY[0] >= areaY[0] && objY[1] <= areaY[1])
        return true;
    return false;
}

#endif