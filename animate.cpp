#include <chrono>
#include <ratio>
#include <iostream>
#include <ctime>
#include "object.cpp"

using namespace std::chrono;

void animateTranslate(Object &obj, GLfloat duration, GLfloat dx, GLfloat dy)
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
            // Linear interpolation
            GLfloat finalX = obj.initialPos[0] + dx;
            GLfloat finalY = obj.initialPos[1] + dy;
            // Calculate the current x and y position of the object base on the elapsed time
            GLfloat currentX = obj.initialPos[0] + (finalX - obj.initialPos[0]) * (elapsedTime / duration);
            GLfloat currentY = obj.initialPos[1] + (finalY - obj.initialPos[1]) * (elapsedTime / duration);

            // Update the object's position
            obj.translateTo(currentX, currentY);
        }
    }
}
