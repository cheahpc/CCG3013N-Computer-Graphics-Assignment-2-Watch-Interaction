#ifndef RENDER_DEBUG_H
#define RENDER_DEBUG_H

void renderGrid()
{
    // Sub 10
    ObjDebug.grid.setColor(COLOR_SILVER);
    ObjDebug.grid.drawGrid(10, 1, 0);
    // Sub 50
    ObjDebug.grid.setColor(COLOR_GRAY);
    ObjDebug.grid.drawGrid(50, 1, 0);
    // Main 100
    ObjDebug.grid.setColor(COLOR_BLACK);
    ObjDebug.grid.drawGrid(100, 1, 0);

    ObjDebug.grid.setColor(COLOR_RED);
    // Center Line
    ObjDebug.grid.drawLine(-WINDOWS_WIDTH / 2, 0, WINDOWS_WIDTH / 2, 0, 2);
    ObjDebug.grid.drawLine(0, -WINDOWS_HEIGHT / 2, 0, WINDOWS_HEIGHT / 2, 2);

    // Center point
    ObjDebug.grid.drawCircle_Fill(5, 0, 360);
}

#endif