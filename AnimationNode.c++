#include <GL/glut.h>
#include "AnimationNode.h"
#include <iostream>

AnimationNode::AnimationNode(const Transform& t, const float cT) : transform(t), cycleTime(cT) 
{ 
	type = ANIMATION;
}

void AnimationNode::execute()
{
	currentTime = clock();
	int currentTimeInt = static_cast<int>(currentTime);
	transform.interpolate(cycleTime, currentTimeInt);
	transform.apply(true);
}

void AnimationNode::setParameters(const TransformType t, const GLfloat* a, const float cT) 
{
	transform.changeArguments(t, a);
	cycleTime = cT;
}

