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
        // ---- Variables
        float ui_AnimTotalDuration = 5000;

        // Complications
        float comp1StartTime = 0;
        float comp2StartTime = 0;
        float comp3StartTime = 0;
        float comp4StartTime = 0;

        float comp4TextStartTime = 2000;

        float comp1Duration = 2000;
        float comp2Duration = 2000;
        float comp3Duration = 2000;
        float comp4Duration = 2000;

        float comp4TextDuration = 3000;

        float comp1YTranslateVal = COMPLICATION_Y_POS_1;
        float comp2YTranslateVal = COMPLICATION_Y_POS_2;
        float comp3YTranslateVal = COMPLICATION_Y_POS_3;
        float comp4YTranslateVal = COMPLICATION_Y_POS_4;

        const float *comp1Easing = EASEOUT4;
        const float *comp4Easing = EASEOUT1;

        const float *comp4TextEasing = EASEOUT3;

        string comp4TextStr;
        if (System.is24HrFormat)
            comp4TextStr = "24";
        else
            comp4TextStr = getAMPM();
        char hrFormatStr[3];
        strcpy(hrFormatStr, comp4TextStr.c_str());

        // DateTime
        float dateTimeADuration = 2200;
        float dateTimeYTranslateVal = -70;
        const float *dateTimeAEasing = EASEOUT3;

        char timeStr[6], dateStr[12];
        strcpy(timeStr, getTimeNow().c_str());
        strcpy(dateStr, getDate().c_str());

        // ---- Drawing
        ObjUI.bg.drawRoundedRect_Fill(UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, UI_SCREEN_ROUND_RADIUS);

        ObjUI.time.drawText(timeStr, 9);
        ObjUI.dateBox.drawRoundedRect_Fill(DATE_BOX_WIDTH, DATE_BOX_HEIGHT, DATE_BOX_ROUND_RADIUS);
        ObjUI.date.drawText(dateStr, 5);

        // Complications
        ObjUI.complication1.drawCircle_Fill(COMPLICATION_RADIUS, 0, 360);
        ObjUI.complication2.drawCircle_Fill(COMPLICATION_RADIUS, 0, 360);
        ObjUI.complication3.drawCircle_Fill(COMPLICATION_RADIUS, 0, 360);
        ObjUI.complication4.drawCircle_Line(COMPLICATION_RADIUS, 0, 360, 4);

        ObjUI.comp4Text.drawText(hrFormatStr, COMP4_TEXT_SIZE);

        // Initiate animation
        if (ObjUI.animState == AnimState::IDLE)
        {
            cout << "UI animation triggered..." << endl;
            ObjUI.animState = AnimState::ANIMATING;
            System.currentScreen = Screen::NONE;
            toggleAnimationFlag(ObjUI.time, true, false, false, true, false);
            toggleAnimationFlag(ObjUI.date, true, false, false, true, false);
            toggleAnimationFlag(ObjUI.dateBox, true, false, false, true, false);
            toggleAnimationFlag(ObjUI.complication1, true, false, true, true, false);
            toggleAnimationFlag(ObjUI.complication2, true, false, true, true, false);
            toggleAnimationFlag(ObjUI.complication3, true, false, true, true, false);
            toggleAnimationFlag(ObjUI.complication4, true, false, true, true, false);

            toggleAnimationFlag(ObjUI.comp4Text, false, false, false, true, false);
            ObjUI.animStartTime = chrono::high_resolution_clock::now();
        }
        // ---- Animate
        if (ObjUI.animState == AnimState::ANIMATING)
        {
            // get elapsed time
            chrono::high_resolution_clock::time_point currentTime = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> elapsedTime = currentTime - ObjUI.animStartTime;

            // Animate the time and date
            // DateTime
            animateOpacity(ObjUI.time, dateTimeADuration, dateTimeAEasing, 100);
            animateOpacity(ObjUI.date, dateTimeADuration, dateTimeAEasing, 100);
            animateTranslate(ObjUI.time, dateTimeADuration, dateTimeAEasing, 0, dateTimeYTranslateVal);
            animateTranslate(ObjUI.date, dateTimeADuration, dateTimeAEasing, 0, dateTimeYTranslateVal);
            animateOpacity(ObjUI.dateBox, dateTimeADuration, dateTimeAEasing, 100);
            animateTranslate(ObjUI.dateBox, dateTimeADuration, dateTimeAEasing, 0, dateTimeYTranslateVal);

            // Animate the complications
            if (elapsedTime.count() >= comp1StartTime)
            {
                animateScale(ObjUI.complication1, comp1Duration, comp1Easing, 1);
                animateOpacity(ObjUI.complication1, comp1Duration, comp1Easing, 100);
                animateTranslate(ObjUI.complication1, comp1Duration, comp1Easing, 0, comp1YTranslateVal);
            }
            if (elapsedTime.count() >= comp2StartTime)
            {
                animateScale(ObjUI.complication2, comp2Duration, comp1Easing, 1);
                animateOpacity(ObjUI.complication2, comp2Duration, comp1Easing, 100);
                animateTranslate(ObjUI.complication2, comp2Duration, comp1Easing, 0, comp2YTranslateVal);
            }
            if (elapsedTime.count() >= comp3StartTime)
            {
                animateScale(ObjUI.complication3, comp3Duration, comp1Easing, 1);
                animateOpacity(ObjUI.complication3, comp3Duration, comp1Easing, 100);
                animateTranslate(ObjUI.complication3, comp3Duration, comp1Easing, 0, comp3YTranslateVal);
            }
            if (elapsedTime.count() >= comp4StartTime)
            {
                animateScale(ObjUI.complication4, comp4Duration, comp1Easing, 1);
                animateOpacity(ObjUI.complication4, comp4Duration, comp1Easing, 100);
                animateTranslate(ObjUI.complication4, comp4Duration, comp1Easing, 0, comp4YTranslateVal);
            }

            // Complication 4 Text
            if (elapsedTime.count() >= comp4TextStartTime)
            {
                animateOpacity(ObjUI.comp4Text, comp4TextDuration, comp4TextEasing, 100);
            }

            // (Too long || Animation is done) == End
            if (elapsedTime.count() >= ui_AnimTotalDuration && (!isBusyAnimating(ObjUI.time) && !isBusyAnimating(ObjUI.date) && !isBusyAnimating(ObjUI.complication1) && !isBusyAnimating(ObjUI.complication2) && !isBusyAnimating(ObjUI.complication3) && !isBusyAnimating(ObjUI.complication4) && !isBusyAnimating(ObjUI.comp4Text)))
            {
                // Reset animation state
                ObjUI.animState = AnimState::DONE;
                System.currentScreen = Screen::MAIN;
                cout << "UI animation completed..." << endl;

                // Reset object
                // ObjUI.time.setOpacity(0);
                // ObjUI.date.setOpacity(0);
                // ObjUI.time.translateTo(-90, 70);
                // ObjUI.date.translateTo(-70, 20);
                // ObjUI.complication1.scaleTo(0);
                // ObjUI.complication2.scaleTo(0);
                // ObjUI.complication3.scaleTo(0);
                // ObjUI.complication4.scaleTo(0);
                // ObjUI.complication1.setOpacity(0);
                // ObjUI.complication2.setOpacity(0);
                // ObjUI.complication3.setOpacity(0);
                // ObjUI.complication4.setOpacity(0);
            }
        }

        // draw the time
    }
}

// TODO 4 complication on the left
// TODO import draw heart object drawing

// TODO mini analog clock under the digital time display
// TODO step counter on top of the digital time display
// TODO heart rate monitor on top of the digital time display
#endif