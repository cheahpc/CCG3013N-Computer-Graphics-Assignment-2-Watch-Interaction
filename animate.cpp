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
    if (obj.translateFlag || obj.aTranslateState == obj.BUSY)
    {
        if (obj.aTranslateState == obj.IDLE)
        {
            // Set the start time, initial position, and flag of the animation
            obj.aTranslateStartTime = std::chrono::high_resolution_clock::now();
            obj.aTranslateState = obj.BUSY;
            obj.initialPos[0] = obj.anchorX;
            obj.initialPos[1] = obj.anchorY;
            obj.animationTaskCount++;
        }

        // Get the current time
        auto currentTime = high_resolution_clock::now();
        // Calculate elapsed time
        auto elapsedTime = duration_cast<milliseconds>(currentTime - obj.aTranslateStartTime).count();

        // Compare if elapsed time is greater than the duration
        if (elapsedTime >= duration)
        {
            // End the animation
            obj.translateTo(obj.initialPos[0] + dx, obj.initialPos[1] + dy);
            obj.translateFlag = false;
            obj.aTranslateState = obj.IDLE;
            obj.animationTaskCount--;
            return;
        }
        else
        {
            // cubic bezier interpolation
            BezierEasing bezier_test({easing[0], easing[1]}, {easing[2], easing[3]});
            GLfloat progress = bezier_test.GetEasingProgress(elapsedTime / duration);
            GLfloat currentX = obj.initialPos[0] + dx * progress;
            GLfloat currentY = obj.initialPos[1] + dy * progress;

            // Update the object's position
            obj.translateTo(currentX, currentY);
        }
    }
}

void animateRotate(Object &obj, GLfloat duration, const GLfloat easing[4], GLfloat angle)
{
    if (obj.rotateFlag || obj.aRotateState == obj.BUSY)
    {
        if (obj.aRotateState == obj.IDLE)
        {
            // Set the start time, initial position, and flag of the animation
            obj.aRotateStartTime = std::chrono::high_resolution_clock::now();
            obj.aRotateState = obj.BUSY;
            obj.initialOrientation = obj.orientation;
            obj.animationTaskCount++;
        }

        // Get the current time
        auto currentTime = high_resolution_clock::now();
        // Calculate elapsed time
        auto elapsedTime = duration_cast<milliseconds>(currentTime - obj.aRotateStartTime).count();

        // Compare if elapsed time is greater than the duration
        if (elapsedTime >= duration)
        {
            // End the animation
            obj.rotateTo(obj.initialOrientation + angle);
            obj.aRotateState = obj.IDLE;
            obj.rotateFlag = false;
            obj.animationTaskCount--;
            return;
        }
        else
        {
            // cubic bezier interpolation
            BezierEasing bezier_test({easing[0], easing[1]}, {easing[2], easing[3]});
            GLfloat progress = bezier_test.GetEasingProgress(elapsedTime / duration);
            GLfloat currentAngle = obj.initialOrientation + angle * progress;

            // Update the object's rotation
            obj.rotateTo(currentAngle);
        }
    }
}

void animateScale(Object &obj, GLfloat duration, const GLfloat easing[4], GLfloat scale)
{
    if (obj.scaleFlag || obj.aScaleState == obj.BUSY)
    {
        if (obj.aScaleState == obj.IDLE)
        {
            // Set the start time, initial position, and flag of the animation
            obj.aScaleStartTime = std::chrono::high_resolution_clock::now();
            obj.aScaleState = obj.BUSY;
            obj.initialScale = obj.scaleFactor;
            obj.animationTaskCount++;
        }
        // Get the current time
        auto currentTime = high_resolution_clock::now();
        // Calculate elapsed time
        auto elapsedTime = duration_cast<milliseconds>(currentTime - obj.aScaleStartTime).count();

        // Compare if elapsed time is greater than the duration
        if (elapsedTime >= duration)
        {
            // End the animation
            obj.scaleTo(obj.initialScale + scale);
            obj.aScaleState = obj.IDLE;
            obj.scaleFlag = false;
            obj.animationTaskCount--;

            return;
        }
        else
        {
            // cubic bezier interpolation
            BezierEasing bezier_test({easing[0], easing[1]}, {easing[2], easing[3]});
            GLfloat progress = bezier_test.GetEasingProgress(elapsedTime / duration);
            GLfloat currentScale = obj.initialScale + scale * progress;

            // Update the object's scale
            obj.scaleTo(currentScale);
        }
    }
}