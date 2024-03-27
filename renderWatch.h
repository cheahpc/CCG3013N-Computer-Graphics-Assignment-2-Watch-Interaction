#ifndef RENDER_WATCH_H
#define RENDER_WATCH_H

// anchorX, anchorY, scaleFactor, orientation, *color, opacity, orbitRadius, orbitAngle
Object watchStrap = Object();
Object watchBody = Object();
Object watchDial = Object(WATCH_DIAL_CENTER_X, WATCH_DIAL_CENTER_Y, 1, 0, COLOR_GOLD, 100);
Object watchButton = Object(WATCH_BUTTON_CENTER_X, WATCH_BUTTON_CENTER_Y, 1, 0, COLOR_GOLD, 100);

bool watchButtonPressed = false; // button press toggle
bool bootingUp = false;          // booting animation toggle
bool bootingUpAnimationToggled = false;
chrono::high_resolution_clock::time_point buttonPressStartTime, bootStartTime;

void renderWatchStrap()
{
    watchStrap.setColor(COLOR_THEME_GREEN_DARK_1);
    watchStrap.drawRect_Fill(WATCH_STRAP_WIDTH, WATCH_STRAP_HEIGHT);
}

void renderWatchBody()
{
    watchBody.setColor(COLOR_BLACK_4);
    watchBody.drawRoundedRect_Fill(WATCH_BODY_WIDTH, WATCH_BODY_HEIGHT, WATCH_BODY_ROUND_RADIUS);

    watchBody.setColor(COLOR_BLACK);
    watchBody.drawRoundedRect_Fill(UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, UI_SCREEN_ROUND_RADIUS);
}

void renderWatchDial()
{
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
        watchButtonPressed = false;
        toggleAnimationFlag(watchButton, false, false, false, false, false);
    }

    // Booting up animation
    if (watchButtonPressed)
    {
        chrono::high_resolution_clock::time_point currentTime = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> pressTime = currentTime - buttonPressStartTime;
        if (pressTime.count() >= SYSTEM_BOOT_BUTTON_PRESS_TIME)
        {
            // Reset button states
            watchButtonPressed = false;
            toggleAnimationFlag(watchButton, false, false, false, false, false);
            bootingUp = true;
            bootStartTime = chrono::high_resolution_clock::now();
        }
    }
}

#endif