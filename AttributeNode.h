#ifndef ATTRIBUTENODE_H
#define ATTRIBUTENODE_H

#include "Node.h"

enum Mode
{
	POINT_MODE = 1,
	WIREFRAME_MODE,
	SOLID_MODE,
	SHADED_MODE,
	FACE_NORMAL_MODE,
	VERTEX_NORMAL_MODE
};

class AttributeNode : Node
{
	private:
		Mode mode;
	public:
		AttributeNode(const Mode& m);
		void execute();
};

#endif
