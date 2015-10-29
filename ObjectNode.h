#ifndef OBJECTNODE_H
#define OBJECTNODE_H

#include <string> //name
#include "Node.h"

class ObjectNode : Node 
{
	private:
		string name;
	public:
		ObjectNode(const String& n) : name(n) { type = OBJECT; }
};

#endif