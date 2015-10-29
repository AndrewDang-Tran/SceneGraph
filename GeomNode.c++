#include "GeomNode.h"

extern bool drawFaceNormal;
extern bool drawVertexNormal;

void GeomNode::GeomNode(const TrimeshLoader& loader, const string& meshName)
{
	loader.loadOBJ(meshName, &mesh);
	type = GEOM;
}
void GeomNode::execute()
{
	mesh.render();
	mesh.renderNormals(drawFaceNormal, drawVertexNormal);
}