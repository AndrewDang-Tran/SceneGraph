#include "Face.h"

Face::Face(const int* vertices) 
{
	for(int i = 0;  i < 3; ++i)
	{
		triangleIndex[i] = vertices[i];
		normal[i] = 0;
	}
}

void Face::setNormal(const GLfloat* n)
{
	for(int i = 0; i < 3; ++i)
		normal[i] = n[i];
}

void Face::computeCenter(const vector<Vertex>& vertices)
{
	GLfloat accumulateX = 0;
	GLfloat accumulateY = 0;
	GLfloat accumulateZ = 0;

	GLfloat vertexCoordinates[3] = {0.0, 0.0, 0.0};

	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
			vertexCoordinates[j] = vertices.at(triangleIndex[i]).getCoordinates()[j];

		accumulateX += vertexCoordinates[0];
		accumulateY += vertexCoordinates[1];
		accumulateZ += vertexCoordinates[2];
	}

	centerCoordinates[0] = accumulateX / 3;
	centerCoordinates[1] = accumulateY / 3;
	centerCoordinates[2] = accumulateZ / 3;
}

void Face::drawNormal() const
{
	glVertex3fv(centerCoordinates);
	glVertex3f(centerCoordinates[0] + normal[0], centerCoordinates[1] + normal[1], centerCoordinates[2] + normal[2]);
}

GLfloat* Face::getNormal() 
{ 
	return normal; 
}

int* Face::getTriangleIndex() 
{ 
	return triangleIndex; 
}

