#ifndef CAMERANODE_H
#define CAMERANODE_H

#include "Node.h"

class CameraNode : Node
{
	private:
		Camera camera;
	public:
		CameraNode(const Camera& c) : camera(c) {}
		void execute();
		addChild(const Node*& child);
};

#endif