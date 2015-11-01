#include "Node.h"

Node::Node()
{
	parent = NULL;
	staticCounter++;
	id = staticCounter;
}

void Node::addChild(const Node* child)
{ 
	child->parent = this;
	children.push_back(child); 
}

void traverseChildren(int& cam, int& li, int& obj) const
{
	*this.execute();
	if(type == TRANSFORM)
		glPushMatrix();
	else if(type == CAMERA)
		++cam;
	else if(type == LIGHT)
		++li;
	else if(type == OBJECT)
		++obj;

	for(int i = 0; i < children.size(); ++i)
		traverseChildren(children[i]);

	if(type == TRANSFORM)
		glPopMatrix();
}
