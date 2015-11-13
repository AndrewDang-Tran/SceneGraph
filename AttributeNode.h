/**
 * Purpose: Class handles some of the OpenGL rendering options for the scene
 * @author Andrew Dang-Tran
 */

#ifndef ATTRIBUTENODE_H
#define ATTRIBUTENODE_H

#include "Node.h"

enum Mode
{
	POINT_MODE = 0, //Only render the vertexes
	WIREFRAME_MODE, //Render the triangles
	SOLID_MODE,		//Render the whole object with no shading
	SHADED_MODE,	//Render whole object with shading
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
