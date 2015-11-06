#include "Node.h"

int Node::staticCounter = 0;

Node::Node()
{
	parent = NULL;
	id = staticCounter;
	staticCounter++;
}

Node::~Node() {}

void Node::addChild(Node* child)
{ 
	child->parent = this;
	children.push_back(child);
}

void Node::traverseChildren()
{
	execute();
	for(int i = 0; i < children.size(); ++i)
		children.at(i)->traverseChildren();
}

void Node::execute() {}
const int Node::getID() const { return id; }
const vector<Node*>& Node::getChildren() const { return children; }
