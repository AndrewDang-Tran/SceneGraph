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

void LightNode::addChild()
{
	throw string("Light nodes cannot have children");
}