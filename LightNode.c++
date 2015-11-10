#include <string>
#include "LightNode.h"

LightNode::LightNode(const Light& l) : light(l)
{
	type = LIGHT;
}

void LightNode::execute() 
{
	light.setLight();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void LightNode::addChild(const Node* child)
{
	throw string("Light nodes cannot have children");
}

void LightNode::setParameters(const LightType t, const GLfloat* pos, const GLfloat* spD, const GLfloat* a, const GLfloat* d, const GLfloat* s)
{
	light.changeLighting(t, pos, spD, a, d, s);
}