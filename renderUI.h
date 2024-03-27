#ifndef RENDER_UI_H
#define RENDER_UI_H


// anchorX, anchorY, scaleFactor, orientation, *color, opacity, orbitRadius, orbitAngle
Object uiBG = Object();

void renderUI_BG()
{
    uiBG.setColor(COLOR_BLACK);
    uiBG.drawRoundedRect_Fill(UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, UI_SCREEN_ROUND_RADIUS);
}

#endif