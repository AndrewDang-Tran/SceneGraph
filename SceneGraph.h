#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <map> // objectMap nodeMap
#include <stdexcept>
#include "AttributeNode.h"
#include "CameraNode.h"
#include "GeomNode.h"
#include "LightNode.h"
#include "ObjectNode.h"
#include "TransformNode.h"
#include "Loader.h"

class SceneGraph
{
	private:
		map<string, Node*> objectMap;
		map<int, Node*> nodeMap;
		ObjectNode root;
		TrimeshLoader loader;

		int camCount;
		int lightCount;
	public:
		SceneGraph();
		void traversal();
		bool addObjectNode(const int parentID, string n);
		bool addGeomNode(const int parentID, const string fileName, const bool drawFN, const bool drawVN, const bool useFN);
		bool addTransformNode(const int parentID, TransformType type, const GLfloat* args);
		bool addAttributeNode(const int parentID, Mode mode);
		bool addLightNode(const int parentID, LightType type, const GLfloat* position, const GLfloat* spotDirection, const GLfloat* ambient, const GLfloat* diffuse, const GLfloat* specular);
		bool isValid();
		void printRootInfo();
};

#endif

