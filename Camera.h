#ifndef CAMERA_H
#define CAMERA_H

#define DEBUG

#include <GL/glut.h> //GLfloat
#include <cmath> //sin(), cos()
#include "VectorMath.h" //vectorSub3d(), normalize()
#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

#define PI 3.14159265

/**
 * Encapsulates all of the variables of a typical OpenGL camera
 */
class Camera 
{
	private:
		GLfloat position[3];
		GLfloat subjectPosition[3];
		GLfloat localX[3];
		GLfloat localY[3];
		GLfloat localZ[3];
		GLfloat near;
		GLfloat far;
		GLfloat radius;
		GLfloat theta;
		GLfloat phi;

		void setLocalDirections();
	public:
		Camera(const GLfloat* pos, const GLfloat* subjectPos,
				const GLfloat n, const GLfloat f, 
				const GLfloat t, const GLfloat p,
				const GLfloat r);

		void setCamera();
		void setRadius(const GLfloat r);
		void setNear(const GLfloat& n);
		void setFar(const GLfloat& f);

		/**
		 * Orbits the camera around the subject position with the current
		 * radius phi and theta.
		 * @param theta 
		 * @param phi
		 */
		void rotate(const GLfloat t, const GLfloat p);
		/**
		 * Moves the camera closer or farther away from the subject position
		 * @param zoom amount
		 */
		void zoom(const GLfloat zoom);
		/**
		 * Pans in the camera's local x,y coordinate system
		 * @param panX - amount of pan in x plane
		 * @param panY - amount of pan in y plane
		 */
		void pan(const GLfloat panX, const GLfloat panY);
 };

 #endif