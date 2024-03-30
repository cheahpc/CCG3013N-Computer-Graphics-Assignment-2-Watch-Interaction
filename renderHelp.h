#ifndef RENDERHELP_H
#define RENDERHELP_H

void renderHelp()
{
    // Legend Background
    const GLfloat *easing = EASEOUT3;
    int duration = 400; // 10 frames in 25fps
    GLfloat helpTextOpacVal, helpTextTransVal;
    GLfloat helpBgOpacVal, helpBgTransVal;

    // 1. Help Text
    ObjHelp.hintText.drawText("Press 'h' for help", HELP_HINT_TEXT_SIZE);

    // 2. Legend Box
    ObjHelp.bg.setColor(COLOR_THEME_GREEN_LIGHT_1);
    ObjHelp.bg.drawRoundedRect_Line(HELP_BOX_WIDTH, HELP_BOX_HEIGHT, HELP_BOX_ROUND_RADIUS, HELP_BOX_OUTLINE_SIZE);

    ObjHelp.bg.setColor(COLOR_THEME_GREEN_DARK_2);
    ObjHelp.bg.drawRoundedRect_Fill(HELP_BOX_WIDTH, HELP_BOX_HEIGHT, HELP_BOX_ROUND_RADIUS);

    if (ObjHelp.isHelpVisible)
    {
        // 1. Legend Help Text Exit
        helpTextTransVal = 60;
        helpTextOpacVal = -100;
        // 2. Legend Text
        helpBgTransVal = 100;
        helpBgOpacVal = 100;
    }
    else
    {
        // 1. Legend Help Text Enter
        helpTextTransVal = -60;
        helpTextOpacVal = 100;
        // 2. Legend Text
        helpBgTransVal = -100;
        helpBgOpacVal = -100;
    }

    // 1. Animate legend help text enter
    animateTranslate(ObjHelp.hintText, duration, easing, helpTextTransVal, 0);
    animateOpacity(ObjHelp.hintText, duration, easing, helpTextOpacVal);
    // 2. Animate legend help text exit
    animateOpacity(ObjHelp.bg, duration, easing, helpBgOpacVal);
    animateTranslate(ObjHelp.bg, duration, easing, helpBgTransVal, 0);

    // Label the buttons and all
}
#endif