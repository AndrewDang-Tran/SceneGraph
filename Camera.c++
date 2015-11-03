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
}

void Camera::setRadius()
{

}

void Camera::setCamera()
{
	GLfloat rTheta = theta * PI / 180;
	GLfloat rPhi = phi * PI / 180;
	position[0] = subjectPosition[0] + radius * sin(rPhi) * sin(rTheta);
	position[1] = subjectPosition[1] + radius * cos(rPhi);
	position[2] = subjectPosition[2] + radius * sin(rPhi) * cos(rTheta);
}