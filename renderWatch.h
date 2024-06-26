#ifndef RENDER_WATCH_H
#define RENDER_WATCH_H

// anchorX, anchorY, scaleFactor, orientation, *color, opacity, orbitRadius, orbitAngle

void renderWatchStrap()
{
    ObjWatch.strap.translateTo(0, 0);
    ObjWatch.strap.setOpacity(100);
    ObjWatch.strap.setColor(COLOR_THEME_GREEN_DARK_2);
    ObjWatch.strap.drawRect_Fill(WATCH_STRAP_WIDTH, WATCH_STRAP_HEIGHT);

    // Shading
    ObjWatch.strap.setColor(COLOR_WHITE);
    ObjWatch.strap.setOpacity(20);
    for (int i = 5; i < 120; i += 5)
        ObjWatch.strap.drawRect_Fill(WATCH_STRAP_WIDTH - i, WATCH_STRAP_HEIGHT - i);

    ObjWatch.strap.setOpacity(100);
    ObjWatch.strap.setColor(COLOR_THEME_GREEN_DARK_2);
    ObjWatch.strap.drawRect_Fill(80, WATCH_STRAP_HEIGHT);

    ObjWatch.strap.setOpacity(20);
    ObjWatch.strap.setColor(COLOR_THEME_GREEN);
    for (int i = 15; i < 80; i += 5)
        ObjWatch.strap.drawRect_Fill(80 - i, WATCH_STRAP_HEIGHT);
    // Stripes
}

void renderWatchBody()
{
    ObjWatch.body.setOpacity(100);
    ObjWatch.body.setColor(COLOR_BLACK_2);
    ObjWatch.body.drawRoundedRect_Fill(WATCH_BODY_WIDTH, WATCH_BODY_HEIGHT, WATCH_BODY_ROUND_RADIUS);

    ObjWatch.body.setColor(COLOR_WHITE);
    ObjWatch.body.setOpacity(25);
    for (int i = 5; i < 80; i += 5)
        ObjWatch.body.drawRoundedRect_Fill(WATCH_BODY_WIDTH - i, WATCH_BODY_HEIGHT - i, WATCH_BODY_ROUND_RADIUS - i);

    ObjWatch.body.setColor(COLOR_BLACK);
    ObjWatch.body.setOpacity(100);
    ObjWatch.body.drawRoundedRect_Fill(UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, UI_SCREEN_ROUND_RADIUS);
}

void renderWatchDial()
{
    ObjWatch.dial.setOpacity(100);
    ObjWatch.dial.setColor(COLOR_BLACK);
    ObjWatch.dial.drawRoundedRect_Fill(WATCH_DIAL_WIDTH, WATCH_DIAL_HEIGHT, WATCH_DIAL_ROUND_RADIUS);

    ObjWatch.dial.setOpacity(20);
    ObjWatch.dial.setColor(COLOR_GREEN);
    for (int i = 2; i < 10; i += 2)
        ObjWatch.dial.drawRoundedRect_Fill(WATCH_DIAL_WIDTH - i, WATCH_DIAL_HEIGHT - i, WATCH_DIAL_ROUND_RADIUS - i);
}

void renderWatchButton()
{
    // ---- Variables
    // Duration
    GLfloat buttonPressAnimationDuration = 10;

    // Easing
    const GLfloat *btnEasing = EASEINOUT1;

    // ---- Drawing
    ObjWatch.Button.obj.setOpacity(100);
    ObjWatch.Button.obj.setColor(COLOR_BLACK);
    ObjWatch.Button.obj.drawRoundedRect_Fill(WATCH_BUTTON_WIDTH, WATCH_BUTTON_HEIGHT, WATCH_BUTTON_ROUND_RADIUS);

    ObjWatch.Button.obj.setOpacity(25);
    ObjWatch.Button.obj.setColor(COLOR_GREEN);
    for (int i = 2; i < 10; i += 2)
        ObjWatch.Button.obj.drawRoundedRect_Fill(WATCH_BUTTON_WIDTH - i, WATCH_BUTTON_HEIGHT - i, WATCH_BUTTON_ROUND_RADIUS - i);

    // ---- Animation
    if (ObjWatch.Button.isDown)
    {
        ObjWatch.Button.obj.translateTo(WATCH_BUTTON_CENTER_X - 7, WATCH_BUTTON_CENTER_Y);

        chrono::high_resolution_clock::time_point currentTime = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> elapsedTime = currentTime - ObjWatch.Button.downStartTime;

        if (elapsedTime.count() >= SYS_P_ON_OFF_BTN_HOLD_TIME)
        {
            if (System.state == SystemState::ON)
            {
                System.state = SystemState::POWERING_OFF_TRIGGERED;
                System.currentScreen = ScreenState::POWER_OFF_CONFIRMATION;
            }
            else if (System.state == SystemState::OFF && System.batteryLevel >= System.minimumBatteryLevel)
            {
                System.state = SystemState::POWERING_ON;
                System.currentScreen = ScreenState::POWERING_ON;
            }
        }
    }
    else
    {
        ObjWatch.Button.obj.translateTo(WATCH_BUTTON_CENTER_X, WATCH_BUTTON_CENTER_Y);
    }
}

#endif