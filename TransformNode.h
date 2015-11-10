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
		void execute();
		void setParameters(const TransformType t, const GLfloat* a);
};

#endif