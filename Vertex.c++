#include "Vertex.h"

Vertex::Vertex(const GLfloat* c = NULL)
{
	numFaces = 0;
	for(int i = 0; i < 3; i++)
	{
		if(c)
			coordinates[i] = c[i];
		else
			coordinates[i] = 0;
		normal[i] = 0;
	}
}

Vertex& Vertex::operator=(const Vertex& other) 
{
	for(int i = 0; i < 3; ++i)
	{
		coordinates[i] = other.getCoordinates()[i];
		normal[i] = other.getNormal()[i];
	}
	numFaces = other.getNumFaces();
}

void Vertex::contributeNormal(const GLfloat* n)
{
	++numFaces;
	for(int i = 0; i < 3; i++)
		normal[i] += n[i];
}

void Vertex::averageNormal()
{
	for(int i = 0 ; i < 3; i++)
		normal[i] /= numFaces;
}

void Vertex::drawNormal() const
{
	glVertex3fv(coordinates);
	glVertex3f(coordinates[0] + normal[0], coordinates[1] + normal[1], coordinates[2] + normal[2]);
}
