#ifndef VERTEX_H
#define VERTEX_H

#include <GL/glut.h>

class Vertex
{
	private:
		GLfloat coordinates[3];
		GLfloat normal[3];
		int numFaces;

	public:
		Vertex();
		Vertex(const GLfloat* c);
		Vertex& operator=(const Vertex&);
		void contributeNormal(const GLfloat* n);
		void averageNormals();
		void drawNormal() const;
		GLfloat* getNormal() { return normal; }
		const GLfloat* getConstNormal() const { return normal; }
		const GLfloat* getCoordinates() const { return coordinates; }
		const int getNumFaces() const { return numFaces; }
};

#endif
