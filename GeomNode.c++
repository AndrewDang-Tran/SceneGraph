#include "GeomNode.h"

extern bool drawFaceNormal;
extern bool drawVertexNormal;

GeomNode::GeomNode(TrimeshLoader& loader, const string& meshName, bool drawFN, bool drawVN, bool useFN = false)
{
	loader.loadOBJ(meshName.c_str(), &mesh);
	cout << "mesh has been loaded" << endl;
	type = GEOM;
}
void GeomNode::execute()
{
	glBegin(GL_TRIANGLES);
		mesh.render(useFaceNormal);
		mesh.renderNormals(drawFaceNormal, drawVertexNormal);
	glEnd();
	glutPostRedisplay();
	#ifdef DEBUG
	cout << "Displaying geometry" << endl;
	#endif
}
