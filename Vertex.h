#ifndef VERTEX_H
#define VERTEX_H

#include <GL/glut.h>

class Vertex
{
	private:
		const GLfloat coordinates[3];
		GLfloat normal[3];
		int numFaces;

	public:
		Vertex();
		Vertex(const GLfloat* c);
		void contributeNormal(const GLfloat* n);
		void averageNormals();
		void drawNormal() const;
		GLfloat* getNormal() { return normal; }
		const GLfloat* getCoordinates() { return coordinates; }
};

#endif
