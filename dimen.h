#ifndef _DIMEN_H_
#define _DIMEN_H_

#include <GL/glut.h>

const float WINDOWS_WIDTH = 1600;
const float WINDOWS_HEIGHT = 900;
// const float WINDOWS_WIDTH = 800;
// const float WINDOWS_HEIGHT = 600;
const float WINDOWS_CENTER_X = WINDOWS_WIDTH / 2;
const float WINDOWS_CENTER_Y = WINDOWS_HEIGHT / 2;

const float SCREEN_CENTER_X = glutGet(GLUT_SCREEN_WIDTH) / 2;
const float SCREEN_CENTER_Y = glutGet(GLUT_SCREEN_HEIGHT) / 2;
const float WINDOWS_INITIAL_POS_X = SCREEN_CENTER_X - (WINDOWS_WIDTH / 2);
const float WINDOWS_INITIAL_POS_Y = SCREEN_CENTER_Y - (WINDOWS_HEIGHT / 2);

// Help
const float HELP_HINT_TEXT_SIZE = 4;
const float HELP_BOX_WIDTH = WINDOWS_WIDTH * 0.52;
const float HELP_BOX_HEIGHT = WINDOWS_HEIGHT * 0.85;
const float HELP_BOX_ROUND_RADIUS = 15;
const float HELP_BOX_OUTLINE_SIZE = 15;
const float HELP_LABEL_TEXT_SCALE = 0.17;
const float HELP_LABEL_TEXT_SIZE = 3;
const float HELP_TEXT_SCALE = 0.10;
const float HELP_TEXT_SIZE = 0.7;
const float HELP_POINT_TEXT_SIZE = 1.7;

const float HELP_TEXT_INIT_X = -790;
const float HELP_TEXT_INIT_Y = 345;
const float HELP_TEXT_Y_OFFSET = 20;

// Watch
// - Strap
const float WATCH_STRAP_WIDTH = 200;
const float WATCH_STRAP_HEIGHT = WINDOWS_WIDTH;
// - Body
const float WATCH_BODY_WIDTH = 450;
const float WATCH_BODY_HEIGHT = 550;
const float WATCH_BODY_ROUND_RADIUS = 75;
// - Dial
const float WATCH_DIAL_WIDTH = 30;
const float WATCH_DIAL_HEIGHT = 100;
const float WATCH_DIAL_ROUND_RADIUS = 15;
const float WATCH_DIAL_CENTER_X = WATCH_BODY_WIDTH / 2 + WATCH_DIAL_WIDTH / 2;
const float WATCH_DIAL_CENTER_Y = WATCH_BODY_HEIGHT / 4;
// - Button
const float WATCH_BUTTON_WIDTH = 25;
const float WATCH_BUTTON_HEIGHT = 220;
const float WATCH_BUTTON_ROUND_RADIUS = 10;
const float WATCH_BUTTON_CENTER_X = WATCH_BODY_WIDTH / 2;
const float WATCH_BUTTON_CENTER_Y = -70;

// - UI
const float UI_SCREEN_WIDTH = WATCH_BODY_WIDTH - 40;
const float UI_SCREEN_HEIGHT = WATCH_BODY_HEIGHT - 40;
const float UI_SCREEN_ROUND_RADIUS = WATCH_BODY_ROUND_RADIUS - (WATCH_BODY_WIDTH - UI_SCREEN_WIDTH) / 2;

// - DateTime
const float DATE_BOX_WIDTH = 500;
const float DATE_BOX_HEIGHT = 100;
const float DATE_BOX_ROUND_RADIUS = 10;

// - Complication
const float COMPLICATION_RADIUS = 40;
const float COMPLICATION_X_POS = -UI_SCREEN_WIDTH / 2 + COMPLICATION_RADIUS + 20;
const float COMPLICATION_Y_POS_1 = UI_SCREEN_HEIGHT / 8 * 3;
const float COMPLICATION_Y_POS_2 = UI_SCREEN_HEIGHT / 8 * 1;
const float COMPLICATION_Y_POS_3 = -UI_SCREEN_HEIGHT / 8 * 1;
const float COMPLICATION_Y_POS_4 = -UI_SCREEN_HEIGHT / 8 * 3;

const float COMP1_BATTERY_TEXT_SIZE = 2;
const float COMP1_BATTERY_TEXT_X_POS = COMPLICATION_X_POS - 22;
const float COMP1_BATTERY_TEXT_Y_POS = 202;
const float COMP4_TEXT_SIZE = 4;
const float COMP4_TEXT_X_POS = COMPLICATION_X_POS - 22;
const float COMP4_TEXT_Y_POS = -202;

// Apps - Timer
const float TIMER_SELECTOR_WIDTH = 100;
const float TIMER_SELECTOR_HEIGHT = 80;
const float TIMER_SELECTOR_ROUND_RADIUS = 10;
const float TIMER_HOUR_POS_X = -127;
const float TIMER_MIN_POS_X = 0;
const float TIMER_SEC_POS_X = 127;
const float TIMER_SELECTOR_POS_Y = -10;

// - Powering Off
const float PO_CONFIRM_DIAG_WIDTH = UI_SCREEN_WIDTH - 50;
const float PO_CONFIRM_DIAG_HEIGHT = UI_SCREEN_HEIGHT / 1.5;
const float PO_CONFIRM_DIAG_ROUND_RADIUS = 25;

// - Charging
const float DOCK_WIDTH = WATCH_BODY_WIDTH * 1.2;
const float DOCK_HEIGHT = WATCH_BODY_HEIGHT * 1.2;
const float DOCK_ROUND_RADIUS = WATCH_BODY_ROUND_RADIUS * 1.2;
const float DOCK_WIRE_WIDTH = 20;
const float DOCK_WIRE_HEIGHT = UI_SCREEN_HEIGHT;

#endif