#ifndef RENDER_WATCH_H
#define RENDER_WATCH_H

// anchorX, anchorY, scaleFactor, orientation, *color, opacity, orbitRadius, orbitAngle
Object watchStrap = Object();
Object watchBody = Object();
Object watchDial = Object(WATCH_DIAL_CENTER_X, WATCH_DIAL_CENTER_Y, 1, 0, COLOR_GOLD, 100);
Object watchButton = Object(WATCH_BUTTON_CENTER_X, WATCH_BUTTON_CENTER_Y, 1, 0, COLOR_GOLD, 100);

bool watchButtonPressed = false; // button press toggle
bool bootingUp = false; // booting animation toggle
chrono::high_resolution_clock::time_point bootStartTime;

void renderWatchStrap()
{
    watchStrap.setColor(COLOR_THEME_GREEN_DARK_1);
    watchStrap.drawRect_Fill(WATCH_STRAP_WIDTH, WATCH_STRAP_HEIGHT);
}

void renderWatchBody()
{
    watchBody.setColor(COLOR_GRAY);
    watchBody.drawRoundedRect_Fill(WATCH_BODY_WIDTH, WATCH_BODY_HEIGHT, WATCH_BODY_ROUND_RADIUS);
}

void renderWatchDial()
{
    watchDial.drawRoundedRect_Fill(WATCH_DIAL_WIDTH, WATCH_DIAL_HEIGHT, WATCH_DIAL_ROUND_RADIUS);
}

void renderWatchButton()
{
    GLfloat xVal;
    GLfloat duration = 100;
    const GLfloat *easing = EASEINOUT3;
    if (watchButtonPressed)
        xVal = -5;
    else
        xVal = 5;

    watchButton.drawRoundedRect_Fill(WATCH_BUTTON_WIDTH, WATCH_BUTTON_HEIGHT, WATCH_BUTTON_ROUND_RADIUS);
    animateTranslate(watchButton, duration, easing, xVal, 0);

    // reset button position when release too early
    if (watchButton.anchorX > WATCH_BUTTON_CENTER_X)
    {
        watchButton.anchorX = WATCH_BUTTON_CENTER_X;
        watchButtonPressed = false;
        toggleAnimationFlag(watchButton, false, false, false, false, false);
    }

    // Booting up animation
    if (watchButtonPressed)
    {
        chrono::high_resolution_clock::time_point currentTime = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> pressTime = currentTime - bootStartTime;
        if (pressTime.count() >= SYSTEM_BOOT_BUTTON_PRESS_TIME)
        {
            bootingUp = true;
            // TODO call the function to start watch booting animation 
        }
    }
}

#endif