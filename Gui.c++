#include <GL/glut.h> //for linux
#include "./glui-2.36/src/include/GL/glui.h"
#include "SceneGraph.h"

#define ADD_OBJECT 100
#define ADD_GEOMETRY 101
#define ADD_TRANSFORM 102
#define ADD_ATTRIBUTE 103

#define RADIO_TRANSFORM 201
#define RADIO_ATTRIBUTE 202
#define RADIO_LIGHTTYPE 203

#define CHECK_VERTEXNORMAL 301
#define CHECK_FACENORMAL 302

int windowWidth = 1024;
int windowHeight = 768;

bool drawFaceNormal = false;
bool drawVertexNormal = false;

GLfloat tempNear = .01;
GLfloat tempFar = 10;

TrimeshLoader loader;
SceneGraph sceneGraph;

/*
 * GLUI variables
 */

//window variables
int mainWindow;
GLUI *horizontalSubWindow, *verticalSubWindow;

//GLUI panels
GLUI_Rollout *objectRoll, *geometryRoll, *transformRoll, *attributeRoll, *lightRoll, *cameraRoll;

//object rollout variables
GLUI_EditText* nameEdit;
string objectName = "Name me";

//geometry rollout variables
GLUI_EditText* fileEdit;
string objFileName = ".Obj file";

//transform rollout variables
GLUI_RadioGroup* transformRadio;
TransformType currentTransformType = TRANSLATE;
GLUI_Spinner *spinTheta, *spinX, *spinY, *spinZ;
GLfloat xArg = 0.0;
GLfloat yArg = 0.0;
GLfloat zArg = 0.0;
GLfloat theta = 0.0;

//Attribute rollout variables
GLUI_RadioGroup* attributeRadio;
Mode currentMode = SHADED_MODE;
GLUI_Checkbox* vertexNormalCheck, *faceNormalCheck;
int showVertexNormal, showFaceNormal;

//Light rollout variables
GLUI_RadioGroup* lightTypeRadio;
LightType currentLightType = POINT_LIGHT;
GLUI_Spinner* spinLightPosXYZ[3];
GLfloat lightPosXYZ[3];

//rollout to show spotlight direction if needed
GLUI_Rollout* spotLightDirectionRoll;
GLUI_Spinner* spinLightTargetXYZ[3];

GLfloat lightTargetXYZ[3];


//rollout to change 
GLUI_Rollout* lightParameterRoll;
GLUI_Spinner* spinAmbientRGBI[4];
GLfloat ambientRGBI[4];

GLUI_Spinner *spinDiffuseRed, *spinDiffuseGreen, *spinDiffuseBlue, *spinDiffuseIntensity;
GLfloat diffuseRGBI[4];

GLUI_Spinner *spinSpecularRed, *spinSpecularGreen, *spinSpecularBlue, *spinSpecularIntensity;
/*GLfloat specularRed = 1.0;
GLfloat specularGreen = 1.0;
GLfloat specularBlue = 1.0;
GLfloat specularIntensity = 1.0;*/
GLfloat specularRGBI[4];

/*
 * Control callback that will make changes according to the user's input
 */
void control_cb(int control)
{
	if(currentLightType == POINT_LIGHT)
		spotLightDirectionRoll->close();
	else
		spotLightDirectionRoll->open();
}

void userInterface()
{
	if(glutGetWindow() != mainWindow);
		glutSetWindow(mainWindow);

	glutPostRedisplay();
}

