#ifndef ANIMATIONNODE_H
#define ANIMATIONNODE_H

#include <ctime> //clock_t clock()
#include "Node.h"
#include "Transform.h"

/**
 * This node animates all it's children with a linearly interpolated transform over time.
 */
class AnimationNode : public Node 
{
	private:
		Transform transform;
		//time_t currentTime;
		clock_t currentTime;
		int cycleTime;
	public:
		AnimationNode(const Transform& t, int cT);
		/**
		 * Interpolates the transform according to the current clock time.
		 * Then adds the transform to the current matrix.
		 */
		void execute();
		void setParameters(const TransformType, const GLfloat* a, const int cT);
};

#endif