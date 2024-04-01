#ifndef RENDER_TIMER_H
#define RENDER_TIMER_H

void timerFunction()
{
}

void renderTimer()
{
    // Start countdown
    // !Working
    if (ObjTimer.timerState == TimerState::RUNNING)
    {
        auto currentTime = chrono::system_clock::now();
        auto elapsedTime = chrono::duration_cast<chrono::seconds>(currentTime - ObjTimer.timerStartTime).count();
        cout << "elapsedTime: " << elapsedTime << endl;
        ObjTimer.timerSecond = ObjTimer.initialSecond - elapsedTime;
        if (ObjTimer.timerSecond < 0)
        {
            ObjTimer.timerSecond = 59;
            ObjTimer.timerMinute--;
        }
        if (ObjTimer.timerMinute < 0)
        {
            ObjTimer.timerMinute = 59;
            ObjTimer.timerHour--;
        }
        if (ObjTimer.timerHour < 0)
        {
            ObjTimer.timerHour = 0;
            ObjTimer.timerMinute = 0;
            ObjTimer.timerSecond = 0;
            ObjTimer.timerState = TimerState::IDLE;
            cout << "Timer ended" << endl;
            // TODO ring the alarm
        }
    }

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
}

#endif