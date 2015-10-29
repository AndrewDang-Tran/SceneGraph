#include "Light.h"

Light::Light(const LightType& t, const GLfloat*& pos, const GLfloat*& spD, const GLfloat*& a, const GLfloat*& d, const GLfloat*& s) : type(t)
{
	for(int i = 0; i < 3; ++i)
	{
		position[i] = pos[i];
		spotDirection[i] = spD[i];
	}
	for(int i = 0; i < 4; ++i)
	{
		ambient[i] = a[i];
		diffuse[i] = d[i];
		specular[i] = s[i];
	}
}

void Light::setLight()
{
	glLightfv(GL_LIGHT0, GL_POSITION, 
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	if(type == DIRECTIONAL_LIGHT)
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
}	
