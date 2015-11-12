#include "Camera.h"

Camera::Camera(const GLfloat* pos, const GLfloat* subjectPos,
		const GLfloat n = .01, const GLfloat f = 10.0, 
		const GLfloat t = 45, const GLfloat p = 45,
		const GLfloat r = 0) 
		: near(n), far(f), theta(t), phi(p), radius(r)
{
	for(int i = 0;  i < 3; ++i)
	{
		position[i] = pos[i];
		subjectPosition[i] = subjectPos[i];
	}
	setLocalDirections();
}

void Camera::setLocalDirections()
{
	GLfloat up[3] = {0.0, 1.0, 0.0};
	vectorSub3d(position, subjectPosition, localZ);
	normalizeVector(localZ);
	crossProduct(up, localZ, localX);
	crossProduct(localZ, localX, localY);
	normalizeVector(localX);
	normalizeVector(localY);
}

void Camera::setRadius(const GLfloat r) { radius = r; }
void Camera::setNear(const GLfloat n) { near = n; }
void Camera::setFar(const GLfloat f) { far = f; }

void Camera::setCamera()
{
	GLfloat rTheta = theta * PI / 180;
	GLfloat rPhi = phi * PI / 180;
	position[0] = subjectPosition[0] + radius * sin(rPhi) * sin(rTheta);
	position[1] = subjectPosition[1] + radius * cos(rPhi);
	position[2] = subjectPosition[2] + radius * sin(rPhi) * cos(rTheta);

	setLocalDirections();

	glLoadIdentity();
	gluLookAt(position[0], position[1], position[2], subjectPosition[0], subjectPosition[1], subjectPosition[2], 0, 1, 0);
}

void Camera::rotate(const GLfloat t, const GLfloat p)
{
	theta = t;
	phi = p;
}

void Camera::zoom(const GLfloat zoom)
{
	for(int i = 0; i < 3; ++i)
		position[i] = position[i] + localZ[i] * zoom;
	radius = radius + zoom;
}

void Camera::pan(const GLfloat panX, const GLfloat panY)
{
	for(int i = 0; i < 3; ++i) 
	{
		position[i] = position[i] + localX[i] * panX;
		position[i] = position[i] + localY[i] * panY;
		subjectPosition[i] = subjectPosition[i] + localX[i] * panX;
		subjectPosition[i] = subjectPosition[i] + localY[i] * panY;
	}
}
