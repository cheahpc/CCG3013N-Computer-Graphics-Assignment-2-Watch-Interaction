#ifndef OBJECT_CPP
#define OBJECT_CPP
#include "object.h"
#ifndef M_PI
#define M_PI 3.1415926535897932384626433
#endif

using namespace std;

#pragma region Constructors
Object::Object()
{
	this->anchorX = 0;
	this->anchorY = 0;
	this->scaleFactor = 1;
	this->orientation = 0;
	this->orbitAngle = 0;
	this->opacity = 100;
	this->color[0] = 0;
	this->color[1] = 0;
	this->color[2] = 0;

	this->scaleFlag = false;
	this->rotateFlag = false;
	this->translateFlag = false;
	this->orbitFlag = false;
	this->clockWiseFlag = false;

	this->orbited = false;
	this->orbitRadius = orbitRadius;

	// Animation properties
	this->initialPos[0] = 0;
	this->initialPos[1] = 0;
	this->initialOrientation = 0;
	this->initialScale = 0;
	this->initialOpacity = 0;
	this->initialOrbitAngle = 0;
	this->animationTaskCount = 0;

	// Animation State
	this->aTranslateState = this->IDLE;
	this->aRotateState = this->IDLE;
	this->aScaleState = this->IDLE;
	this->aOpacityState = this->IDLE;
	this->aOrbitState = this->IDLE;
}
Object::Object(GLfloat anchorX, GLfloat anchorY)
{
	this->anchorX = anchorX;
	this->anchorY = anchorY;
	this->scaleFactor = 1;
	this->orientation = 0;
	this->orbitAngle = 0;
	this->opacity = 100;
	this->color[0] = 0;
	this->color[1] = 0;
	this->color[2] = 0;

	this->scaleFlag = false;
	this->rotateFlag = false;
	this->translateFlag = false;
	this->orbitFlag = false;
	this->clockWiseFlag = false;
	this->opacityFlag = false;

	this->orbited = false;
	this->orbitRadius = 0;

	// Animation properties
	this->initialPos[0] = 0;
	this->initialPos[1] = 0;
	this->initialOrientation = 0;
	this->initialScale = 0;
	this->initialOpacity = 0;
	this->initialOrbitAngle = 0;
	this->animationTaskCount = 0;

	// Animation State
	this->aTranslateState = this->IDLE;
	this->aRotateState = this->IDLE;
	this->aScaleState = this->IDLE;
	this->aOpacityState = this->IDLE;
	this->aOrbitState = this->IDLE;
}
Object::Object(GLfloat anchorX, GLfloat anchorY, GLfloat scaleFactor, GLfloat orientation, const GLfloat *color, GLfloat opacity)
{
	this->anchorX = anchorX;
	this->anchorY = anchorY;
	this->scaleFactor = scaleFactor;
	this->orientation = orientation;
	this->orbitAngle = 0;
	this->opacity = opacity;
	this->color[0] = color[0];
	this->color[1] = color[1];
	this->color[2] = color[2];

	this->scaleFlag = false;
	this->rotateFlag = false;
	this->translateFlag = false;
	this->orbitFlag = false;
	this->clockWiseFlag = false;
	this->opacityFlag = false;

	this->orbited = false;
	this->orbitRadius = 0;

	// Animation properties
	this->initialPos[0] = 0;
	this->initialPos[1] = 0;
	this->initialOrientation = 0;
	this->initialScale = 0;
	this->initialOpacity = 0;
	this->initialOrbitAngle = 0;
	this->animationTaskCount = 0;

	// Animation State
	this->aTranslateState = this->IDLE;
	this->aRotateState = this->IDLE;
	this->aScaleState = this->IDLE;
	this->aOpacityState = this->IDLE;
	this->aOrbitState = this->IDLE;
}
Object::Object(GLfloat anchorX, GLfloat anchorY, GLfloat scaleFactor, GLfloat orientation, const GLfloat *color, GLfloat opacity, GLfloat orbitRadius, GLfloat orbitAngle)
{
	this->anchorX = anchorX;
	this->anchorY = anchorY;
	this->scaleFactor = scaleFactor;
	this->orientation = orientation;
	this->orbitAngle = orbitAngle;
	this->opacity = opacity;
	this->color[0] = color[0];
	this->color[1] = color[1];
	this->color[2] = color[2];

	this->scaleFlag = false;
	this->rotateFlag = false;
	this->translateFlag = false;
	this->orbitFlag = false;
	this->clockWiseFlag = false;
	this->opacityFlag = false;

	this->orbited = true;
	this->orbitRadius = orbitRadius;

	// Animation properties
	this->initialPos[0] = 0;
	this->initialPos[1] = 0;
	this->initialOrientation = 0;
	this->initialScale = 0;
	this->initialOpacity = 0;
	this->initialOrbitAngle = 0;
	this->animationTaskCount = 0;

	// Animation State
	this->aTranslateState = this->IDLE;
	this->aRotateState = this->IDLE;
	this->aScaleState = this->IDLE;
	this->aOpacityState = this->IDLE;
	this->aOrbitState = this->IDLE;
}
Object::~Object()
{
}
#pragma endregion Constructors

