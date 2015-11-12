#include "Geom.h"
#include "VectorMath.h"

void Trimesh::addVertex(const GLfloat* coordinates)
{
	Vertex newVertex = Vertex(coordinates);
	vertices.push_back(newVertex);
}

void Trimesh::addFace(int* cornerIndexes) 
{
	Face newFace = Face(cornerIndexes);
	faces.push_back(newFace);
}

void Trimesh::calculateNormals()
{
	//saveNormal[0] = x, saveNormal[1] = y, newNormal[2] = z DIRECTON
	GLfloat saveNormal[3];
	list<Face>::iterator b = faces.begin();
	list<Face>::iterator e = faces.end();
	//calculate face normals
	while(b != e)
	{

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
