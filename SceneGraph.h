#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <map> // objectMap nodeMap
#include "AttributeNode.h"
#include "CameraNode.h"
#include "GeomNode.h"
#include "LightNode.h"
#include "ObjectNode.h"
#include "TransformNode.h"

class SceneGraph
{
	private:
		map<string, Node*> objectMap;
		map<int, Node*> nodeMap;
		ObjectNode root;
		int camCount;
		int lightCount;
	public:
		SceneGraph();
		//SceneGraph(const ObjectNode& r);
		void traversal();
		void addNode(const Node& newNode, const int parentID, const NodeType nt);
		bool isValid();
};

#endif

