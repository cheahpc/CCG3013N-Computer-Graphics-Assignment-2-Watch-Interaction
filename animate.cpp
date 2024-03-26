#include <chrono>
#include <ratio>
#include <iostream>
#include <ctime>
#include <cmath>
#include "object.cpp"
#include "bezier-easing.cpp"
// #include "bezier.cpp"

using namespace std::chrono;

void animateTranslate(Object &obj, GLfloat duration, const GLfloat bezierPoints[4], GLfloat dx, GLfloat dy)
{
    // Check if the animation flag is turned on
    if (obj.translateFlag == true)
    {
        if (obj.animationState != obj.STARTED)
        {
            // Set the start time of the animation
            obj.startTime = std::chrono::high_resolution_clock::now();
            obj.animationState = obj.STARTED;
            obj.initialPos[0] = obj.anchorX;
            obj.initialPos[1] = obj.anchorY;
        }

        // Get the current time
        auto currentTime = high_resolution_clock::now();
        // get elapsed time and cast it to compare with the duration in glfloat
        auto elapsedTime = duration_cast<milliseconds>(currentTime - obj.startTime).count();
        if (elapsedTime >= duration)
        {
            // End the animation
            obj.translateFlag = false;
            obj.animationState = obj.IDLE;

            return;
        }
        else
        {
            // cubic bezier interpolation
            // bezierPoints[0] = initial time = obj.startTime
            // bezierPoints[1] = initial value = obj.initialPos[0]
            // bezierPoints[2] = final value = obj.initialPos[0] + dx / dy
            // bezierPoints[3] = final time = obj.startTime + duration

            // bezier.cpp version
            // BezierEasing bezier_test({bezierPoints[0], bezierPoints[1]}, {bezierPoints[2], bezierPoints[3]});
            // GLfloat currentX = bezier_test.GetEasingProgress(elapsedTime / duration) * dx + obj.initialPos[0];
            // GLfloat currentY = bezier_test.GetEasingProgress(elapsedTime / duration) * dy + obj.initialPos[1];

            // Create a BezierEasing object with control points (0.25, 0.1) and (0.25, 1.0)
            BezierEasing easing({bezierPoints[0], bezierPoints[1]}, {bezierPoints[2], bezierPoints[3]});

            // Get the easing value for x = 0.5
            double easingValue = easing.BezierEasingGet(0.5);
            

            // Update the object's position
            obj.translateTo(currentX, currentY);
        }
    }
}
