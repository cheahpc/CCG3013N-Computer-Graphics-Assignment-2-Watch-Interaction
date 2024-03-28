#ifndef RENDER_WATCH_BOOT_UI_H
#define RENDER_WATCH_BOOT_UI_H

Object bootUI_BG = Object(0, 0, 1, 0, COLOR_BLACK_1, 0);
Object bootUI_Logo = Object(-170, -100, 0.55, 0, COLOR_THEME_GREEN, 0);
Object bootUI_Indicator = Object((-UI_SCREEN_WIDTH / 2) + 40, (UI_SCREEN_HEIGHT / 2) - 40, 1, 0, COLOR_THEME_GREEN_LIGHT_1, 0);
Object bootUI_BootingText = Object(-130, -50, 0.20, 0, COLOR_WHITE, 100);

void renderBoot()
{
    // Booting up animation
    // BG
    GLfloat bootBGAnimationDuration = 1000;
    const GLfloat *bootBGEasing = EASEOUT3;
    // Indicator
    GLfloat bootIndicatorAnimationDuration = 1000;
    const GLfloat *bootIndicatorEasing = EASEOUT3;
    // Logo
    GLfloat bootLogoYval = 120;
    GLfloat bootLogoAnimationDuration = 1000;
    const GLfloat *bootLogoEasing = EASEINOUT2;
    // Booting up Text
    GLfloat bootingUpTextSize = 5;

    // if (bootingUp)
    if (sys.poweringUp)
    {
        bootUI_BG.drawRoundedRect_Fill(UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, UI_SCREEN_ROUND_RADIUS);
        bootUI_Indicator.drawCircle_Fill(10, 0, 360);
        bootUI_Logo.drawText("OppsOS", 5);
        // Enable animations for first time
        // if (!bootingUpAnimationToggled)
        if (!sys.poweringUpAnimation)
        {
            toggleAnimationFlag(bootUI_BG, false, false, false, true, false);
            toggleAnimationFlag(bootUI_Indicator, false, false, false, true, false);
            toggleAnimationFlag(bootUI_Logo, true, false, false, true, false);
            // bootingUpAnimationToggled = true;
            bootingUpAnimationToggled = sys.poweringUpAnimation = true;
        }

        chrono::high_resolution_clock::time_point currentTime = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> bootTime = currentTime - bootStartTime;
        if (bootTime.count() >= SYSTEM_BOOT_TIME)
        {
            // Boot completed
            // bootingUp = false;
            // systemRunning = true;
            // bootingUpAnimationToggled = false;

            sys.poweringUp = false;
            sys.isOn = true;
            sys.poweringUpAnimation = false;
            cout << "Boot completed..." << endl;
        }
        else
        {
            // 1 - Boot UI BG
            animateOpacity(bootUI_BG, bootLogoAnimationDuration, bootLogoEasing, 100);

            // 2 - Boot Indicator
            if (bootTime.count() >= bootBGAnimationDuration)
            {
                animateOpacity(bootUI_Indicator, bootIndicatorAnimationDuration, bootIndicatorEasing, 100);
            }

            // 3 - Boot Logo
            if (bootTime.count() >= 3000)
            {
                animateTranslate(bootUI_Logo, bootLogoAnimationDuration, bootLogoEasing, 0, bootLogoYval);
                animateOpacity(bootUI_Logo, bootLogoAnimationDuration, bootLogoEasing, 100);
            }

            if (bootTime.count() >= 5000)
            {
                int index = static_cast<int>(bootTime.count() / 1000) % 4; // There are 4 variations

                // Draw the text using the calculated index
                switch (index)
                {
                case 0:
                    bootUI_BootingText.drawText("Booting up", bootingUpTextSize);
                    break;
                case 1:
                    bootUI_BootingText.drawText("Booting up.", bootingUpTextSize);
                    break;
                case 2:
                    bootUI_BootingText.drawText("Booting up..", bootingUpTextSize);
                    break;
                case 3:
                    bootUI_BootingText.drawText("Booting up...", bootingUpTextSize);
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