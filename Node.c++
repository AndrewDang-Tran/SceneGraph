#include "Node.h"

Node::Node()
{
	parent = NULL;
	staticCounter++;
	id = staticCounter;
}

Node* Node::addChild(Node& child)
{ 
	child.parent = this;
	children.push_back(child);
	return &children.back();
}

int Node::getID() { return id; }
