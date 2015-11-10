#include "CameraNode.h"

CameraNode::CameraNode(const Camera& c) : camera(c)
{
	type = CAMERA;
}

void CameraNode::execute()
{
	camera.setCamera();
	#ifdef DEBUG
	//cout << "Camera executing" << endl;
	#endif
}

void CameraNode::addChild(const Node* child)
{
	throw string("Camera nodes cannot have children");
}

void CameraNode::cameraNodeRotate(const GLfloat theta, const GLfloat phi)
{
	camera.rotate(theta, phi);
}

void CameraNode::cameraNodeZoom(const GLfloat zoom)
{
	camera.zoom(zoom);
}

void CameraNode::cameraNodePan(const GLfloat panX, const GLfloat panY)
{
	camera.pan(panX, panY);
}