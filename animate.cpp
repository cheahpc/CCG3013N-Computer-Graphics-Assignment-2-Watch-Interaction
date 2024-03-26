#include <chrono>
#include <ratio>
#include <iostream>
#include <ctime>
#include <cmath>
#include "object.cpp"
#include "bezier-easing.cpp"

using namespace std::chrono;

void animateTranslate(Object &obj, GLfloat duration, const GLfloat easing[4], GLfloat dx, GLfloat dy)
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
            // easing[0] = initial time = obj.startTime
            // easing[1] = initial value = obj.initialPos[0]
            // easing[2] = final value = obj.initialPos[0] + dx / dy
            // easing[3] = final time = obj.startTime + duration
            BezierEasing bezier_test({easing[0], easing[1]}, {easing[2], easing[3]});
            GLfloat currentX = bezier_test.GetEasingProgress(elapsedTime / duration) * dx + obj.initialPos[0];
            GLfloat currentY = bezier_test.GetEasingProgress(elapsedTime / duration) * dy + obj.initialPos[1];

            // Update the object's position
            obj.translateTo(currentX, currentY);
        }
    }
}

void animateRotate(Object &obj, GLfloat duration, const GLfloat easing[4], GLfloat angle)
{
    // Check if the animation flag is turned on
    if (obj.rotateFlag == true)
    {
        // ! solve the animation reset problem when 2 and more animation is called
        if (obj.animationState != obj.STARTED)
        {
            // Set the start time of the animation
            obj.startTime = std::chrono::high_resolution_clock::now();
            obj.animationState = obj.STARTED;
            obj.initialOrientation = obj.orientation;
        }

        // Get the current time
        auto currentTime = high_resolution_clock::now();
        // get elapsed time and cast it to compare with the duration in glfloat
        auto elapsedTime = duration_cast<milliseconds>(currentTime - obj.startTime).count();
        if (elapsedTime >= duration)
        {
            // End the animation
            obj.rotateFlag = false;
            obj.animationState = obj.IDLE;
            return;
        }
        else
        {
            // cubic bezier interpolation
            // easing[0] = initial time = obj.startTime
            // easing[1] = initial value = obj.initialOrientation
            // easing[2] = final value = obj.initialOrientation + angle
            // easing[3] = final time = obj.startTime + duration
            BezierEasing bezier_test({easing[0], easing[1]}, {easing[2], easing[3]});
            GLfloat currentAngle = bezier_test.GetEasingProgress(elapsedTime / duration) * angle + obj.initialOrientation;

            // Update the object's position
            obj.rotateTo(currentAngle);
        }
    }
}
