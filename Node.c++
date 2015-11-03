#include "Node.h"

Node::Node()
{
	parent = NULL;
	staticCounter++;
	id = staticCounter;
}

Node* Node::addChild(const Node& child)
{ 
	child.parent = this;
	children.push_back(child);
	return &children.back();
}

void traverseChildren() const
{
	*this.execute();
	if(type == TRANSFORM)
		glPushMatrix();

	for(int i = 0; i < children.size(); ++i)
		children.at(i).traverseChildren();

	if(type == TRANSFORM)
		glPopMatrix();
}

int getID() { return id; }
