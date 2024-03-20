#ifndef _DIMEN_H_
#define _DIMEN_H_

#include <GL/glut.h>

const float WINDOWS_WIDTH = 1440;
const float WINDOWS_HEIGHT = 900;
// const float WINDOWS_WIDTH = 800;
// const float WINDOWS_HEIGHT = 600;
const float WINDOWS_CENTER_X = WINDOWS_WIDTH / 2;
const float WINDOWS_CENTER_Y = WINDOWS_HEIGHT / 2;

const float SCREEN_CENTER_X = glutGet(GLUT_SCREEN_WIDTH) / 2;
const float SCREEN_CENTER_Y = glutGet(GLUT_SCREEN_HEIGHT) / 2;
const float WINDOWS_INITIAL_POS_X = SCREEN_CENTER_X - (WINDOWS_WIDTH / 2);
const float WINDOWS_INITIAL_POS_Y = SCREEN_CENTER_Y - (WINDOWS_HEIGHT / 2);

#endif