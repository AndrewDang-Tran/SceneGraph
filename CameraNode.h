#ifndef CAMERANODE_H
#define CAMERANODE_H

#include <string>
#include <iostream>
#include "Node.h"
#include "Camera.h"

class CameraNode : public Node
{
	private:
		Camera camera;
	public:
		CameraNode(const Camera& c);
		void execute();
		void addChild(const Node& child);
		void cameraNodeRotate(const GLfloat theta, const GLfloat phi);
		void cameraNodeZoom(const GLfloat zoom);
		void cameraNodePan(const GLfloat panX, const GLfloat panY);
};

#endif