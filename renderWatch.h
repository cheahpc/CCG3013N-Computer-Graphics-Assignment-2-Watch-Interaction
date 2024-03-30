#ifndef RENDER_WATCH_H
#define RENDER_WATCH_H

// anchorX, anchorY, scaleFactor, orientation, *color, opacity, orbitRadius, orbitAngle

void renderWatchStrap()
{
    ObjWatch.strap.translateTo(0, 0);
    ObjWatch.strap.setColor(COLOR_THEME_GREEN_DARK_1);
    ObjWatch.strap.setOpacity(100);
    ObjWatch.strap.drawRect_Fill(WATCH_STRAP_WIDTH, WATCH_STRAP_HEIGHT);

    // Shades
    ObjWatch.strap.setOpacity(40);
    ObjWatch.strap.translateTo(0, WINDOWS_HEIGHT / 2);
    ObjWatch.strap.setColor(COLOR_WHITE);
    ObjWatch.strap.drawRoundedRect_Fill((WATCH_STRAP_WIDTH - 80), (WINDOWS_HEIGHT - WATCH_BODY_HEIGHT) - 50, 50);
    ObjWatch.strap.setColor(COLOR_THEME_GREEN_DARK_1);
    ObjWatch.strap.drawRoundedRect_Fill((WATCH_STRAP_WIDTH - 110), (WINDOWS_HEIGHT - WATCH_BODY_HEIGHT) - 80, 35);
    ObjWatch.strap.setColor(COLOR_THEME_GREEN_DARK_1);
    ObjWatch.strap.drawRoundedRect_Fill((WATCH_STRAP_WIDTH - 150), (WINDOWS_HEIGHT - WATCH_BODY_HEIGHT) - 120, 15);
    ObjWatch.strap.setColor(COLOR_WHITE);
    ObjWatch.strap.translateTo(0, -WINDOWS_HEIGHT / 2);
    ObjWatch.strap.drawRoundedRect_Fill((WATCH_STRAP_WIDTH - 80), (WINDOWS_HEIGHT - WATCH_BODY_HEIGHT) - 50, 50);
    ObjWatch.strap.setColor(COLOR_THEME_GREEN_DARK_1);
    ObjWatch.strap.drawRoundedRect_Fill((WATCH_STRAP_WIDTH - 110), (WINDOWS_HEIGHT - WATCH_BODY_HEIGHT) - 80, 35);
    ObjWatch.strap.setColor(COLOR_THEME_GREEN_DARK_1);
    ObjWatch.strap.drawRoundedRect_Fill((WATCH_STRAP_WIDTH - 150), (WINDOWS_HEIGHT - WATCH_BODY_HEIGHT) - 120, 15);

    // Stripes
    ObjWatch.strap.setColor(COLOR_WHITE);
    ObjWatch.strap.setOpacity(20);

    // for (int i = -80; i <= 80; i += 20)
    // {
    //     ObjWatch.strap.translateTo(i, 0);
    //     ObjWatch.strap.drawRect_Fill(3, WATCH_STRAP_HEIGHT);
    // }
    ObjWatch.strap.translateTo(0, 0);
    ObjWatch.strap.setColor(COLOR_GOLD);
}

void renderWatchBody()
{
    // Todo add more texture and details
    ObjWatch.body.setColor(COLOR_BLACK_4);
    ObjWatch.body.drawRoundedRect_Fill(WATCH_BODY_WIDTH, WATCH_BODY_HEIGHT, WATCH_BODY_ROUND_RADIUS);
    ObjWatch.body.setColor(COLOR_BLACK);
    ObjWatch.body.drawRoundedRect_Fill(UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, UI_SCREEN_ROUND_RADIUS);
}

void renderWatchDial()
{
    // Todo add more texture and details
    ObjWatch.dial.drawRoundedRect_Fill(WATCH_DIAL_WIDTH, WATCH_DIAL_HEIGHT, WATCH_DIAL_ROUND_RADIUS);
}

void renderWatchButton()
{
    // ---- Variables
    GLfloat btnXval = (ObjWatch.Button.isDown)? -5 : 5;
    GLfloat buttonPressAnimationDuration = 100;
    const GLfloat *btnEasing = EASEINOUT5;
 
    // ---- Drawing
    ObjWatch.button.drawRoundedRect_Fill(WATCH_BUTTON_WIDTH, WATCH_BUTTON_HEIGHT, WATCH_BUTTON_ROUND_RADIUS);
    // ---- Animation
    animateTranslate(ObjWatch.button, buttonPressAnimationDuration, btnEasing, btnXval, 0);

    // reset button position when release too early
    if (ObjWatch.button.anchorX > WATCH_BUTTON_CENTER_X)
    {
        ObjWatch.button.anchorX = WATCH_BUTTON_CENTER_X;
        toggleAnimationFlag(ObjWatch.button, false, false, false, false, false);
    }

    if (ObjWatch.Button.isDown)
    {
        // Booting up animation
        chrono::high_resolution_clock::time_point currentTime = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> pressTime = currentTime - ObjWatch.Button.downStartTime;

        if (pressTime.count() >= SYS_P_ON_OFF_BTN_HOLD_TIME)
        {
            // Reset button states
            ObjWatch.Button.isDown = false;
            toggleAnimationFlag(ObjWatch.button, false, false, false, false, false);

            // Check current system state
            if (System.state == SystemState::ON)
            {
                System.state = SystemState::POWERING_OFF_TRIGGERED;
                System.currentScreen = Screen::POWER_OFF_CONFIRMATION;
            }
            else if (System.state == SystemState::OFF && System.batteryLevel >= System.minimumBatteryLevel)
            {
                System.state = SystemState::POWERING_ON;
                System.currentScreen = Screen::POWERING_ON;
            }
        }
    }
}

#endif