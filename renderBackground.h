#ifndef RENDER_BACKGROUND_H
#define RENDER_BACKGROUND_H

Object bg = Object();

void renderBackground()
{
    // Coordinates
    GLint x[4] = {-WINDOWS_WIDTH / 2, -WINDOWS_WIDTH / 2, WINDOWS_WIDTH / 2, WINDOWS_WIDTH / 2};
    GLint y[4] = {-WINDOWS_HEIGHT / 2, WINDOWS_HEIGHT / 2, WINDOWS_HEIGHT / 2, -WINDOWS_HEIGHT / 2};

    bg.translateTo(0, 0);
    bg.scaleTo(1);
    bg.setOpacity(100);
    bg.setColor(COLOR_SILVER);
    // Draw the background
    bg.drawQuad_Fill(x, y);

    // Top half
    y[0] = 150;
    y[1] = (WINDOWS_HEIGHT / 2);
    y[2] = (WINDOWS_HEIGHT / 2);
    y[3] = 150;
    bg.setColor(COLOR_THEME_GREEN);
    bg.drawQuad_Fill(x, y);

    // Bottom half
    y[0] = -150;
    y[1] = -(WINDOWS_HEIGHT / 2);
    y[2] = -(WINDOWS_HEIGHT / 2);
    y[3] = -150;
    bg.drawQuad_Fill(x, y);
}
#endif