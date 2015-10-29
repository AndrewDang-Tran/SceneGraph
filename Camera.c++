#include "Camera.h"

Camera::Camera(const GLfloat*& pos, const GLfloat*& subjectPos,
		const GLfloat& n, const GLfloat& f, 
		const GLfloat& t = 45, const GLfloat& p = 45,
		const GLfloat& r = 0) 
		: near(n), far(f), theta(t), phi(p)
{
	for(int i = 0;  i < 3; ++i)
	{
		position[i] = pos[i];
		subjectPosition[i] = subjectPos[i];
	}
}

Camera::setRadius()
{

}

Camera::setCamera()
{
	GLfloat rTheta = theta * PI / 180;
	GLfloat rPhi = phi * PI / 180;
	position[0] = subjectPos[0] + radius * sin(rPhi) * sin(rTheta);
	position[1] = subjectPos[1] + radius * cos(rPhi);
	position[2] = subjectPos[2] + radius * sin(rPhi) * cos(rTheta);
}