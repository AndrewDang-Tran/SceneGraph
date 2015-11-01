#include <GL/glut.h> //for linux
#include "SceneGraph.h"

int windowWidth = 500;
int windowHeight = 500;

int main(int argc, char **argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Scene Graph");
	glEnable(GL_COLOR_MATERIAL);





	glDepthFunc(GL_LESS);
	glutMainLoop();
}