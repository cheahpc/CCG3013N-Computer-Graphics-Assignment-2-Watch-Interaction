#ifndef _OJBECT_H_
#define _OBJECT_H_
#include <iostream>
#include <GL/glut.h>
#include <chrono>
#include "math.h"

using namespace std;
class Object
{
public:
	// Constructor and Destructor
	Object();
	Object(GLfloat anchorX, GLfloat anchorY);
	Object(GLfloat anchorX, GLfloat anchorY, GLfloat scaleFactor, GLfloat orientation, const GLfloat *color, GLfloat opacity);
	Object(GLfloat anchorX, GLfloat anchorY, GLfloat scaleFactor, GLfloat orientation, const GLfloat *color, GLfloat opacity, GLfloat orbitRadius, GLfloat orbitAngle);
	~Object();

	// 2D primitives
	// Points
	void drawPoint(GLfloat size);
	void drawPoint(GLfloat x, GLfloat y, GLfloat size);
	void drawPoint(const GLfloat *v, GLfloat size);
	// Line
	void drawLine(GLfloat x1, GLfloat y1,
				  GLfloat x2, GLfloat y2,
				  GLfloat thickness);
	void drawLine(const GLfloat *v1, const GLfloat *v2, GLfloat thickness);
	// Triangle
	void drawTriangle_Fill(GLfloat x1, GLfloat y1,
						   GLfloat x2, GLfloat y2,
						   GLfloat x3, GLfloat y3);
	void drawTriangle_Fill(const GLfloat *x, const GLfloat *y);
	void drawTriangle_Line(GLfloat x1, GLfloat y1,
						   GLfloat x2, GLfloat y2,
						   GLfloat x3, GLfloat y3,
						   GLfloat thickness);
	void drawTriangle_Line(const GLfloat *x, const GLfloat *y, GLfloat thickness);
	// Rectangle
	void drawRect_Fill(GLfloat width, GLfloat height);
	void drawRect_Line(GLfloat width, GLfloat height, GLfloat thickness);
	// Quad
	void drawQuad_Fill(GLfloat x1, GLfloat y1,
					   GLfloat x2, GLfloat y2,
					   GLfloat x3, GLfloat y3,
					   GLfloat x4, GLfloat y4);
	void drawQuad_Fill(const GLfloat *x, const GLfloat *y);
	void drawQuad_Line(GLfloat x1, GLfloat y1,
					   GLfloat x2, GLfloat y2,
					   GLfloat x3, GLfloat y3,
					   GLfloat x4, GLfloat y4,
					   GLfloat thickness);
	void drawQuad_Line(const GLfloat *x, const GLfloat *y, GLfloat thickness);

	// Circles
	void drawCircle_Fill(GLfloat radius, GLfloat startDegree, GLfloat endDegree);
	void drawCircle_Line(GLfloat radius, GLfloat startDegree, GLfloat endDegree, GLfloat thickness);

	// Rounded Rectangle
	void drawRoundedRect_Fill(GLfloat width, GLfloat height, GLfloat radius);
	void drawRoundedRect_Line(GLfloat width, GLfloat height, GLfloat radius, GLfloat thickness);

	// Heart
	void drawHeart_Fill(GLfloat size);

	// Battery
	void drawBattery_Fill(GLfloat size, GLfloat batteryLevel, bool isCharging, const GLfloat *batColor, const GLfloat *batLvlColor);

	// Timer
	void drawStopwatch_Fill(GLfloat size);

	// Alarm
	void drawTimer_Fill(GLfloat size);

	// 2D transformation
	void translateTo(GLfloat x, GLfloat y);
	void translateTo(GLfloat *p);
	void translate(GLfloat tX, GLfloat tY);
	void translate(GLfloat *p);
	void rotateTo(GLfloat angle);
	void rotate(GLfloat angle);
	void orbitTo(GLfloat anchorX, GLfloat anchorY, GLfloat radius, GLfloat angle);
	void orbit(GLfloat radius, GLfloat speed);
	void orbit(GLfloat anchorX, GLfloat anchorY, GLfloat radius, GLfloat speed);
	void mirrorX();
	void mirrorY();

	void scaleTo(GLfloat scaleFactor);
	void scale(GLfloat scale);

	// Utilities
	void drawText(char *string, GLfloat size);
	void drawGrid(GLfloat gridSpace, GLfloat lineThickness, GLfloat length);

	// Other Control
	void setOpacity(GLfloat opacity);
	void setColor(const GLfloat *color);

	void glStartInit();
	void glEndReset();

	GLfloat anchorX, anchorY, scaleFactor, orientation, orbitAngle;
	GLfloat color[3], opacity;
	bool scaleFlag, rotateFlag, translateFlag, orbitFlag, clockWiseFlag, opacityFlag;
	bool orbited, orbitRadius;

	// Properties for translate animation
	GLfloat initialPos[2];
	GLfloat initialOrientation;
	GLfloat initialScale;
	GLfloat initialOpacity;
	GLfloat initialOrbitAngle;
	int animationTaskCount;

	chrono::high_resolution_clock::time_point aTranslateStartTime, aRotateStartTime, aScaleStartTime, aOpacityStartTime, aOrbitStartTime;

	enum AnimationState
	{
		BUSY,
		IDLE
	};

	AnimationState aRotateState, aTranslateState, aScaleState, aOpacityState, aOrbitState;
};

#endif