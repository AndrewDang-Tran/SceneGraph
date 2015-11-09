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
	cout << "Address of new Node: " << newObjectNode << endl;
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
	cout << "Address of new Node: " <<  newGeomNode << endl;
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
	cout << "Address of new Node: " << newTransformNode << endl;
	#endif
	return true;
}

bool SceneGraph::addAttributeNode(const int parentID, const Mode mode, const int showFaceNormal, const int showVertexNormal)
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
	AttributeNode* newAttributeNode = new AttributeNode(mode, showFaceNormal, showVertexNormal);
	parentNode->addChild(newAttributeNode);
	nodeMap.emplace(newAttributeNode->getID(), newAttributeNode);
	#ifdef DEBUG
	cout << "New AttributeNode with ID: " << newAttributeNode->getID() << endl;
	cout << "Address of new Node: " << newAttributeNode << endl;
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
	cout << "Address of new Node: " << newLightNode << endl;
	#endif
	++lightCount;
	return true;
}

CameraNode* SceneGraph::addCameraNode(const int parentID, const GLfloat* position, const GLfloat* subjectPosition, const GLfloat near, const GLfloat far, const GLfloat theta, const GLfloat phi, const GLfloat radius)
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
	CameraNode* newCameraNode = new CameraNode(newCamera);
	parentNode->addChild(newCameraNode);
	nodeMap.emplace(newCameraNode->getID(), newCameraNode);
	#ifdef DEBUG
	cout << "New CameraNode with ID: " << newCameraNode->getID() << endl;
	cout << "Address of new Node: " << newCameraNode << endl;
	#endif
	return newCameraNode;
}

bool SceneGraph::deleteNode(const int id)
{
	if(id == 0 || id == 1)
		return false;
	
	Node* nodeToDelete = nodeMap.at(id);

	#ifdef DEBUG
	cout << "Delete Node Address: " << nodeToDelete << endl;
	#endif
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

void SceneGraph::cameraRotate(const GLfloat theta, const GLfloat phi)
{
	camera->cameraNodeRotate(theta, phi);
}

void SceneGraph::cameraZoom(const GLfloat zoom)
{
	camera->cameraNodeZoom(zoom);
}

void SceneGraph::cameraPan(const GLfloat panX, const GLfloat panY)
{
	camera->cameraNodePan(panX, panY);
}
