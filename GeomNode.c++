#include "GeomNode.h"


GeomNode::GeomNode(TrimeshLoader& loader, const string& meshName, bool drawFN, bool drawVN, bool useFN = false)
{
	loader.loadOBJ(meshName.c_str(), &mesh);
	useFaceNormal = useFN;
	drawFaceNormal = drawFN;
	drawVertexNormal = drawVN;
	type = GEOM;
	#ifdef DEBUG
	cout << "mesh has been loaded" << endl;
	#endif
}
void GeomNode::execute()
{
	glBegin(GL_TRIANGLES);
		mesh.render(useFaceNormal);
	glEnd();

	glBegin(GL_LINES);
		mesh.renderNormals(drawFaceNormal, drawVertexNormal);
	glEnd();
}

void GeomNode::setParameters(TrimeshLoader& loader, const string newObjFile, const bool drawFN, const bool drawVN, const bool useFN)
{
	mesh = Trimesh();
	loader.loadOBJ(newObjFile.c_str(), &mesh);
	useFaceNormal = useFN;
	drawFaceNormal = drawFN;
	drawVertexNormal = drawVN;
}
