#ifndef LIGHTNODE_H
#define LIGHT_NODE_H

#include "Node.h"

class LightNode : Node
{
	private:
		Light light;
	public:
		Light(const Light& l);
		void execute();
		void addChild(const Node*& child);
};

#endif