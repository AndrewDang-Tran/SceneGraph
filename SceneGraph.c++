#include "SceneGraph.h"

int SceneGraph::debugNodeCounter = 0;


SceneGraph::SceneGraph()
{
	camCount = 0;
	lightCount = 0;
	root = new ObjectNode("World");
	objectMap[root->getName()] = root;
	nodeMap[root->getID()] = root;
	#ifdef DEBUG
	cout << "Root Name: " << root->getName() << endl;
	cout << "Root ID: " << root->getID() << endl;
	#endif
	const GLfloat position[3] = {0.0, 0.0, 5.0};
	const GLfloat subjectPosition[3] = {0.0, 0.0, 0.0};
	camera = addCameraNode(0, position, subjectPosition, 1.0, 10.0, 45.0, 45.0, 5.0);
	++camCount;
	camera->execute();
}

SceneGraph::~SceneGraph()
{
	deleteGraph(root);
}

void SceneGraph::traversal()
{
	#ifdef DEBUG
	//cout << "valid: " << isValid() << endl;
	#endif
	if(isValid()) 
		root->traverseChildren();
}

bool SceneGraph::addObjectNode(const int parentID, string n)
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
	Node* newObjectNode = new ObjectNode(n);
	if(objectMap[n] == NULL)
		objectMap.emplace(n, newObjectNode);
	else
	{
		delete newObjectNode;
		return false;
	}
	parentNode->addChild(newObjectNode);
	nodeMap.emplace(newObjectNode->getID(), newObjectNode);
	#ifdef DEBUG
	cout << "New ObjectNode ID: " << newObjectNode->getID() << endl <<  "Name: \"" << n << "\"" << endl;
	#endif
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
	Node* newGeomNode = new GeomNode(loader, fileName, drawFN, drawVN, useFN);
	parentNode->addChild(newGeomNode);
	nodeMap.emplace(newGeomNode->getID(), newGeomNode);
	#ifdef DEBUG
	cout << "New GeomNode with ID: " << newGeomNode->getID() << endl;
	#endif
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
	Node* newTransformNode = new TransformNode(newTransform);
	parentNode->addChild(newTransformNode);
	nodeMap.emplace(newTransformNode->getID(), newTransformNode);
	#ifdef DEBUG
	cout << "New TransformNode with ID: " << newTransformNode->getID() << endl;
	#endif
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
	AttributeNode* newAttributeNode = new AttributeNode(mode);
	parentNode->addChild(newAttributeNode);
	nodeMap.emplace(newAttributeNode->getID(), newAttributeNode);
	#ifdef DEBUG
	cout << "New AttributeNode with ID: " << newAttributeNode->getID() << endl;
	#endif
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
	LightNode* newLightNode = new LightNode(newLight);
	parentNode->addChild(newLightNode);
	nodeMap.emplace(newLightNode->getID(), newLightNode);
	#ifdef DEBUG
	cout << "New LightNode with ID: " << newLightNode->getID() << endl;
	#endif
	++lightCount;
	return true;
}

Node* SceneGraph::addCameraNode(const int parentID, const GLfloat* position, const GLfloat* subjectPosition, const GLfloat near, const GLfloat far, const GLfloat theta, const GLfloat phi, const GLfloat radius)
{
	Node* parentNode;
	try
	{
		parentNode = nodeMap.at(parentID);
	}
	catch(const out_of_range& oor)
	{
		return NULL;
	}
	Camera newCamera(position, subjectPosition, near, far, theta, phi, radius);
	Node* newCameraNode = new CameraNode(newCamera);
	parentNode->addChild(newCameraNode);
	nodeMap.emplace(newCameraNode->getID(), newCameraNode);
	#ifdef DEBUG
	cout << "New CameraNode with ID: " << newCameraNode->getID() << endl;
	#endif
	return newCameraNode;
}

bool SceneGraph::deleteNode(const int id)
{
	Node* nodeToDelete = nodeMap.at(id);
	/**
	 * May need to change this to make these nodes children have their grandparent as * parent
	 */
	 deleteGraph(nodeToDelete);
	 return true;
}

bool SceneGraph::isValid()
{
	return camCount > 0 && lightCount > 0 && objectMap.size() > 0;
}


void SceneGraph::deleteGraph(const Node* nodeToDelete)
{
	if(!nodeToDelete)
		return;
	vector<Node*> childrenToDelete = nodeToDelete->getChildren();
	for(int i = 0; i < childrenToDelete.size(); ++i)
		deleteGraph(childrenToDelete.at(i));

	#ifdef DEBUG
	cout << "Deleted Node ID: " << nodeToDelete->getID() << endl;
	cout << "deleting " << debugNodeCounter  << " nodes (not by id)" << endl;
	debugNodeCounter++;
	#endif

	delete nodeToDelete;
}

