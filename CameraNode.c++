#include "CameraNode.h"

CameraNode::CameraNode(const Camera& c) : camera(c)
{
	type = CAMERA;
}

CameraNode::execute()
{
	camera.setCamera();
}

CameraNode::addChild()
{
	throw string("Camera nodes cannot have children");
}