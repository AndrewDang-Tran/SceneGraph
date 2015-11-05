#ifndef GEOMNODE_H
#define GEOMNODE_H

#include <string> //meshName
#include "Node.h"
#include "Loader.h"
#include "Geom.h"

class GeomNode : Node
{
	private:
		Trimesh mesh;
		bool useFaceNormal;
		bool drawFaceNormal;
		bool drawVertexNormal;
	public:
		GeomNode(TrimeshLoader& loader, const string& meshName, bool drawFN, bool drawVN, bool useFN);
		void execute();
};

#endif