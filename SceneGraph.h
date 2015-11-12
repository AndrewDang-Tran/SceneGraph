#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <map> // nodeMap, objectMap
#include <stdexcept> //std::out_of_range
#include "AttributeNode.h"
#include "CameraNode.h"
#include "GeomNode.h"
#include "LightNode.h"
#include "ObjectNode.h"
#include "TransformNode.h"
#include "AnimationNode.h"
#include "Loader.h"

class SceneGraph
{
	private:
		map<string, Node*> objectMap; //planning on deleting by name, but didn't end up doing it yet. still use it to check for valid graph.
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

		/**
		 * Start the traversal of the graph from the root.
		 */
		void traversal();

		bool addObjectNode(const int parentID, string n);
		void editObjectNode(const int nodeID, const string newName);

		bool addGeomNode(const int parentID, string& fileName, const bool drawFN, const bool drawVN, const bool useFN);
		void editGeomNode(const int nodeID, string& newFileName, const bool drawFN, const bool drawVN, const bool useFN);

		bool addTransformNode(const int parentID, const TransformType type, const GLfloat* args);
		void editTransformNode(const int nodeID, const TransformType t, const GLfloat* newArgs);

		bool addAnimationNode(const int parentID, const TransformType type, const GLfloat* args, int cycleTime);
		void editAnimationNode(const int nodeID, const TransformType t, const GLfloat* newArgs, int newCycleTime);

		bool addAttributeNode(const int parentID, const Mode mode);
		void editAttributeNode(const int nodeID, const Mode newMode);

		bool addLightNode(const int parentID, LightType type, const GLfloat* position, const GLfloat* spotDirection, const GLfloat* ambient, const GLfloat* diffuse, const GLfloat* specular);
		void editLightNode(const int nodeID, LightType newType, const GLfloat* newPos, const GLfloat* newSpotD, const GLfloat* newAmb, const GLfloat* newDif, const GLfloat* newSpec);

		bool deleteNode(const int id);
		void cameraRotate(const GLfloat theta, const GLfloat phi);
		void cameraZoom(const GLfloat zoom);
		void cameraPan(const GLfloat panX, const GLfloat panY);
		NodeType getNodeType(const int id);
};

#endif

