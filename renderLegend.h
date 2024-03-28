#ifndef RENDERLEGEND_H
#define RENDERLEGEND_H


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
    ObjLegend.hintText.drawText("Press 'h' for legend", LEGEND_HELP_TEXT_SIZE);

    // 2. Legend Box
    ObjLegend.bg.setColor(COLOR_THEME_GREEN_LIGHT_1);
    ObjLegend.bg.drawRoundedRect_Line(LEGEND_BOX_WIDTH, LEGEND_BOX_HEIGHT, LEGEND_BOX_ROUND_RADIUS, LEGEND_BOX_OUTLINE_SIZE);

    ObjLegend.bg.setColor(COLOR_THEME_GREEN_DARK_2);
    ObjLegend.bg.drawRoundedRect_Fill(LEGEND_BOX_WIDTH, LEGEND_BOX_HEIGHT, LEGEND_BOX_ROUND_RADIUS);

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
    animateTranslate(ObjLegend.hintText, duration, easing, legendHelpTextTransVal, 0);
    animateOpacity(ObjLegend.hintText, duration, easing, legendHelpTextOpacVal);
    // 2. Animate legend help text exit
    animateOpacity(ObjLegend.bg, duration, easing, legendBgOpacVal);
    animateTranslate(ObjLegend.bg, duration, easing, legendBgTransVal, 0);

    // S - boot
    // Q - close notification
    // C - show clock
    // A - toggle always on display (AOD)
}
#endif