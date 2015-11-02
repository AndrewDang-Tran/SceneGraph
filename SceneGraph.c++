#include "SceneGraph.h"

SceneGraph::SceneGraph()
{
	valid = false;
	ObjectNode rootNode("World");
	nodeContainer.push_back(rootNode);
	root = &nodeContainer[0];
}

void SceneGraph::traversal()
{
	int cameraCount = 0;
	int lightCount = 0;
	int objectCount = -1;
	root->traverseChildren(cameraCount, lightCount, objectCount);
	if(cameraCount > 0 && lightCount > 0 && objectCount > 0)
		valid = true;
	else
		valid = false;
}

void SceneGraph::addNode(const Node& newNode, const int& parentID) 
{
	nodeContainer.push_back(newNode);
	Node* parentNode = nodeContainer[parentID];
	parentNode->addChild(&nodeContainer.back());
}

bool SceneGraph::isValid()
{
	return valid;
}