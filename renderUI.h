#ifndef RENDER_UI_H
#define RENDER_UI_H

void renderUI_BG()
{
    // Check if system is on
    if (System.isOn)
    {
        // Draw the background
    }
}

void renderTime()
{
    if (System.isOn)
    {
        float dateTimeADuration = 2200;
        const float *dateTimeAEasing = EASEOUT3;
        float dateTimeYTranslateVal = -70;

        char timeStr[6], dateStr[12];
        strcpy(timeStr, getTimeNow().c_str());
        strcpy(dateStr, get_formatted_date().c_str());

        ObjUI.time.drawText(timeStr, 9);
        ObjUI.date.drawText(dateStr, 5);
        if (!ObjUI.DateTime.isShow)
        {
            // Toggle animation flag
            toggleAnimationFlag(ObjUI.time, true, false, false, true, false);
            toggleAnimationFlag(ObjUI.date, true, false, false, true, false);

            ObjUI.DateTime.isShow = true;
            ObjUI.DateTime.isAnimating = true;
        }

        if (ObjUI.DateTime.isAnimating)
        {
            // Animate the time and date
            animateOpacity(ObjUI.time, dateTimeADuration, dateTimeAEasing, 100);
            animateOpacity(ObjUI.date, dateTimeADuration, dateTimeAEasing, 100);
            animateTranslate(ObjUI.time, dateTimeADuration, dateTimeAEasing, 0, dateTimeYTranslateVal);
            animateTranslate(ObjUI.date, dateTimeADuration, dateTimeAEasing, 0, dateTimeYTranslateVal);
            if (!isBusyAnimating(ObjUI.time) && !isBusyAnimating(ObjUI.date))
                ObjUI.DateTime.isAnimating = false;
        }

        // draw the time
    }
}

// TODO 4 complication on the left
// TODO digital time display on the right
// TODO date display under the digital time display
// TODO mini analog clock under the digital time display
// TODO step counter on top of the digital time display
// TODO heart rate monitor on top of the digital time display
#endif