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
};

#endif