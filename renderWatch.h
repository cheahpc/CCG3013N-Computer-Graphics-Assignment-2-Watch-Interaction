#ifndef RENDER_WATCH_H
#define RENDER_WATCH_H

// anchorX, anchorY, scaleFactor, orientation, *color, opacity, orbitRadius, orbitAngle

void renderWatchStrap()
{
    // Todo add more texture and details
    ObjWatch.strap.drawRect_Fill(WATCH_STRAP_WIDTH, WATCH_STRAP_HEIGHT);
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
    GLfloat btnXval = 0;
    GLfloat buttonPressAnimationDuration = 100;
    const GLfloat *btnEasing = EASEINOUT5;
    if (ObjWatch.Button.isDown)
        btnXval = -5;
    else
        btnXval = 5;

    ObjWatch.button.drawRoundedRect_Fill(WATCH_BUTTON_WIDTH, WATCH_BUTTON_HEIGHT, WATCH_BUTTON_ROUND_RADIUS);

    animateTranslate(ObjWatch.button, buttonPressAnimationDuration, btnEasing, btnXval, 0);
    // reset button position when release too early
    if (ObjWatch.button.anchorX > WATCH_BUTTON_CENTER_X)
    {
        ObjWatch.button.anchorX = WATCH_BUTTON_CENTER_X;
        ObjWatch.Button.isDown = false;
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
                System.state = SystemState::POWERING_OFF_TRIGGERED;
            else if (System.state == SystemState::OFF)
                System.state = SystemState::POWERING_ON;
        }
    }
}

#endif