#include "GeomNode.h"

extern bool drawFaceNormal;
extern bool drawVertexNormal;

GeomNode::GeomNode(TrimeshLoader& loader, const string& meshName, bool drawFN, bool drawVN, bool useFN = false)
{
	loader.loadOBJ(meshName.c_str(), &mesh);
	type = GEOM;
}
void GeomNode::execute()
{
	mesh.render(useFaceNormal);
	mesh.renderNormals(drawFaceNormal, drawVertexNormal);
}
