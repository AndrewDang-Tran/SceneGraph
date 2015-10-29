#include "LightNode.h"

LightNode::LightNode(const Light& l) : light(l)
{
	type = LIGHT;
}

void LightNode::execute() 
{
	light.setLight();
}

void LightNode::addChild()
{
	throw string("Light nodes cannot have children");
}