// 2D drawing functions
#pragma region Points
void Object::drawPoint(GLfloat size)
{
	glStartInit();
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2f(0, 0);
	glEndReset();
}
void Object::drawPoint(GLfloat x, GLfloat y, GLfloat size)
{
	glStartInit();
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEndReset();
}
void Object::drawPoint(const GLfloat *v, GLfloat size)
{
	drawPoint(v[0], v[1], size);
}
#pragma endregion Points

#pragma region Line
void Object::drawLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat thickness)
{
	glStartInit();
	glLineWidth(thickness);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEndReset();
}
void Object::drawLine(const GLfloat *v1, const GLfloat *v2, GLfloat thickness)
{
	drawLine(v1[0], v1[1], v2[0], v2[1], thickness);
}
#pragma endregion Line

#pragma region Triangle
void Object::drawTriangle_Fill(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3)
{
	glStartInit();
	glBegin(GL_TRIANGLES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glEndReset();
}
void Object::drawTriangle_Fill(const GLfloat *x, const GLfloat *y)
{
	drawTriangle_Fill(x[0], y[0], x[1], y[1], x[2], y[2]);
}
void Object::drawTriangle_Line(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat thickness)
{
	glStartInit();
	glLineWidth(thickness);
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glEndReset();
}
void Object::drawTriangle_Line(const GLfloat *x, const GLfloat *y, GLfloat thickness)
{
	drawTriangle_Line(x[0], y[0], x[1], y[1], x[2], y[2], thickness);
}
#pragma endregion Triangle

#pragma region Rectangle
void Object::drawRect_Fill(GLfloat width, GLfloat height)
{
	GLfloat x[2] = {(-width / 2), (width / 2)};
	GLfloat y[2] = {(-height / 2), (height / 2)};
	glStartInit(); // Apply settings
	glBegin(GL_QUADS);
	glVertex2f(x[0], y[0]);
	glVertex2f(x[0], y[1]);
	glVertex2f(x[1], y[1]);
	glVertex2f(x[1], y[0]);
	glEndReset();
}
void Object::drawRect_Line(GLfloat width, GLfloat height, GLfloat thickness)
{
	GLfloat outerX[2] = {(-width / 2) - (thickness / 2), (width / 2) + (thickness / 2)};
	GLfloat outerY[2] = {(-height / 2) - (thickness / 2), (height / 2) + (thickness / 2)};
	GLfloat innerX[2] = {(-width / 2) + (thickness / 2), (width / 2) - (thickness / 2)};
	GLfloat innerY[2] = {(-height / 2) + (thickness / 2), (height / 2) - (thickness / 2)};
	glStartInit(); // Apply settings
	glBegin(GL_QUADS);
	// Left Part
	glVertex2f(outerX[0], outerY[0]);
	glVertex2f(outerX[0], outerY[1]);
	glVertex2f(innerX[0], outerY[1]);
	glVertex2f(innerX[0], outerY[0]);

	// Top Part
	glVertex2f(innerX[0], innerY[1]);
	glVertex2f(innerX[0], outerY[1]);
	glVertex2f(innerX[1], outerY[1]);
	glVertex2f(innerX[1], innerY[1]);

	// Right Part
	glVertex2f(innerX[1], outerY[0]);
	glVertex2f(innerX[1], outerY[1]);
	glVertex2f(outerX[1], outerY[1]);
	glVertex2f(outerX[1], outerY[0]);

	// Bottom Part
	glVertex2f(innerX[0], outerY[0]);
	glVertex2f(innerX[0], innerY[0]);
	glVertex2f(innerX[1], innerY[0]);
	glVertex2f(innerX[1], outerY[0]);

	glEndReset();
}
#pragma endregion Rectangle

#pragma region Quad
void Object::drawQuad_Fill(GLfloat x1, GLfloat y1,
						   GLfloat x2, GLfloat y2,
						   GLfloat x3, GLfloat y3,
						   GLfloat x4, GLfloat y4)
{
	glStartInit(); // Apply settings
	glBegin(GL_QUADS);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEndReset();
}

void Object::drawQuad_Fill(const GLfloat *x, const GLfloat *y)
{
	this->drawQuad_Fill(x[0], y[0], x[1], y[1], x[2], y[2], x[3], y[3]);
}
void Object::drawQuad_Line(GLfloat x1, GLfloat y1,
						   GLfloat x2, GLfloat y2,
						   GLfloat x3, GLfloat y3,
						   GLfloat x4, GLfloat y4,
						   GLfloat thickness)
{
	glStartInit(); // Apply settings

	glLineWidth(thickness);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);

	glVertex2f(x2, y2);
	glVertex2f(x3, y3);

	glVertex2f(x3, y3);
	glVertex2f(x4, y4);

	glVertex2f(x4, y4);
	glVertex2f(x1, y1);
	glEndReset();
}
void Object::drawQuad_Line(const GLfloat *x,
						   const GLfloat *y,
						   GLfloat thickness)
{
	drawQuad_Line(x[0], y[0], x[1], y[1], x[2], y[2], x[3], y[3], thickness);
}
#pragma endregion Quad

