#ifndef RENDER_CHARGING_H
#define RENDER_CHARGING_H

void chargingStopped()
{
    cout << "Charging stopped...  Battery level: " << System.batteryLevel << endl;
    ObjCharging.chargingAnimState = AnimState::IDLE;
    ObjCharging.bg.setOpacity(0);
    ObjCharging.battery.setOpacity(0);
    ObjCharging.chargingText.setOpacity(0);
}

void renderScreenOffCharging()
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
        cout << "Watch is charging... Battery level: " << System.batteryLevel << endl;
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
        }
    }
}

void renderChargingDock()
{
    ObjCharging.dock.setOpacity(100);
    ObjCharging.dock.setColor(COLOR_THEME_GREEN_DARK_2);
    ObjCharging.dock.drawRoundedRect_Fill(DOCK_WIDTH, DOCK_HEIGHT, DOCK_ROUND_RADIUS);
    ObjCharging.dock.setOpacity(25);
    ObjCharging.dock.setColor(COLOR_WHITE);
    for (int i = 10; i <= 90; i += 5)
        ObjCharging.dock.drawRoundedRect_Fill(DOCK_WIDTH - i, DOCK_HEIGHT - i, DOCK_ROUND_RADIUS - 10);

    ObjCharging.dock.setOpacity(100);
    ObjCharging.dock.setColor(COLOR_GRAY_4);
    ObjCharging.dock.drawCircle_Line(150, 0, 360, 30);

    ObjCharging.dock.drawCircle_Fill(200, 40, 50);
    ObjCharging.dock.drawCircle_Fill(200, 130, 140);
    ObjCharging.dock.drawCircle_Fill(200, 220, 230);
    ObjCharging.dock.drawCircle_Fill(200, 310, 320);

    ObjCharging.dock.setColor(COLOR_THEME_GREEN);
    ObjCharging.dock.drawCircle_Fill(20, 0, 360);
    ObjCharging.dock.drawCircle_Line(30, 0, 360, 5);
    ObjCharging.dock.drawCircle_Line(30, 0, 360, 5);
    ObjCharging.dock.setColor(COLOR_THEME_GREEN);
    ObjCharging.dock.drawCircle_Line(150, 0, 360, 2);

    ObjCharging.dockWire.setOpacity(100);
    ObjCharging.dockWire.translateTo(ObjCharging.dock.anchorX + WINDOWS_WIDTH / 2 + DOCK_WIDTH / 2, ObjCharging.dock.anchorY);
    ObjCharging.dockWire.setColor(COLOR_BLACK_1);
    ObjCharging.dockWire.drawRect_Fill(WINDOWS_WIDTH, 50);

    ObjCharging.dockWire.setOpacity(5);
    ObjCharging.dockWire.setColor(COLOR_GRAY_2);
    for (int i = 2; i <= 40; i += 4)
        ObjCharging.dockWire.drawRect_Fill(WINDOWS_WIDTH, i);

    // Charging dock text
    ObjCharging.dockLabel.setColor(COLOR_THEME_GREEN);
    ObjCharging.dockLabel.scaleTo(0.3);
    ObjCharging.dockLabel.translateTo(ObjCharging.dock.anchorX + 50 - (DOCK_WIDTH / 2), ObjCharging.dock.anchorY - 90 + (DOCK_HEIGHT / 2));
    ObjCharging.dockLabel.drawText("240W", 7);
    ObjCharging.dockLabel.scaleTo(0.25);
    ObjCharging.dockLabel.translateTo(ObjCharging.dock.anchorX + 50 - (DOCK_WIDTH / 2), ObjCharging.dock.anchorY - 130 + (DOCK_HEIGHT / 2));
    ObjCharging.dockLabel.drawText("Charger", 7);
}

#endif