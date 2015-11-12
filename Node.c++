#include <GL/glut.h>
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
	if(type == TRANSFORM || type == ANIMATION || type == GEOM)
		glPushMatrix();

	execute();
	for(int i = 0; i < children.size(); ++i)
		children.at(i)->traverseChildren();

	if(type == TRANSFORM || type == ANIMATION || type == GEOM)
		glPopMatrix();
}

void Node::removeChild(Node* targetChild)
{
	vector<Node*>::iterator b = children.begin();
	vector<Node*>::iterator e = children.end();
	while(b != e)
	{
		if(*b == targetChild)
		{
			children.erase(b);
			return;
		}
		++b;
	}
}

void Node::execute() {}

const int Node::getID() const 
{ 
	return id; 
}

const vector<Node*>& Node::getChildren() const 
{ 
	return children; 
}

const NodeType Node::getType() const 
{ 
	return type; 
}

const Node* Node::getParent() const 
{ 
	return parent; 
}

Node* Node::getParent() 
{ 
	return parent; 
}
