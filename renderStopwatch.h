#ifndef RENDERSTOPWATCH_H
#define RENDERSTOPWATCH_H
void timerFunction()
{
    if (ObjStopwatch.stopwatchState == StopwatchState::RUNNING)
    {
        auto elapsedTime = chrono::high_resolution_clock::now() - ObjStopwatch.stopwatchStartTime;
        auto elapsedTimeSec = chrono::duration_cast<chrono::seconds>(elapsedTime).count();
        auto elapsedTimeMin = chrono::duration_cast<chrono::minutes>(elapsedTime).count();
        auto elapsedTimeMilli = chrono::duration_cast<chrono::milliseconds>(elapsedTime).count() % 1000;

        stringstream minSecss, milliss;
        minSecss << setfill('0') << setw(2) << elapsedTimeMin << ":" << setw(2) << elapsedTimeSec;
        milliss << setfill('0') << setw(3) << elapsedTimeMilli;

        ObjStopwatch.elapsedMinSec = minSecss.str();
        ObjStopwatch.elapsedMilli = milliss.str();
    }
}

void renderStopwatch()
{

    // variables

    // Duration
    float uiDuration = 400;

    // Easing
    const float *ui_OpactEasing = EASEINOUT3;

    // Color
    if (ObjStopwatch.stopwatchState == StopwatchState::IDLE)
        ObjStopwatch.stopwatchIcon.setColor(COLOR_WHITE);
    else if (ObjStopwatch.stopwatchState == StopwatchState::RUNNING)
        ObjStopwatch.stopwatchIcon.setColor(COLOR_THEME_GREEN);
    else if (ObjStopwatch.stopwatchState == StopwatchState::PAUSED)
        ObjStopwatch.stopwatchIcon.setColor(COLOR_ORANGE);

    // Drawing
    ObjStopwatch.bg.drawRoundedRect_Fill(UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, UI_SCREEN_ROUND_RADIUS);
    ObjStopwatch.stopwatchIcon.drawStopwatch_Fill(30);
    ObjStopwatch.stopwatchLabel.drawText("STOPWATCH", 7);
    char cMinSec[6], cMilli[4];
    strcpy(cMinSec, ObjStopwatch.elapsedMinSec.c_str());
    strcpy(cMilli, ObjStopwatch.elapsedMilli.c_str());
    ObjStopwatch.elapsedTimeText.drawText(cMinSec, 10);
    ObjStopwatch.elapsedTimeMilliText.drawText(cMilli, 10);

    // Initiate animation
    if (ObjStopwatch.animState == AnimState::IDLE)
    {
        ObjStopwatch.animState = AnimState::ANIMATING;
        toggleAnimationFlag(ObjStopwatch.bg, false, false, false, true, false);
        toggleAnimationFlag(ObjStopwatch.stopwatchIcon, false, false, false, true, false);
        toggleAnimationFlag(ObjStopwatch.stopwatchLabel, false, false, false, true, false);
        toggleAnimationFlag(ObjStopwatch.elapsedTimeText, false, false, false, true, false);
        toggleAnimationFlag(ObjStopwatch.elapsedTimeMilliText, false, false, false, true, false);
        ObjStopwatch.animStartTime = chrono::high_resolution_clock::now();
    }

    // ---- Animate
    if (ObjStopwatch.animState == AnimState::ANIMATING)
    {
        chrono::high_resolution_clock::time_point currentTime = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> elapsedTime = currentTime - ObjStopwatch.animStartTime;

        animateOpacity(ObjStopwatch.bg, uiDuration, ui_OpactEasing, 100);
        animateOpacity(ObjStopwatch.stopwatchIcon, uiDuration, ui_OpactEasing, 100);
        animateOpacity(ObjStopwatch.stopwatchLabel, uiDuration, ui_OpactEasing, 100);
        animateOpacity(ObjStopwatch.elapsedTimeText, uiDuration, ui_OpactEasing, 100);
        animateOpacity(ObjStopwatch.elapsedTimeMilliText, uiDuration, ui_OpactEasing, 100);
        if (elapsedTime.count() >= uiDuration && (!isBusyAnimating(ObjStopwatch.bg) && !isBusyAnimating(ObjStopwatch.elapsedTimeText)))
            ObjStopwatch.animState = AnimState::DONE;
    }

    if (ObjStopwatch.animState == AnimState::DONE)
        timerFunction();
}

#endif