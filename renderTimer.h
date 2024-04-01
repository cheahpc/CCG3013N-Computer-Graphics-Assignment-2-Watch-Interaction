#ifndef RENDER_TIMER_H
#define RENDER_TIMER_H

void timerFunction()
{
    if (ObjTimer.timerState == TimerState::RUNNING)
    {
        auto currentTime = chrono::system_clock::now();
        auto elapsedTime = chrono::duration_cast<chrono::seconds>(currentTime - ObjTimer.timerStartTime).count();

        auto currentTimerValue = ObjTimer.totalTimerDuration - elapsedTime;

        ObjTimer.timerSecond = currentTimerValue % 60;
        ObjTimer.timerMinute = (currentTimerValue / 60) % 60;
        ObjTimer.timerHour = (currentTimerValue / 3600);

        if (currentTimerValue <= 0)
        {
            cout << "Timer ended" << endl;
            ObjTimer.timerSecond = 0;
            ObjTimer.timerMinute = 0;
            ObjTimer.timerHour = 0;
            ObjTimer.isTimesUp = true;
            ObjTimer.timerState = TimerState::PAUSED;
        }
    }
}

void renderTimer()
{
    timerFunction();

    // Process timer
    stringstream hourMinSec;
    hourMinSec << setfill('0') << setw(2) << ObjTimer.timerHour << ":" << setw(2) << ObjTimer.timerMinute << ":" << setw(2) << ObjTimer.timerSecond;
    ObjTimer.timerHourMinSec = hourMinSec.str();

    // variables
    // Duration
    float uiDuration = 400;

    // Easing
    const float *ui_OpactEasing = EASEINOUT3;

    // Color
    if (ObjTimer.timerState == TimerState::IDLE)
        ObjTimer.timerIcon.setColor(COLOR_WHITE);
    else if (ObjTimer.timerState == TimerState::RUNNING)
        ObjTimer.timerIcon.setColor(COLOR_THEME_GREEN);
    else if (ObjTimer.timerState == TimerState::PAUSED)
        ObjTimer.timerIcon.setColor(COLOR_ORANGE);

    char cHourMinSec[9];
    strcpy(cHourMinSec, ObjTimer.timerHourMinSec.c_str());

    if (ObjTimer.timerSelectorState == TimerSelectorState::SECOND)
        ObjTimer.selector.translateTo(TIMER_SEC_POS_X, TIMER_SELECTOR_POS_Y);
    else if (ObjTimer.timerSelectorState == TimerSelectorState::MINUTE)
        ObjTimer.selector.translateTo(TIMER_MIN_POS_X, TIMER_SELECTOR_POS_Y);
    else if (ObjTimer.timerSelectorState == TimerSelectorState::HOUR)
        ObjTimer.selector.translateTo(TIMER_HOUR_POS_X, TIMER_SELECTOR_POS_Y);

    // Drawing
    ObjTimer.bg.drawRoundedRect_Fill(UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, UI_SCREEN_ROUND_RADIUS);
    ObjTimer.timerIcon.drawTimer_Fill(30);

    ObjTimer.timerLabel.drawText("TIMER", 7);
    if (ObjTimer.timerState == TimerState::IDLE)
        ObjTimer.selector.drawRoundedRect_Fill(TIMER_SELECTOR_WIDTH, TIMER_SELECTOR_HEIGHT, TIMER_SELECTOR_ROUND_RADIUS);
    ObjTimer.timerText.drawText(cHourMinSec, 10);
    ObjTimer.divider.drawRect_Fill(UI_SCREEN_WIDTH * 0.9, 3);
    if (ObjTimer.timerState == TimerState::IDLE)
        ObjTimer.startBtnText.drawText("START", 7);
    else if (ObjTimer.timerState == TimerState::RUNNING)
        ObjTimer.startBtnText.drawText("PAUSE", 7);
    else if (ObjTimer.timerState == TimerState::PAUSED)
        ObjTimer.startBtnText.drawText("RESET", 7);

    // Initialize animation
    if (ObjTimer.animState == AnimState::IDLE)
    {
        ObjTimer.animState = AnimState::ANIMATING;
        toggleAnimationFlag(ObjTimer.bg, false, false, false, true, false);
        toggleAnimationFlag(ObjTimer.timerIcon, false, false, false, true, false);
        toggleAnimationFlag(ObjTimer.timerLabel, false, false, false, true, false);
        toggleAnimationFlag(ObjTimer.timerText, false, false, false, true, false);
        toggleAnimationFlag(ObjTimer.selector, false, false, false, true, false);
        toggleAnimationFlag(ObjTimer.divider, false, false, false, true, false);
        toggleAnimationFlag(ObjTimer.startBtnText, false, false, false, true, false);
        ObjTimer.animStartTime = chrono::high_resolution_clock::now();
    }

    if (ObjTimer.animState == AnimState::ANIMATING)
    {
        auto currentTime = chrono::high_resolution_clock::now();
        auto elapsedTime = chrono::duration_cast<chrono::milliseconds>(currentTime - ObjTimer.animStartTime).count();
        animateOpacity(ObjTimer.bg, uiDuration, ui_OpactEasing, 100);
        animateOpacity(ObjTimer.timerIcon, uiDuration, ui_OpactEasing, 100);
        animateOpacity(ObjTimer.timerLabel, uiDuration, ui_OpactEasing, 100);
        animateOpacity(ObjTimer.timerText, uiDuration, ui_OpactEasing, 100);
        animateOpacity(ObjTimer.selector, uiDuration, ui_OpactEasing, 100);
        animateOpacity(ObjTimer.divider, uiDuration, ui_OpactEasing, 100);
        animateOpacity(ObjTimer.startBtnText, uiDuration, ui_OpactEasing, 100);

        if (elapsedTime > uiDuration && !(isBusyAnimating(ObjTimer.bg) || isBusyAnimating(ObjTimer.timerIcon) || isBusyAnimating(ObjTimer.timerLabel) || isBusyAnimating(ObjTimer.timerText) || isBusyAnimating(ObjTimer.selector) || isBusyAnimating(ObjTimer.divider) || isBusyAnimating(ObjTimer.startBtnText)))
            ObjTimer.animState = AnimState::DONE;
    }

}

#endif