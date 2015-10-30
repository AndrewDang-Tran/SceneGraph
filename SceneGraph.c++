#include "SceneGraph.h"

SceneGraph::SceneGraph()
{
	ObjectNode rootNode("World");
	nodeContainer.push_back(rootNode);
	root = &nodeContainer[0];
}

void SceneGraph::traversal()
{
	root->traverseChildren();
}

void SceneGraph::addNode(const Node& newNode, const int& parentID) 
{
	nodeContainer.push_back(newNode);
	Node* parentNode = nodeContainer[parentID];
	parentNode->addChild(&nodeContainer.back());
}

bool SceneGraph::valid()
{
	
}