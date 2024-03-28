#ifndef RENDER_POWER_ON_H
#define RENDER_POWER_ON_H

void renderPowerOn()
{

    if (System.state == SystemState::POWERING_ON)
    {
        // ---- Variables
        // Powering up animation
        float bgDuration = 1000;
        const float *bgEasing = EASEOUT3;
        // Indicator
        float indicatorDuration = 1000;
        float indicatorStartTime = bgDuration; // After BG finish
        const float *indicatorEasing = EASEOUT3;

        // Loading Ring
        float loadingRing1Duration = 3000;
        float loadingRing1StartTime = bgDuration + 800; // Before logo start
        const float *loadingRing1Easing = EASEINOUT1;

        // Logo
        float logoTranslateYVal = 120;
        float logoDuration = 1000;
        float logoStartTime = loadingRing1StartTime + loadingRing1Duration; // After loading ring 1 finish
        const float *logoEasing = EASEINOUT2;

        // Loading text
        float loadingTextStartTime = 7000;
        float textSize = 5;

        // ---- Drawing
        ObjPowerOn.bg.drawRoundedRect_Fill(UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, UI_SCREEN_ROUND_RADIUS);
        ObjPowerOn.indicator.drawCircle_Fill(10, 0, 360);
        ObjPowerOn.logo.drawText("OppsOS", 7);
        ObjPowerOn.loadingRing.drawCircle_Line(60, 0, ObjPowerOn.loadingRing_Null.anchorX, 15);

        // Initiate animation
        if (System.pwrOnAnimState == AnimState::IDLE)
        {
            cout << "Power on triggered..." << endl;
            System.pwrOnAnimState = AnimState::ANIMATING;
            toggleAnimationFlag(ObjPowerOn.bg, false, false, false, true, false);
            toggleAnimationFlag(ObjPowerOn.indicator, false, false, false, true, false);
            toggleAnimationFlag(ObjPowerOn.logo, true, false, false, true, false);
            toggleAnimationFlag(ObjPowerOn.loadingRing, true, false, false, true, false);
            toggleAnimationFlag(ObjPowerOn.loadingRing_Null, true, false, false, false, false);
            System.pOnStartTime = chrono::high_resolution_clock::now();
            cout << "Is busy? + " << isBusyAnimating(ObjPowerOn.bg) << endl;
        }
        // ---- Animate
        if (System.pwrOnAnimState == AnimState::ANIMATING)
        {
            // get elapsed time
            chrono::high_resolution_clock::time_point currentTime = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> elapsedTime = currentTime - System.pOnStartTime;

            // 1 - Boot UI BG
            animateOpacity(ObjPowerOn.bg, logoDuration, logoEasing, 100);

            // 2 - Boot Indicator
            if (elapsedTime.count() >= bgDuration)
            {
                animateOpacity(ObjPowerOn.indicator, indicatorDuration, indicatorEasing, 100);
            }

            // 3 - Loading Ring 1
            if (elapsedTime.count() >= loadingRing1StartTime)
            {
                animateTranslate(ObjPowerOn.loadingRing_Null, loadingRing1Duration, loadingRing1Easing, 360, 0);
            }

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

            cout << "Booting up..." << endl;

            // (Too long || Animation is done) == End
            if (elapsedTime.count() >= SYS_P_ON_TIME && (!isBusyAnimating(ObjPowerOn.bg) && !isBusyAnimating(ObjPowerOn.indicator) && !isBusyAnimating(ObjPowerOn.logo) && !isBusyAnimating(ObjPowerOn.loadingRing) && !isBusyAnimating(ObjPowerOn.loadingRing_Null)))
            {
                // Reset animation state
                System.state = SystemState::ON;
                System.pwrOnAnimState = AnimState::IDLE;
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
}

#endif