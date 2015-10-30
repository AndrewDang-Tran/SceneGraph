#include "Node.h"

Node::Node()
{
	parent = NULL;
	staticCounter++;
	id = staticCounter;
}

void Node::addChild()
{ 
	child->parent = this;
	children.push_back(child); 
}

void traverseChildren() const
{
	*this.execute();
	if(type == TRANSFORM)
		glPushMatrix();

	for(int i = 0; i < children.size(); ++i)
		traverseChildren(children[i]);

	if(type == TRANSFORM)
		glPopMatrix();
}
