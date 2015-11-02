#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "AttributeNode.h"
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
		bool valid;
	public:
		void traversal();
		void addNode(const Node& newNode, const int& parentID);
		bool isValid();
};

#endif