#pragma region Circle
void Object::drawCircle_Fill(GLfloat radius, GLfloat startDegree, GLfloat endDegree)
{
	endDegree += startDegree > endDegree ? 360 : 0;
	GLfloat angle = (endDegree - startDegree) * M_PI / 180;	   // get the angle in radian
	int triangleAmount = (int)((endDegree - startDegree) / 3); // Calculate the triangle amount base on the angle

	glStartInit();
	glRotatef(90 - startDegree, 0.0f, 0.0f, 1.0f); // Offset

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0); // center of circle
	for (int i = 0; i <= triangleAmount; i++)
	{
		GLfloat currentAngle = i * angle / triangleAmount;

		glVertex2f((radius * cos(currentAngle)),
				   -(radius * sin(currentAngle)));
	}
	glEndReset();
}
void Object::drawCircle_Line(GLfloat radius, GLfloat startDegree, GLfloat endDegree, GLfloat thickness)
{
	endDegree += startDegree > endDegree ? 360 : 0;
	GLfloat angle = (endDegree - startDegree) * M_PI / 180;	 // get the angle in radian
	int triangleAmount = (int)(endDegree - startDegree) * 4; // Calculate the triangle amount base on the angle
	GLfloat currentAngle;
	GLfloat radius_outer = radius + (thickness / 2);
	GLfloat radius_inner = radius - (thickness / 2);

	glStartInit();
	glRotatef(90 - startDegree, 0.0f, 0.0f, 1.0f);

	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= triangleAmount; i++)
	{
		currentAngle = i * angle / triangleAmount;
		glVertex2f((radius_outer * cos(currentAngle)),
				   -(radius_outer * sin(currentAngle)));
		glVertex2f((radius_inner * cos(currentAngle)),
				   -(radius_inner * sin(currentAngle)));
	}
	this->glEndReset();
}
#pragma endregion Circle

