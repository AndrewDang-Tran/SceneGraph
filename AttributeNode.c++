#include <GL/glut.h>
#include "AttributeNode.h"
#ifdef DEBUG
#include <iostream>
#endif

extern bool drawFaceNormal;
extern bool drawVertexNormal;

AttributeNode::AttributeNode(const Mode& m, const int f, const int v) : mode(m)
{
	showFaceNormal = bool(f);
	showVertexNormal = bool(v);
	type = ATTRIBUTE;
}

void AttributeNode::execute()
{
	drawFaceNormal = showFaceNormal;
	drawVertexNormal = showVertexNormal;
	#ifdef DEBUG
	//cout << "AttributeNode::drawFaceNormal = " << drawFaceNormal << endl;
	//cout << "AttributeNode::drawVertexNormal = " << drawVertexNormal << endl;
	#endif
	switch(mode)
	{
		case POINT_MODE:
			glDisable(GL_LIGHTING);
			glPointSize(.5);
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			break;
		case WIREFRAME_MODE:
			glDisable(GL_LIGHTING);
			glLineWidth(.5);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case SOLID_MODE:
			glDisable(GL_LIGHTING);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		case SHADED_MODE:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			break;
	}
}

void AttributeNode::setParameters(const Mode m, const bool showVN, const bool showFN)
{
	mode = m;
	showVertexNormal = showVN;
	showFaceNormal = showFN;
}
