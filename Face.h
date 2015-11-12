#ifndef FACE_H
#define FACE_H

#include <vector>    //vector<Vertex>
#include "Vertex.h"

using namespace std;

class Face
{
	private:
		int triangleIndex[3];
		GLfloat normal[3];
		GLfloat centerCoordinates[3];

	public:
		Face(const int* vertices);
		/**
		 * Compute the normal of the face
		 * @param normal - array of xyz[3] for the direction of the normal
		 */
		void setNormal(const GLfloat* n);
		/**
		 * Compute the center of the face to draw normal lines on
		 * @param vertices - the three vertices which make up the face
		 */
		void computeCenter(const vector<Vertex>& vertices);
		void drawNormal() const;
		GLfloat* getNormal();
		int* getTriangleIndex();
};

#endif