#pragma region Rounded Rectangle
void Object::drawRoundedRect_Fill(GLfloat width, GLfloat height, GLfloat radius)
{
	GLfloat angle = 90 * M_PI / 180; // get the angle in radian
	GLfloat x[4], y[4], currentAngle;
	x[0] = -(width / 2);
	x[1] = -(width / 2) + radius;
	x[2] = (width / 2) - radius;
	x[3] = (width / 2);
	y[0] = -(height / 2);
	y[1] = -(height / 2) + radius;
	y[2] = (height / 2) - radius;
	y[3] = (height / 2);

	// Draw the rectangles
	glStartInit();
	glBegin(GL_QUADS);
	// Center rectangle
	glVertex2f(x[1], y[1]);
	glVertex2f(x[2], y[1]);
	glVertex2f(x[2], y[2]);
	glVertex2f(x[1], y[2]);

	// Start rectangle
	glVertex2f(x[0], y[1]);
	glVertex2f(x[1], y[1]);
	glVertex2f(x[1], y[2]);
	glVertex2f(x[0], y[2]);

	// End rectangle
	glVertex2f(x[2], y[1]);
	glVertex2f(x[3], y[1]);
	glVertex2f(x[3], y[2]);
	glVertex2f(x[2], y[2]);

	// Top rectangle
	glVertex2f(x[1], y[2]);
	glVertex2f(x[2], y[2]);
	glVertex2f(x[2], y[3]);
	glVertex2f(x[1], y[3]);

	// Bottom rectangle
	glVertex2f(x[1], y[0]);
	glVertex2f(x[2], y[0]);
	glVertex2f(x[2], y[1]);
	glVertex2f(x[1], y[1]);
	glEndReset();

	// Draw the corners
	// Top left corner
	glStartInit();
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x[1], y[2]);
	for (int i = 0; i <= 30; i++)
	{
		currentAngle = i * angle / 30;
		glVertex2f(x[1] - (radius * cos(currentAngle)),
				   y[2] + (radius * sin(currentAngle)));
	}
	glEndReset();

	// Top right corner
	glStartInit();
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x[2], y[2]);
	for (int i = 0; i <= 30; i++)
	{
		currentAngle = i * angle / 30;
		glVertex2f(x[2] + (radius * cos(currentAngle)),
				   y[2] + (radius * sin(currentAngle)));
	}
	glEndReset();

	// Bottom right corner
	glStartInit();
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x[2], y[1]);
	for (int i = 0; i <= 30; i++)
	{
		currentAngle = i * angle / 30;
		glVertex2f(x[2] + (radius * cos(currentAngle)),
				   y[1] - (radius * sin(currentAngle)));
	}
	glEndReset();

	// Bottom left corner
	glStartInit();
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x[1], y[1]);
	for (int i = 0; i <= 30; i++)
	{
		currentAngle = i * angle / 30;
		glVertex2f(x[1] - (radius * cos(currentAngle)),
				   y[1] - (radius * sin(currentAngle)));
	}
	glEndReset();
}

