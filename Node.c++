#include "Node.h"

int Node::staticCounter = 0;

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

void Node::execute() {}
int Node::getID() { return id; }

