#ifndef ATTRIBUTENODE_H
#define ATTRIBUTENODE_H

#include "Node.h"

enum Mode
{
	POINT_MODE = 0,
	WIREFRAME_MODE,
	SOLID_MODE,
	SHADED_MODE,
};

/**
 * This node determines the rendering mode of all of it's children.
 */
class AttributeNode : public Node
{
	private:
		Mode mode;
	public:
		AttributeNode(const Mode m);
		/**
		 * Sets the correct OpenGL parameters for each mode
		 */
		void execute();
		void setParameters(const Mode m);
};

#endif
