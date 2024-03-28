#ifndef RENDER_POWER_ON_H
#define RENDER_POWER_ON_H

void renderPowerOn()
{
    // Powering up animation
    // BG
    GLfloat bgDuration = 1000;
    const GLfloat *bgEasing = EASEOUT3;
    // Indicator
    GLfloat indicatorDuration = 1000;
    GLfloat indicatorStartTime = bgDuration; // After BG finish
    const GLfloat *indicatorEasing = EASEOUT3;

    // Loading Ring
    GLfloat loadingRing1Duration = 3000;
    GLfloat loadingRing1StartTime = bgDuration + 800; // Before logo start
    const GLfloat *loadingRing1Easing = EASEINOUT1;

    // Logo
    GLfloat logoTranslateYVal = 120;
    GLfloat logoDuration = 1000;
    GLfloat logoStartTime = loadingRing1StartTime + loadingRing1Duration; // After loading ring 1 finish
    const GLfloat *logoEasing = EASEINOUT2;

    // Loading text
    GLfloat loadingTextStartTime = 7000;
    GLfloat textSize = 5;

    // if (bootingUp)
    if (System.poweringUp)
    {
        ObjPowerOn.bg.drawRoundedRect_Fill(UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, UI_SCREEN_ROUND_RADIUS);
        ObjPowerOn.indicator.drawCircle_Fill(10, 0, 360);
        ObjPowerOn.logo.drawText("OppsOS", 5);
        ObjPowerOn.loadingRing1.drawCircle_Line(60, 0, ObjPowerOn.loadingRing1_null.anchorX, 15);
        // ObjPowerOn.loadingRing1.drawCircle_Line(40, 0, 333, 15);

        // Enable animations for first time
        // if (!bootingUpAnimationToggled)
        if (!System.poweringUpAnimation)
        {
            toggleAnimationFlag(ObjPowerOn.bg, false, false, false, true, false);
            toggleAnimationFlag(ObjPowerOn.indicator, false, false, false, true, false);
            toggleAnimationFlag(ObjPowerOn.logo, true, false, false, true, false);
            toggleAnimationFlag(ObjPowerOn.loadingRing1, true, false, false, true, false);
            toggleAnimationFlag(ObjPowerOn.loadingRing1_null, true, false, false, false, false);

            // bootingUpAnimationToggled = true;
            bootingUpAnimationToggled = System.poweringUpAnimation = true;
        }

        chrono::high_resolution_clock::time_point currentTime = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> bootTime = currentTime - System.poweringUpStartTime;
        if (bootTime.count() >= SYSTEM_BOOT_TIME)
        {
            // Boot completed
            System.poweringUp = false;
            System.isOn = true;
            System.poweringUpAnimation = false;
            cout << "Boot completed..." << endl;
        }
        else
        {
            // 1 - Boot UI BG
            animateOpacity(ObjPowerOn.bg, logoDuration, logoEasing, 100);

            // 2 - Boot Indicator
            if (bootTime.count() >= bgDuration)
            {
                animateOpacity(ObjPowerOn.indicator, indicatorDuration, indicatorEasing, 100);
            }

            // 3 - Loading Ring 1
            if (bootTime.count() >= loadingRing1StartTime)
            {
                animateTranslate(ObjPowerOn.loadingRing1_null, loadingRing1Duration, loadingRing1Easing, 360, 0);
            }

            // 3 - Boot Logo
            if (bootTime.count() >= logoStartTime)
            {
                animateTranslate(ObjPowerOn.loadingRing1, logoDuration, logoEasing, 0, logoTranslateYVal);
                animateOpacity(ObjPowerOn.loadingRing1, logoDuration, logoEasing, -100);
                animateTranslate(ObjPowerOn.logo, logoDuration, logoEasing, 0, logoTranslateYVal);
                animateOpacity(ObjPowerOn.logo, logoDuration, logoEasing, 100);
            }

            if (bootTime.count() >= loadingTextStartTime)
            {
                int index = static_cast<int>(bootTime.count() / 1000) % 4; // There are 4 variations

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

            cout << "Booting up..." << endl;
        }
    }
}

#endif