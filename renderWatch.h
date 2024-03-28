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
    ObjWatch.body.drawRoundedRect_Fill(WATCH_BODY_WIDTH, WATCH_BODY_HEIGHT, WATCH_BODY_ROUND_RADIUS);
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
        // watchButtonPressed = false;
        ObjWatch.Button.isDown = false;
        toggleAnimationFlag(ObjWatch.button, false, false, false, false, false);
    }

    // if (watchButtonPressed && !systemRunning)
    if (ObjWatch.Button.isDown)
    {
        // Booting up animation
        chrono::high_resolution_clock::time_point currentTime = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> pressTime = currentTime - ObjWatch.Button.downTime;
        if (pressTime.count() >= SYSTEM_BOOT_BUTTON_PRESS_TIME)
        {
            // Reset button states
            // watchButtonPressed = false;
            ObjWatch.Button.isDown = false;
            toggleAnimationFlag(ObjWatch.button, false, false, false, false, false);
            // bootingUp = true;
            System.poweringUp = true;
            // bootStartTime = chrono::high_resolution_clock::now();
            System.poweringUpStartTime = chrono::high_resolution_clock::now();
        }
    }
    // else if (watchButtonPressed && systemRunning)
    // {
    // Power off animation
    // TODO implement power off time
    // chrono::high_resolution_clock::time_point currentTime = chrono::high_resolution_clock::now();
    // chrono::duration<double, milli> pressTime = currentTime - buttonPressStartTime;
    // if (pressTime.count() >= SYSTEM_SHUTDOWN_BUTTON_PRESS_TIME)
    // {
    // Reset button states
    // watchButtonPressed = false;
    // toggleAnimationFlag(ObjWatch.button, false, false, false, false, false);
    // shuttingDown = true;

    // }
    // }
}

#endif