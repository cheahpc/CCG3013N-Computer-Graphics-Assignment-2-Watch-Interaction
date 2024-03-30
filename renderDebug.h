#ifndef RENDER_DEBUG_H
#define RENDER_DEBUG_H

// anchorX, anchorY, scaleFactor, orientation, *color, opacity, orbitRadius, orbitAngle

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

void renderDebug()
{
    GLfloat x[4] = {-150, 150, 150, -150};
    GLfloat y[4] = {150, 150, -150, -150};
    // ObjDebug.test.setOpacity(40);
    // ObjDebug.test.scaleTo(0.4);
    // ObjDebug.test.rotateTo(25);
    // ObjDebug.test.translateTo(-100, -200);
    // ObjDebug.test.orbit(0, 0, 50, 1);
    // ObjDebug.test.orbit(50, 1);

    // ObjDebug.test.drawPoint(0, 0, 20);
    // ObjDebug.test.drawLine(x, y, 10);
    // ObjDebug.test.drawTriangle_Fill(x, y);
    // ObjDebug.test.drawTriangle_Line(x, y, 10);
    // ObjDebug.test.drawQuad_Fill(x, y);
    // ObjDebug.test.drawQuad_Line(x, y, 10);
    // ObjDebug.test.drawCircle_Fill(200, 270, 340);
    // ObjDebug.test.drawCircle_Line(100, 0, 270, 10);
    // ObjDebug.test.setColor(COLOR_BRONZE);
    // ObjDebug.test.drawRoundedRect_Fill(200, 200, 40);
    // ObjDebug.test.drawRoundedRect_Line(200, 200, 40, 40);
    // ObjDebug.test.drawText("Hello World", 20);
}

void renderDebugControlTest()
{
    GLfloat xVal, yVal, rotateVal, scaleVal, opacityVal, orbitVal;
    renderGrid(); // For references only
    // GLfloat x[4] = {-10, -10, 10, 10};
    // GLfloat y[4] = {-10, 10, 10, -10};

    // ObjDebug.ctrlTest1.drawCircle_Line(50, 25, 330, 80);
    // ObjDebug.ctrlTest1.drawQuad_Fill(x, y);
    // ObjDebug.ctrlTest2.drawPoint(10);

    // if (ObjDebug.ctrlTest2.anchorX == 100 && ObjDebug.ctrlTest2.anchorY == 100)
    //     xVal = yVal = -200;
    // else if (ObjDebug.ctrlTest2.anchorX == -100 && ObjDebug.ctrlTest2.anchorY == -100)
    //     xVal = yVal = 200;
    // if (ObjDebug.ctrlTest1.orientation == -45)
    //     rotateVal = 90;
    // else if (ObjDebug.ctrlTest1.orientation == 45)
    //     rotateVal = -90;
    // if (ObjDebug.ctrlTest1.scaleFactor == 1)
    //     scaleVal = 4;
    // else if (ObjDebug.ctrlTest1.scaleFactor == 5)
    //     scaleVal = -4;
    // if (ObjDebug.ctrlTest1.opacity == 100)
    //     opacityVal = -80;
    // else if (ObjDebug.ctrlTest1.opacity == 20)
    //     opacityVal = 80;
    // if (ObjDebug.ctrlTest1.clockWiseFlag)
    //     orbitVal = 1;
    // else if (!ObjDebug.ctrlTest1.clockWiseFlag)
    //     orbitVal = -1;
    // if (ObjDebug.ctrlTest1.clockWiseFlag)
    //     orbitVal = 180;
    // else if (!ObjDebug.ctrlTest1.clockWiseFlag)
    //     orbitVal = -180;

    // animateTranslate(ObjDebug.ctrlTest1, 1000, EASEOUT5, 100, 100);
    // animateTranslate(ObjDebug.ctrlTest2, 1000, EASEOUT5, xVal, yVal);
    // animateTranslate(ObjDebug.ctrlTest1, 1000, EASEOUT5, xVal, yVal);
    // animateRotate(ObjDebug.ctrlTest1, 1000, EASEOUT5, rotateVal);
    // animateScale(ObjDebug.ctrlTest1, 1000, EASEOUT5, scaleVal);
    // animateOpacity(ObjDebug.ctrlTest1, 1000, EASEOUT5, opacityVal);
    // animateOrbit(ObjDebug.ctrlTest1, 1000, EASEINOUT1, ObjDebug.ctrlTest2.anchorX, ObjDebug.ctrlTest2.anchorY, 100, orbitVal);
}

#endif