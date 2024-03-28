#ifndef RENDER_UI_H
#define RENDER_UI_H

void renderUI_BG()
{
    // Check if system is on
}

void renderMainUI()
{
    if (System.state == SystemState::ON || System.state == SystemState::POWERING_OFF_TRIGGERED)
    {
        // Complications
        float comp1Duration = 1500;
        float comp2Duration = 2000;
        float comp3Duration = 2500;
        float comp4Duration = 3000;

        // Todo Animate in complication

        // DateTime
        float dateTimeADuration = 2200;
        const float *dateTimeAEasing = EASEOUT3;
        float dateTimeYTranslateVal = -70;

        char timeStr[6], dateStr[12];
        strcpy(timeStr, getTimeNow().c_str());
        strcpy(dateStr, getDate().c_str());

        // DateTime
        ObjUI.time.drawText(timeStr, 9);
        ObjUI.date.drawText(dateStr, 5);

        // Initiate animation
        if (ObjUI.animState == AnimState::IDLE)
        {
            ObjUI.animState = AnimState::ANIMATING;
            toggleAnimationFlag(ObjUI.time, true, false, false, true, false);
            toggleAnimationFlag(ObjUI.date, true, false, false, true, false);
            ObjUI.uiAnimationStartTime = chrono::high_resolution_clock::now();
        }

        if (ObjUI.animState == AnimState::ANIMATING)
        {
            // Animate the time and date
            // DateTime
            animateOpacity(ObjUI.time, dateTimeADuration, dateTimeAEasing, 100);
            animateOpacity(ObjUI.date, dateTimeADuration, dateTimeAEasing, 100);
            animateTranslate(ObjUI.time, dateTimeADuration, dateTimeAEasing, 0, dateTimeYTranslateVal);
            animateTranslate(ObjUI.date, dateTimeADuration, dateTimeAEasing, 0, dateTimeYTranslateVal);

            // Check if animation is done
            if (!isBusyAnimating(ObjUI.time) && !isBusyAnimating(ObjUI.date))
            {
                ObjUI.animState = AnimState::DONE;
            }
        }

        // draw the time
    }
}

// TODO 4 complication on the left

// TODO mini analog clock under the digital time display
// TODO step counter on top of the digital time display
// TODO heart rate monitor on top of the digital time display
#endif