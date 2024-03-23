#ifndef _RENDER_DEBUG_H_
#define _RENDER_DEBUG_H_

#include "object.cpp"
#include "color.h"
#include "dimen.h"

Object debugGrid = Object();
Object debug = Object();
void renderGrid()
{
    // Draw the grid
    debugGrid.scaleTo(1);
    debugGrid.translateTo(0, 0);
    debugGrid.setColor(COLOR_SILVER, 100);
    debugGrid.drawGrid(10, 1, 0);
    debugGrid.setColor(COLOR_GRAY, 100);
    debugGrid.drawGrid(50, 1, 0);
    debugGrid.setColor(COLOR_BLACK, 100);
    debugGrid.drawGrid(100, 1, 0);

    debugGrid.setColor(COLOR_RED, 100);
    // Center Line
    debugGrid.drawLine(-WINDOWS_WIDTH / 2, 0, WINDOWS_WIDTH / 2, 0, 2);
    debugGrid.drawLine(0, -WINDOWS_HEIGHT / 2, 0, WINDOWS_HEIGHT / 2, 2);

    // Center point
    debugGrid.drawCircle_Fill(5, 0, 360);
}

void renderDebug()
{
    GLint x[4] = {-150, 150, 150, -150};
    GLint y[4] = {150, 150, -150, -150};
    debug.setColor(COLOR_RED, 30);
    // debug.setOpacity(40);
    // debug.scaleTo(0.4);
    // debug.rotateTo(25);
    debug.translateTo(-100, -200);
    // debug.orbit(0, 0, 50, 1);
    debug.orbit(50, 1);

    // debug.drawPoint(0, 0, 20);
    // debug.drawLine(x, y, 10);
    // debug.drawTriangle_Fill(x, y);
    // debug.drawTriangle_Line(x, y, 10);
    // debug.drawQuad_Fill(x, y);
    // debug.drawQuad_Line(x, y, 10);
    debug.drawCircle_Fill(200, 270, 340);
    // debug.drawCircle_Line(100, 0, 270, 10);
    // debug.setColor(COLOR_BRONZE, 30);
    // debug.drawRoundedRect_Fill(200, 200, 40);
    // debug.drawRoundedRect_Line(200, 200, 40, 40);
    // debug.drawText("Hello World", 20);
}

#endif