#ifndef RENDERLEGEND_H
#define RENDERLEGEND_H

// anchorX, anchorY, scaleFactor, orientation, *color, opacity, orbitRadius, orbitAngle
Object legendHelpText = Object(-700, 160, 0.10, 0, COLOR_THEME_GREEN_DARK_1, 100);
Object legendBg = Object(-650, 0, 1, 0, COLOR_THEME_GREEN_DARK_2, 0);
Object legendText = Object();
bool legendShow = false;

void renderLegend()
{
    // Legend Background

    const GLfloat *easing = EASEOUT3;
    int duration = 400; // 10 frames in 25fps
    GLfloat legendHelpTextOpacVal, legendHelpTextTransVal;
    GLfloat legendBgOpacVal, legendBgTransVal;

    // 1. Help Text
    legendHelpText.drawText("Press 'h' for legend", LEGEND_HELP_TEXT_SIZE);

    // 2. Legend Box
    legendBg.setColor(COLOR_THEME_GREEN_DARK_2);
    legendBg.drawRoundedRect_Fill(LEGEND_BOX_WIDTH, LEGEND_BOX_HEIGHT, 25);

    legendBg.setColor(COLOR_THEME_GREEN_LIGHT_1);
    legendBg.drawRoundedRect_Line(LEGEND_BOX_WIDTH, LEGEND_BOX_HEIGHT, 25, LEGEND_BOX_OUTLINE_SIZE);

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