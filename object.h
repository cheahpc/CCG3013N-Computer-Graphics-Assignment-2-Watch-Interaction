#ifndef _OJBECT_H_
#define _OBJECT_H_
#include <iostream>
#include <GL/glut.h>
#include "math.h"

using namespace std;
class Object
{
public:
	Object();
	Object(GLfloat anchorX, GLfloat anchorY);
	Object(GLfloat anchorX, GLfloat anchorY, GLfloat width, GLfloat height);
	Object(GLfloat anchorX, GLfloat anchorY, GLfloat width, GLfloat height, GLfloat xVel, GLfloat yVel);
	~Object();

	// 2D primitives
	// Points
	void drawPoint(GLfloat size);
	void drawPoint(GLint x, GLint y, GLfloat size);
	void drawPoint(const GLint *v, GLfloat size);
	// Line
	void drawLine(GLint x1, GLint y1,
				  GLint x2, GLint y2,
				  GLfloat thickness);
	void drawLine(const GLint *v1,
				  const GLint *v2,
				  GLfloat thickness);
	// Triangle
	void drawTriangle_Fill(GLint x1, GLint y1,
						   GLint x2, GLint y2,
						   GLint x3, GLint y3);
	void drawTriangle_Fill(const GLint *v1,
						   const GLint *v2,
						   const GLint *v3);
	void drawTriangle_Line(GLint x1, GLint y1,
						   GLint x2, GLint y2,
						   GLint x3, GLint y3,
						   GLfloat thickness);
	void drawTriangle_Line(const GLint *v1,
						   const GLint *v2,
						   const GLint *v3,
						   GLfloat thickness);
	// Quad
	void drawQuad_Fill(GLint x1, GLint y1,
					   GLint x2, GLint y2,
					   GLint x3, GLint y3,
					   GLint x4, GLint y4);
	void drawQuad_Fill(const GLint *v1,
					   const GLint *v2,
					   const GLint *v3,
					   const GLint *v4);
	void drawQuad_Line(GLint x1, GLint y1,
					   GLint x2, GLint y2,
					   GLint x3, GLint y3,
					   GLint x4, GLint y4,
					   GLfloat thickness);
	void drawQuad_Line(const GLint *v1,
					   const GLint *v2,
					   const GLint *v3,
					   const GLint *v4,
					   GLfloat thickness);

	// Circles
	void drawCircle_Fill(GLfloat radius, GLfloat startDegree, GLfloat endDegree);
	void drawCircle_Line(GLfloat radius, GLfloat startDegree, GLfloat endDegree, GLfloat thickness);

	// TODO remove draw rect?
	// void drawRect(GLfloat width, GLfloat height);
	void drawRegularPolygon(GLfloat cx, GLfloat cy, GLfloat radius, GLint side, GLfloat orientation, GLfloat width, GLfloat height);

	void drawSineCurve(GLfloat int0, GLfloat int1);

	// 2D transformation
	void moveTo(GLfloat x, GLfloat y);
	void moveTo(GLfloat *p);
	void translate(GLfloat tX, GLfloat tY);
	void translate(GLfloat *p);
	void rotate(GLfloat angle); // Object origin
	void rotate(GLfloat angle, GLfloat pX, GLfloat pY);
	void rotate(GLfloat angle, GLfloat *p);
	void mirrorX();
	void mirrorY();
	void orbit(GLfloat radius, GLfloat speed);
	void orbit(GLfloat anchorX, GLfloat anchorY, GLfloat radius, GLfloat speed);
	void orbit(GLfloat *anchor, GLfloat radius, GLfloat &angle, GLfloat speed);
	void scale(GLfloat sX, GLfloat sY);
	void scale(GLfloat scale);

	// Utilities
	void drawText(char *string, GLfloat size);
	void drawGrid(GLint gridSpace, GLfloat lineThickness, GLfloat length);

	void static glEndReset();

	GLfloat anchorX, anchorY, scaleX, scaleY, orientation, orbitAngle, opacity;
	boolean scaleFlag, rotateFlag, translateFlag, orbitFlag, clockWiseFlag, opacityFlag;
};

#endif