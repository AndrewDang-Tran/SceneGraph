#ifndef VECTORMATH_H
#define VECTORMATH_H

#include <GL/glut.h>
#include <cmath> //pow()

/**
 * Does vector subtraction for 3d vectors.
 * @param minuend - The vector being subtracted from
 * @param subtrahend - The vector subtracting
 * @param difference - The resulting vector
 */
void vectorSub3d(const GLfloat* minuend, const GLfloat* subtrahend, GLfloat* difference);
/**
 * Computes cross product of u cross v. 
 */
void crossProduct(const GLfloat* u, const GLfloat* v, GLfloat* result);

void normalizeVector(GLfloat* vector);

#endif