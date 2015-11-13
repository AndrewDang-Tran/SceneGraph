/**
 * Purpose: handles the parameters of a light.
 * @author Andrew Dang-Tran
 */

#ifndef LIGHT_H
#define LIGHT_H

#include <GL/glut.h>

//#define DEBUG

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

/**
 * Could have been a boolean, but I made it a enum to match the other "types"
 * Determines whether the light is a point light or directional.
 */
enum LightType
{
	POINT_LIGHT,
	DIRECTIONAL_LIGHT
};
/**
 * Encapsulates all of the variables of a typical OpenGL light
 */
class Light
{
	private:
		LightType type;
		int lightNumber;
		GLfloat position[3];
		GLfloat spotDirection[3];
		GLfloat ambient[4];
		GLfloat diffuse[4];
		GLfloat specular[4];
	public:
		Light(const LightType t, const GLfloat* pos, const GLfloat* spD, const GLfloat* a, const GLfloat* d, const GLfloat* s, const int lN);
		/**
		 * Sets the light in the appropriate location and with the correct ambience, diffuse, and specular values.
		 */
		void setLight();
		void changeLighting(const LightType t, const GLfloat* pos, const GLfloat* spD, const GLfloat* a, const GLfloat* d, const GLfloat* s);
		void disable() const;
};

#endif
