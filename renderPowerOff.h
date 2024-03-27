#ifndef RENDER_POWEROFF_H
#define RENDER_POWEROFF_H

// anchorX, anchorY, scaleFactor, orientation, *color, opacity, orbitRadius, orbitAngle
Object powerOffBG = Object();

// Todo render power off screen

// 1 Power off confirm screen
// 2 Power off animation
void renderPowerOff()
{
    powerOffBG.setColor(COLOR_BLACK);
    powerOffBG.drawRoundedRect_Fill(UI_SCREEN_WIDTH, UI_SCREEN_HEIGHT, UI_SCREEN_ROUND_RADIUS);
}

#endif