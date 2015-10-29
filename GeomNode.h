#ifndef GEOMNODE_H
#define GEOMNODE_H

#include <string> //meshName
#include "Node.h"
#include "geom.h"
#include "loader.h"

class GeomNode : Node
{
	private:
		Trimesh mesh;
	public:
		GeomNode(const TrimeshLoader& loader, const string& meshName);
		void execute();
};

#endif