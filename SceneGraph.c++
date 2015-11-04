#include <utility>
#include "SceneGraph.h"

SceneGraph::SceneGraph()
{
	camCount = 0;
	lightCount = 0;
}

void SceneGraph::traversal()
{
	if(!isValid()) 
		return;
	
}

void SceneGraph::addNode(Node& newNode, const int parentID, const NodeType nt) 
{
	Node* parentNode = nodeMap.at(parentID);
	Node* newNodePointer = (*parentNode).addChild(newNode);

	if(nt == CAMERA)
		++camCount;
	else if(nt == LIGHT)
		++lightCount;
	else if(nt == OBJECT)
	{
		ObjectNode* newObjectNodePointer = reinterpret_cast<ObjectNode*>(newNodePointer);
		//pair<string, int> newPair(newObjectNodePointer->getName(), newObjectNodePointer->getID());
		objectMap.emplace(newObjectNodePointer->getName(), &newNode);
	}
}

bool SceneGraph::isValid()
{
	return camCount > 0 && lightCount > 0 && objectMap.size() > 0;
}