void Object::drawRoundedRect_Line(GLfloat width, GLfloat height, GLfloat radius, GLfloat thickness)
{
	GLfloat angle = 90 * M_PI / 180; // get the angle in radian
	GLfloat x[4], y[4], currentAngle;
	GLfloat outerRadius = -(thickness / 2) - (thickness / 2);
	GLfloat innerRadius = -(thickness / 2) + (thickness / 2);
	x[0] = -(width / 2) - (thickness / 2);
	x[1] = -(width / 2) + (thickness / 2);
	x[2] = (width / 2) - (thickness / 2);
	x[3] = (width / 2) + (thickness / 2);
	y[0] = -(height / 2) - (thickness / 2);
	y[1] = -(height / 2) + (thickness / 2);
	y[2] = (height / 2) - (thickness / 2);
	y[3] = (height / 2) + (thickness / 2);

	// Draw the rectangles
	glStartInit();
	glBegin(GL_QUADS);
	// Start rectangle
	glVertex2f(x[0], y[1]);
	glVertex2f(x[1], y[1]);
	glVertex2f(x[1], y[2]);
	glVertex2f(x[0], y[2]);

	// End rectangle
	glVertex2f(x[2], y[1]);
	glVertex2f(x[3], y[1]);
	glVertex2f(x[3], y[2]);
	glVertex2f(x[2], y[2]);

	// Top rectangle
	glVertex2f(x[1], y[2]);
	glVertex2f(x[2], y[2]);
	glVertex2f(x[2], y[3]);
	glVertex2f(x[1], y[3]);

	// Bottom rectangle
	glVertex2f(x[1], y[0]);
	glVertex2f(x[2], y[0]);
	glVertex2f(x[2], y[1]);
	glVertex2f(x[1], y[1]);
	glEndReset();

	// Draw the corners
	// Top left corner
	glStartInit();
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 30; i++)
	{
		currentAngle = i * angle / 30;
		glVertex2f(x[1] + (outerRadius * cos(currentAngle)),
				   y[2] - (outerRadius * sin(currentAngle)));
		glVertex2f(x[1] + (innerRadius * cos(currentAngle)),
				   y[2] - (innerRadius * sin(currentAngle)));
	}
	glEndReset();

	// Top right corner
	glStartInit();
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 30; i++)
	{
		currentAngle = i * angle / 30;
		glVertex2f(x[2] - (outerRadius * cos(currentAngle)),
				   y[2] - (outerRadius * sin(currentAngle)));
		glVertex2f(x[2] - (innerRadius * cos(currentAngle)),
				   y[2] - (innerRadius * sin(currentAngle)));
	}
	glEndReset();

	// Bottom right corner
	glStartInit();
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 30; i++)
	{
		currentAngle = i * angle / 30;
		glVertex2f(x[2] - (outerRadius * cos(currentAngle)),
				   y[1] + (outerRadius * sin(currentAngle)));
		glVertex2f(x[2] - (innerRadius * cos(currentAngle)),
				   y[1] + (innerRadius * sin(currentAngle)));
	}
	glEndReset();

	// Bottom left corner
	glStartInit();
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 30; i++)
	{
		currentAngle = i * angle / 30;
		glVertex2f(x[1] + (outerRadius * cos(currentAngle)),
				   y[1] + (outerRadius * sin(currentAngle)));
		glVertex2f(x[1] + (innerRadius * cos(currentAngle)),
				   y[1] + (innerRadius * sin(currentAngle)));
	}
	glEndReset();
}

#pragma endregion Rounded Rectangle

#pragma region Heart
void Object::drawHeart_Fill(GLfloat size)
{
	GLfloat initialX = this->anchorX;
	GLfloat initialY = this->anchorY;

	GLfloat x[2] = {(-size / 2), (size / 2)};
	GLfloat y[2] = {(-size / 2), (size / 2)};
	GLfloat radius = size / 2;

	rotateTo(45);
	// 1. draw a square
	drawRect_Fill(size, size);

	// 2. draw a semi-circle
	glStartInit();
	glTranslatef(-radius, 0, 0);
	glRotatef(-90, 0.0f, 0.0f, 1.0f);
	glTranslatef(radius, 0, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(-radius, 0); // center of circle
	for (int i = 0; i <= 60; i++)
	{
		GLfloat currentAngle = i * M_PI / 60;
		glVertex2f(-radius - radius * cos(currentAngle),
				   -radius * sin(currentAngle));
	}
	glEndReset();

	// 3. draw another semi-circle
	glStartInit();
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, radius); // center of circle
	for (int i = 0; i <= 60; i++)
	{
		GLfloat currentAngle = i * M_PI / 60;
		glVertex2f(-radius * cos(currentAngle),
				   radius + radius * sin(currentAngle));
	}
	glEndReset();

	rotateTo(0);
}
#pragma endregion Heart

