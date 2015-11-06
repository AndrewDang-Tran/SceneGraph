#ifndef CAMERA_H
#define CAMERA_H

#define DEBUG

#include <GL/glut.h> //GLfloat
#include <cmath> //sin(), cos()
#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

#define PI 3.14159265

class Camera 
{
	private:
		GLfloat position[3];
		GLfloat subjectPosition[3];
		GLfloat near;
		GLfloat far;
		GLfloat radius;
		GLfloat theta;
		GLfloat phi;
	public:
		Camera(const GLfloat* pos, const GLfloat* subjectPos,
				const GLfloat n, const GLfloat f, 
				const GLfloat t, const GLfloat p,
				const GLfloat r);

		void setCamera();
		void setRadius(const GLfloat r);
		void setNear(const GLfloat& n) { near = n; }
		void setFar(const GLfloat& f) { far = f; }
		
 };

 #endif