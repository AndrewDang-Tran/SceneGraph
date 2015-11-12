#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <GL/glut.h>

enum TransformType
{
	TRANSLATE,
	SCALE,
	ROTATE,
};

class Transform
{
	private:
		GLfloat args[4];
		GLfloat animatedArgs[4];
		TransformType type;
		int argc;

	public:
		Transform(const TransformType t, const GLfloat* a);
		/**
		 * Apply the transform to the matrix.
		 */ 
		void apply(const bool anime = false) const;
		void changeArguments(const TransformType t, const GLfloat* a);
		void interpolate(const int cycleTime, const int currentTime);
};

#endif