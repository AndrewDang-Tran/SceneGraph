#include "VectorMath.h"

void vectorSub3d(const GLfloat* minuend, const GLfloat* subtrahend, GLfloat* difference)
{
	for(int i = 0; i < 3; i++)
		difference[i] = minuend[i] - subtrahend[i];
}

void crossProduct(const GLfloat* u, const GLfloat* v, GLfloat* result)
{
	result[0] = u[1] * v[2] - u[2] * v[1]; // UyVz - UzVy
	result[1] = u[2] * v[0] - u[0] * v[2]; // UzVx - UxVz
	result[2] = u[0] * v[1] - u[1] * v[0]; // UxVy - UyVx
}

void normalizeVector(GLfloat* vector)
{
	GLfloat magnitude = sqrt(pow(vector[0],2) + pow(vector[1],2) + pow(vector[2],2));
	vector[0] = vector[0] / magnitude;
	vector[1] = vector[1] / magnitude;
	vector[2] = vector[2] / magnitude;
}