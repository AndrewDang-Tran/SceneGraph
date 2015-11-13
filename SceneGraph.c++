#include "SceneGraph.h"
#define SCALE_TIME 850000

#ifdef DEBUG
int SceneGraph::debugNodeCounter = 0;
#endif

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
	const GLfloat cameraPosition[3] = {0.0, 0.0, 5.0};
	const GLfloat subjectPosition[3] = {0.0, 0.0, 0.0};
	camera = addCameraNode(0, cameraPosition, subjectPosition, 1.0, 100.0, 45.0, 45.0, 5.0);

	const GLfloat lightPosition[3] = {1.0, 1.0, 1.0};
	const GLfloat lightDirection[3] = {0.0, 0.0, 0.0};
	const GLfloat amb[4] = {0.0, 0.0, 0.0, 1.0};
	const GLfloat dif[4] = {1.0, 1.0, 1.0, 1.0};
	const GLfloat spec[4] = {1.0, 1.0, 1.0, 1.0};
	addLightNode(0, POINT_LIGHT, lightPosition, lightDirection, amb, dif, spec);
	
	++camCount;
	camera->execute();
}

SceneGraph::~SceneGraph()
{
	deleteGraph(root);
}

void SceneGraph::traversal()
{	
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
	cout << "New ObjectNode ID: " << newObjectNode->getID() << endl  << "Parent ID: " << parentID << endl << "" << endl <<  "Name: \"" << n << "\"" << endl;
	#ifdef DEBUG
	cout << "Address of new Node: " << newObjectNode << endl;
	#endif
	return true;
}

void SceneGraph::editObjectNode(const int nodeID, const string newName)
{	
	Node* nodeP;
	try
	{
		nodeP = nodeMap.at(nodeID);
	}
	catch(const out_of_range& oor)
	{
		return;
	}
	if(nodeP->getType() != OBJECT)
		return;
	ObjectNode* objectNodeP = static_cast<ObjectNode*>(nodeP);
	objectNodeP->setName(newName);
}

bool SceneGraph::addGeomNode(const int parentID, string& fileName, const bool drawFN, const bool drawVN, const bool useFN)
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

	if(fileName.find(".obj") == string::npos)
		fileName = fileName + ".obj";

	Node* newGeomNode = new GeomNode(loader, fileName, drawFN, drawVN, useFN);
	parentNode->addChild(newGeomNode);
	nodeMap.emplace(newGeomNode->getID(), newGeomNode);
	cout << "New GeomNode with ID: " << newGeomNode->getID() << endl << "Parent ID: " << parentID << endl << "" << endl;
	#ifdef DEBUG
	cout << "Address of new Node: " <<  newGeomNode << endl;
	#endif
	return true;
}

void SceneGraph::editGeomNode(const int nodeID, string& newFileName, const bool drawFN, const bool drawVN, const bool useFN)
{	
	Node* nodeP;
	try
	{
		nodeP = nodeMap.at(nodeID);
	}
	catch(const out_of_range& oor)
	{
		return;
	}
	if(nodeP->getType() != GEOM)
		return;
	GeomNode* geomNodeP = static_cast<GeomNode*>(nodeP);
	if(newFileName.find(".obj") == string::npos)
		newFileName = newFileName + ".obj";
	geomNodeP->setParameters(loader, newFileName, drawFN, drawVN, useFN);
}

bool SceneGraph::addTransformNode(const int parentID, const TransformType type, const GLfloat* args)
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
	cout << "New TransformNode with ID: " << newTransformNode->getID() << endl << "Parent ID: " << parentID << endl << "" << endl;
	#ifdef DEBUG
	cout << "Address of new Node: " << newTransformNode << endl;
	#endif
	return true;
}

void SceneGraph::editTransformNode(const int nodeID, const TransformType t, const GLfloat* newArgs)
{
	Node* nodeP;
	try
	{
		nodeP = nodeMap.at(nodeID);
	}
	catch(const out_of_range& oor)
	{
		return;
	}
	if(nodeP->getType() != TRANSFORM)
		return;
	TransformNode* transformNodeP = static_cast<TransformNode*>(nodeP);
	transformNodeP->setParameters(t, newArgs);
}

bool SceneGraph::addAnimationNode(const int parentID, const TransformType type, const GLfloat* args, float cycleTime)
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
	cycleTime = cycleTime * SCALE_TIME;
	Node* newAnimationNode = new AnimationNode(newTransform, cycleTime);
	parentNode->addChild(newAnimationNode);
	nodeMap.emplace(newAnimationNode->getID(), newAnimationNode);
	cout << "New AnimationNode with ID: " << newAnimationNode->getID() << endl << "Parent ID: " << parentID << endl << "" << endl;
	#ifdef DEBUG
	cout << "Address of new Node: " << newAnimationNode << endl;
	#endif
	return true;
}

