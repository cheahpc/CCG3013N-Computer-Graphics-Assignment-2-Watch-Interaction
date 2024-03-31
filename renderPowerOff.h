#ifndef RENDER_POWEROFF_H
#define RENDER_POWEROFF_H

// anchorX, anchorY, scaleFactor, orientation, *color, opacity, orbitRadius, orbitAngle

void renderPowerOff()
{
    // Low battery power off
    if (System.batteryLevel <= 0 && System.state == SystemState::ON && ObjPowerOff.pOffConfirmation != PowerOffConfirmation::YES)
    {
        cout << "Battery running out... shutting down" << endl;
        System.state == SystemState::POWERING_OFF_TRIGGERED;
        ObjPowerOff.pOffConfirmation = PowerOffConfirmation::YES;

        System.batteryLevel = 0;
    }

    // Power off confirm screen
    if (System.state == SystemState::POWERING_OFF_TRIGGERED)
    {
        // ---- Variables
        // Durations
        float poOverlay_TotalDuration = 1200;
        float poOverlay_BG_Blur_Duration = 1000;
        float poOverlay_BG_Duration = 1000;
        float poOverlay_Text_Duration = 1000;
        float poOverlay_Separator_Duration = 1000;

        // Easing
        const float *poOverlay_BG_Blur_Easing = EASEOUT3;
        const float *poOverlay_BG_Easing = EASEOUT3;
        const float *poOverlay_Tittle_Easing = EASEOUT3;
        const float *poOverlay_Separator_Easing = EASEOUT3;

        // Translate Values
        float poOverlay_BG_TranslateYVal = -80;
        float poOverlay_Text_TranslateYVal = -80;
        float poOverlay_Separator_TranslateYVal = -80;

        // Opacity Values
        float poOverlay_BG_Blur_Opacity = 80;
        float poOverlay_Separator_Opacity = 50;

        // ---- Drawing
        ObjPowerOff.bgBlur.drawRoundedRect_Fill(UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, UI_SCREEN_ROUND_RADIUS);
        ObjPowerOff.bg.drawRoundedRect_Fill(PO_CONFIRM_DIAG_WIDTH, PO_CONFIRM_DIAG_HEIGHT, PO_CONFIRM_DIAG_ROUND_RADIUS);
        ObjPowerOff.title.drawText("Power Off", 7);
        ObjPowerOff.message.drawText("Are you sure?", 3);
        ObjPowerOff.yesText.drawText("Yes", 3);
        ObjPowerOff.noText.drawText("No", 3);
        ObjPowerOff.separatorLineHorizontal.drawRect_Fill(PO_CONFIRM_DIAG_WIDTH - 20, 2);
        ObjPowerOff.separatorLineVertical.drawRect_Fill(2, 40);

        // Initiate animation
        if (ObjPowerOff.pOffOverlayAnimState == AnimState::IDLE)
        {
            cout << "Power off triggered..." << endl;
            ObjPowerOff.pOffOverlayAnimState = AnimState::ANIMATING;
            toggleAnimationFlag(ObjPowerOff.bgBlur, false, false, false, true, false);
            toggleAnimationFlag(ObjPowerOff.bg, true, false, false, true, false);
            toggleAnimationFlag(ObjPowerOff.title, true, false, false, true, false);
            toggleAnimationFlag(ObjPowerOff.message, true, false, false, true, false);
            toggleAnimationFlag(ObjPowerOff.yesText, true, false, false, true, false);
            toggleAnimationFlag(ObjPowerOff.noText, true, false, false, true, false);
            toggleAnimationFlag(ObjPowerOff.separatorLineHorizontal, true, false, false, true, false);
            toggleAnimationFlag(ObjPowerOff.separatorLineVertical, true, false, false, true, false);
            ObjPowerOff.pOffOverlayStartTime = chrono::high_resolution_clock::now();
        }
        // ---- Animate
        if (ObjPowerOff.pOffOverlayAnimState == AnimState::ANIMATING)
        {
            // get elapsed time
            chrono::high_resolution_clock::time_point currentTime = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> elapsedTime = currentTime - ObjPowerOff.pOffOverlayStartTime;

            // 1 - Power off overlay BG Blur
            animateOpacity(ObjPowerOff.bgBlur, poOverlay_BG_Blur_Duration, poOverlay_BG_Blur_Easing, poOverlay_BG_Blur_Opacity);
            // 2 - Power off overlay BG
            animateTranslate(ObjPowerOff.bg, poOverlay_BG_Duration, poOverlay_BG_Easing, 0, poOverlay_BG_TranslateYVal);
            animateOpacity(ObjPowerOff.bg, poOverlay_BG_Duration, poOverlay_BG_Easing, 100);
            // 3 - Power off overlay Title
            animateTranslate(ObjPowerOff.title, poOverlay_Text_Duration, poOverlay_Tittle_Easing, 0, poOverlay_Text_TranslateYVal);
            animateOpacity(ObjPowerOff.title, poOverlay_Text_Duration, poOverlay_Tittle_Easing, 100);
            // 4 - Power off overlay Message
            animateTranslate(ObjPowerOff.message, poOverlay_Text_Duration, poOverlay_Tittle_Easing, 0, poOverlay_Text_TranslateYVal);
            animateOpacity(ObjPowerOff.message, poOverlay_Text_Duration, poOverlay_Tittle_Easing, 100);
            // 5 - Power off overlay Yes Text
            animateTranslate(ObjPowerOff.yesText, poOverlay_Text_Duration, poOverlay_Tittle_Easing, 0, poOverlay_Text_TranslateYVal);
            animateOpacity(ObjPowerOff.yesText, poOverlay_Text_Duration, poOverlay_Tittle_Easing, 100);
            // 6 - Power off overlay No Text
            animateTranslate(ObjPowerOff.noText, poOverlay_Text_Duration, poOverlay_Tittle_Easing, 0, poOverlay_Text_TranslateYVal);
            animateOpacity(ObjPowerOff.noText, poOverlay_Text_Duration, poOverlay_Tittle_Easing, 100);
            // 7 - Power off overlay Separator Line Horizontal
            animateTranslate(ObjPowerOff.separatorLineHorizontal, poOverlay_Separator_Duration, poOverlay_Separator_Easing, 0, poOverlay_Separator_TranslateYVal);
            animateOpacity(ObjPowerOff.separatorLineHorizontal, poOverlay_Separator_Duration, poOverlay_Separator_Easing, poOverlay_Separator_Opacity);
            // 8 - Power off overlay Separator Line Vertical
            animateTranslate(ObjPowerOff.separatorLineVertical, poOverlay_Separator_Duration, poOverlay_Separator_Easing, 0, poOverlay_Separator_TranslateYVal);
            animateOpacity(ObjPowerOff.separatorLineVertical, poOverlay_Separator_Duration, poOverlay_Separator_Easing, poOverlay_Separator_Opacity);

            // (Too long || Animation is done) == End
            if (elapsedTime.count() >= poOverlay_TotalDuration && !(isBusyAnimating(ObjPowerOff.bg) || isBusyAnimating(ObjPowerOff.title) || isBusyAnimating(ObjPowerOff.message) || isBusyAnimating(ObjPowerOff.yesText) || isBusyAnimating(ObjPowerOff.noText) || isBusyAnimating(ObjPowerOff.separatorLineHorizontal) || isBusyAnimating(ObjPowerOff.separatorLineVertical)))
            {
                cout << "Confirm power off?..." << endl;
                ObjPowerOff.pOffOverlayAnimState = AnimState::DONE;
                System.currentScreen = Screen::POWER_OFF_CONFIRMATION;
            }
        }
        if (ObjPowerOff.pOffOverlayAnimState == AnimState::DONE)
        {
            switch (ObjPowerOff.pOffConfirmation)
            {
            case PowerOffConfirmation::YES:
                cout << "Powering off..." << endl;
                ObjPowerOff.pOffOverlayAnimState = AnimState::IDLE;
                System.currentScreen = Screen::POWERING_OFF;
                System.state = SystemState::POWERING_OFF;
                break;
            case PowerOffConfirmation::NO:
                ObjPowerOff.pOffOverlayAnimState = AnimState::IDLE;
                cout << "Power off cancelled..." << endl;
                System.currentScreen = Screen::MAIN;
                System.state = SystemState::ON;
                break;
            }
        }
    }
    else if (ObjPowerOff.pOffConfirmation != PowerOffConfirmation::NONE)
    {
        // ---- Variables
        // Easing
        const float *poOverlay_BG_Blur_Easing = EASEOUT2;
        const float *poOverlay_BG_Easing = EASEOUT3;
        const float *poOverlay_Tittle_Easing = EASEOUT2;
        const float *poOverlay_Separator_Easing = EASEOUT2;

        // Durations
        float poOverlay_TotalDuration = 1000;
        float poOverlay_BG_Blur_Duration = 400;
        float poOverlay_BG_Duration = 400;
        float poOverlay_Text_Duration = 400;
        float poOverlay_Separator_Duration = 400;

        // Translate Values
        float poOverlay_BG_TranslateYVal = -80;
        float poOverlay_Text_TranslateYVal = -80;
        float poOverlay_Separator_TranslateYVal = -80;

        // Opacity Values
        float poOverlay_BG_Blur_Opacity = 80;
        float poOverlay_Separator_Opacity = 50;

        // ---- Drawing
        ObjPowerOff.bgBlur.drawRoundedRect_Fill(UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, UI_SCREEN_ROUND_RADIUS);
        ObjPowerOff.bg.drawRoundedRect_Fill(PO_CONFIRM_DIAG_WIDTH, PO_CONFIRM_DIAG_HEIGHT, PO_CONFIRM_DIAG_ROUND_RADIUS);
        ObjPowerOff.title.drawText("Power Off", 7);
        ObjPowerOff.message.drawText("Are you sure?", 3);
        ObjPowerOff.yesText.drawText("Yes", 3);
        ObjPowerOff.noText.drawText("No", 3);
        ObjPowerOff.separatorLineHorizontal.drawRect_Fill(PO_CONFIRM_DIAG_WIDTH - 20, 2);
        ObjPowerOff.separatorLineVertical.drawRect_Fill(2, 40);

        // Initiate animation
        if (ObjPowerOff.pOffOverlayAnimState == AnimState::IDLE)
        {
            ObjPowerOff.pOffOverlayAnimState = AnimState::ANIMATING;
            toggleAnimationFlag(ObjPowerOff.bgBlur, false, false, false, true, false);
            toggleAnimationFlag(ObjPowerOff.bg, true, false, false, true, false);
            toggleAnimationFlag(ObjPowerOff.title, true, false, false, true, false);
            toggleAnimationFlag(ObjPowerOff.message, true, false, false, true, false);
            toggleAnimationFlag(ObjPowerOff.yesText, true, false, false, true, false);
            toggleAnimationFlag(ObjPowerOff.noText, true, false, false, true, false);
            toggleAnimationFlag(ObjPowerOff.separatorLineHorizontal, true, false, false, true, false);
            toggleAnimationFlag(ObjPowerOff.separatorLineVertical, true, false, false, true, false);
            ObjPowerOff.pOffOverlayStartTime = chrono::high_resolution_clock::now();
        }
        // ---- Animate
        if (ObjPowerOff.pOffOverlayAnimState == AnimState::ANIMATING)
        {
            // get elapsed time
            chrono::high_resolution_clock::time_point currentTime = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> elapsedTime = currentTime - ObjPowerOff.pOffOverlayStartTime;

            // 1 - Power off overlay BG Blur
            animateOpacity(ObjPowerOff.bgBlur, poOverlay_BG_Blur_Duration, poOverlay_BG_Blur_Easing, -poOverlay_BG_Blur_Opacity);
            // 2 - Power off overlay BG
            animateTranslate(ObjPowerOff.bg, poOverlay_BG_Duration, poOverlay_BG_Easing, 0, -poOverlay_BG_TranslateYVal);
            animateOpacity(ObjPowerOff.bg, poOverlay_BG_Duration, poOverlay_BG_Easing, -100);
            // 3 - Power off overlay Title
            animateTranslate(ObjPowerOff.title, poOverlay_Text_Duration, poOverlay_Tittle_Easing, 0, -poOverlay_Text_TranslateYVal);
            animateOpacity(ObjPowerOff.title, poOverlay_Text_Duration, poOverlay_Tittle_Easing, -100);
            // 4 - Power off overlay Message
            animateTranslate(ObjPowerOff.message, poOverlay_Text_Duration, poOverlay_Tittle_Easing, 0, -poOverlay_Text_TranslateYVal);
            animateOpacity(ObjPowerOff.message, poOverlay_Text_Duration, poOverlay_Tittle_Easing, -100);
            // 5 - Power off overlay Yes Text
            animateTranslate(ObjPowerOff.yesText, poOverlay_Text_Duration, poOverlay_Tittle_Easing, 0, -poOverlay_Text_TranslateYVal);
            animateOpacity(ObjPowerOff.yesText, poOverlay_Text_Duration, poOverlay_Tittle_Easing, -100);
            // 6 - Power off overlay No Text
            animateTranslate(ObjPowerOff.noText, poOverlay_Text_Duration, poOverlay_Tittle_Easing, 0, -poOverlay_Text_TranslateYVal);
            animateOpacity(ObjPowerOff.noText, poOverlay_Text_Duration, poOverlay_Tittle_Easing, -100);
            // 7 - Power off overlay Separator Line Horizontal
            animateTranslate(ObjPowerOff.separatorLineHorizontal, poOverlay_Separator_Duration, poOverlay_Separator_Easing, 0, -poOverlay_Separator_TranslateYVal);
            animateOpacity(ObjPowerOff.separatorLineHorizontal, poOverlay_Separator_Duration, poOverlay_Separator_Easing, -poOverlay_Separator_Opacity);
            // 8 - Power off overlay Separator Line Vertical
            animateTranslate(ObjPowerOff.separatorLineVertical, poOverlay_Separator_Duration, poOverlay_Separator_Easing, 0, -poOverlay_Separator_TranslateYVal);
            animateOpacity(ObjPowerOff.separatorLineVertical, poOverlay_Separator_Duration, poOverlay_Separator_Easing, -poOverlay_Separator_Opacity);

            // (Too long || Animation is done) == End
            if (elapsedTime.count() >= poOverlay_TotalDuration && !(isBusyAnimating(ObjPowerOff.bg) || isBusyAnimating(ObjPowerOff.title) || isBusyAnimating(ObjPowerOff.message) || isBusyAnimating(ObjPowerOff.yesText) || isBusyAnimating(ObjPowerOff.noText) || isBusyAnimating(ObjPowerOff.separatorLineHorizontal) || isBusyAnimating(ObjPowerOff.separatorLineVertical)))
            {
                ObjPowerOff.pOffOverlayAnimState = AnimState::DONE;

                // Reset all object
                ObjPowerOff.bg.translateTo(0, 80);
                ObjPowerOff.title.translateTo(-140, 180);
                ObjPowerOff.message.translateTo(-140, 80);
                ObjPowerOff.yesText.translateTo(60, -50);
                ObjPowerOff.noText.translateTo(-115, -50);
                ObjPowerOff.separatorLineHorizontal.translateTo(0, 10);
                ObjPowerOff.separatorLineVertical.translateTo(0, -40);
                ObjPowerOff.bgBlur.setOpacity(0);
                ObjPowerOff.bg.setOpacity(0);
                ObjPowerOff.title.setOpacity(0);
                ObjPowerOff.message.setOpacity(0);
                ObjPowerOff.yesText.setOpacity(0);
                ObjPowerOff.noText.setOpacity(0);
                ObjPowerOff.separatorLineHorizontal.setOpacity(0);
                ObjPowerOff.separatorLineVertical.setOpacity(0);
            }
        }
        if (ObjPowerOff.pOffOverlayAnimState == AnimState::DONE)
        {
            switch (ObjPowerOff.pOffConfirmation)
            {
            case PowerOffConfirmation::YES:
                ObjPowerOff.pOffOverlayAnimState = AnimState::IDLE;
                ObjPowerOff.pOffConfirmation = PowerOffConfirmation::NONE;
                System.state = SystemState::POWERING_OFF;
                System.currentScreen = Screen::POWERING_OFF;
                break;
            case PowerOffConfirmation::NO:
                ObjPowerOff.pOffOverlayAnimState = AnimState::IDLE;
                ObjPowerOff.pOffConfirmation = PowerOffConfirmation::NONE;
                System.state = SystemState::ON;
                System.currentScreen = Screen::MAIN;
                break;
            }
        }
    }
    else if (System.state == SystemState::POWERING_OFF)
    {
        // ---- Variables
        // Durations
        float po_OffBg_Duration = 500;
        float po_OffIndicator_Duration = 500;
        float po_OffRing_Duration = 400;
        float po_OffRing_Null_Duration = 5000;
        float po_OffLogo_Duration = 1000;
        float po_OffText_Duration = 1000;

        // Start times
        float po_OffBg_StartTime = 400;
        float po_OffIndicator_StartTime = po_OffBg_StartTime + 400;
        float po_OffRing_StartTime = po_OffIndicator_StartTime + po_OffIndicator_Duration + 1000;
        float po_OffLogo_StartTime = po_OffRing_StartTime + po_OffRing_Duration + po_OffRing_Null_Duration;
        float po_OffText_StartTime = po_OffLogo_StartTime + 200;

        // Total duration
        float po_TotalDuration = po_OffText_StartTime + po_OffText_Duration + 2000;
        // Translate Values
        float po_OffRing_Null_TranslateXVal = -360;

        // Easing
        const float *po_OffBg_Easing = EASEOUT3;
        const float *po_OffIndicator_Easing = EASEOUT3;
        const float *po_OffLogo_Easing = EASEOUT2;
        const float *po_OffText_Easing = EASEOUT2;
        const float *po_OffRing_Easing = EASEOUT2;
        const float *po_OffRing_Null_Easing = EASEINOUT2;

        // ---- Drawing
        ObjPowerOff.offBg.drawRoundedRect_Fill(UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, UI_SCREEN_ROUND_RADIUS);
        ObjPowerOff.offIndicator.drawCircle_Fill(10, 0, 360);
        ObjPowerOff.offRing.drawCircle_Line(60, 0, ObjPowerOff.offRing_Null.anchorX, 15);
        ObjPowerOff.offLogo.drawText("OppsOS", 7);
        ObjPowerOff.offText.drawText("Au Revoir", 3);

        // Initiate animation
        if (ObjPowerOff.pOffAnimState == AnimState::IDLE)
        {
            ObjPowerOff.pOffAnimState = AnimState::ANIMATING;

            toggleAnimationFlag(ObjPowerOff.offBg, false, false, false, true, false);
            toggleAnimationFlag(ObjPowerOff.offRing_Null, true, false, false, false, false);
            toggleAnimationFlag(ObjPowerOff.offIndicator, false, false, false, true, false);
            toggleAnimationFlag(ObjPowerOff.offLogo, false, false, false, true, false);
            toggleAnimationFlag(ObjPowerOff.offText, false, false, false, true, false);
            toggleAnimationFlag(ObjPowerOff.offRing, false, false, false, true, false);
            ObjPowerOff.pOffStartTime = chrono::high_resolution_clock::now();
        }

        // ---- Animate
        if (ObjPowerOff.pOffAnimState == AnimState::ANIMATING)
        {
            // get elapsed time
            chrono::high_resolution_clock::time_point currentTime = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> elapsedTime = currentTime - ObjPowerOff.pOffStartTime;

            // 1 - Power off BG
            if (elapsedTime.count() >= po_OffBg_StartTime)
                animateOpacity(ObjPowerOff.offBg, po_OffBg_Duration, po_OffBg_Easing, 100);

            // 2 - Power off Indicator
            if (elapsedTime.count() >= po_OffIndicator_StartTime)
                animateOpacity(ObjPowerOff.offIndicator, po_OffIndicator_Duration, po_OffIndicator_Easing, 100);

            // 3 - Power Ring
            if (elapsedTime.count() >= po_OffRing_StartTime)
            {
                animateOpacity(ObjPowerOff.offRing, po_OffRing_Duration, po_OffRing_Easing, 100);
                if (elapsedTime.count() >= po_OffRing_StartTime + po_OffRing_Duration)
                    animateTranslate(ObjPowerOff.offRing_Null, po_OffRing_Null_Duration, po_OffRing_Null_Easing, po_OffRing_Null_TranslateXVal, 0);
            }

            // 4 - Power off Logo
            // TODO
            if (elapsedTime.count() >= po_OffLogo_StartTime)
                animateOpacity(ObjPowerOff.offLogo, po_OffLogo_Duration, po_OffLogo_Easing, 100);

            // 5 - Power off Text
            if (elapsedTime.count() >= po_OffText_StartTime)
                animateOpacity(ObjPowerOff.offText, po_OffText_Duration, po_OffText_Easing, 100);

            // (Too long || Animation is done) == End
            if (elapsedTime.count() >= po_TotalDuration && !(isBusyAnimating(ObjPowerOff.offBg) || isBusyAnimating(ObjPowerOff.offRing) || isBusyAnimating(ObjPowerOff.offIndicator) || isBusyAnimating(ObjPowerOff.offLogo) || isBusyAnimating(ObjPowerOff.offText) || isBusyAnimating(ObjPowerOff.offRing_Null)))
            {
                ObjPowerOff.pOffAnimState = AnimState::DONE;
            }
        }

        // ---- Finish animation
        if (ObjPowerOff.pOffAnimState == AnimState::DONE)
        {
            // Reset power off objects
            ObjPowerOff.offBg.setOpacity(0);
            ObjPowerOff.offRing.setOpacity(0);
            ObjPowerOff.offIndicator.setOpacity(0);
            ObjPowerOff.offRing_Null.translateTo(-po_OffRing_Null_TranslateXVal, 0);
            ObjPowerOff.offLogo.setOpacity(0);
            ObjPowerOff.offText.setOpacity(0);

            cout << "Power off completed... System is off" << endl;
            ObjPowerOff.pOffAnimState = AnimState::IDLE;
            System.state = SystemState::OFF;

            // Reset all object logic
            ObjUI.isHeartBeating = false;
            ObjUI.isBatteryPercentageVisible = false;

            // Reset all object opacity
            // Bg
            ObjUI.bg.setOpacity(100);
            // Complications
            ObjUI.complication1.setOpacity(0);
            ObjUI.complication2.setOpacity(0);
            ObjUI.complication3.setOpacity(0);
            ObjUI.complication4.setOpacity(0);
            ObjUI.comp1Battery.setOpacity(0);
            ObjUI.comp2Timer.setOpacity(0);
            ObjUI.comp3Alarm.setOpacity(0);
            ObjUI.comp4Text.setOpacity(0);

            // Heart rate monitor
            ObjUI.heartIcon.setOpacity(0);
            ObjUI.heartRate.setOpacity(0);

            // Step counter
            ObjUI.stepCountText.setOpacity(0);
            ObjUI.stepStepText.setOpacity(0);

            // DateTime
            ObjUI.time.setOpacity(0);
            ObjUI.dateBox.setOpacity(0);
            ObjUI.date.setOpacity(0);

            // Reset all object position
            // Bg
            ObjUI.bg.translateTo(0, 0);
            // Complications
            ObjUI.complication1.translateTo(COMPLICATION_X_POS, COMPLICATION_Y_POS_1);
            ObjUI.complication2.translateTo(COMPLICATION_X_POS, COMPLICATION_Y_POS_1);
            ObjUI.complication3.translateTo(COMPLICATION_X_POS, COMPLICATION_Y_POS_1);
            ObjUI.complication4.translateTo(COMPLICATION_X_POS, COMPLICATION_Y_POS_1);
            ObjUI.comp4Text.translateTo(COMP4_TEXT_X_POS, COMP4_TEXT_Y_POS);

            // DateTime
            ObjUI.time.translateTo(-90, 70);
            ObjUI.dateBox.translateTo(43, 20);
            ObjUI.date.translateTo(-70, 10);

            // Reset all object scale
            // Complications
            ObjUI.complication1.scaleTo(0);
            ObjUI.complication2.scaleTo(0);
            ObjUI.complication3.scaleTo(0);
            ObjUI.complication4.scaleTo(0);

            // Update system state
            ObjUI.animState = AnimState::IDLE;
            System.currentScreen = Screen::NONE;
        }
    }
}

#endif