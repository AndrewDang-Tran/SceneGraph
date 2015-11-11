#include "Light.h"

Light::Light(const LightType t, const GLfloat* pos, const GLfloat* spD, const GLfloat* a, const GLfloat* d, const GLfloat* s, const int lN) : type(t)
{
	type = t;
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
	lightNumber = lN;
}

void Light::setLight()
{
	switch(lightNumber)
	{
		case 0:
			glLightfv(GL_LIGHT0, GL_POSITION, position);
			glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
			glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
			if(type == DIRECTIONAL_LIGHT)
				glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
			glEnable(GL_LIGHT0);
			break;
		case 1:	
			glLightfv(GL_LIGHT1, GL_POSITION, position);
			glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
			glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
			if(type == DIRECTIONAL_LIGHT)
				glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection);
			glEnable(GL_LIGHT1);
			break;
		case 2:
			glLightfv(GL_LIGHT2, GL_POSITION, position);
			glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
			glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
			glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
			if(type == DIRECTIONAL_LIGHT)
				glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDirection);
			glEnable(GL_LIGHT2);
			break;
		case 3:
			glLightfv(GL_LIGHT3, GL_POSITION, position);
			glLightfv(GL_LIGHT3, GL_AMBIENT, ambient);
			glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse);
			glLightfv(GL_LIGHT3, GL_SPECULAR, specular);
			if(type == DIRECTIONAL_LIGHT)
				glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spotDirection);
			glEnable(GL_LIGHT3);
			break;
		case 4:
			glLightfv(GL_LIGHT4, GL_POSITION, position);
			glLightfv(GL_LIGHT4, GL_AMBIENT, ambient);
			glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuse);
			glLightfv(GL_LIGHT4, GL_SPECULAR, specular);
			if(type == DIRECTIONAL_LIGHT)
				glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spotDirection);
			glEnable(GL_LIGHT4);
			break;
		case 5:
			glLightfv(GL_LIGHT5, GL_POSITION, position);
			glLightfv(GL_LIGHT5, GL_AMBIENT, ambient);
			glLightfv(GL_LIGHT5, GL_DIFFUSE, diffuse);
			glLightfv(GL_LIGHT5, GL_SPECULAR, specular);
			if(type == DIRECTIONAL_LIGHT)
				glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, spotDirection);
			glEnable(GL_LIGHT5);
			break;
		case 6:
			glLightfv(GL_LIGHT6, GL_POSITION, position);
			glLightfv(GL_LIGHT6, GL_AMBIENT, ambient);
			glLightfv(GL_LIGHT6, GL_DIFFUSE, diffuse);
			glLightfv(GL_LIGHT6, GL_SPECULAR, specular);
			if(type == DIRECTIONAL_LIGHT)
				glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, spotDirection);
			glEnable(GL_LIGHT6);
			break;
		case 7:
			glLightfv(GL_LIGHT7, GL_POSITION, position);
			glLightfv(GL_LIGHT7, GL_AMBIENT, ambient);
			glLightfv(GL_LIGHT7, GL_DIFFUSE, diffuse);
			glLightfv(GL_LIGHT7, GL_SPECULAR, specular);
			if(type == DIRECTIONAL_LIGHT)
				glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, spotDirection);
			glEnable(GL_LIGHT7);
			break;
	}
}

void Light::changeLighting(const LightType t, const GLfloat* pos, const GLfloat* spD, const GLfloat* a, const GLfloat* d, const GLfloat* s)
{
	type = t;
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

void Light::disable() const
{
	#ifdef DEBUG
	cout << "Light::disable" << endl;
	cout << "lightNumber = " << lightNumber << endl;
	#endif
	switch(lightNumber)
	{
		case 0:
			glDisable(GL_LIGHT0);
			break;
		case 1:
			glDisable(GL_LIGHT1);
			#ifdef DEBUG
			cout << "Disabling light 1" << endl;
			#endif
			break;
		case 2:
			glDisable(GL_LIGHT2);
			break;
		case 3:
			glDisable(GL_LIGHT3);
			break;
		case 4:
			glDisable(GL_LIGHT4);
			break;
		case 5:
			glDisable(GL_LIGHT5);
			break;
		case 6:
			glDisable(GL_LIGHT6);
			break;
		case 7:
			glDisable(GL_LIGHT7);
			break;
	}
}
