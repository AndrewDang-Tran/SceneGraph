#ifndef ATTRIBUTENODE_H
#define ATTRIBUTENODE_H

#include "Node.h"

enum Mode
{
	POINT_MODE = 0,
	WIREFRAME_MODE,
	SOLID_MODE,
	SHADED_MODE,
	//FACE_NORMAL_MODE,
	//VERTEX_NORMAL_MODE
};

class AttributeNode : public Node
{
	private:
		Mode mode;
		bool showVertexNormal;
		bool showFaceNormal;
	public:
		AttributeNode(const Mode& m, const int f, const int v);
		void execute();
		void setParameters(const Mode m, const bool showVN, const bool showFN);
};

#endif
