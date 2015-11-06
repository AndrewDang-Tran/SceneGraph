#include "SceneGraph.h"

SceneGraph::SceneGraph()
{
	camCount = 0;
	lightCount = 0;
}

void SceneGraph::traversal()
{
	if(isValid()) 
		root.traverseChildren();
}

bool SceneGraph::addObjectNode(const int parentID, string n)
{
	cout << "addObject Test 1" << endl;
	Node* parentNode;
	try
	{
		cout << "addObject Test 2" << endl;
		parentNode = nodeMap.at(parentID);
	}
	catch(const out_of_range& oor)
	{
		cout << "addObject Test 3" << endl;
		return false;
	}
	cout << "addObject Test 4" << endl;
	ObjectNode newObjectNode(n);
	Node* newNode = parentNode->addChild(newObjectNode);
	objectMap.emplace(n, newNode);
	nodeMap.emplace(newObjectNode.getID(), newNode);
	cout << "Adding object node with ID: " << newObjectNode.getID() << " and name: " << newObjectNode.getName() << endl;
	return true;
}

bool SceneGraph::addGeomNode(const int parentID, const string fileName, const bool drawFN, const bool drawVN, const bool useFN)
{
	Node* parentNode;
	try
	{
		parentNode = nodeMap.at(parentID);
	}
	catch(const out_of_range& oor)
	{
		return false;
	}
	GeomNode newGeomNode(loader, fileName, drawFN, drawVN, useFN);
	Node* newNode = parentNode->addChild(newGeomNode);
	nodeMap.emplace(newGeomNode.getID(), newNode);
	cout << "Adding GeomNode with ID: " << newGeomNode.getID() << endl;
	return true;
}

bool SceneGraph::addTransformNode(const int parentID, TransformType type, const GLfloat* args)
{
	Node* parentNode;
	try
	{
		parentNode = nodeMap.at(parentID);
	}
	catch(const out_of_range& oor)
	{
		return false;
	}
	Transform newTransform(type, args);
	TransformNode newTransformNode(newTransform);
	Node* newNode = parentNode->addChild(newTransformNode);
	nodeMap.emplace(newTransformNode.getID(), newNode);
	cout << "Adding TransformNode with ID: " << newTransformNode.getID() << endl;
	return true;
}

bool SceneGraph::addAttributeNode(const int parentID, Mode mode)
{
	Node* parentNode;
	try
	{
		parentNode = nodeMap.at(parentID);
	}
	catch(const out_of_range& oor)
	{
		return false;
	}
	AttributeNode newAttributeNode(mode);
	Node* newNode = parentNode->addChild(newAttributeNode);
	nodeMap.emplace(newAttributeNode.getID(), newNode);
	cout << "Addimg AttributeNode with ID: " << newAttributeNode.getID() << endl;
	return true;
}

bool SceneGraph::addLightNode(const int parentID, LightType type, const GLfloat* position, const GLfloat* spotDirection, const GLfloat* ambient, const GLfloat* diffuse, const GLfloat* specular)
{
	Node* parentNode;
	try
	{
		parentNode = nodeMap.at(parentID);
	}
	catch(const out_of_range& oor)
	{
		return false;
	}
	Light newLight(type, position, spotDirection, ambient, diffuse, specular);
	LightNode newLightNode(newLight);
	Node* newNode = parentNode->addChild(newLightNode);
	nodeMap.emplace(newLightNode.getID(), newNode);
	cout << "Adding LightNode with ID: " << newLightNode.getID() << endl;
	return true;
}

bool SceneGraph::isValid()
{
	return camCount > 0 && lightCount > 0 && objectMap.size() > 0;
}

void SceneGraph::printRootInfo()
{
	cout << "Root ID: " << root.getID() << endl << "Root Name: " << root.getName() << endl;
}