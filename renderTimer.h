#ifndef RENDER_TIMER_H
#define RENDER_TIMER_H

if ((System.state == SystemState::ON || System.state == SystemState::POWERING_OFF_TRIGGERED) && System.currentScreen == Screen::TIMER)
{
    // ---- Variables
    // Start Time
    float comp1StartTime = 0;

    // Easing

    const float *heartBeatEasing = ObjUI.isHeartBeatUp ? EASEIN3 : EASEOUT3;

    // ---- Drawing

    // Initiate animation
    if (ObjTimer.animState == AnimState::IDLE)
    {
        ObjUI.animState = AnimState::ANIMATING;
        System.currentScreen = Screen::NONE;
        toggleAnimationFlag(ObjUI.time, true, false, false, true, false);

        ObjUI.animStartTime = chrono::high_resolution_clock::now();
    }

    // ---- Animate
    if (ObjUI.animState == AnimState::ANIMATING)
    {
        // get elapsed time
        chrono::high_resolution_clock::time_point currentTime = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> elapsedTime = currentTime - ObjUI.animStartTime;

        // Animate the time and date
        // DateTime
        // animateOpacity(ObjUI.time, dateTimeADuration, ui_OpactEasing, 100);
        // animateOpacity(ObjUI.date, dateTimeADuration, ui_OpactEasing, 100);
        // animateOpacity(ObjUI.dateBox, dateTimeADuration, ui_OpactEasing, 100);

        // (Too long || Animation is done) == End
        if (elapsedTime.count() >= ui_AnimTotalDuration)
        {
            // Reset animation state
            ObjTimer.animState = AnimState::DONE;
            // System.currentScreen = Screen::MAIN;
            // cout << "Welcome..." << endl;
        }
    }
}

#endif