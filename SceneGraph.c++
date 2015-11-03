#include "SceneGraph.h"

SceneGraph::SceneGraph()
{
	root = ObjectNode(string("World"));
	camCount = 0;
	lightCount = 0;
}

void SceneGraph::traversal()
{
	if(isValid())
		root.traverseChildren();
}

void SceneGraph::addNode(const Node& newNode, const int parentID, const NodeType nt) 
{
	Node* parentNode = nodeMap.at(parentID);
	Node* newNodePointer = (*parentNode).addChild(newNode);

	if(nt == CAMERA)
		++camCount;
	else if(nt == LIGHT)
		++lightCount;
	else if(nt == OBJECT)
		objectMap.insert(pair<string, int>(newNode.getName(), newNode.getID()));
}

bool SceneGraph::isValid()
{
	return camCount > 0 && lightCount > 0 && objectMap.size() > 0;
}