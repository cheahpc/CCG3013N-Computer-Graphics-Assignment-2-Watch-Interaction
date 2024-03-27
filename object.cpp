#ifndef OBJECT_CPP
#define OBJECT_CPP
#include "object.h"
#ifndef M_PI
#define M_PI 3.1415926535897932384626433
#endif

using namespace std;
#pragma region Constructors
// Default constructor
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

// Destructor
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
	glVertex2i(0, 0);
	glEndReset();
}

void Object::drawPoint(GLint x, GLint y, GLfloat size)
{
	glStartInit();
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEndReset();
}
void Object::drawPoint(const GLint *v, GLfloat size)
{
	drawPoint(v[0], v[1], size);
}
#pragma endregion Points

#pragma region Line
void Object::drawLine(GLint x1, GLint y1, GLint x2, GLint y2, GLfloat thickness)
{
	glStartInit();
	glLineWidth(thickness);
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEndReset();
}
void Object::drawLine(const GLint *v1, const GLint *v2, GLfloat thickness)
{
	drawLine(v1[0], v1[1], v2[0], v2[1], thickness);
}
#pragma endregion Line

#pragma region Triangle
void Object::drawTriangle_Fill(GLint x1, GLint y1, GLint x2, GLint y2, GLint x3, GLint y3)
{
	glStartInit();
	glBegin(GL_TRIANGLES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glVertex2i(x3, y3);
	glEndReset();
}
void Object::drawTriangle_Fill(const GLint *x, const GLint *y)
{
	drawTriangle_Fill(x[0], y[0], x[1], y[1], x[2], y[2]);
}
void Object::drawTriangle_Line(GLint x1, GLint y1, GLint x2, GLint y2, GLint x3, GLint y3, GLfloat thickness)
{
	glStartInit();
	glLineWidth(thickness);
	glBegin(GL_LINE_LOOP);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glVertex2i(x3, y3);
	glEndReset();
}
void Object::drawTriangle_Line(const GLint *x, const GLint *y, GLfloat thickness)
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
};

#pragma endregion Rectangle

#pragma region Quad
void Object::drawQuad_Fill(GLint x1, GLint y1,
						   GLint x2, GLint y2,
						   GLint x3, GLint y3,
						   GLint x4, GLint y4)
{
	glStartInit(); // Apply settings

	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glVertex2i(x3, y3);
	glVertex2i(x4, y4);
	glEndReset();
}

