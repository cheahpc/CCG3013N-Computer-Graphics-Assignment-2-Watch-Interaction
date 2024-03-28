#ifndef RENDER_WATCH_H
#define RENDER_WATCH_H

// anchorX, anchorY, scaleFactor, orientation, *color, opacity, orbitRadius, orbitAngle
Object watchStrap = Object(0, 0, 1, 0, COLOR_THEME_GREEN_DARK_1, 100);
Object watchBody = Object(0, 0, 1, 0, COLOR_BLACK_4, 100);
Object watchDial = Object(WATCH_DIAL_CENTER_X, WATCH_DIAL_CENTER_Y, 1, 0, COLOR_GOLD, 100);
Object watchButton = Object(WATCH_BUTTON_CENTER_X, WATCH_BUTTON_CENTER_Y, 1, 0, COLOR_GOLD, 100);

void renderWatchStrap()
{
    // Todo add more texture and details
    watchStrap.drawRect_Fill(WATCH_STRAP_WIDTH, WATCH_STRAP_HEIGHT);
}

void renderWatchBody()
{
    // Todo add more texture and details
    watchBody.drawRoundedRect_Fill(WATCH_BODY_WIDTH, WATCH_BODY_HEIGHT, WATCH_BODY_ROUND_RADIUS);
}

void renderWatchDial()
{
    // Todo add more texture and details
    watchDial.drawRoundedRect_Fill(WATCH_DIAL_WIDTH, WATCH_DIAL_HEIGHT, WATCH_DIAL_ROUND_RADIUS);
}

void renderWatchButton()
{
    GLfloat btnXval = 0;
    GLfloat buttonPressAnimationDuration = 100;
    const GLfloat *btnEasing = EASEINOUT5;
    if (watchButtonPressed)
        btnXval = -5;
    else
        btnXval = 5;

    watchButton.drawRoundedRect_Fill(WATCH_BUTTON_WIDTH, WATCH_BUTTON_HEIGHT, WATCH_BUTTON_ROUND_RADIUS);

    animateTranslate(watchButton, buttonPressAnimationDuration, btnEasing, btnXval, 0);
    // reset button position when release too early
    if (watchButton.anchorX > WATCH_BUTTON_CENTER_X)
    {
        watchButton.anchorX = WATCH_BUTTON_CENTER_X;
        // watchButtonPressed = false;
        watchBtn.isDown = false;
        toggleAnimationFlag(watchButton, false, false, false, false, false);
    }

    // if (watchButtonPressed && !systemRunning)
    if (watchBtn.isDown && !sys.isOn)
    {
        // Booting up animation
        chrono::high_resolution_clock::time_point currentTime = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> pressTime = currentTime - buttonPressStartTime;
        if (pressTime.count() >= SYSTEM_BOOT_BUTTON_PRESS_TIME)
        {
            // Reset button states
            // watchButtonPressed = false;
            watchBtn.isDown = false;
            toggleAnimationFlag(watchButton, false, false, false, false, false);
            // bootingUp = true;
            sys.poweringUp = true;
            // bootStartTime = chrono::high_resolution_clock::now();
            sys.poweringUpStartTime = chrono::high_resolution_clock::now();
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
    // toggleAnimationFlag(watchButton, false, false, false, false, false);
    // shuttingDown = true;

    // }
    // }
}

#endif