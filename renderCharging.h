#ifndef RENDER_CHARGING_H
#define RENDER_CHARGING_H

void renderCharging()
{
    if (System.isCharging == true && System.batteryLevel < 100)
        System.batteryLevel += System.chargingRate;

    if (System.batteryLevel > 100)
        System.batteryLevel = 100;

    if (System.state == SystemState::OFF && System.currentScreen == Screen::NONE && System.isCharging == true)
    {
        if (System.batteryLevel == 100)
            System.state = SystemState::POWERING_ON;

        // ---- Variables
        // Battery Level Color
        const float *batteryLevelColor = (System.batteryLevel > 40)   ? COLOR_THEME_GREEN
                                         : (System.batteryLevel > 15) ? COLOR_ORANGE
                                                                      : COLOR_RED;

        // Easing
        const float *bgEasing = EASEOUT3;
        const float *indicatorEasing = EASEOUT3;
        const float *loadingRing1Easing = EASEINOUT1;
        const float *logoEasing = EASEINOUT2;

        // Durations
        float bgDuration = 2400;
        float batteryDuration = 2000;
        float batteryTextDuration = 2000;
        float totalDuration = 2400;

        // Translate Values
        float textSize = 6;

        // ---- Drawing
        ObjCharging.bg.drawRoundedRect_Fill(UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, UI_SCREEN_ROUND_RADIUS);
        ObjCharging.battery.drawBattery_Fill(120, System.batteryLevel, System.isCharging, COLOR_WHITE, batteryLevelColor);

        stringstream btrLvl;
        btrLvl << setfill(' ') << setw(3) << (int)(System.batteryLevel) << "%";
        char cBtrStr[6];
        strcpy(cBtrStr, btrLvl.str().c_str());

        if (System.batteryLevel < 10)
            ObjCharging.chargingText.translateTo(-123, -200);
        else if (System.batteryLevel < 100)
            ObjCharging.chargingText.translateTo(-106, -200);
        else
            ObjCharging.chargingText.translateTo(-87, -200);

        ObjCharging.chargingText.drawText(cBtrStr, textSize);

        // Initiate animation
        if (ObjCharging.chargingAnimState == AnimState::IDLE)
        {
            cout << "Charging animation triggered..." << endl;
            ObjCharging.chargingAnimState = AnimState::ANIMATING;
            toggleAnimationFlag(ObjCharging.bg, false, false, false, true, false);
            toggleAnimationFlag(ObjCharging.battery, false, false, false, true, false);
            toggleAnimationFlag(ObjCharging.chargingText, false, false, false, true, false);
            ObjCharging.chargingAnimStartTime = chrono::high_resolution_clock::now();
        }
        // ---- Animate
        if (ObjCharging.chargingAnimState == AnimState::ANIMATING)
        {
            // get elapsed time
            chrono::high_resolution_clock::time_point currentTime = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> elapsedTime = currentTime - ObjPowerOn.pOnStartTime;

            animateOpacity(ObjCharging.bg, bgDuration, bgEasing, 100);
            animateOpacity(ObjCharging.battery, batteryDuration, indicatorEasing, 100);
            animateOpacity(ObjCharging.chargingText, batteryTextDuration, indicatorEasing, 100);

            // (Too long || Animation is done) == End
            if (elapsedTime.count() >= totalDuration && !(isBusyAnimating(ObjCharging.bg) || isBusyAnimating(ObjCharging.battery) || isBusyAnimating(ObjCharging.chargingText)))
            {
                // Reset animation state
                ObjCharging.chargingAnimState = AnimState::DONE;
                cout << "Charging animation completed..." << endl;
            }
        }
    }

    if (System.isCharging == false && ObjCharging.chargingAnimState == AnimState::DONE)
    {
        cout << "Charging animation reset..." << endl;
        ObjCharging.chargingAnimState = AnimState::IDLE;
        ObjCharging.bg.setOpacity(0);
        ObjCharging.battery.setOpacity(0);
        ObjCharging.chargingText.setOpacity(0);
    }
}

void renderChargingDock()
{
    // ObjCharging.dock.drawRoundedRect_Fill(UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, UI_SCREEN_ROUND_RADIUS);

}

#endif