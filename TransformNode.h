#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Node.h"

class TransformNode
{
	private:
		Transform transform;
	public:
		TransformNode(const Transform& t) : transform(t) {}
		void execute() { transform.apply(); }
};

#endif