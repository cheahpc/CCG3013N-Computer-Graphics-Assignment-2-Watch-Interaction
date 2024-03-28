#ifndef RENDER_BACKGROUND_H
#define RENDER_BACKGROUND_H

void renderBackground()
{
    // Coordinates
    GLint x[4] = {-WINDOWS_WIDTH / 2, -WINDOWS_WIDTH / 2, WINDOWS_WIDTH / 2, WINDOWS_WIDTH / 2};
    GLint y[4] = {-WINDOWS_HEIGHT / 2, WINDOWS_HEIGHT / 2, WINDOWS_HEIGHT / 2, -WINDOWS_HEIGHT / 2};

    // Draw the background
    ObjBackdrop.bg.setColor(COLOR_WHITE);
    ObjBackdrop.bg.drawQuad_Fill(x, y);

    // Top half
    y[0] = 150;
    y[1] = (WINDOWS_HEIGHT / 2);
    y[2] = (WINDOWS_HEIGHT / 2);
    y[3] = 150;
    ObjBackdrop.bg.setColor(COLOR_THEME_GREEN);
    ObjBackdrop.bg.drawQuad_Fill(x, y);

    // Bottom half
    y[0] = -150;
    y[1] = -(WINDOWS_HEIGHT / 2);
    y[2] = -(WINDOWS_HEIGHT / 2);
    y[3] = -150;
    ObjBackdrop.bg.drawQuad_Fill(x, y);
}
#endif