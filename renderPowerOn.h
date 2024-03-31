#ifndef RENDER_POWER_ON_H
#define RENDER_POWER_ON_H

void renderPowerOn()
{

    // ---- Variables
    // Easing
    const float *bgEasing = EASEOUT3;
    const float *indicatorEasing = EASEOUT3;
    const float *loadingRing1Easing = EASEINOUT1;
    const float *logoEasing = EASEINOUT2;

    // Durations
    float bgDuration = 1000;
    float indicatorDuration = 1000;
    float loadingRing1Duration = 3000;
    float logoDuration = 1000;

    // Start Times
    float indicatorStartTime = bgDuration;                              // After BG finish
    float loadingRing1StartTime = bgDuration + 800;                     // Before logo start
    float logoStartTime = loadingRing1StartTime + loadingRing1Duration; // After loading ring 1 finish
    float loadingTextStartTime = 7000;

    // Translate Values
    float logoTranslateYVal = 120;
    float textSize = 3;

    // ---- Drawing
    ObjPowerOn.bg.drawRoundedRect_Fill(UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, UI_SCREEN_ROUND_RADIUS);
    ObjPowerOn.indicator.drawCircle_Fill(10, 0, 360);
    ObjPowerOn.logo.drawText("OppsOS", 7);
    ObjPowerOn.loadingRing.drawCircle_Line(60, 0, ObjPowerOn.loadingRing_Null.anchorX, 15);

    // Initiate animation
    if (ObjPowerOn.pOnAnimState == AnimState::IDLE)
    {
        cout << "Power on triggered..." << endl;
        cout << "System is powering on..." << endl;
        ObjPowerOn.pOnAnimState = AnimState::ANIMATING;
        System.currentScreen = Screen::POWERING_ON;
        toggleAnimationFlag(ObjPowerOn.bg, false, false, false, true, false);
        toggleAnimationFlag(ObjPowerOn.indicator, false, false, false, true, false);
        toggleAnimationFlag(ObjPowerOn.logo, true, false, false, true, false);
        toggleAnimationFlag(ObjPowerOn.loadingRing, true, false, false, true, false);
        toggleAnimationFlag(ObjPowerOn.loadingRing_Null, true, false, false, false, false);
        ObjPowerOn.pOnStartTime = chrono::high_resolution_clock::now();
    }
    // ---- Animate
    if (ObjPowerOn.pOnAnimState == AnimState::ANIMATING)
    {
        // get elapsed time
        chrono::high_resolution_clock::time_point currentTime = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> elapsedTime = currentTime - ObjPowerOn.pOnStartTime;

        // 1 - Boot UI BG
        animateOpacity(ObjPowerOn.bg, logoDuration, logoEasing, 100);

        // 2 - Boot Indicator
        if (elapsedTime.count() >= bgDuration)
            animateOpacity(ObjPowerOn.indicator, indicatorDuration, indicatorEasing, 100);

        // 3 - Loading Ring 1
        if (elapsedTime.count() >= loadingRing1StartTime)
            animateTranslate(ObjPowerOn.loadingRing_Null, loadingRing1Duration, loadingRing1Easing, 360, 0);

        // 3 - Boot Logo
        if (elapsedTime.count() >= logoStartTime)
        {
            animateTranslate(ObjPowerOn.loadingRing, logoDuration, logoEasing, 0, logoTranslateYVal);
            animateOpacity(ObjPowerOn.loadingRing, logoDuration, logoEasing, -100);
            animateTranslate(ObjPowerOn.logo, logoDuration, logoEasing, 0, logoTranslateYVal);
            animateOpacity(ObjPowerOn.logo, logoDuration, logoEasing, 100);
        }
        //  4 - Loading Text
        if (elapsedTime.count() >= loadingTextStartTime)
        {
            int index = static_cast<int>(elapsedTime.count() / 1000) % 4; // There are 4 variations

            // Draw the text using the calculated index
            switch (index)
            {
            case 0:
                ObjPowerOn.loadingText.drawText("Booting up", textSize);
                break;
            case 1:
                ObjPowerOn.loadingText.drawText("Booting up.", textSize);
                break;
            case 2:
                ObjPowerOn.loadingText.drawText("Booting up..", textSize);
                break;
            case 3:
                ObjPowerOn.loadingText.drawText("Booting up...", textSize);
                break;
            default:
                break;
            }
        }

        // (Too long || Animation is done) == End
        if (elapsedTime.count() >= SYS_P_ON_TIME && (!isBusyAnimating(ObjPowerOn.bg) && !isBusyAnimating(ObjPowerOn.indicator) && !isBusyAnimating(ObjPowerOn.logo) && !isBusyAnimating(ObjPowerOn.loadingRing) && !isBusyAnimating(ObjPowerOn.loadingRing_Null)))
        {
            System.state = SystemState::ON;
            System.currentScreen = Screen::MAIN;

            // Reset animation state
            ObjPowerOn.pOnAnimState = AnimState::IDLE;
            cout << "Boot completed..." << endl;

            // Reset objects
            ObjPowerOn.bg.setOpacity(0);
            ObjPowerOn.indicator.setOpacity(0);
            ObjPowerOn.logo.setOpacity(0);
            ObjPowerOn.logo.translateTo(-170, -100);
            ObjPowerOn.loadingRing_Null.translateTo(0, 0);
            ObjPowerOn.loadingRing.translateTo(0, 0);
            ObjPowerOn.loadingRing.setOpacity(100);
        }
    }
}

#endif