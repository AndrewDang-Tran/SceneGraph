#ifndef LIGHTNODE_H
#define LIGHT_NODE_H

#include "Node.h"
#include "Light.h"

class LightNode : Node
{
	private:
		Light light;
	public:
		LightNode(const Light& l);
		void execute();
		void addChild(const Node*& child);
};

#endif