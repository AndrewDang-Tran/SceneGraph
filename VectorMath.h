#ifndef VECTORMATH_H
#define VECTORMATH_H

#include <GL/glut.h>
#include <cmath> //pow()

void vectorSub3d(const GLfloat* minuend, const GLfloat* subtrahend, GLfloat* difference);
void crossProduct(const GLfloat* u, const GLfloat* v, GLfloat* result);

void normalizeVector(GLfloat* vector);

#endif