void display() 
{
	glClearColor(0.0, 0.0 , 0.0 , 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();
}

void reshape(GLint width, GLint height) 
{
	windowWidth = width;
	windowHeight = height;

	int vx, vy, vw, vh;
	GLUI_Master.get_viewport_area( &vx, &vy, &vw, &vh );
	glViewport( vx, vy, vw, vh );

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float) vw / vh, tempNear, tempFar);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) 
{
	/*
	 * Usual glut initialization and display
	 */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	mainWindow = glutCreateWindow("Scene Graph");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	/*
	 * New Glui Code
	 */
	horizontalSubWindow = GLUI_Master.create_glui_subwindow(mainWindow, GLUI_SUBWINDOW_BOTTOM);
	verticalSubWindow = GLUI_Master.create_glui_subwindow(mainWindow, GLUI_SUBWINDOW_RIGHT);

	/**
	 * Object Rollout panel
	 */
	objectRoll = new GLUI_Rollout(verticalSubWindow, "Object", false);
	nameEdit = new GLUI_EditText(objectRoll, "Name: ", objectName);
	new GLUI_Button(objectRoll, "Add Object Node", ADD_OBJECT, control_cb);

	/**
	 * Geometry Rollout panel
	 */
	geometryRoll = new GLUI_Rollout(verticalSubWindow, "Geometry", false);
	fileEdit = new GLUI_EditText(geometryRoll, ".obj File: ", objFileName);
	new GLUI_Button(geometryRoll, "Add Geometry Node", ADD_GEOMETRY, control_cb);

	/**
	 * Transform rollout panel
	 */
	transformRoll = new GLUI_Rollout(verticalSubWindow, "Transform", true);
	transformRadio = new GLUI_RadioGroup(transformRoll, (int*) &currentTransformType, RADIO_TRANSFORM, control_cb);
	new GLUI_RadioButton(transformRadio, "TRANSLATE");
	new GLUI_RadioButton(transformRadio, "SCALE");
	new GLUI_RadioButton(transformRadio, "ROTATE");

	//Spinners for x, y, z and theta arguments
	spinX = new GLUI_Spinner(transformRoll, "X: ", &xArg);
	spinX->set_float_limits(-10.0, 10.0);
	spinX->set_alignment(GLUI_ALIGN_RIGHT);
	spinY = new GLUI_Spinner(transformRoll, "Y: ", &yArg);
	spinY->set_float_limits(-10.0, 10.0);
	spinY->set_alignment(GLUI_ALIGN_RIGHT);
	spinZ = new GLUI_Spinner(transformRoll, "Z: ", &zArg);
	spinZ->set_float_limits(-10.0, 10.0);
	spinZ->set_alignment(GLUI_ALIGN_RIGHT);
	spinTheta = new GLUI_Spinner(transformRoll, "Theta: ", &zArg);
	spinTheta->set_float_limits(-180, 180);
	spinTheta->set_alignment(GLUI_ALIGN_RIGHT);
	new GLUI_Button(transformRoll, "Add Transform Node", ADD_TRANSFORM, control_cb);

	/*
	 * Attribute rollout panel
	 */
	attributeRoll = new GLUI_Rollout(verticalSubWindow, "Attribute", false);
	attributeRadio = new GLUI_RadioGroup(attributeRoll, (int*) &currentMode, RADIO_ATTRIBUTE, control_cb);
	new GLUI_RadioButton(attributeRadio, "Point Mode");
	new GLUI_RadioButton(attributeRadio, "Wireframe Mode");
	new GLUI_RadioButton(attributeRadio, "Solid Mode");
	new GLUI_RadioButton(attributeRadio, "Shaded Mode");
	//separate panel to differentiate radio of modes and showing normals
	GLUI_Panel *normalsPanel = new GLUI_Panel(attributeRoll, "Show Normals");
	vertexNormalCheck = new GLUI_Checkbox(normalsPanel, "Vertex Normals", &showVertexNormal, CHECK_VERTEXNORMAL, control_cb);
	faceNormalCheck = new GLUI_Checkbox(normalsPanel, "Face Normals", &showFaceNormal, CHECK_FACENORMAL, control_cb);
	new GLUI_Button(attributeRoll, "Add Attribute Node", ADD_ATTRIBUTE, control_cb);



	/*
	 * Light rollout panel
	 */
	lightRoll = new GLUI_Rollout(verticalSubWindow, "Light", false);

	//light type
	lightTypeRadio = new GLUI_RadioGroup(lightRoll, (int*) currentLightType, RADIO_LIGHTTYPE, control_cb);
	new GLUI_RadioButton(lightTypeRadio, "Point Light");
	new GLUI_RadioButton(lightTypeRadio, "Directional Light");

	//starting location of light
	spinLightPosXYZ[0] = new GLUI_Spinner(lightRoll, "X Position: ", &lightPosXYZ[0]);
	spinLightPosXYZ[1] = new GLUI_Spinner(lightRoll, "Y Position: ", &lightPosXYZ[1]);
	spinLightPosXYZ[2] = new GLUI_Spinner(lightRoll, "Z Position: ", &lightPosXYZ[2]);

	//directional light target values
	spotLightDirectionRoll = new GLUI_Rollout(lightRoll, "Directional Target",  (int) currentLightType);
	spinLightTargetXYZ[0] = new GLUI_Spinner(spotLightDirectionRoll, "X Target: ", &lightTargetXYZ[0]);
	spinLightTargetXYZ[1] = new GLUI_Spinner(spotLightDirectionRoll, "Y Target: ", &lightTargetXYZ[1]);
	spinLightTargetXYZ[2] = new GLUI_Spinner(spotLightDirectionRoll, "Z Target: ", &lightTargetXYZ[2]);

	//ambience, specular and diffuse values
	lightParameterRoll = new GLUI_Rollout(lightRoll, "Other Parameters", false);
	GLUI_Panel *ambientPanel = new GLUI_Panel(lightParameterRoll, "Ambient");	
	spinAmbientRGBI[0] = new GLUI_Spinner(ambientPanel, "Red: ", &ambientRGBI[0]);
	spinAmbientRGBI[1]  = new GLUI_Spinner(ambientPanel, "Green: ", &ambientRGBI[1]);
	spinAmbientRGBI[2] = new GLUI_Spinner(ambientPanel, "Blue: ", &ambientRGBI[2]);
	spinAmbientRGBI[3]  = new GLUI_Spinner(ambientPanel, "Intensity", &ambientRGBI[3]);

	GLUI_Panel *diffusePanel = new GLUI_Panel(lightParameterRoll, "Diffuse");
	spinDiffuseRed = new GLUI_Spinner(diffusePanel, "Red: ", &diffuseRGBI[0]);

	GLUI_Master.set_glutIdleFunc(userInterface);

	glDepthFunc(GL_LESS);
	glutMainLoop();
}