/**
 * Purpose: file just has simple vector math functions.
 * @author Andrew Dang-Tran
 */

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
 * Computes cross product of u cross v and stores it in result
 * @param u
 * @param v
 * @param result
 */
void crossProduct(const GLfloat* u, const GLfloat* v, GLfloat* result);

void normalizeVector(GLfloat* vector);

#endif