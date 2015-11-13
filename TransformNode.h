/**
 * Purpose: Wraps the Transform class with a node so it can be added to the scene.
 * @author Andrew Dang-Tran
 */

#ifndef TRANSFORMNODE_H
#define TRANSFORMNODE_H

#include "Node.h"
#include "Transform.h"

class TransformNode : public Node
{
	private:
		Transform transform;
	public:
		TransformNode(const Transform& t);
		/**
		 * Applies the transform within the Node to the matrix
		 */
		void execute();
		void setParameters(const TransformType t, const GLfloat* a);
};

#endif