#pragma region Battery
void Object::drawBattery_Fill(GLfloat size, GLfloat batteryLevel, bool isCharging, const GLfloat *batColor, const GLfloat *batLvlColor)
{
	// Battery properties
	GLfloat width = size, height = size * 2;
	GLfloat thickness = size * 0.12;
	GLfloat radius = thickness;

	GLfloat capCenterX = 0;
	GLfloat capCenterY = (height / 2) + thickness * 2;
	GLfloat capWidth = width * 0.45;

	GLfloat originalX = this->anchorX;
	GLfloat originalY = this->anchorY;

	// Draw the battery level
	setColor(batLvlColor);
	GLfloat levelHeight = (height - thickness) * batteryLevel / 100;
	translateTo(this->anchorX, this->anchorY - height / 2 + levelHeight / 2 + thickness / 2);
	drawRect_Fill(width - thickness, levelHeight);
	setColor(batColor);

	// Draw the battery charging lightning icon
	if (isCharging)
	{
		// Define 7 point of the lightning
		GLfloat x[5] = {-(size / 2) * 0.75,
						-(size / 2) * 0.4,
						-(size / 2) * 0.25,
						(size / 2) * 0.1,
						(size / 2) * 0.75};

		GLfloat y[6] = {-size * 0.8,
						-size * 0.1,
						-size * 0.05,
						size * 0.15,
						size * 0.2,
						size * 0.7};
		translateTo(originalX, originalY);
		glStartInit();
		glBegin(GL_POLYGON);
		glVertex2f(x[2], y[2]); // point 7
		glVertex2f(x[0], y[1]); // point 1
		glVertex2f(x[1], y[5]); // point 2
		glVertex2f(x[4], y[5]); // point 3
		glVertex2f(x[3], y[3]); // point 4
		glVertex2f(x[4], y[4]); // point 5
		glVertex2f(x[4], y[4]); // point 5
		glVertex2f(x[0], y[0]); // point 6
		glEndReset();
	}

	// Draw the battery head
	translateTo(originalX + capCenterX, originalY + capCenterY);
	GLfloat angle = 90 * M_PI / 180; // get the angle in radian
	GLfloat x[2], y[2], currentAngle;
	GLfloat capRadius = 2 * (radius * 0.75);
	GLfloat innerRadius = 4;
	x[0] = -capWidth / 2 + radius;
	x[1] = capWidth / 2 - radius;
	y[0] = -radius * 0.75;
	y[1] = radius * 0.75;
	// Center piece
	drawQuad_Fill(x[0], y[0], x[0], y[1], x[1], y[1], x[1], y[0]);
	// Cap left corner
	glStartInit();
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x[0], y[0]); // center of circle
	for (int i = 0; i <= 30; i++)
	{
		GLfloat currentAngle = i * angle / 30;
		glVertex2f(x[0] - (capRadius * cos(currentAngle)),
				   y[0] + (capRadius * sin(currentAngle)));
	}
	glEndReset();
	// Cap right corner
	glStartInit();
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x[1], y[0]); // center of circle
	for (int i = 0; i <= 30; i++)
	{
		GLfloat currentAngle = i * angle / 30;
		glVertex2f(x[1] + (capRadius * cos(currentAngle)),
				   y[0] + (capRadius * sin(currentAngle)));
	}
	glEndReset();

	// Draw the battery body
	translateTo(originalX, originalY);
	drawRoundedRect_Line(width, height, radius, thickness);
}
#pragma endregion Battery

#pragma region Timer
void Object::drawTimer_Fill(GLfloat size)
{
	GLfloat innerSize = size * 0.7;
	GLfloat lineSize = (size - innerSize) / 3;
	GLfloat initialX = this->anchorX;
	GLfloat initialY = this->anchorY;

	rotateTo(0);
	// Draw the outer circle
	translateTo(initialX, initialY - size * 0.2);
	drawCircle_Line(size, 0, 360, lineSize);

	// Draw the inner circle
	translateTo(initialX, initialY - size * 0.2);
	drawCircle_Fill(innerSize, 0, 270);

	// Draw the buttons
	orbitTo(initialX, initialY - size * 0.2, size + size / 6, 45);
	rotateTo(45);
	drawRect_Fill(size / 6, size / 4);
	translateTo(initialX, initialY);

	orbitTo(initialX, initialY - size * 0.2, size + size / 5, 90);
	rotateTo(0);
	drawRect_Fill(size / 4, size / 3);

	// Draw the cap
	translateTo(initialX, initialY + size + (size / 3) - size * 0.2);
	drawRect_Fill(size, size / 4);
	translateTo(initialX, initialY + size);

	orbitTo(initialX, initialY - size * 0.2, size + size / 6, 135);
	rotateTo(-45);
	drawRect_Fill(size / 6, size / 4);
	translateTo(initialX, initialY);
	// rotateTo(-45);
}
#pragma endregion Timer

