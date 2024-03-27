#ifndef RENDER_DEBUG_H
#define RENDER_DEBUG_H

// anchorX, anchorY, scaleFactor, orientation, *color, opacity, orbitRadius, orbitAngle
Object debugGrid = Object(0, 0, 1, 0, COLOR_BLACK, 0);
Object debug = Object();

void renderGrid()
{
    // Sub 10
    debugGrid.setColor(COLOR_SILVER);
    debugGrid.drawGrid(10, 1, 0);
    // Sub 50
    debugGrid.setColor(COLOR_GRAY);
    debugGrid.drawGrid(50, 1, 0);
    // Main 100
    debugGrid.setColor(COLOR_BLACK);
    debugGrid.drawGrid(100, 1, 0);

    debugGrid.setColor(COLOR_RED);
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
    debug.setColor(COLOR_RED);
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
    debug.drawQuad_Fill(x, y);
    // debug.drawQuad_Line(x, y, 10);
    debug.drawCircle_Fill(200, 270, 340);
    // debug.drawCircle_Line(100, 0, 270, 10);
    // debug.setColor(COLOR_BRONZE);
    // debug.drawRoundedRect_Fill(200, 200, 40);
    // debug.drawRoundedRect_Line(200, 200, 40, 40);
    // debug.drawText("Hello World", 20);
}

Object debugObj1 = Object(100, 100, 1, -45, COLOR_BLUE, 100, 100, 120);
Object debugObj2 = Object(100, 100, 1, -45, COLOR_GREEN, 100);
GLfloat xVal, yVal, rotateVal, scaleVal, opacityVal, orbitVal;
void renderDebugControlTest()
{
    renderGrid(); // For references only
    GLint x[4] = {-10, -10, 10, 10};
    GLint y[4] = {-10, 10, 10, -10};

    debugObj1.drawCircle_Line(50, 25, 330, 80);
    // debugObj1.drawQuad_Fill(x, y);
    debugObj2.drawPoint(10);

    if (debugObj2.anchorX == 100 && debugObj2.anchorY == 100)
        xVal = yVal = -200;
    else if (debugObj2.anchorX == -100 && debugObj2.anchorY == -100)
        xVal = yVal = 200;
    if (debugObj1.orientation == -45)
        rotateVal = 90;
    else if (debugObj1.orientation == 45)
        rotateVal = -90;
    if (debugObj1.scaleFactor == 1)
        scaleVal = 4;
    else if (debugObj1.scaleFactor == 5)
        scaleVal = -4;

    if (debugObj1.opacity == 100)
        opacityVal = -80;
    else if (debugObj1.opacity == 20)
        opacityVal = 80;

    if (debugObj1.clockWiseFlag)
        orbitVal = 1;
    else if (!debugObj1.clockWiseFlag)
        orbitVal = -1;

    if (debugObj1.clockWiseFlag)
        orbitVal = 180;
    else if (!debugObj1.clockWiseFlag)
        orbitVal = -180;

    // animateTranslate(debugObj1, 1000, EASEOUT5, 100, 100);
    animateTranslate(debugObj2, 1000, EASEOUT5, xVal, yVal);
    animateTranslate(debugObj1, 1000, EASEOUT5, xVal, yVal);
    animateRotate(debugObj1, 1000, EASEOUT5, rotateVal);
    animateScale(debugObj1, 1000, EASEOUT5, scaleVal);
    animateOpacity(debugObj1, 1000, EASEOUT5, opacityVal);
    animateOrbit(debugObj1, 1000, EASEINOUT1, debugObj2.anchorX, debugObj2.anchorY, 100, orbitVal);
}

#endif