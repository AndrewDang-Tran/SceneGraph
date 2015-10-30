#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "Attribute.h"
#include "CameraNode.h"
#include "GeomNode.h"
#include "LightNode.h"
#include "ObjectNode.h"
#include "TransformNode.h"

class SceneGraph
{
	private:
		vector<Node> nodeContainer;
		Node* root;
	public:
		SceneGraph();
		void traversal();
		void addNode(const Node& newNode, const int& parentID);
		bool valid();
};

#endif

