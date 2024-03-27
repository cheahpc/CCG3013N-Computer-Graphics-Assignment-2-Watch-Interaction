#ifndef ANIMATE_CPP
#define ANIMATE_CPP
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

void animateOpacity(Object &obj, GLfloat duration, const GLfloat easing[4], GLfloat opacity)
{
    if (obj.opacityFlag || obj.aOpacityState == obj.BUSY)
    {
        if (obj.aOpacityState == obj.IDLE)
        {
            // Set the start time, initial position, and flag of the animation
            obj.aOpacityStartTime = std::chrono::high_resolution_clock::now();
            obj.aOpacityState = obj.BUSY;
            obj.initialOpacity = obj.opacity;
            obj.animationTaskCount++;
        }

        // Get the current time
        auto currentTime = high_resolution_clock::now();
        // Calculate elapsed time
        auto elapsedTime = duration_cast<milliseconds>(currentTime - obj.aOpacityStartTime).count();

        // Compare if elapsed time is greater than the duration
        if (elapsedTime >= duration)
        {
            // End the animation
            obj.setOpacity(obj.initialOpacity + opacity);
            obj.aOpacityState = obj.IDLE;
            obj.opacityFlag = false;
            obj.animationTaskCount--;
            return;
        }
        else
        {
            // cubic bezier interpolation
            BezierEasing bezier_test({easing[0], easing[1]}, {easing[2], easing[3]});
            GLfloat progress = bezier_test.GetEasingProgress(elapsedTime / duration);
            GLfloat currentOpacity = obj.initialOpacity + opacity * progress;

            // Update the object's opacity
            obj.setOpacity(currentOpacity);
        }
    }
}

void animateOrbit(Object &obj, GLfloat duration, const GLfloat easing[4], GLfloat anchorX, GLfloat anchorY, GLfloat radius, GLfloat angle)
{
    if (obj.orbitFlag || obj.aOrbitState == obj.BUSY)
    {
        if (obj.aOrbitState == obj.IDLE)
        {
            // Set the start time, initial position, and flag of the animation
            obj.aOrbitStartTime = std::chrono::high_resolution_clock::now();
            obj.aOrbitState = obj.BUSY;
            obj.initialOrbitAngle = obj.orbitAngle;
            obj.animationTaskCount++;
        }

        // Get the current time
        auto currentTime = high_resolution_clock::now();
        // Calculate elapsed time
        auto elapsedTime = duration_cast<milliseconds>(currentTime - obj.aOrbitStartTime).count();

        // Compare if elapsed time is greater than the duration
        if (elapsedTime >= duration)
        {
            // End the animation
            obj.orbitTo(anchorX, anchorY, radius, obj.initialOrbitAngle + angle);
            obj.aOrbitState = obj.IDLE;
            obj.orbitFlag = false;
            obj.animationTaskCount--;
            return;
        }
        else
        {
            // cubic bezier interpolation
            BezierEasing bezier_test({easing[0], easing[1]}, {easing[2], easing[3]});
            GLfloat progress = bezier_test.GetEasingProgress(elapsedTime / duration);
            GLfloat currentAngle = obj.initialOrbitAngle + angle * progress;

            // Update the object's orbit
            obj.orbitTo(anchorX, anchorY, radius, currentAngle);
        }
    }
    else if (obj.orbited)
    {
        obj.orbitTo(anchorX, anchorY, radius, obj.orbitAngle);
    }
}
#endif