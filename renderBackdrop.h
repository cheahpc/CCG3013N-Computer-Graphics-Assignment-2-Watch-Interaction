#ifndef RENDER_BACKGROUND_H
#define RENDER_BACKGROUND_H

void renderBackdrop()
{
    ObjBackdrop.bg.translateTo(0, 0);
    ObjBackdrop.bg.setColor(COLOR_THEME_GREEN_LIGHT_3);
    ObjBackdrop.bg.setOpacity(100);
    ObjBackdrop.bg.drawRect_Fill(WINDOWS_WIDTH, WINDOWS_HEIGHT);

    ObjBackdrop.bg.setOpacity(30);
    ObjBackdrop.bg.setColor(COLOR_THEME_GREEN);
    ObjBackdrop.bg.translateTo(-600, -100);
    ObjBackdrop.bg.drawCircle_Fill(100, 0, 360);

    ObjBackdrop.bg.setColor(COLOR_RED);
    ObjBackdrop.bg.translateTo(300, -200);
    ObjBackdrop.bg.drawCircle_Fill(200, 0, 360);

    ObjBackdrop.bg.setColor(COLOR_ORANGE);
    ObjBackdrop.bg.translateTo(-300, 200);
    ObjBackdrop.bg.drawCircle_Fill(100, 0, 360);

    ObjBackdrop.bg.translateTo(700, 100);
    ObjBackdrop.bg.drawCircle_Fill(50, 0, 360);

    ObjBackdrop.bg.setColor(COLOR_THEME_GREEN);
    ObjBackdrop.bg.translateTo(700, 200);
    ObjBackdrop.bg.drawCircle_Fill(300, 0, 360);

    ObjBackdrop.bg.translateTo(-700, 200);
    ObjBackdrop.bg.drawCircle_Fill(400, 0, 360);

    // Draw the background shade
    ObjBackdrop.bg.setColor(COLOR_THEME_GREEN_DARK_2);
    ObjBackdrop.bg.setOpacity(10);

    ObjBackdrop.bg.translateTo(0, 300);
    for (int i = 0; i < 80; i += 5)
    {
        ObjBackdrop.bg.drawRect_Fill(WINDOWS_WIDTH * 2, i + (((WINDOWS_HEIGHT / 2) - 300) * 2));
    }

    ObjBackdrop.bg.translateTo(0, -300);
    for (int i = 0; i < 80; i += 5)
    {
        ObjBackdrop.bg.drawRect_Fill(WINDOWS_WIDTH * 2, i + (((WINDOWS_HEIGHT / 2) - 300) * 2));
    }

    ObjBackdrop.bg.setColor(COLOR_THEME_GREEN);
    ObjBackdrop.bg.setOpacity(100);
    // Top half
    ObjBackdrop.bg.translateTo(0, 300);
    ObjBackdrop.bg.drawRect_Fill(WINDOWS_WIDTH, ((WINDOWS_HEIGHT / 2) - 300) * 2);

    // Bottom half
    ObjBackdrop.bg.translateTo(0, -300);
    ObjBackdrop.bg.drawRect_Fill(WINDOWS_WIDTH, ((WINDOWS_HEIGHT / 2) - 300) * 2);

    // Draw top shade
    ObjBackdrop.bg.setColor(COLOR_THEME_GREEN_DARK_2);
    ObjBackdrop.bg.setOpacity(10);
    ObjBackdrop.bg.translateTo(0, 0);

    for (int i = 0; i < 40; i += 4)
    {
        ObjBackdrop.bg.drawRect_Line(WINDOWS_WIDTH * 2, WINDOWS_HEIGHT - i, 40);
    }

    ObjBackdrop.bg.setColor(COLOR_WHITE);
    ObjBackdrop.bg.setOpacity(100);
    ObjBackdrop.bg.drawRect_Line(WINDOWS_WIDTH * 2, WINDOWS_HEIGHT, 20);
}
#endif