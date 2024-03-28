#ifndef RENDER_POWEROFF_H
#define RENDER_POWEROFF_H

// anchorX, anchorY, scaleFactor, orientation, *color, opacity, orbitRadius, orbitAngle
Object powerOffBG = Object();

// Todo render power off screen

// 1 Power off confirm screen
// 2 Power off animation
void renderPowerOff()
{
    // Power off confirm screen
    if (System.state == SystemState::POWERING_OFF_TRIGGERED)
    {
        float po_OverlayOpacity = 80;
        float po_OverlayDuration = 1000;
        const float *po_OverlayEasing = EASEOUT3;

        float po_BGOpacity = 100;
        float po_BGDuration = 1000;
        float po_BGTranslateYVal = -70;
        const float *po_BGEasing = EASEOUT3;

        // Draw the confirm dialog screen
        // Overlay
        ObjPowerOff.overlay.drawRoundedRect_Fill(UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, UI_SCREEN_ROUND_RADIUS);
        ObjPowerOff.bg.drawRoundedRect_Fill(PO_CONFIRM_DIAG_WIDTH, PO_CONFIRM_DIAG_HEIGHT, PO_CONFIRM_DIAG_ROUND_RADIUS);

        // Initiate animation
        if (!ObjPowerOff.State.confirmDiagAnimStarted)
        {
            ObjPowerOff.State.confirmDiagAnimStarted = true;
            ObjPowerOff.State.confirmDiagAnimEnded = false;
            // toggle animation
            toggleAnimationFlag(ObjPowerOff.overlay, false, false, false, true, false);
            toggleAnimationFlag(ObjPowerOff.bg, true, false, false, true, false);
        }

        if (!ObjPowerOff.State.confirmDiagAnimEnded)
        {
            animateOpacity(ObjPowerOff.overlay, po_OverlayDuration, po_OverlayEasing, po_OverlayOpacity);
            animateOpacity(ObjPowerOff.bg, po_BGDuration, po_BGEasing, po_BGOpacity);
            animateTranslate(ObjPowerOff.bg, po_BGDuration, po_BGEasing, 0, po_BGTranslateYVal);
        }
    }
    else if (System.state == SystemState::POWERING_OFF)
    {
        // Draw the power off animation
        // Todo add power off animation
    }
}

#endif