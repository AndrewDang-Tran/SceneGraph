#include "Transform.h"
//#define DEBUG

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

Transform::Transform(const TransformType t, const GLfloat* a) : type(t)
{
	#ifdef DEBUG
	cout << "Transform::Transform type = " << type << endl;
	#endif
	if(type == TRANSLATE || type == SCALE)
		argc = 3;
	else
		argc = 4;

	for(int i = 0; i < argc; ++i)
		args[i] = a[i];
}

void Transform::apply(const bool anime) const
{
	if(!anime)
	{
		if(type == TRANSLATE)
			glTranslatef(args[0], args[1], args[2]);
		else if(type == SCALE)
			glScalef(args[0], args[1], args[2]);
		else
			glRotatef(args[3], args[0], args[1], args[2]);

		#ifdef DEBUG
		cout << "in !animated if statement" << endl;
		#endif
	}
	else
	{
		#ifdef DEBUG
		cout << "In anime with type: " << type << endl;
		#endif
		if(type == TRANSLATE)
			glTranslatef(animatedArgs[0], animatedArgs[1], animatedArgs[2]);
		else if(type == SCALE)
			glScalef(animatedArgs[0], animatedArgs[1], animatedArgs[2]);
		else
		{
			glRotatef(animatedArgs[3], animatedArgs[0], animatedArgs[1], animatedArgs[2]);
			#ifdef DEBUG
			cout << "in animated rotate" << endl;
			#endif
		}
		#ifdef DEBUG
		cout << "in animated if statement" << endl;
		#endif
	}
}

void Transform::changeArguments(const TransformType t, const GLfloat* a)
{
	type = t;
	if(type == TRANSLATE || type == SCALE)
		argc = 3;
	else
		argc = 4;

	for(int i = 0; i < argc; ++i)
		args[i] = a[i];
}

void Transform::interpolate(const int cycleTime, const int currentTime)
{
	float ratio = ((float) (currentTime % cycleTime)) / cycleTime;
	for(int i = 0; i < argc; ++i)
		animatedArgs[i] = args[i] * ratio;
}