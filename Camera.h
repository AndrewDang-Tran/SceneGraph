#ifndef CAMERA_H
#define CAMERA_H

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
		Camera(const GLfloat*& pos, const GLfloat*& subjectPos,
				const GLfloat& n, const GLfloat& f, 
				const GLfloat& t = 45, const GLfloat& p = 45);

		void setCamera() const;
		void setRadius();
		void setNear(const GLfloat& n) { near = n; }
		void setFar(const GLfloat& f) { far = f; }
		
 };

 #endif