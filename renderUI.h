#ifndef RENDER_UI_H
#define RENDER_UI_H

void renderMainUI()
{

    // ---- Variables
    // Start Time
    float comp1StartTime = 0;
    float comp2StartTime = 200;
    float comp3StartTime = 400;
    float comp4StartTime = 600;
    float compContentStartTime = 1500;
    float heartStepStartTime = 1500;

    // Duration
    float comp1Duration = 1000;
    float comp2Duration = 1100;
    float comp3Duration = 1200;
    float comp4Duration = 1300;
    float compContentDuration = 1000;
    float dateTimeADuration = 2500;
    float heartStepDuration = 1000;
    float heartBeatDuration = (60 / ObjUI.heartRateValue / 2) * 1000;

    // Translate Value
    float comp1YTranslateVal = 0;
    float comp2YTranslateVal = -(COMPLICATION_Y_POS_1 - COMPLICATION_Y_POS_2);
    float comp3YTranslateVal = -(COMPLICATION_Y_POS_1 - COMPLICATION_Y_POS_3);
    float comp4YTranslateVal = -(COMPLICATION_Y_POS_1 - COMPLICATION_Y_POS_4);
    float dateTimeYTranslateVal = -70;

    // Scale Value
    float heartBeatScaleVal = ObjUI.isHeartBeatUp ? 0.7 : -0.7;

    // Color Value
    const float *batteryLevelColor = (System.batteryLevel > 40)   ? COLOR_THEME_GREEN
                                     : (System.batteryLevel > 15) ? COLOR_ORANGE
                                                                  : COLOR_RED;

    // Easing
    float ui_AnimTotalDuration = 10000;
    const float *ui_OpactEasing = EASEINOUT3;
    const float *compRingEasing = EASEOUT4;
    const float *dateTimeAEasing = EASEOUT3;
    const float *compContentEasing = EASEOUT4;

    const float *heartBeatEasing = ObjUI.isHeartBeatUp ? EASEIN3 : EASEOUT3;

    string comp4TextStr = System.is24HrFormat ? "24" : getAMPM();
    char hrFormatStr[3];
    strcpy(hrFormatStr, comp4TextStr.c_str());

    char timeStr[6], dateStr[12];
    strcpy(timeStr, getTimeNow().c_str());
    strcpy(dateStr, getDate().c_str());

    // ---- Drawing
    // Background
    ObjUI.bg.drawRoundedRect_Fill(UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, UI_SCREEN_ROUND_RADIUS);

    // DateTime
    ObjUI.time.drawText(timeStr, 9);
    ObjUI.dateBox.drawRoundedRect_Fill(DATE_BOX_WIDTH, DATE_BOX_HEIGHT, DATE_BOX_ROUND_RADIUS);
    ObjUI.date.drawText(dateStr, 5);

    // Heart Rate Monitor
    char hrStr[10];
    strcpy(hrStr, getHeartRate().c_str());
    ObjUI.heartRate.drawText(hrStr, 3);
    ObjUI.heartIcon.drawHeart_Fill(30);

    // Step Counter
    stringstream stepCountss;
    stepCountss << ObjUI.stepCount << endl;
    char stepCountStr[5];
    strcpy(stepCountStr, stepCountss.str().c_str());

    if (ObjUI.stepCount < 10)
        ObjUI.stepCountText.translateTo(23, -150);
    else if (ObjUI.stepCount < 100)
        ObjUI.stepCountText.translateTo(4, -150);
    else if (ObjUI.stepCount < 1000)
        ObjUI.stepCountText.translateTo(-15, -150);
    else
        ObjUI.stepCountText.translateTo(-40, -150);

    ObjUI.stepCountText.drawText(stepCountStr, 3);
    ObjUI.stepStepText.drawText("STEPS", 5);

    // Complications
    ObjUI.complication1.setColor(COLOR_THEME_GREEN_DARK_2);
    ObjUI.complication1.drawCircle_Fill(COMPLICATION_RADIUS - 8, 0, 360);
    ObjUI.complication1.setColor(batteryLevelColor);
    ObjUI.complication1.drawCircle_Line(COMPLICATION_RADIUS, 0, System.batteryLevel * 3.6, 8);
    ObjUI.complication2.drawCircle_Fill(COMPLICATION_RADIUS, 0, 360);
    ObjUI.complication3.drawCircle_Fill(COMPLICATION_RADIUS, 0, 360);
    ObjUI.complication4.drawCircle_Line(COMPLICATION_RADIUS, 0, 360, 4);
    // Complications Content
    if (ObjUI.isBatteryPercentageVisible)
    {
        stringstream batteryLevelss;
        batteryLevelss << (int)System.batteryLevel << "%" << endl;
        char batteryLevelStr[5];
        strcpy(batteryLevelStr, batteryLevelss.str().c_str());
        if (System.batteryLevel < 10)
            ObjUI.comp1BatteryText.translateTo(COMPLICATION_X_POS - 14, 185);
        else if (System.batteryLevel < 100)
            ObjUI.comp1BatteryText.translateTo(COMPLICATION_X_POS - 22, 185);
        else
            ObjUI.comp1BatteryText.translateTo(COMPLICATION_X_POS - 30, 185);
        ObjUI.comp1BatteryText.drawText(batteryLevelStr, COMP1_BATTERY_TEXT_SIZE);
    }
    else
    {
        ObjUI.comp1Battery.drawBattery_Fill(20, System.batteryLevel, System.isCharging, COLOR_WHITE, batteryLevelColor);
    }
    ObjUI.comp2Timer.drawStopwatch_Fill(20);
    ObjUI.comp3Alarm.drawTimer_Fill(20);
    ObjUI.comp4Text.drawText(hrFormatStr, COMP4_TEXT_SIZE);

    if (ObjUI.isHeartBeating)
    {
        animateScale(ObjUI.heartIcon, heartBeatDuration, heartBeatEasing, heartBeatScaleVal);
        if (!isBusyAnimating(ObjUI.heartIcon))
        {
            toggleAnimationFlag(ObjUI.heartIcon, false, false, true, false, false); // Always animate the heart icon scale
            ObjUI.isHeartBeatUp = (ObjUI.heartIcon.scaleFactor == 1) ? true : false;
            System.batteryLevel = System.batteryLevel - 0.02;
        }
    }

    // Initiate animation
    if (ObjUI.animState == AnimState::IDLE)
    {
        ObjUI.animState = AnimState::ANIMATING;
        toggleAnimationFlag(ObjUI.time, true, false, false, true, false);
        toggleAnimationFlag(ObjUI.date, true, false, false, true, false);
        toggleAnimationFlag(ObjUI.dateBox, true, false, false, true, false);
        toggleAnimationFlag(ObjUI.heartIcon, false, false, false, true, false);
        toggleAnimationFlag(ObjUI.heartRate, false, false, false, true, false);
        toggleAnimationFlag(ObjUI.stepCountText, false, false, true, true, false);
        toggleAnimationFlag(ObjUI.stepStepText, false, false, true, true, false);
        toggleAnimationFlag(ObjUI.complication1, true, false, true, true, false);
        toggleAnimationFlag(ObjUI.complication2, true, false, true, true, false);
        toggleAnimationFlag(ObjUI.complication3, true, false, true, true, false);
        toggleAnimationFlag(ObjUI.complication4, true, false, true, true, false);
        toggleAnimationFlag(ObjUI.comp1Battery, false, false, false, true, false);
        toggleAnimationFlag(ObjUI.comp2Timer, false, false, false, true, false);
        toggleAnimationFlag(ObjUI.comp3Alarm, false, false, false, true, false);
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
        animateOpacity(ObjUI.time, dateTimeADuration, ui_OpactEasing, 100);
        animateOpacity(ObjUI.date, dateTimeADuration, ui_OpactEasing, 100);
        animateOpacity(ObjUI.dateBox, dateTimeADuration, ui_OpactEasing, 100);

        if (elapsedTime.count() >= heartStepStartTime)
        {
            animateOpacity(ObjUI.heartIcon, heartStepDuration, ui_OpactEasing, 100);
            animateOpacity(ObjUI.heartRate, heartStepDuration, ui_OpactEasing, 100);
            animateOpacity(ObjUI.stepCountText, heartStepDuration, ui_OpactEasing, 100);
            animateOpacity(ObjUI.stepStepText, heartStepDuration, ui_OpactEasing, 100);
        }

        animateTranslate(ObjUI.time, dateTimeADuration, dateTimeAEasing, 0, dateTimeYTranslateVal);
        animateTranslate(ObjUI.date, dateTimeADuration, dateTimeAEasing, 0, dateTimeYTranslateVal);
        animateTranslate(ObjUI.dateBox, dateTimeADuration, dateTimeAEasing, 0, dateTimeYTranslateVal);

        // Animate the complications
        if (elapsedTime.count() >= comp1StartTime) // Complication 1
        {
            animateScale(ObjUI.complication1, comp1Duration, compRingEasing, 1);
            animateOpacity(ObjUI.complication1, comp1Duration, ui_OpactEasing, 100);
        }
        if (elapsedTime.count() >= comp2StartTime) // Complication 2
        {
            animateScale(ObjUI.complication2, comp2Duration, compRingEasing, 1);
            animateOpacity(ObjUI.complication2, comp2Duration, ui_OpactEasing, 100);
            animateTranslate(ObjUI.complication2, comp2Duration, compRingEasing, 0, comp2YTranslateVal);
        }
        if (elapsedTime.count() >= comp3StartTime) // Complication 3
        {
            animateScale(ObjUI.complication3, comp3Duration, compRingEasing, 1);
            animateOpacity(ObjUI.complication3, comp3Duration, ui_OpactEasing, 100);
            animateTranslate(ObjUI.complication3, comp3Duration, compRingEasing, 0, comp3YTranslateVal);
        }
        if (elapsedTime.count() >= comp4StartTime) // Complication 4
        {
            animateScale(ObjUI.complication4, comp4Duration, compRingEasing, 1);
            animateOpacity(ObjUI.complication4, comp4Duration, ui_OpactEasing, 100);
            animateTranslate(ObjUI.complication4, comp4Duration, compRingEasing, 0, comp4YTranslateVal);
        }

        // Complication Content
        if (elapsedTime.count() >= compContentStartTime)
        {
            animateOpacity(ObjUI.comp1Battery, compContentDuration, ui_OpactEasing, 100);
            animateOpacity(ObjUI.comp2Timer, compContentDuration, ui_OpactEasing, 100);
            animateOpacity(ObjUI.comp3Alarm, compContentDuration, ui_OpactEasing, 100);
            animateOpacity(ObjUI.comp4Text, compContentDuration, ui_OpactEasing, 100);
        }

        // (Too long || Animation is done) == End
        if (elapsedTime.count() >= ui_AnimTotalDuration || !(isBusyAnimating(ObjUI.time) || isBusyAnimating(ObjUI.date) || isBusyAnimating(ObjUI.dateBox) || isBusyAnimating(ObjUI.heartIcon) || isBusyAnimating(ObjUI.heartRate) || isBusyAnimating(ObjUI.complication1) || isBusyAnimating(ObjUI.complication2) || isBusyAnimating(ObjUI.complication3) || isBusyAnimating(ObjUI.complication4) || isBusyAnimating(ObjUI.comp4Text)))
        {
            // Reset animation state
            ObjUI.animState = AnimState::DONE;
            System.currentScreen = ScreenState::MAIN;
            cout << "Welcome..." << endl;
        }
    }
}
#endif