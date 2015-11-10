#include "Geom.h"
#include "VectorMath.h"

void Trimesh::checkObjectBounds(const GLfloat* xyz)
{
	if(xyz[0] > rightBound)
		rightBound = xyz[0];
	else if(xyz[0] < leftBound)
		leftBound = xyz[0];

	if(xyz[1] > topBound)
		topBound = xyz[1];
	else if(xyz[1] < bottomBound)
		bottomBound = xyz[1];

	if(xyz[2] > closeZ)
		closeZ = xyz[2];
	else if(xyz[2] < farZ)
		farZ = xyz[2];
}

const GLfloat Trimesh::calculateDistance(const GLfloat* otherPoint) 
{
	GLfloat distanceX = abs(otherPoint[0] - center[0]);
	GLfloat distanceY = abs(otherPoint[1] - center[1]);
	GLfloat distanceZ = abs(otherPoint[2] - center[2]);

	GLfloat distanceBeforeSqrt = pow(distanceX, 2) + pow(distanceY, 2) + pow(distanceZ, 2);
	const GLfloat totalDistance = sqrt(distanceBeforeSqrt);
	return totalDistance;
}

void Trimesh::normalizeVector(GLfloat* vector)
{
	GLfloat magnitude = sqrt(pow(vector[0],2) + pow(vector[1],2) + pow(vector[2],2));
	vector[0] = vector[0] / magnitude;
	vector[1] = vector[1] / magnitude;
	vector[2] = vector[2] / magnitude;
}

Trimesh::Trimesh()
{
	closeZ = 0;
	farZ = 0;
	rightBound = 0;
	leftBound = 0;
	topBound = 0;
	bottomBound = 0;

	height = 0;
	width = 0;
	depth = 0;
	cameraRadius = 0;

	for(int i = 0; i < 3; ++i)
	{
		center[i] = 0;
		localDirectionX[i] = 0;
		localDirectionY[i] = 0;
		localDirectionZ[i] = 0;
	}
}

void Trimesh::addVertex(const GLfloat* coordinates)
{
	Vertex newVertex = Vertex(coordinates);
	vertices.push_back(newVertex);
	checkObjectBounds(coordinates);
}

void Trimesh::addFace(int* cornerIndexes) 
{
	Face newFace = Face(cornerIndexes);
	faces.push_back(newFace);
}

void Trimesh::calculateNormals()
{
	//saveNormal[0] = x, saveNormal[1] = y, newNoraml[2] = z DIRECTON
	GLfloat saveNormal[3];
	list<Face>::iterator b = faces.begin();
	list<Face>::iterator e = faces.end();
	//calculate face normals
	while(b != e)
	{
		(*b).computeCenter(vertices);

		const GLfloat* trianglePoints[3];
		Vertex triangleVertices[3];
		for(int i = 0; i < 3; ++i)
		{
			triangleVertices[i] = vertices.at((*b).getTriangleIndex()[i]);
			trianglePoints[i] = triangleVertices[i].getCoordinates();
		}

		GLfloat u[3];
		GLfloat v[3];

		//prep to compute crossproduct
		vectorSub3d(trianglePoints[1], trianglePoints[0], &u[0]);
		vectorSub3d(trianglePoints[2], trianglePoints[0], &v[0]);

		crossProduct(&u[0], &v[0], saveNormal);
		
		normalizeVector(saveNormal);

		(*b).setNormal(saveNormal);
		for(int i = 0; i < 3; ++i)
			vertices.at((*b).getTriangleIndex()[i]).contributeNormal(saveNormal);
	
		++b; 
	}
	//calculate vertex normals
	for(unsigned i = 0; i < vertices.size(); ++i)
	{
		vertices.at(i).averageNormals();
		normalizeVector(vertices.at(i).getNormal());
	}
}

void Trimesh::render(bool faceNormal)
{
	list<Face>::iterator b = faces.begin();
	list<Face>::iterator e = faces.end();
	
	while(b != e)
	{
		Vertex triangleVertices[3];
		for(int i = 0; i < 3; ++i)
			triangleVertices[i] = vertices.at((*b).getTriangleIndex()[i]);

		glColor3f(0, .5, .5);
		if(faceNormal)
		{
			GLfloat normal[3];
			for(int i = 0; i < 3; i++)
				normal[i] = (*b).getNormal()[i];
			glNormal3fv(normal);;
		}
		for(int i = 0; i < 3; ++i)
		{
			if(!faceNormal)
			{
				GLfloat normal[3][3];
				for(int j = 0; j < 3; j++)
					normal[i][j] = triangleVertices[i].getNormal()[j];
				glNormal3fv(normal[i]);
			}
			glVertex3fv(triangleVertices[i].getCoordinates());
		}
		++b;
	}
}

void Trimesh::renderNormals(bool faceNormal, bool vertexNormal)
{
	if(faceNormal)
	{
		glColor3f(0, 0, 1);
		list<Face>::iterator b = faces.begin();
		list<Face>::iterator e = faces.end();
		while(b != e)
		{
			(*b).drawNormal();
			++b;
		}
	}

	if(vertexNormal)
	{
		glColor3f(1, 0, 0);
		for(unsigned i = 0; i < vertices.size(); ++i)
			vertices.at(i).drawNormal();
	}
}

void Trimesh::setLocalDirections(const GLfloat* eye, const GLfloat* at, GLfloat* x, GLfloat* y, GLfloat* z)
{
	const GLfloat up[3] = {0.0, 1.0, 0.0};
	vectorSub3d(eye, at, z);
	normalizeVector(z);
	crossProduct(up, z, x);
	crossProduct(z, x, y);
	normalizeVector(x);
	normalizeVector(y);
}

void Trimesh::setCamera(GLfloat theta, GLfloat phi)
{
	//set light wherever the camera is going to be
	GLfloat newLightPosition[3];

	theta = theta * PI / 180;
	phi = phi * PI / 180;

	GLfloat cameraPos[3]; 
	cameraPos[0] = center[0] + cameraRadius * sin(phi) * sin(theta);
	cameraPos[1] = center[1] + cameraRadius * cos(phi);
	cameraPos[2] = center[2] + cameraRadius * sin(phi) * cos(theta);

	for(int i = 0; i < 3; ++i)
		newLightPosition[i] = cameraPos[i];

	setLocalDirections(cameraPos, center, localDirectionX, localDirectionY, localDirectionZ);

	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_POSITION, newLightPosition);
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], center[0], center[1], center[2], 0, 1, 0);
}

void Trimesh::setSize()
{

	width = rightBound - leftBound;
	height = topBound - bottomBound;
	depth = closeZ - farZ;

	center[0] = rightBound - width / 2;
	center[1] = topBound - height / 2;
	center[2] = closeZ - depth / 2;

	for(unsigned i = 0; i < vertices.size(); ++i)
	{
		const GLfloat tempDistance = calculateDistance(vertices.at(i).getCoordinates());
		if(tempDistance > cameraRadius)
			cameraRadius = tempDistance; 
	}
	cameraRadius = cameraRadius + 2 * depth;
	assert(cameraRadius > 0);
}

void Trimesh::applyTransforms()
{
	stack<Transform> copy = transforms;
	while(!copy.empty())
	{
		Transform newT = copy.top();
		newT.apply();
		copy.pop();
	}
}
