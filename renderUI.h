#ifndef RENDER_UI_H
#define RENDER_UI_H

// anchorX, anchorY, scaleFactor, orientation, *color, opacity, orbitRadius, orbitAngle
Object uiBG = Object();

void renderUI_BG()
{
    uiBG.setColor(COLOR_BLACK);
    uiBG.drawRoundedRect_Fill(UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, UI_SCREEN_ROUND_RADIUS);
}

// TODO 4 complication on the left
// TODO digital time display on the right
// TODO date display under the digital time display
// TODO mini analog clock under the digital time display
// TODO step counter on top of the digital time display
// TODO heart rate monitor on top of the digital time display
#endif