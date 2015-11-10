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
		void execute();
		void addChild(const Node* child);
		void setParameters(const LightType t, const GLfloat* pos, const GLfloat* spD, const GLfloat* a, const GLfloat* d, const GLfloat* s);
};

#endif