void Object::drawQuad_Fill(const GLint *x, const GLint *y)
{
	this->drawQuad_Fill(x[0], y[0], x[1], y[1], x[2], y[2], x[3], y[3]);
}
void Object::drawQuad_Line(GLint x1, GLint y1,
						   GLint x2, GLint y2,
						   GLint x3, GLint y3,
						   GLint x4, GLint y4,
						   GLfloat thickness)
{
	glStartInit(); // Apply settings

	glLineWidth(thickness);
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);

	glVertex2i(x2, y2);
	glVertex2i(x3, y3);

	glVertex2i(x3, y3);
	glVertex2i(x4, y4);

	glVertex2i(x4, y4);
	glVertex2i(x1, y1);
	glEndReset();
}
void Object::drawQuad_Line(const GLint *x,
						   const GLint *y,
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

	this->glEndReset();
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

	glPushMatrix();
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
	glEnd();

	// Draw the corners
	// Top left corner
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x[1], y[2]);
	for (int i = 0; i <= 30; i++)
	{
		currentAngle = i * angle / 30;
		glVertex2f(x[1] - (radius * cos(currentAngle)),
				   y[2] + (radius * sin(currentAngle)));
	}
	glEnd();

	// Top right corner
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x[2], y[2]);
	for (int i = 0; i <= 30; i++)
	{
		currentAngle = i * angle / 30;
		glVertex2f(x[2] + (radius * cos(currentAngle)),
				   y[2] + (radius * sin(currentAngle)));
	}
	glEnd();

	// Bottom right corner
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x[2], y[1]);
	for (int i = 0; i <= 30; i++)
	{
		currentAngle = i * angle / 30;
		glVertex2f(x[2] + (radius * cos(currentAngle)),
				   y[1] - (radius * sin(currentAngle)));
	}
	glEnd();

	// Bottom left corner
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x[1], y[1]);
	for (int i = 0; i <= 30; i++)
	{
		currentAngle = i * angle / 30;
		glVertex2f(x[1] - (radius * cos(currentAngle)),
				   y[1] - (radius * sin(currentAngle)));
	}
	glEnd();
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
	glEnd();

	// Draw the corners
	// Top left corner
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 30; i++)
	{
		currentAngle = i * angle / 30;
		glVertex2f(x[1] + (outerRadius * cos(currentAngle)),
				   y[2] - (outerRadius * sin(currentAngle)));
		glVertex2f(x[1] + (innerRadius * cos(currentAngle)),
				   y[2] - (innerRadius * sin(currentAngle)));
	}
	glEnd();

	// Top right corner
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 30; i++)
	{
		currentAngle = i * angle / 30;
		glVertex2f(x[2] - (outerRadius * cos(currentAngle)),
				   y[2] - (outerRadius * sin(currentAngle)));
		glVertex2f(x[2] - (innerRadius * cos(currentAngle)),
				   y[2] - (innerRadius * sin(currentAngle)));
	}
	glEnd();

	// Bottom right corner
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 30; i++)
	{
		currentAngle = i * angle / 30;
		glVertex2f(x[2] - (outerRadius * cos(currentAngle)),
				   y[1] + (outerRadius * sin(currentAngle)));
		glVertex2f(x[2] - (innerRadius * cos(currentAngle)),
				   y[1] + (innerRadius * sin(currentAngle)));
	}
	glEnd();

	// Bottom left corner
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 30; i++)
	{
		currentAngle = i * angle / 30;
		glVertex2f(x[1] + (outerRadius * cos(currentAngle)),
				   y[1] + (outerRadius * sin(currentAngle)));
		glVertex2f(x[1] + (innerRadius * cos(currentAngle)),
				   y[1] + (innerRadius * sin(currentAngle)));
	}
	glEnd();

	glEndReset();
}

#pragma endregion Rounded Rectangle

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

void Object::drawGrid(GLint gridSpace, GLfloat lineThickness, GLfloat length)
{
	glStartInit();
	glLineWidth(lineThickness);
	glBegin(GL_LINES);
	// Positive x-axis lines
	for (int i = 0; i <= WINDOWS_WIDTH / 2; i += gridSpace)
	{
		if (length == 0)
		{
			glVertex2i(i, -WINDOWS_HEIGHT / 2);
			glVertex2i(i, WINDOWS_HEIGHT / 2);
		}
		else
		{
			glVertex2i(i, -length);
			glVertex2i(i, length);
		}
	}
	// Negative x-axis lines
	for (int i = 0; i >= -WINDOWS_WIDTH / 2; i -= gridSpace)
	{
		if (length == 0)
		{
			glVertex2i(i, -WINDOWS_HEIGHT / 2);
			glVertex2i(i, WINDOWS_HEIGHT / 2);
		}
		else
		{
			glVertex2i(i, -length);
			glVertex2i(i, length);
		}
	}
	// Positive y-axis lines
	for (int i = 0; i <= WINDOWS_HEIGHT / 2; i += gridSpace)
	{
		if (length == 0)
		{
			glVertex2i(-WINDOWS_WIDTH / 2, i);
			glVertex2i(WINDOWS_WIDTH / 2, i);
		}
		else
		{
			glVertex2i(-length, i);
			glVertex2i(length, i);
		}
	}
	// Negative y-axis lines
	for (int i = 0; i >= -WINDOWS_HEIGHT / 2; i -= gridSpace)
	{
		if (length == 0)
		{
			glVertex2i(-WINDOWS_WIDTH / 2, i);
			glVertex2i(WINDOWS_WIDTH / 2, i);
		}
		else
		{
			glVertex2i(-length, i);
			glVertex2i(length, i);
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