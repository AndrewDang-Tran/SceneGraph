/**
 * Purpose: Class which handles the animation within the Scene Graph
 * @author Andrew Dang-Tran
 */

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
		clock_t currentTime;
		float cycleTime;
	public:
		AnimationNode(const Transform& t, const float cT);
		/**
		 * Interpolates the transform according to the current clock time.
		 * Then multiplies the transform to the current matrix.
		 */
		void execute();
		void setParameters(const TransformType, const GLfloat* a, const float cT);
};

#endif