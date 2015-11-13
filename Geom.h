/**
 * Purpose: Class stores face/vertex information
 * @author Andrew Dang-Tran
 */

#ifndef GEOM_H
#define GEOM_H

#include <list>
#include <cassert>
#include <cmath> 
#include <stack>
#include "Face.h"
#include "Transform.h"
#include "VectorMath.h"

#define PI 3.14159265
#define DIMENSIONS 3

class Trimesh
{
	private:
		vector<Vertex> vertices;
		list<Face> faces;

	public:
		void addVertex(const GLfloat* coordinates);
		void addFace(int* cornerIndexes);
		/**
		 * Calculate the face and vertex normals of the mesh
		 */
		void calculateNormals();
		/**
		 * Render the mesh
		 * @param faceNormal - variable determining whether the normals are face normals or vertex normals. primarily affects lighting.
		 */
		void render(bool faceNormal);
		/**
		 * Render lines which represent the normals.
		 */
		void renderNormals(bool faceNormal, bool vertexNormal);
};

#endif
