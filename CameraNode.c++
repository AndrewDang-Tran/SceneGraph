#include "CameraNode.h"

CameraNode::CameraNode(const Camera& c) : camera(c)
{
	type = CAMERA;
}

void CameraNode::execute()
{
	camera.setCamera();
	#ifdef DEBUG
	cout << "Camera executing" << endl;
	#endif
}

void CameraNode::addChild(const Node& child)
{
	throw string("Camera nodes cannot have children");
}