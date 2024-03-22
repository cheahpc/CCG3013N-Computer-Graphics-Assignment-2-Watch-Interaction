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

	this->scaleFlag = false;
	this->rotateFlag = false;
	this->translateFlag = false;
	this->orbitFlag = false;
	this->clockWiseFlag = false;
	this->animationState = IDLE;
}

Object::Object(GLfloat anchorX, GLfloat anchorY)
{
	this->anchorX = anchorX;
	this->anchorY = anchorY;
	this->scaleFactor = 1;
	this->orientation = 0;
	this->orbitAngle = 0;
	this->opacity = 1;

	this->scaleFlag = false;
	this->rotateFlag = false;
	this->translateFlag = false;
	this->orbitFlag = false;
	this->clockWiseFlag = false;
	this->opacityFlag = false;
}

// Destructor
Object::~Object() {}

#pragma endregion Constructors

// 2D drawing functions
#pragma region Points
void Object::drawPoint(GLfloat size)
{
	glPushMatrix();
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2i(this->anchorX, this->anchorY);
	this->glEndReset();
}
void Object::drawPoint(GLint x, GLint y, GLfloat size)
{
	glPushMatrix();
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	this->glEndReset();
}
void Object::drawPoint(const GLint *v, GLfloat size)
{
	glPushMatrix();
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2i(v[0], v[1]);
	this->glEndReset();
}
#pragma endregion Points

#pragma region Line
void Object::drawLine(GLint x1, GLint y1, GLint x2, GLint y2, GLfloat thickness)
{
	glPushMatrix();
	glLineWidth(thickness);
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	this->glEndReset();
}
void Object::drawLine(const GLint *v1, const GLint *v2, GLfloat thickness)
{
	glPushMatrix();
	glLineWidth(thickness);
	glBegin(GL_LINES);
	glVertex2i(v1[0], v1[1]);
	glVertex2i(v2[0], v2[1]);
	this->glEndReset();
}
#pragma endregion Line

#pragma region Triangle
void Object::drawTriangle_Fill(GLint x1, GLint y1, GLint x2, GLint y2, GLint x3, GLint y3)
{
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glVertex2i(x3, y3);
	this->glEndReset();
}
void Object::drawTriangle_Fill(const GLint *v1, const GLint *v2, const GLint *v3)
{
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex2i(v1[0], v1[1]);
	glVertex2i(v2[0], v2[1]);
	glVertex2i(v3[0], v3[1]);
	this->glEndReset();
}
void Object::drawTriangle_Line(GLint x1, GLint y1, GLint x2, GLint y2, GLint x3, GLint y3, GLfloat thickness)
{
	glPushMatrix();
	glLineWidth(thickness);
	glBegin(GL_LINE_LOOP);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glVertex2i(x3, y3);
	this->glEndReset();
}
void Object::drawTriangle_Line(const GLint *v1, const GLint *v2, const GLint *v3, GLfloat thickness)
{
	glPushMatrix();
	glLineWidth(thickness);
	glBegin(GL_LINE_LOOP);
	glVertex2i(v1[0], v1[1]);
	glVertex2i(v2[0], v2[1]);
	glVertex2i(v3[0], v3[1]);
	this->glEndReset();
}
#pragma endregion Triangle

#pragma region Quad
void Object::drawQuad_Fill(GLint x1, GLint y1,
						   GLint x2, GLint y2,
						   GLint x3, GLint y3,
						   GLint x4, GLint y4)
{
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glVertex2i(x3, y3);
	glVertex2i(x4, y4);
	this->glEndReset();
}
void Object::drawQuad_Fill(const GLint *v1,
						   const GLint *v2,
						   const GLint *v3,
						   const GLint *v4)
{
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex2i(v1[0], v1[1]);
	glVertex2i(v2[0], v2[1]);
	glVertex2i(v3[0], v3[1]);
	glVertex2i(v4[0], v4[1]);
	this->glEndReset();
}
void Object::drawQuad_Line(GLint x1, GLint y1,
						   GLint x2, GLint y2,
						   GLint x3, GLint y3,
						   GLint x4, GLint y4,
						   GLfloat thickness)
{
	glPushMatrix();
	glPointSize(thickness);
	glBegin(GL_POINTS);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glVertex2i(x3, y3);
	glVertex2i(x4, y4);
	this->glEndReset();
}
void Object::drawQuad_Line(const GLint *v1,
						   const GLint *v2,
						   const GLint *v3,
						   const GLint *v4,
						   GLfloat thickness)
{
	glPushMatrix();
	glPointSize(thickness);
	glBegin(GL_POINTS);
	glVertex2i(v1[0], v1[1]);
	glVertex2i(v2[0], v2[1]);
	glVertex2i(v3[0], v3[1]);
	glVertex2i(v4[0], v4[1]);
	this->glEndReset();
}
#pragma endregion Quad

