#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <map> // objectMap nodeMap
#include <stdexcept>
#include "AttributeNode.h"
#include "CameraNode.h"
#include "GeomNode.h"
#include "LightNode.h"
#include "ObjectNode.h"
#include "TransformNode.h"
#include "Loader.h"

class SceneGraph
{
	private:
		map<string, Node*> objectMap;
		map<int, Node*> nodeMap;
		ObjectNode* root;
		TrimeshLoader loader;
		CameraNode* camera;

		int camCount;
		int lightCount;

		static int debugNodeCounter;

		bool isValid();
		void deleteGraph(const Node* nodeToDelete);
		CameraNode* addCameraNode(const int parentID, const GLfloat* position, const GLfloat* subjectPosition, const GLfloat near, const GLfloat far, const GLfloat theta, const GLfloat phi, const GLfloat radius);
	public:
		SceneGraph();
		~SceneGraph();
		void traversal();
		bool addObjectNode(const int parentID, string n);
		void editObjectNode(const int nodeID, const string newName);

		bool addGeomNode(const int parentID, const string fileName, const bool drawFN, const bool drawVN, const bool useFN);
		void editGeomNode(const int nodeID, const string newFileName, const bool drawFN, const bool drawVN, const bool useFN);

		bool addTransformNode(const int parentID, TransformType type, const GLfloat* args);
		void editTransformNode(const int nodeID, TransformType t, const GLfloat* newArgs);

		bool addAttributeNode(const int parentID, const Mode mode, const int showFaceNormal, const int showVertexNormal);
		void editAttributeNode(const int nodeID, const Mode newMode, const int showFN, const int showVN);

		bool addLightNode(const int parentID, LightType type, const GLfloat* position, const GLfloat* spotDirection, const GLfloat* ambient, const GLfloat* diffuse, const GLfloat* specular);
		void editLightNode(const int nodeID, LightType newType, const GLfloat* newPos, const GLfloat* newSpotD, const GLfloat* newAmb, const GLfloat* newDif, const GLfloat* newSpec);

		bool deleteNode(const int id);
		void cameraRotate(const GLfloat theta, const GLfloat phi);
		void cameraZoom(const GLfloat zoom);
		void cameraPan(const GLfloat panX, const GLfloat panY);
		NodeType getNodeType(const int id);
};

#endif

