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
		stack<Transform> transforms;

		//used to set the camera
		GLfloat closeZ;
		GLfloat farZ;
		GLfloat rightBound;
		GLfloat leftBound; 
		GLfloat topBound;
		GLfloat bottomBound;

		GLfloat height;
		GLfloat width;
		GLfloat depth;

		GLfloat center[3];

		GLfloat cameraRadius;
		GLfloat localDirectionX[3];
		GLfloat localDirectionY[3];
		GLfloat localDirectionZ[3];

		void checkObjectBounds(const GLfloat* xyz);
		const GLfloat calculateDistance(const GLfloat* otherPoint);
		void normalizeVector(GLfloat* vector);

	public:
		Trimesh();
		void addVertex(const GLfloat* coordinates);
		void addFace(int* cornerIndexes);
		void calculateNormals();
		void render(bool faceNormal);
		void renderNormals(bool faceNormal, bool vertexNormal);
		void setLocalDirections(const GLfloat* eye, const GLfloat* at, GLfloat* x, GLfloat* y, GLfloat* z);
		void setCamera(GLfloat theta, GLfloat phi);
		void setSize();
		void applyTransforms();

		void addTransform(Transform t) { transforms.push(t); }
		GLfloat* getLocalDirectionX() { return localDirectionX; }
		GLfloat* getLocalDirectionY() { return localDirectionY; }
		GLfloat* getLocalDirectionZ() { return localDirectionZ; }
		void setCameraRadius(GLfloat r) { cameraRadius = r; }
		GLfloat getCameraRadius() { return cameraRadius; }
		GLfloat getFarValue() { return cameraRadius + depth * 2; }
};

#endif
