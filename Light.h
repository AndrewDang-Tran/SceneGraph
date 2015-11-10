#ifndef LIGHT_H
#define LIGHT_H

#include <GL/glut.h>

enum LightType
{
	POINT_LIGHT,
	DIRECTIONAL_LIGHT
};

class Light
{
	private:
		LightType type;
		GLfloat position[3];
		GLfloat spotDirection[3];
		GLfloat ambient[4];
		GLfloat diffuse[4];
		GLfloat specular[4];
	public:
		Light(const LightType t, const GLfloat* pos, const GLfloat* spD, const GLfloat* a, const GLfloat* d, const GLfloat* s);
		void setLight();
		void changeLighting(const LightType t, const GLfloat* pos, const GLfloat* spD, const GLfloat* a, const GLfloat* d, const GLfloat* s);
};

#endif