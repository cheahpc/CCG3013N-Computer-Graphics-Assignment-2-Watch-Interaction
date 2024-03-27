#ifndef RENDERLEGEND_H
#define RENDERLEGEND_H

#include "Object.cpp"
#include "animate.h"
// anchorX, anchorY, scaleFactor, orientation, *color, opacity, orbitRadius, orbitAngle
Object legendHelpText = Object(-700, 160, 0.15, 0, COLOR_THEME_GREEN_DARK_1, 100);
Object legendBg = Object(-650, 0, 1, 0, COLOR_THEME_GREEN_DARK_2, 0);
Object legendText = Object();
// GLfloat durationVal = 400; // 10 frames in 25fps
bool legendShow = false;

void renderLegend()
{
    // Legend Background

    const GLfloat *easing = EASEOUT3;
    int duration = 400;
    GLfloat legendHelpTextOpacVal, legendHelpTextTransVal;
    GLfloat legendBgOpacVal, legendBgTransVal;

    legendHelpText.drawText("Press 'h' for legend.", 3);
    legendBg.setColor(COLOR_THEME_GREEN_DARK_2);
    legendBg.drawRoundedRect_Fill(520, 520, 30);

    legendBg.setColor(COLOR_THEME_GREEN_LIGHT_1);
    legendBg.drawRoundedRect_Fill(500, 500, 20);

    if (legendShow)
    {
        // 1. Legend Help Text Exit
        legendHelpTextTransVal = 60;
        legendHelpTextOpacVal = -100;
        // 2. Legend Text
        legendBgTransVal = 100;
        legendBgOpacVal = 100;
    }
    else
    {
        // 1. Legend Help Text Enter
        legendHelpTextTransVal = -60;
        legendHelpTextOpacVal = 100;
        // 2. Legend Text
        legendBgTransVal = -100;
        legendBgOpacVal = -100;
    }

    // 1. Animate legend help text enter
    animateTranslate(legendHelpText, duration, easing, legendHelpTextTransVal, 0);
    animateOpacity(legendHelpText, duration, easing, legendHelpTextOpacVal);
    // 2. Animate legend help text exit
    animateOpacity(legendBg, duration, easing, legendBgOpacVal);
    animateTranslate(legendBg, duration, easing, legendBgTransVal, 0);

    // S - boot
    // Q - close notification
    // C - show clock
    // A - toggle always on display (AOD)
}

#endif