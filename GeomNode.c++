#include "GeomNode.h"

extern bool drawFaceNormal;
extern bool drawVertexNormal;

GeomNode::GeomNode(const TrimeshLoader& loader, const string& meshName)
{
	loader.loadOBJ(meshName.c_str(), &mesh);
	type = GEOM;
}
void GeomNode::execute()
{
	mesh.render();
	mesh.renderNormals(drawFaceNormal, drawVertexNormal);
}