void SceneGraph::editAnimationNode(const int nodeID, const TransformType t, const GLfloat* newArgs, float newCycleTime)
{
	Node* nodeP;
	try
	{
		nodeP = nodeMap.at(nodeID);
	}
	catch(const out_of_range& oor)
	{
		return;
	}
	if(nodeP->getType() != ANIMATION)
		return;
	AnimationNode* animationNodeP = static_cast<AnimationNode*>(nodeP);
	newCycleTime = newCycleTime * SCALE_TIME;
	animationNodeP->setParameters(t, newArgs, newCycleTime);
}

bool SceneGraph::addAttributeNode(const int parentID, const Mode mode)
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
	cout << "New AttributeNode with ID: " << newAttributeNode->getID() << endl << "Parent ID: " << parentID << endl << "" << endl;
	#ifdef DEBUG
	cout << "Address of new Node: " << newAttributeNode << endl;
	#endif
	return true;
}

void SceneGraph::editAttributeNode(const int nodeID, const Mode newMode)
{
	Node* nodeP;
	try
	{
		nodeP = nodeMap.at(nodeID);
	}
	catch(const out_of_range& oor)
	{
		return;
	}
	if(nodeP->getType() != ATTRIBUTE)
		return;
	AttributeNode* attributeNodeP = static_cast<AttributeNode*>(nodeP);
	attributeNodeP->setParameters(newMode);
}

bool SceneGraph::addLightNode(const int parentID, LightType type, const GLfloat* position, const GLfloat* spotDirection, const GLfloat* ambient, const GLfloat* diffuse, const GLfloat* specular)
{
	if(lightCount > 7)
		return false;
	Node* parentNode;
	try
	{
		parentNode = nodeMap.at(parentID);
	}
	catch(const out_of_range& oor)
	{
		return false;
	}
	Light newLight(type, position, spotDirection, ambient, diffuse, specular, lightCount);
	LightNode* newLightNode = new LightNode(newLight);
	parentNode->addChild(newLightNode);
	nodeMap.emplace(newLightNode->getID(), newLightNode);
	cout << "New LightNode with ID: " << newLightNode->getID() << endl << "Parent ID: " << parentID << endl << "" << endl;
	#ifdef DEBUG
	cout << "Address of new Node: " << newLightNode << endl;
	#endif
	++lightCount;
	return true;
}
void SceneGraph::editLightNode(const int nodeID, LightType newType, const GLfloat* newPos, const GLfloat* newSpotD, const GLfloat* newAmb, const GLfloat* newDif, const GLfloat* newSpec)
{
	Node* nodeP;
	try
	{
		nodeP = nodeMap.at(nodeID);
	}
	catch(const out_of_range& oor)
	{
		return;
	}
	if(nodeP->getType() != LIGHT)
		return;
	LightNode* lightNodeP = static_cast<LightNode*>(nodeP);
	lightNodeP->setParameters(newType, newPos, newSpotD, newAmb, newDif, newSpec);
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
	cout << "New CameraNode with ID: " << newCameraNode->getID() << endl << "Parent ID: " << parentID << endl << "" << endl;
	cout << "Address of new Node: " << newCameraNode << endl;
	#endif
	return newCameraNode;
}

bool SceneGraph::deleteNode(const int id)
{
	if(id == 0 || id == 1)
		return false;
	
	Node* nodeToDelete;
	try
	{
		nodeToDelete = nodeMap.at(id);
	}
	catch(const out_of_range& oor)
	{
		return false;
	}
	nodeMap.erase(id);
	Node* parentNode = nodeToDelete->getParent();
	parentNode->removeChild(nodeToDelete);

	cout << "Deleted Node " << id << endl;
	#ifdef DEBUG
	cout << "Delete Node Address: " << nodeToDelete << endl;
	#endif
	/**
	 * May need to change this to make these nodes children have their grandparent as * parent
	 */
	deleteGraph(nodeToDelete);
	glutPostRedisplay();
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

	if(nodeToDelete->getType() == LIGHT)
	{
		const LightNode* lightNodeToDelete = static_cast<const LightNode*>(nodeToDelete);
		#ifdef DEBUG
		cout << "inside light disable SceneGraph::deleteGraph" << endl;
		#endif
		lightNodeToDelete->disableLight();
		--lightCount;
	}

	const vector<Node*>& childrenToDelete = nodeToDelete->getChildren();
	#ifdef DEBUG
	cout << "childrenToDelete: " << &childrenToDelete << endl;
	cout << "size: " << childrenToDelete.size() << endl;
	#endif
	for(int i = 0; i < childrenToDelete.size(); ++i)
		deleteGraph(childrenToDelete.at(i));


	#ifdef DEBUG
	cout << "Deleted Node ID: " << nodeToDelete->getID() << endl;
	cout << "deleting " << debugNodeCounter  << " nodes (not by id)" << endl;
	debugNodeCounter++;
	cout << "Deleting Node Address " << nodeToDelete << endl;
	#endif


	delete nodeToDelete;
	#ifdef DEBUG
	cout << "after delete nodeToDelete in SceneGraph::deleteGraph" << endl;
	#endif
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

NodeType SceneGraph::getNodeType(const int id)
{

	Node* targetNode;
	try
	{
		targetNode = nodeMap.at(id);
	}
	catch(const out_of_range& oor)
	{
		return FAIL;
	}
	return targetNode->getType();
}
