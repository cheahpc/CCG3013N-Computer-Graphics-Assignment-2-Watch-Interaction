#ifndef RENDERHELP_H
#define RENDERHELP_H

void renderHelp()
{
    // Legend Background
    const GLfloat *easing = EASEINOUT2;
    int duration = 1500; // 10 frames in 25fps

    // Opacity `
    GLfloat helpOpacityVal = (ObjHelp.isHelpVisible) ? 100 : -100;
    GLfloat hintOpacityVal = (ObjHelp.isHelpVisible) ? -100 : 100;

    // Hint
    ObjHelp.hintText.drawText("Press 'h' for help", HELP_HINT_TEXT_SIZE);

    // Help
    ObjHelp.bg.setColor(COLOR_THEME_GREEN_DARK_1);
    ObjHelp.bg.drawRoundedRect_Line(HELP_BOX_WIDTH, HELP_BOX_HEIGHT, HELP_BOX_ROUND_RADIUS * 3, HELP_BOX_OUTLINE_SIZE);
    ObjHelp.bg.setColor(COLOR_WHITE);
    ObjHelp.bg.drawRoundedRect_Fill(HELP_BOX_WIDTH, HELP_BOX_HEIGHT, HELP_BOX_ROUND_RADIUS);

    // Drawing
    // Labels
    ObjHelp.helpText.scaleTo(HELP_LABEL_TEXT_SCALE);
    ObjHelp.helpText.setColor(COLOR_BLACK);
    ObjHelp.helpText.translateTo(200, -280);
    ObjHelp.helpText.drawText("Watch", HELP_LABEL_TEXT_SIZE);
    ObjHelp.helpText.translateTo(120, -350);
    ObjHelp.helpText.drawText("Watch strap", HELP_LABEL_TEXT_SIZE);
    ObjHelp.helpText.translateTo(600, -90);
    ObjHelp.helpText.drawText("(The Charger)", HELP_LABEL_TEXT_SIZE);
    ObjHelp.helpText.translateTo(270, 100);
    ObjHelp.helpText.drawText("(Watch Dial)", HELP_LABEL_TEXT_SIZE);
    ObjHelp.helpText.translateTo(260, -90);
    ObjHelp.helpText.drawText("(Watch Button)", HELP_LABEL_TEXT_SIZE);

    // Helps
    ObjHelp.helpText.scaleTo(HELP_TEXT_SCALE);
    ObjHelp.helpText.setColor(COLOR_BLACK_3);
    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y);
    ObjHelp.helpText.drawText("1) Charge the watch:", HELP_POINT_TEXT_SIZE);
    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y - HELP_TEXT_Y_OFFSET);
    ObjHelp.helpText.drawText(" - Drag (The Charger) to the center of the watch.", HELP_TEXT_SIZE);

    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y - HELP_TEXT_Y_OFFSET * 3);
    ObjHelp.helpText.drawText("2) Power on/off:", HELP_POINT_TEXT_SIZE);
    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y - HELP_TEXT_Y_OFFSET * 4);
    ObjHelp.helpText.drawText(" - Click and hold the (Watch Button) for 5 seconds.", HELP_TEXT_SIZE);

    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y - HELP_TEXT_Y_OFFSET * 6);
    ObjHelp.helpText.drawText("2*) Note:", HELP_POINT_TEXT_SIZE);
    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y - HELP_TEXT_Y_OFFSET * 7);
    ObjHelp.helpText.drawText(" - Auto power off when battery level at 0%", HELP_TEXT_SIZE);
    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y - HELP_TEXT_Y_OFFSET * 8);
    ObjHelp.helpText.drawText(" - Auto power on when battery charged to 100%", HELP_TEXT_SIZE);
    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y - HELP_TEXT_Y_OFFSET * 9);
    ObjHelp.helpText.drawText(" - Unable to power on when battery level below 10%", HELP_TEXT_SIZE);

    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y - HELP_TEXT_Y_OFFSET * 11);
    ObjHelp.helpText.drawText("3) Toggle heart beating. *beating speed follows bpm", HELP_POINT_TEXT_SIZE);
    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y - HELP_TEXT_Y_OFFSET * 12);
    ObjHelp.helpText.drawText(" - Click the heart icon.", HELP_TEXT_SIZE);

    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y - HELP_TEXT_Y_OFFSET * 14);
    ObjHelp.helpText.drawText("4) Simulate walking:", HELP_POINT_TEXT_SIZE);
    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y - HELP_TEXT_Y_OFFSET * 15);
    ObjHelp.helpText.drawText(" - Press 'a' and 'b' in alternating pattern.", HELP_TEXT_SIZE);

    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y - HELP_TEXT_Y_OFFSET * 17);
    ObjHelp.helpText.drawText("5) Increase heart rate:", HELP_POINT_TEXT_SIZE);
    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y - HELP_TEXT_Y_OFFSET * 18);
    ObjHelp.helpText.drawText(" - Walk faster. *walking speed affects heart rate", HELP_TEXT_SIZE);

    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y - HELP_TEXT_Y_OFFSET * 20);
    ObjHelp.helpText.drawText("6) Complications:", HELP_POINT_TEXT_SIZE);
    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y - HELP_TEXT_Y_OFFSET * 21);
    ObjHelp.helpText.drawText(" - A. Battery: Toggle show battery percentage. ", HELP_TEXT_SIZE);
    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y - HELP_TEXT_Y_OFFSET * 22);
    ObjHelp.helpText.drawText(" - B. Stopwatch: Launch stopwatch app. ", HELP_TEXT_SIZE);
    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y - HELP_TEXT_Y_OFFSET * 23);
    ObjHelp.helpText.drawText(" - C. Timer: Launch timer app. ", HELP_TEXT_SIZE);
    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y - HELP_TEXT_Y_OFFSET * 24);
    ObjHelp.helpText.drawText(" - D. Time Format: Switch 24/12 hour format.", HELP_TEXT_SIZE);

    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y - HELP_TEXT_Y_OFFSET * 26);
    ObjHelp.helpText.drawText("<<Stopwatch App>>.", HELP_POINT_TEXT_SIZE);
    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y - HELP_TEXT_Y_OFFSET * 27);
    ObjHelp.helpText.drawText("Click (Watch Dial) to:", HELP_TEXT_SIZE);
    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y - HELP_TEXT_Y_OFFSET * 28);
    ObjHelp.helpText.drawText(" - Start", HELP_TEXT_SIZE);
    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y - HELP_TEXT_Y_OFFSET * 29);
    ObjHelp.helpText.drawText(" - Pause", HELP_TEXT_SIZE);
    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y - HELP_TEXT_Y_OFFSET * 30);
    ObjHelp.helpText.drawText(" - Reset", HELP_TEXT_SIZE);

    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y - HELP_TEXT_Y_OFFSET * 32);
    ObjHelp.helpText.drawText("<<Timer App>>.", HELP_POINT_TEXT_SIZE);
    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y - HELP_TEXT_Y_OFFSET * 33);
    ObjHelp.helpText.drawText(" - Click 'Hour/Minute/Seconds' on screen to select.", HELP_TEXT_SIZE);
    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y - HELP_TEXT_Y_OFFSET * 34);
    ObjHelp.helpText.drawText(" - Click and drag watch dial up/down to set.", HELP_TEXT_SIZE);
    ObjHelp.helpText.translateTo(HELP_TEXT_INIT_X, HELP_TEXT_INIT_Y - HELP_TEXT_Y_OFFSET * 35);
    ObjHelp.helpText.drawText(" - Click 'start' button on screen to start the timer.", HELP_TEXT_SIZE);

    // Animate
    animateOpacity(ObjHelp.bg, duration, easing, helpOpacityVal);
    animateOpacity(ObjHelp.hintText, duration, easing, hintOpacityVal);
    animateOpacity(ObjHelp.helpText, duration, easing, helpOpacityVal);
}
#endif