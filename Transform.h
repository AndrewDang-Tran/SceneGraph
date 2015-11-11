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
		TransformType type;

	public:
		Transform(const TransformType t, const GLfloat* a);
		/**
		 * Apply the transform to the matrix.
		 */ 
		void apply() const;
		void changeArguments(const TransformType t, const GLfloat* a);
};

#endif