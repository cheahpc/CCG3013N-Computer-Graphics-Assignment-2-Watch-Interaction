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
	this->scaleX = 1;
	this->scaleY = 1;
	this->orientation = 0;
	this->orbitAngle = 0;

	this->scaleFlag = false;
	this->rotateFlag = false;
	this->translateFlag = false;
	this->orbitFlag = false;
	this->clockWiseFlag = false;
}

Object::Object(GLfloat anchorX, GLfloat anchorY)
{
	this->anchorX = anchorX;
	this->anchorY = anchorY;
	this->scaleX = 1;
	this->scaleY = 1;
	this->orientation = 0;
	this->orbitAngle = 0;

	this->scaleFlag = false;
	this->rotateFlag = false;
	this->translateFlag = false;
	this->orbitFlag = false;
	this->clockWiseFlag = false;
}

// Destructor
Object::~Object() {}

#pragma endregion Constructors

// 2D drawing functions
// Points
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
// Lines
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

// Triangles
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

// Quads
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

// Draw Circles
void Object::drawCircle_Fill(GLfloat radius, GLfloat startDegree, GLfloat endDegree)
{
	endDegree += startDegree > endDegree ? 360 : 0;
	GLfloat angle = (endDegree - startDegree) * M_PI / 180;	   // get the angle in radian
	int triangleAmount = (int)((endDegree - startDegree) / 3); // Calculate the triangle amount base on the angle
	GLfloat cx = this->anchorX;
	GLfloat cy = this->anchorY;

	// Pre-rotate the circle to counter the drawing rotation
	glTranslated(cx, cy, 0);
	glRotatef(90 + startDegree, 0.0f, 0.0f, 1.0f);
	glTranslated(-cx, -cy, 0);

	glPushMatrix();
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(cx, cy); // center of circle
	for (int i = 0; i <= triangleAmount; i++)
	{
		GLfloat currentAngle = i * angle / triangleAmount;

		glVertex2f(
			cx + (radius * cos(currentAngle)),
			cy - (radius * sin(currentAngle)));
	}

	this->glEndReset();
}
void Object::drawCircle_Line(GLfloat radius, GLfloat startDegree, GLfloat endDegree, GLfloat thickness)
{
	endDegree += startDegree > endDegree ? 360 : 0;
	GLfloat angle = (endDegree - startDegree) * M_PI / 180;	 // get the angle in radian
	int triangleAmount = (int)(endDegree - startDegree) * 4; // Calculate the triangle amount base on the angle
	GLfloat cx = this->anchorX;
	GLfloat cy = this->anchorY;
	GLfloat currentX, currentY, currentAngle;
	GLfloat radius_outer = radius + (thickness / 2);
	GLfloat radius_inner = radius - (thickness / 2);

	// Pre-rotate the circle to counter the drawing rotation
	glTranslated(cx, cy, 0);
	glRotatef(90 + startDegree, 0.0f, 0.0f, 1.0f);
	glTranslated(-cx, -cy, 0);

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

void Object::drawRegularPolygon(GLfloat cx, GLfloat cy, GLfloat radius, GLint side, GLfloat orientation, GLfloat width, GLfloat height)
{
	if (side >= 3)
	{
		glPushMatrix();
		GLint xp, yp; // Interpolation points
		glBegin(GL_POLYGON);
		for (int i = 0; i < side; i++)
		{
			xp = (int)(cx + width * radius * cos(orientation + 2 * M_PI / side * i));
			yp = (int)(cy + width * radius * sin(orientation + 2 * M_PI / side * i));
			glVertex2i(xp, yp);
		}
		glEnd();
		glPopMatrix();
	}
	else
	{
		cerr << "Could not render polygon with less than three sides." << endl;
	}
}

void Object::drawSineCurve(GLfloat int0, GLfloat int1)
{
	for (this->anchorX = int0; this->anchorX < int1; this->anchorX++)
	{
		this->anchorY += 2 * sin(this->anchorX * M_PI / 180);
		this->drawPoint(this->anchorX, this->anchorY, 5.0);
	}
}
// 2D transformation
void Object::moveTo(GLfloat x, GLfloat y)
{
	this->anchorX = x;
	this->anchorY = y;
}
void Object::moveTo(GLfloat *p)
{
	this->anchorX = p[0];
	this->anchorY = p[1];
}
void Object::translate(GLfloat tX, GLfloat tY)
{
	this->anchorX = this->anchorX + tX;
	this->anchorY = this->anchorY + tY;
}

void Object::translate(GLfloat *p)
{
	this->anchorX = this->anchorX + p[0];
	this->anchorY = this->anchorY + p[1];
}

void Object::rotate(GLfloat angle)
{
	this->orientation += angle;
	glTranslatef(this->anchorX, this->anchorY, 0);
	glRotatef(this->orientation, 0.0f, 0.0f, 1.0f);
	glTranslatef(-this->anchorX, -this->anchorY, 0);
}

void Object::rotate(GLfloat angle, GLfloat pX, GLfloat pY)
{
	this->orientation += angle;
	glTranslated(pX, pY, 0);
	glRotatef(this->orientation, 0.0f, 0.0f, 1.0f);
	glTranslated(-pX, -pY, 0);
}

void Object::rotate(GLfloat angle, GLfloat *p)
{
	this->orientation += angle;
	glTranslated(p[0], p[1], 0);
	glRotatef(this->orientation, 0.0f, 0.0f, 1.0f);
	glTranslated(-p[0], -p[1], 0);
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

void Object::scale(GLfloat sX, GLfloat sY)
{
	this->scaleX = sX;
	this->scaleY = sY;
	glTranslated(this->anchorX, this->anchorY, 0);
	glScalef(this->scaleX, this->scaleY, 1);
	glTranslated(-this->anchorX, -this->anchorY, 0);
}
void Object::scale(GLfloat scale)
{
	this->scale(scale, scale);
}

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