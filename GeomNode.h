/**
 * Purpose: Wraps the trimesh class in a node so it can be inserted in the scene.
 * @author Andrew Dang-Tran
 */

#ifndef GEOMNODE_H
#define GEOMNODE_H

#include <string> //meshName
#include "Node.h"
#include "Loader.h"
#include "Geom.h"

class GeomNode : public Node
{
	private:
		Trimesh mesh;
		bool useFaceNormal; //when true uses the face normals for lighting otherwise uses the vertex normals for lighting
		bool drawFaceNormal;
		bool drawVertexNormal;
	public:
		GeomNode(TrimeshLoader& loader, const string& meshName, bool drawFN, bool drawVN, bool useFN);
		/**
		 * Renders the object and the face normals / vertex normals if necessary.
		 */ 
		void execute();
		void setParameters(TrimeshLoader& loader, const string newObjFile, const bool drawFN, const bool drawVN, const bool useFN);
};

#endif