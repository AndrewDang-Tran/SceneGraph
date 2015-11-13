/**
 * Purpose: Class which brings all the nodes together, and creates the scene.
 * @author Andrew Dang-Tran
 */

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

/**
 * 
 */
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

		#ifdef DEBUG
		static int debugNodeCounter;
		#endif

		/**
		 * SceneGraphs are valid when they have at least 1 object, camera, and light node.
		 */
		bool isValid();
		/**
		 * helper method to delete a node and all of its children recursively
		 */
		void deleteGraph(const Node* nodeToDelete);
		/**
		 * Add a camera to 
		 */
		CameraNode* addCameraNode(const int parentID, const GLfloat* position, const GLfloat* subjectPosition, const GLfloat near, const GLfloat far, const GLfloat theta, const GLfloat phi, const GLfloat radius);
	public:
		/**
		 * Construct a typical SceneGraph with a root "World" node, (ID = 0)
		 * Camera Node (ID = 1) and
		 * Light Node (ID = 2)
		 * The nodes your adding should be the children of the root. 
		 */
		SceneGraph();

		/**
		 * Makes sure to properly free the memory of all the Nodes in the Scene Graph
		 */
		~SceneGraph();

		/**
		 * Start the traversal of the graph from the root.
		 */
		void traversal();

		/**
		 * Add an ObjectNode to the Scene Graph
		 * @param parentID
		 * @param name
		 */
		bool addObjectNode(const int parentID, string n);
		/**
		 * Edit a Node within the Scene Graph
		 * @param nodeID
		 * @param newName
		 */
		void editObjectNode(const int nodeID, const string newName);

		/**
		 * Add a Geometry Node to the Scene Graph
		 * @param parentID
		 * @param drawFaceNormals - show the lines which represent face normals
		 * @param drawVertexNormals - show the lines representing vertex normals
		 * @param useFaceNormals - use face or vertex normals for shading
		 */
		bool addGeomNode(const int parentID, string& fileName, const bool drawFN, const bool drawVN, const bool useFN);
		/**
		 * Edit a Geometry Node within the Scene Graph
		 * @param parentID
		 * @param drawFaceNormals - show the lines which represent face normals
		 * @param drawVertexNormals - show the lines representing vertex normals
		 * @param useFaceNormals - use face or vertex normals for shading
		 */
		void editGeomNode(const int nodeID, string& newFileName, const bool drawFN, const bool drawVN, const bool useFN);

		/**
		 * Add a Transform Node to the Scene Graph
		 * @param parentID
		 * @param TransformType - Translate, Scale, Rotate
		 * @param Arguments - x y z Theta array
		 */
		bool addTransformNode(const int parentID, const TransformType type, const GLfloat* args);
		/**
		 * Edit a Transform Node within a Scene Graph
		 * @param nodeID
		 * @param TransformType - Translate, Scale, Rotate
		 * @param Arguments - x y z Theta array
		 */
		void editTransformNode(const int nodeID, const TransformType t, const GLfloat* newArgs);

		/**
		 * Add an Animation Node to the Scene Graph
		 * @param parentID
		 * @param TransformType - Translate, Scale, Rotate
		 * @param Arguments - x y z Theta array
		 * @param cycleTime - Estimate of Seconds
		 */
		bool addAnimationNode(const int parentID, const TransformType type, const GLfloat* args, float cycleTime);
		/**
		 * Edit an AnimationNode within the Scene Graph
		 * @param nodeID
		 * @param newTransformType - Translate, Scale, Rotate
		 * @param newArguments - x y z Theta array
		 * @param newcycleTime - Estimate of Seconds for the animation complete and restart.
		 */
		void editAnimationNode(const int nodeID, const TransformType t, const GLfloat* newArgs, float newCycleTime);

		/**
		 * Add an AnimationNode to the Scene Graph
		 * @param parentID
		 * @param Mode - POINT_MODE, WIREFRAME_MODE, SOLID_MODE, SHADED_MODE
		 */
		bool addAttributeNode(const int parentID, const Mode mode);
		/**
		 * Edit an Attribute Node within the Scene Graph
		 * @param nodeID
		 * @param newMode - POINT_MODE, WIREFRAME_MODE, SOLID_MODE, SHADED_MODE
		 */
		void editAttributeNode(const int nodeID, const Mode newMode);

		/**
		 * Add a Light Node to the Scene Graph
		 * @param parentID
		 * @param LightType - POINT, DIRECTIONAL
		 * @param position - x y z array
		 * @param spotDirection - x y z array
		 * @param ambient - r g b i array
		 * @param diffuse - r g b i array
		 * @param specular - r g b i array
		 */
		bool addLightNode(const int parentID, LightType type, const GLfloat* position, const GLfloat* spotDirection, const GLfloat* ambient, const GLfloat* diffuse, const GLfloat* specular);
		/**
		 * Edit a Light Node within the Scene Graph
		 * @param nodeID
		 * @param newLightType - POINT, DIRECTIONAL
		 * @param newposition - x y z array
		 * @param newSpotDirection - x y z array
		 * @param newAmbient - r g b i array
		 * @param newDiffuse - r g b i array
		 * @param newSpecular - r g b i array
		 */
		void editLightNode(const int nodeID, LightType newType, const GLfloat* newPos, const GLfloat* newSpotD, const GLfloat* newAmb, const GLfloat* newDif, const GLfloat* newSpec);

		/**
		 * Delete a node and all of its children
		 * @param id
		 */
		bool deleteNode(const int id);
		/**
		 * rotate the camera
		 * @param theta
		 * @param phi
		 */
		void cameraRotate(const GLfloat theta, const GLfloat phi);
		/**
		 * zoom the camera
		 * @param zoom
		 */
		void cameraZoom(const GLfloat zoom);
		/**
		 * pan the camera
		 * @param panX
		 * @param panY
		 */
		void cameraPan(const GLfloat panX, const GLfloat panY);
		NodeType getNodeType(const int id);
};

#endif