#pragma region Alarm
void Object::drawAlarm_Fill(GLfloat size)
{
	GLfloat thickness = size * 0.15;
	GLfloat outerRadius = size * 1.3;
	GLfloat hourHandLength = size * 0.5;
	GLfloat minuteHandLength = size * 0.8;
	GLfloat bellWidth = 15;
	GLfloat intialX = this->anchorX;
	GLfloat intialY = this->anchorY;

	// Draw the circle
	translateTo(intialX, intialY - thickness);
	drawCircle_Line(size, 0, 360, thickness);

	// Draw the bell
	translateTo(intialX, intialY - thickness);
	drawCircle_Line(outerRadius, 20, 45, thickness);
	translateTo(intialX, intialY - thickness);
	drawCircle_Line(outerRadius, 315, 340, thickness);

	// Draw the hand
	// Minute hand
	translateTo(intialX, intialY + minuteHandLength / 2 - thickness);
	drawRect_Fill(thickness, minuteHandLength);

	// Hour hand
	translateTo(intialX, intialY + hourHandLength / 2 - thickness);
	glTranslatef(intialX, intialY - thickness, 0);
	glRotatef(-135, 0.0f, 0.0f, 1.0f);
	glTranslatef(-intialX, -intialY + thickness, 0);
	drawRect_Fill(thickness, hourHandLength);

	translateTo(intialX, intialY);
}
#pragma endregion Alarm

#pragma region 2D Transformation
// 2D Transformation
void Object::translateTo(GLfloat x, GLfloat y)
{
	this->anchorX = x;
	this->anchorY = y;
}
void Object::translateTo(GLfloat *p)
{
	this->translateTo(p[0], p[1]);
}
void Object::translate(GLfloat tX, GLfloat tY)
{
	this->anchorX = this->anchorX + tX;
	this->anchorY = this->anchorY + tY;
}
void Object::translate(GLfloat *p)
{
	this->translate(p[0], p[1]);
}
void Object::rotateTo(GLfloat angle)
{
	this->orientation = angle;
}
void Object::rotate(GLfloat angle)
{
	this->orientation += angle;
}
void Object::mirrorX()
{
	glTranslated(this->anchorX, this->anchorY, 0);
	glScalef(-1, 1, 1);
	glTranslated(-this->anchorX, -this->anchorY, 0);
}
void Object::mirrorY()
{
	glTranslated(this->anchorX, this->anchorY, 0);
	glScalef(1, -1, 1);
	glTranslated(-this->anchorX, -this->anchorY, 0);
}

void Object::orbitTo(GLfloat anchorX, GLfloat anchorY, GLfloat radius, GLfloat angle)
{
	this->orbitAngle = angle;
	if (this->orbitAngle > 360)
		this->orbitAngle -= 360;
	else if (this->orbitAngle < 0)
		this->orbitAngle += 360;
	GLfloat currentAngle = this->orbitAngle * M_PI / 180;
	this->anchorX = anchorX + radius * cos(currentAngle);
	this->anchorY = anchorY + radius * sin(currentAngle);
}

