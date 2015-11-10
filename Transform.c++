#include "Transform.h"

Transform::Transform(const TransformType t, const GLfloat* a)
{
	type = t;
	int argc;
	if(type == TRANSLATE || SCALE)
		argc = 3;
	else
		argc = 4;

	for(int i = 0; i < argc; ++i)
		args[i] = a[i];
}

void Transform::apply() const
{
	if(type == TRANSLATE)
		glTranslatef(args[0], args[1], args[2]);
	else if(type == SCALE)
		glScalef(args[0], args[1], args[2]);
	else
		glRotated(args[0], args[1], args[2], args[3]);
}

void Transform::changeArguments(const TransformType t, const GLfloat* a)
{
	type = t;
	int argc;
	if(type == TRANSLATE || SCALE)
		argc = 3;
	else
		argc = 4;

	for(int i = 0; i < argc; ++i)
		args[i] = a[i];
}