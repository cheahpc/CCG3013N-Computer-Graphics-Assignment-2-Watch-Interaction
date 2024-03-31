#ifndef RENDERMASTER_H
#define RENDERMASTER_H

// Renders
#include "renderdebug.h"
#include "renderBackdrop.h"
#include "renderHelp.h"
#include "renderWatch.h"
#include "renderUI.h"
#include "renderTimer.h"
#include "renderAlarm.h" // TODO: Implement renderAlarm.h
#include "renderPowerOn.h"
#include "renderPowerOff.h"
#include "renderCharging.h"

// anchorX, anchorY, scaleFactor, orientation, *color, opacity, orbitRadius, orbitAngle
void renderInit()
{
    // Initialize the rendering context
    glClearColor(1, 1, 1, 1);    // Set the background color to white, any area not rendered will be white.
    glMatrixMode(GL_PROJECTION); // Set the matrix mode to projection.
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT); // Load frame buffer.
    glMatrixMode(GL_MODELVIEW);   // Set matrix to
    glLoadIdentity();
    gluOrtho2D(-(WINDOWS_WIDTH / 2), WINDOWS_WIDTH / 2, -(WINDOWS_HEIGHT / 2), WINDOWS_HEIGHT / 2); // Set canvas to windows width and height.
}

void renderFinish()
{
    glutSwapBuffers();   // Swap foreground and background frames.
    glutPostRedisplay(); // Update the canvas display.
    glFlush();
    glFinish();
}

void renderMaster()
{
    renderInit(); // Initialize the canvas

    // Update the battery level
    if (System.isCharging && System.batteryLevel < 100)
        System.batteryLevel += System.chargingRate;

    if (System.batteryLevel > 100)
        System.batteryLevel = 100;
    // Backdrop
    renderBackdrop(); // Draw the backdrop

    // Charging Dock
    renderChargingDock(); // Draw the charging dock

    // Watch
    renderWatchStrap();
    renderWatchDial();   // Draw the watch dial
    renderWatchButton(); // Draw the watch button
    renderWatchBody();   // Draw the watch body

    // Charging
    if (System.state == SystemState::OFF && System.isCharging)
        renderScreenOffCharging(); // Draw the charging screen
    else if (!System.isCharging && ObjCharging.chargingAnimState != AnimState::IDLE)
        chargingStopped(); // Stop charging

    // Power On
    if (System.state == SystemState::POWERING_ON && System.batteryLevel >= System.minimumBatteryLevel)
        renderPowerOn(); // Draw the booting up UI

    if (System.state == SystemState::ON || System.state == SystemState::POWERING_OFF_TRIGGERED || System.state == SystemState::POWERING_OFF_CANCELLED)
    {
        // UI
        renderMainUI(); // Draw the time

        // Render Timer
        renderTimer(); // Draw the timer

        // Render Alarm
        renderAlarm(); // Draw the alarm

        // Low battery power off
        if (System.batteryLevel <= 0)
        {
            cout << "Battery running out... shutting down" << endl;
            System.state == SystemState::POWERING_OFF_TRIGGERED;
        }

        if (System.state == SystemState::POWERING_OFF_TRIGGERED)
            renderPowerOffConfirm();

        if (System.state == SystemState::POWERING_OFF_CANCELLED)
            renderPowerOffCancelled();
    }
    else if (System.state == SystemState::POWERING_OFF)
        renderPowerOff(); // Draw the power off UI

    // Help
    renderHelp(); // Draw the help

    // Grid Overlay
    renderGrid(); // Draw the grid

    renderFinish(); // Finish the rendering
}

#endif