void Object::orbit(GLfloat radius, GLfloat speed)
{
	GLfloat currentAngle = this->orbitAngle * M_PI / 180;
	this->anchorX = this->anchorX + radius * cos(currentAngle);
	this->anchorY = this->anchorY + radius * sin(currentAngle);
	if (this->orbitAngle < 360)
		this->orbitAngle += speed; // Speed of rotation.
	else
		this->orbitAngle = 0.0;
}
void Object::orbit(GLfloat cx, GLfloat cy, GLfloat radius, GLfloat speed)
{
	GLfloat currentAngle = this->orbitAngle * M_PI / 180;
	this->anchorX = cx + radius * cos(currentAngle);
	this->anchorY = cy - radius * sin(currentAngle);
	if (this->orbitAngle < 360)
		this->orbitAngle += speed; // Speed of rotation.
	else
		this->orbitAngle = 0.0;
}

void Object::scaleTo(GLfloat scaleFactor)
{
	this->scaleFactor = scaleFactor;
}
void Object::scale(GLfloat scaleFactor)
{
	this->scaleFactor += scaleFactor;
}
#pragma endregion 2D Transformation

// Utilities
void Object::drawText(char *string, GLfloat size)
{
	char *p;
	glStartInit();
	glLineWidth(size);
	for (p = string; *p; p++)
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *p);

	this->glEndReset();
}

void Object::drawGrid(GLfloat gridSpace, GLfloat lineThickness, GLfloat length)
{
	glStartInit();
	glLineWidth(lineThickness);
	glBegin(GL_LINES);
	// Positive x-axis lines
	for (int i = 0; i <= WINDOWS_WIDTH / 2; i += gridSpace)
	{
		if (length == 0)
		{
			glVertex2f(i, -WINDOWS_HEIGHT / 2);
			glVertex2f(i, WINDOWS_HEIGHT / 2);
		}
		else
		{
			glVertex2f(i, -length);
			glVertex2f(i, length);
		}
	}
	// Negative x-axis lines
	for (int i = 0; i >= -WINDOWS_WIDTH / 2; i -= gridSpace)
	{
		if (length == 0)
		{
			glVertex2f(i, -WINDOWS_HEIGHT / 2);
			glVertex2f(i, WINDOWS_HEIGHT / 2);
		}
		else
		{
			glVertex2f(i, -length);
			glVertex2f(i, length);
		}
	}
	// Positive y-axis lines
	for (int i = 0; i <= WINDOWS_HEIGHT / 2; i += gridSpace)
	{
		if (length == 0)
		{
			glVertex2f(-WINDOWS_WIDTH / 2, i);
			glVertex2f(WINDOWS_WIDTH / 2, i);
		}
		else
		{
			glVertex2f(-length, i);
			glVertex2f(length, i);
		}
	}
	// Negative y-axis lines
	for (int i = 0; i >= -WINDOWS_HEIGHT / 2; i -= gridSpace)
	{
		if (length == 0)
		{
			glVertex2f(-WINDOWS_WIDTH / 2, i);
			glVertex2f(WINDOWS_WIDTH / 2, i);
		}
		else
		{
			glVertex2f(-length, i);
			glVertex2f(length, i);
		}
	}

	glEndReset();
}

// Other control
void Object::setOpacity(GLfloat opacity)
{
	this->opacity = opacity;
}

void Object::setColor(const GLfloat *color)
{
	this->color[0] = color[0];
	this->color[1] = color[1];
	this->color[2] = color[2];
}

void Object::glStartInit()
{
	// Set color
	glColor4f(this->color[0], this->color[1], this->color[2], this->opacity / 100);

	// Rotate with orientation
	glTranslatef(this->anchorX, this->anchorY, 0);
	glRotatef(-(this->orientation), 0.0f, 0.0f, 1.0f);
	glTranslatef(-this->anchorX, -this->anchorY, 0);

	// Move
	glTranslatef(this->anchorX, this->anchorY, 0);

	// Scale
	glScalef(this->scaleFactor, this->scaleFactor, 1);

	// Push the matrix
	glPushMatrix();
}

void Object::glEndReset()
{
	glEnd();
	glPopMatrix();
	glLoadIdentity();
	gluOrtho2D(-(WINDOWS_WIDTH / 2), WINDOWS_WIDTH / 2, -(WINDOWS_HEIGHT / 2), WINDOWS_HEIGHT / 2); // Set canvas to windows width and height.
}

#endif