#pragma region Circle
void Object::drawCircle_Fill(GLfloat radius, GLfloat startDegree, GLfloat endDegree)
{
	// !270 360 not working
	endDegree += startDegree > endDegree ? 360 : 0;
	GLfloat angle = (endDegree - startDegree) * M_PI / 180;	   // get the angle in radian
	int triangleAmount = (int)((endDegree - startDegree) / 3); // Calculate the triangle amount base on the angle
	GLfloat scaledRadius = radius * this->scaleFactor;
	GLfloat cx = this->anchorX;
	GLfloat cy = this->anchorY;

	// Rotate with orientation + offset
	glRotatef(90 - startDegree - this->orientation, 0.0f, 0.0f, 1.0f);

	// Scale
	glScalef(this->scaleFactor, this->scaleFactor, 1);

	glPushMatrix();
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(cx, cy); // center of circle
	for (int i = 0; i <= triangleAmount; i++)
	{
		GLfloat currentAngle = i * angle / triangleAmount;

		glVertex2f(
			cx + (scaledRadius * cos(currentAngle)),
			cy - (scaledRadius * sin(currentAngle)));
	}

	this->glEndReset();
}
void Object::drawCircle_Line(GLfloat radius, GLfloat startDegree, GLfloat endDegree, GLfloat thickness)
{
	endDegree += startDegree > endDegree ? 360 : 0;
	GLfloat angle = (endDegree - startDegree) * M_PI / 180;	 // get the angle in radian
	int triangleAmount = (int)(endDegree - startDegree) * 4; // Calculate the triangle amount base on the angle
	GLfloat scaledRadius = radius * this->scaleFactor;
	GLfloat scaledThickness = thickness * this->scaleFactor;
	GLfloat cx = this->anchorX;
	GLfloat cy = this->anchorY;
	GLfloat currentX, currentY, currentAngle;
	GLfloat radius_outer = scaledRadius + (scaledThickness / 2);
	GLfloat radius_inner = scaledRadius - (scaledThickness / 2);

	// Rotate with orientation + offset
	glRotatef(90 - startDegree - this->orientation, 0.0f, 0.0f, 1.0f);

	// Scale
	glScalef(this->scaleFactor, this->scaleFactor, 1);

	glPushMatrix();
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= triangleAmount; i++)
	{
		currentAngle = i * angle / triangleAmount;
		glVertex2f(
			cx + (radius_outer * cos(currentAngle)),
			cy - (radius_outer * sin(currentAngle)));
		glVertex2f(
			cx + (radius_inner * cos(currentAngle)),
			cy - (radius_inner * sin(currentAngle)));
	}
	this->glEndReset();
}
#pragma endregion Circle

#pragma region Rounded Rectangle
void Object::drawRoundedRect_Fill(GLfloat width, GLfloat height, GLfloat radius)
{
	// TODO Implement rounded rectangle
	GLfloat originalX = this->anchorX;
	GLfloat originalY = this->anchorY;
	GLfloat startX1, startX2, endX1, endX2;
	GLfloat startY1, startY2, endY1, endY2;
	GLfloat scaledWidth = width * this->scaleFactor;
	GLfloat scaledHeight = height * this->scaleFactor;
	GLfloat scaledRadius = radius * this->scaleFactor;
	GLfloat diameter = scaledRadius * 2;
	startX1 = this->anchorX - (scaledWidth / 2);
	startX2 = this->anchorX - (scaledWidth / 2) + scaledRadius;
	endX1 = this->anchorX + (scaledWidth / 2) - scaledRadius;
	endX2 = this->anchorX + (scaledWidth / 2);
	startY1 = this->anchorY - (scaledHeight / 2);
	startY2 = this->anchorY - (scaledHeight / 2) + scaledRadius;
	endY1 = this->anchorY + (scaledHeight / 2) - scaledRadius;
	endY2 = this->anchorY + (scaledHeight / 2);

	// Draw the rectangles
	// Center rectangle
	// this->drawQuad_Fill(startX2, startY2, endX1, startY2, endX1, endY1, startX2, endY1);
	// Start rectangle
	// this->drawQuad_Fill(startX1, startY2, startX2, startY2, startX2, endY1, startX1, endY1);
	// End rectangle
	this->drawQuad_Fill(endX1, startY2, endX2, startY2, endX2, endY1, endX1, endY1);
	// Top rectangle
	// this->drawQuad_Fill(startX2, endY1, endX1, endY1, endX1, endY2, startX2, endY2);
	// Bottom rectangle
	this->drawQuad_Fill(startX2, startY1, endX1, startY1, endX1, startY2, startX2, startY2);

	// Draw the corners
	// Top left corner
	this->translateTo(startX2, endY1);
	this->drawCircle_Fill(radius, 270, 360);

	// Top right corner
	this->translateTo(endX1, endY1);
	this->drawCircle_Fill(radius, 0, 90);

	// Bottom right corner
	this->translateTo(endX1, startY2);
	this->drawCircle_Fill(radius, 90, 180);

	// Bottom left corner
	this->translateTo(startX2, startY2);
	this->drawCircle_Fill(radius, 180, 270);

	// Reset the position
	this->translateTo(originalX, originalY);
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
	glPushMatrix();
	glLineWidth(size);

	glTranslatef(this->anchorX, this->anchorY, 0);
	for (p = string; *p; p++)
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *p);

	this->glEndReset();
}

void Object::drawGrid(GLint gridSpace, GLfloat lineThickness, GLfloat length)
{
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

	glEnd();
}

void Object::glEndReset()
{
	glEnd();
	glPopMatrix();
	// gluOrtho2D(0, WINDOWS_WIDTH, 0, WINDOWS_HEIGHT); // Set canvas to windows width and height.
	glLoadIdentity();
	gluOrtho2D(-(WINDOWS_WIDTH / 2), WINDOWS_WIDTH / 2, -(WINDOWS_HEIGHT / 2), WINDOWS_HEIGHT / 2); // Set canvas to windows width and height.
}