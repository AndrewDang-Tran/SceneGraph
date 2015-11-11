#include "ObjectNode.h"

ObjectNode::ObjectNode(const string& n) : name(n) 
{ 
	type = OBJECT;
}

const string ObjectNode::getName() 
{ 
	return name; 
}

void ObjectNode::execute() {}

void ObjectNode::setName(const string newName) 
{
	name = newName; 
}
