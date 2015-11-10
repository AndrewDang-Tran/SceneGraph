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
		/**
		 * Sets the camera in the correct position
		 */
		void execute();
		/**
		 * Camera Nodes cannot have children, and this will throw an error
		 */ 
		void addChild(const Node* child);

		/**
		 * Passes the values along to the camera to rotate
		 * @param theta
		 * @param phi
		 */
		void cameraNodeRotate(const GLfloat theta, const GLfloat phi);
		/**
		 * Passes the values along to the camera to zoom
		 * @param zoom
		 */
		void cameraNodeZoom(const GLfloat zoom);
		/**
		 * Passes the values along to the camera to pan
		 * @param panX
		 * @param panY
		 */
		void cameraNodePan(const GLfloat panX, const GLfloat panY);
};

#endif