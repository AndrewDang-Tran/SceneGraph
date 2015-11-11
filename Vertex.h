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
		Vertex(const GLfloat* c = NULL);
		Vertex& operator=(const Vertex&);
		/**
		 * Add the normal of a face to the vertex
		 */
		void contributeNormal(const GLfloat* n);
		/**
		 * Average the normals of all the connecting faces of this vertex.
		 */
		void averageNormals();
		void drawNormal() const;
		GLfloat* getNormal() { return normal; }
		const GLfloat* getConstNormal() const { return normal; }
		const GLfloat* getCoordinates() const { return coordinates; }
		/**
		 * Return the number of faces which is connected to this vertices
		 */ 
		const int getNumFaces() const { return numFaces; }
};

#endif
