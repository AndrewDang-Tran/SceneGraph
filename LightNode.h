#ifndef LIGHTNODE_H
#define LIGHTNODE_H

#include "Node.h"
#include "Light.h"

class LightNode : public Node
{
	private:
		Light light;
	public:
		LightNode(const Light& l);
		/**
		 * Sets the light in right position with parameters given.
		 */
		void execute();
		/**
		 * Light Nodes cannot have children, and this will throw an error
		 * A simple string with an error message is thrown.
		 */ 
		void addChild(const Node* child);
		void setParameters(const LightType t, const GLfloat* pos, const GLfloat* spD, const GLfloat* a, const GLfloat* d, const GLfloat* s);
		void disableLight() const;
};

#endif