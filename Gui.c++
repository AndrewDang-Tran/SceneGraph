#include <GL/glut.h> //for linux
#include <sstream> //ostringstream
#include "./glui-2.36/src/include/GL/glui.h"
#include "SceneGraph.h"

#define ADD_OBJECT 100
#define ADD_GEOMETRY 101
#define ADD_TRANSFORM 102
#define ADD_ATTRIBUTE 103
#define ADD_LIGHT 104
#define ADD_CAMERA 105
#define GET_NODE 106
#define EDIT_NODE 107
#define DELETE_NODE 108

#define RADIO_TRANSFORM 201
#define RADIO_ATTRIBUTE 202
#define RADIO_LIGHTTYPE 203

#define CHECK_VERTEXNORMAL 301
#define CHECK_FACENORMAL 302
#define CHECK_FACEVERTEX 303

#define TRANSLATE_LIMIT 1000.0

//Functions implemented at the bottom of the file to create the GUI with GLUI
static void createObjectPanel();
static void createGeometryPanel();
static void createTransformPanel();
static void createAttributePanel();
static void createLightPanel();
static void createCameraPanel();
static void createEditingPanel();
static void createDeletePanel();

int windowWidth = 1024;
int windowHeight = 768;

bool drawFaceNormal = false;
bool drawVertexNormal = false;
bool useFaceNormal = false;

GLfloat tempNear = 1;
GLfloat tempFar = 100;

SceneGraph sceneGraph;

/*
 * GLUI variables
 */
//window variables
int mainWindow;
GLUI* verticalSubWindow;

//GLUI minimizable panels / Rollouts
GLUI_Rollout *objectRoll, *geometryRoll, *transformRoll, *attributeRoll, *lightRoll, *cameraRoll, *editRoll, *deleteRoll;

/**
 * 0 - object
 * 1 - geometry
 * 2 - transform
 * 3 - attribute
 * 4 - light
 */


//object rollout variables
GLUI_EditText* nameEdit;
string objectName = "Name me";

//geometry rollout variables
GLUI_EditText* fileEdit;
string objFileName = "sphere.obj";
GLUI_Checkbox *vertexNormalCheck, *faceNormalCheck, *useFaceNormalCheck; 
int showVertexNormal, showFaceNormal, useFaceNormalInt;

//transform rollout variables
GLUI_RadioGroup* transformRadio;
TransformType currentTransformType = TRANSLATE;
GLUI_Spinner* spinXYZT[4];
GLfloat xyzTheta[4];

//Attribute rollout variables
GLUI_RadioGroup* attributeRadio;
Mode currentMode = SHADED_MODE;

//Light rollout variables
GLUI_RadioGroup* lightTypeRadio;
LightType currentLightType = POINT_LIGHT;
GLUI_Spinner* spinLightPosXYZ[3];
GLfloat lightPosXYZ[3];

//rollout within Light rollout show spotlight direction if needed
GLUI_Rollout* spotLightDirectionRoll;
GLUI_Spinner* spinLightTargetXYZ[3];
GLfloat lightTargetXYZ[3];

//GUI to change ambience, diffuse or specular lighting
GLUI_Rollout* lightParameterRoll;
GLUI_Spinner* spinAmbientRGBI[4];
GLfloat ambientRGBI[4] = {0.0, 0.0, 0.0, 1.0};

GLUI_Spinner *spinDiffuseRGBI[4];
GLfloat diffuseRGBI[4] = {1.0, 1.0, 1.0, 1.0};

GLUI_Spinner *spinSpecularRGBI[4];
GLfloat specularRGBI[4] = {1.0, 1.0, 1.0, 1.0};

//Camera rollout variables
/*GLUI_Spinner* spinCameraXYZ[3];
GLfloat cameraPositionXYZ[3];

GLUI_Spinner* spinSubjectXYZ[3];
GLfloat cameraSubjectXYZ[3];*/

//Editing rollout variables
GLUI_Spinner* getNodeID;
int findID = -1;
GLUI_Button* getNode;
GLUI_StaticText* editType;
GLUI_StaticText* editNodeID;
int currentEditNodeID = -1;
NodeType currentEditNodeType;

//Deleting rollout variables
GLUI_Spinner* deleteNodeID;
int deleteID = -1;
GLUI_Button* deleteButton;


//Important spinner for adding nodes
//when add node is clicked it will add it to this node ID
GLUI_Spinner* addToParent;
int addToParentID;

GLUI_Spinner* spinNear;
GLUI_Spinner* spinFar;
GLfloat near =  .01;
GLfloat far = 10.0;


//INTERACTIVE CONTROL VARIABLES
GLfloat rotateX = 0.0;
GLfloat rotateY = 0.0;
GLfloat panX = 0.0;
GLfloat panY = 0.0;
GLfloat zoom = 0.0;
GLfloat theta = 0.0;
GLfloat phi = 0.0;

GLfloat initialMouseX = 250;
GLfloat initialMouseY = 250;

bool leftDown = false;
bool middleDown = false;
bool rightDown = false;

/**
 * Simply draws the xyz axis for reference
 */
void drawAxis(GLfloat scale)
{
	glDisable(GL_LIGHTING);

	glPushMatrix();
	glScalef(scale, scale, scale);
	glBegin(GL_LINES);
		glColor3f( 1.0, 0.0, 0.0 );
	  	glVertex3f( .8f, 0.05f, 0.0 );  glVertex3f( 1.0, 0.25f, 0.0 ); /* Letter X */
		glVertex3f( 0.8f, .25f, 0.0 );  glVertex3f( 1.0, 0.05f, 0.0 );
		glVertex3f( 0.0, 0.0, 0.0 );  glVertex3f( 1.0, 0.0, 0.0 ); /* X axis      */

		glColor3f( 0.0, 1.0, 0.0 );
		glVertex3f( 0.0, 0.0, 0.0 );  glVertex3f( 0.0, 1.0, 0.0 ); /* Y axis      */

		glColor3f( 0.0, 0.0, 1.0 );
		glVertex3f( 0.0, 0.0, 0.0 );  glVertex3f( 0.0, 0.0, 1.0 ); /* Z axis    */
  	glEnd();

  	glPopMatrix();

  	glEnable(GL_LIGHTING);
}

/**
 * Changes the GUI to represent which type of Node you want to edit.
 */
void changeEditInfo()
{

	objectRoll->close();
	geometryRoll->close();
	transformRoll->close();
	attributeRoll->close();
	lightRoll->close();
	
	ostringstream ss;
	ss << "ID: " << currentEditNodeID;

	editNodeID->set_text(ss.str().c_str());
	switch(currentEditNodeType)
	{
		case OBJECT:
			objectRoll->open();
			editType->set_text("Type: Object");
			break;
		case GEOM:
			geometryRoll->open();
			editType->set_text("Type: Geometry");
			#ifdef DEBUG
			cout << "Entered changeEditInfo - GEOM" << endl;
			#endif
			break;
		case TRANSFORM:
			#ifdef DEBUG
			cout << "entered changeEditInfo - TRANSFORM" << endl;
			#endif
			transformRoll->open();
			editType->set_text("Type: Transform");
			break;
		case ATTRIBUTE:
			attributeRoll->open();
			editType->set_text("Type: Attribute");
			break;
		case LIGHT:
			lightRoll->open();
			editType->set_text("Type: Light");
			break;
	}
}

/**
 * Edits the current Edit Node with new parameters
 */
void editNode()
{
	switch(currentEditNodeType)
	{
		case OBJECT:
			sceneGraph.editObjectNode(currentEditNodeID, objectName);
			break;
		case GEOM:
			sceneGraph.editGeomNode(currentEditNodeID, objFileName, drawFaceNormal, drawVertexNormal, useFaceNormal);
			break;
		case TRANSFORM:
			sceneGraph.editTransformNode(currentEditNodeID, currentTransformType, xyzTheta);
			break;
		case ATTRIBUTE:
			sceneGraph.editAttributeNode(currentEditNodeID, currentMode);
			break;
		case LIGHT:
			sceneGraph.editLightNode(currentEditNodeID, currentLightType, lightPosXYZ, lightTargetXYZ, ambientRGBI, diffuseRGBI, specularRGBI);
			break;
	}
}

/*
 * Control callback that will make changes according to the user's input
 */
void control_cb(int control)
{
	bool check = true;
	switch(control)
	{
		case CHECK_VERTEXNORMAL:
			#ifdef DEBUG
			cout << "inside check vertex normal" << endl;
			cout << "showVertexNormal: " << showVertexNormal << endl;
			#endif
			drawVertexNormal = !drawVertexNormal;
			break;
		case CHECK_FACENORMAL:
			#ifdef DEBUG
			cout << "inside check face normal" << endl;
			cout << "showFaceNormal: " << showFaceNormal << endl;
			#endif
			drawFaceNormal = !drawFaceNormal;
			break;
		case CHECK_FACEVERTEX:
			useFaceNormal = !useFaceNormal;
			break;
		case RADIO_TRANSFORM:
			#ifdef DEBUG
			cout << "Transform Type # " << currentTransformType << endl;
			#endif
			break;
		case RADIO_ATTRIBUTE:
			#ifdef DEBUG
			cout << "Current Attribute # " << currentMode << endl;
			#endif
			break;
		case RADIO_LIGHTTYPE:
			#ifdef DEBUG
			cout << "Current Light Type # " << currentLightType << endl;
			#endif
			break;
		case ADD_OBJECT:
			check = sceneGraph.addObjectNode(addToParentID, objectName);
			break;
		case ADD_GEOMETRY:
			check = sceneGraph.addGeomNode(addToParentID, objFileName, drawFaceNormal, drawVertexNormal, useFaceNormal);
			break;
		case ADD_TRANSFORM:
			check = sceneGraph.addTransformNode(addToParentID, currentTransformType, xyzTheta);
			break;
		case ADD_ATTRIBUTE:
			check = sceneGraph.addAttributeNode(addToParentID, currentMode);
			break;
		case ADD_LIGHT:
			check = sceneGraph.addLightNode(addToParentID, currentLightType, lightPosXYZ, lightTargetXYZ, ambientRGBI, diffuseRGBI, specularRGBI);
			break;
		case GET_NODE:
			currentEditNodeType = sceneGraph.getNodeType(findID);
			currentEditNodeID = findID;
			changeEditInfo();
			break;
		case EDIT_NODE:
			editNode();
			break;
		case DELETE_NODE:
			sceneGraph.deleteNode(deleteID);
			break;
	}
	#ifdef DEBUG
	if(!check)
		cout << "something went wrong" << endl << "control = " << control << endl;
	#endif
	

}

/**
 * Callback for when the mouse is clicked within the viewport
 */ 
void mouseButton(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON) 
	{
		leftDown = (state == GLUT_DOWN) ? true : false;
		initialMouseX = x;
		initialMouseY = y;
	}
	if(button == GLUT_MIDDLE_BUTTON)
	{
		middleDown = (state == GLUT_DOWN) ? true : false;
		initialMouseX = x;
		initialMouseY = y;
	}
	if(button == GLUT_RIGHT_BUTTON)
	{
		rightDown = (state == GLUT_DOWN) ? true : false;
		initialMouseX = x;
		initialMouseY = y;
	}
}

/**
 * Callback for when the mouse is moved within the viewport
 */
void mouseMotion(int x, int y)
{
	if(leftDown)
	{
		rotateX = (x - initialMouseX) / 50;
		rotateY = (y - initialMouseY) / 50;
		theta -= rotateX; 
		phi -= rotateY;

		if(phi < -175)
			phi = -175;
		else if(phi > -1)
			phi = -1;

		sceneGraph.cameraRotate(theta, phi);
	}
	else if(middleDown)
	{
		zoom = (y - initialMouseY) / 75;
		sceneGraph.cameraZoom(zoom);
	}
	else if(rightDown)
	{
		panX = (x - initialMouseX) / 500;
		panY = (y - initialMouseY) / 500;
		panY = -panY;
		sceneGraph.cameraPan(panX, panY);
	}
	glutPostRedisplay();
}

/**
 * sets up the main window
 */
void userInterface()
{
	if(glutGetWindow() != mainWindow)
		glutSetWindow(mainWindow);

	glutPostRedisplay();
}

/**
 * Return to the default settings before traversing through the scene graph again. This way the attributes of the last nodes don't carry on to the first.
 * I may move this to a default method within the scene graph
 */
static void defaultSettings()
{
	glLoadIdentity();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_LIGHTING);
}

/**
 * Display callback which starts the traversal through the scene graph
 */
void display() 
{
	glClearColor(0.0, 0.0 , 0.0 , 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_NORMALIZE);
	
	defaultSettings();
	drawAxis(2.0);
	sceneGraph.traversal();
	glutSwapBuffers();
}

/**
 * Reshape callback which is only called once at the beginning in this program.
 */
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

	glutPostRedisplay();
}

/**
 * Initializes many of the openGL values. Determines which functions are used as callbacks.
 * Creates the GLUI interface, and starts the main loop.
 */
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
	//glShadeModel(GL_SMOOTH);

	//glut Callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);

	/*
	 * New Glui Code
	 */
	verticalSubWindow = GLUI_Master.create_glui_subwindow(mainWindow, GLUI_SUBWINDOW_RIGHT);

	addToParent = new GLUI_Spinner(verticalSubWindow, "Parent ID", &addToParentID);
	createObjectPanel();
	createGeometryPanel();
	createTransformPanel();
	createAttributePanel();
	createLightPanel();
	//createCameraPanel();
	createEditingPanel();
	createDeletePanel();
	GLUI_Master.set_glutIdleFunc(userInterface);

	glDepthFunc(GL_LESS);
	glutMainLoop();
}

static void createObjectPanel()
{
	objectRoll = new GLUI_Rollout(verticalSubWindow, "Object", false);
	nameEdit = new GLUI_EditText(objectRoll, "Name: ", objectName);
	new GLUI_Button(objectRoll, "Add Object Node", ADD_OBJECT, control_cb);
}

static void createGeometryPanel()
{
	geometryRoll = new GLUI_Rollout(verticalSubWindow, "Geometry", false);
	fileEdit = new GLUI_EditText(geometryRoll, ".obj File: ", objFileName);
	useFaceNormalCheck = new GLUI_Checkbox(geometryRoll, "Use Face Normals", &useFaceNormalInt, CHECK_FACEVERTEX, control_cb);
	//separate panel to differentiate radio of modes and showing normals
	GLUI_Panel *normalsPanel = new GLUI_Panel(geometryRoll, "Show Normal Lines");
	vertexNormalCheck = new GLUI_Checkbox(normalsPanel, "Vertex", &showVertexNormal, CHECK_VERTEXNORMAL, control_cb);
	faceNormalCheck = new GLUI_Checkbox(normalsPanel, "Face", &showFaceNormal, CHECK_FACENORMAL, control_cb);
	new GLUI_Button(geometryRoll, "Add Geometry Node", ADD_GEOMETRY, control_cb);
}

static void createTransformPanel()
{
	transformRoll = new GLUI_Rollout(verticalSubWindow, "Transform", true);
	transformRadio = new GLUI_RadioGroup(transformRoll, (int*) &currentTransformType, RADIO_TRANSFORM, control_cb);
	string transformTypeStrings[3] = {"Translate", "Scale", "Rotate"};
	for(int i = 0; i < 3; ++i)
		new GLUI_RadioButton(transformRadio, transformTypeStrings[i].c_str());

	//Spinners for x, y, z and theta arguments
	string xyztString[4] = {"X: ", "Y: ", "Z: ", "Theta: "};
	for(int i = 0; i < 4; ++i)
	{
		spinXYZT[i] = new GLUI_Spinner(transformRoll, xyztString[i].c_str(), &xyzTheta[i]);
		spinXYZT[i]->set_float_limits(-TRANSLATE_LIMIT, TRANSLATE_LIMIT);
		spinXYZT[i]->set_alignment(GLUI_ALIGN_RIGHT);
	}
	new GLUI_Button(transformRoll, "Add Transform Node", ADD_TRANSFORM, control_cb);
}

static void createAttributePanel()
{
	attributeRoll = new GLUI_Rollout(verticalSubWindow, "Attribute", false);
	attributeRadio = new GLUI_RadioGroup(attributeRoll, (int*) &currentMode, RADIO_ATTRIBUTE, control_cb);
	string modeStrings[4] = {"Point Mode", "Wireframe Mode", "Solid Mode", "Shaded Mode"};
	for(int i = 0; i < 4; ++i)
		new GLUI_RadioButton(attributeRadio, modeStrings[i].c_str());
	
	new GLUI_Button(attributeRoll, "Add Attribute Node", ADD_ATTRIBUTE, control_cb);
}

static void createLightPanel()
{
	lightRoll = new GLUI_Rollout(verticalSubWindow, "Light", false);

	//light type
	lightTypeRadio = new GLUI_RadioGroup(lightRoll, (int*) &currentLightType, RADIO_LIGHTTYPE, control_cb);
	new GLUI_RadioButton(lightTypeRadio, "Point Light");
	new GLUI_RadioButton(lightTypeRadio, "Directional Light");

	string xyztString[4] = {"X: ", "Y: ", "Z: ", "Theta: "};
	GLUI_Panel* lightPositionPanel = new GLUI_Panel(lightRoll, "Light Position");
	//starting location of light
	for(int i = 0; i < 3; ++i)
		spinLightPosXYZ[i] = new GLUI_Spinner(lightPositionPanel, xyztString[i].c_str(), &lightPosXYZ[i]);


	//directional light target values
	spotLightDirectionRoll = new GLUI_Rollout(lightRoll, "Directional Target",  (int) currentLightType);
	for(int i = 0; i < 3; ++i)
		spinLightTargetXYZ[i] = new GLUI_Spinner(spotLightDirectionRoll, xyztString[i].c_str(), &lightTargetXYZ[i]);

	//ambience, specular and diffuse values
	lightParameterRoll = new GLUI_Rollout(lightRoll, "Other Parameters", false);
	string rgbi[4] = {"Red: ", "Green: ", "Blue: ", "Intensity: "};
	GLUI_Panel* ambientPanel = new GLUI_Panel(lightParameterRoll, "Ambient");
	GLUI_Panel* diffusePanel = new GLUI_Panel(lightParameterRoll, "Diffuse");
	GLUI_Panel* specularPanel = new GLUI_Panel(lightParameterRoll, "Specular");
	for(int i = 0; i < 4; ++i)
	{
		const char* cString = rgbi[i].c_str();
		spinDiffuseRGBI[i] = new GLUI_Spinner(diffusePanel, cString, &diffuseRGBI[i]);
		spinAmbientRGBI[i] = new GLUI_Spinner(ambientPanel, cString, &ambientRGBI[i]);
		spinSpecularRGBI[i] = new GLUI_Spinner(specularPanel, cString, &specularRGBI[i]);
	}
	new GLUI_Button(lightRoll, "Add Light Node", ADD_LIGHT, control_cb);
}

/*static void createCameraPanel()
{
	string xyztString[4] = {"X: ", "Y: ", "Z: ", "Theta: "};
	cameraRoll = new GLUI_Rollout(verticalSubWindow, "Camera", false);
	GLUI_Panel* cameraPositionPanel = new GLUI_Panel(cameraRoll, "Camera Position");
	GLUI_Panel* subjectPositionPanel = new GLUI_Panel(cameraRoll, "Subject Position");
	for(int i = 0; i < 3; ++i)
	{
		const char* cString = xyztString[i].c_str();
		spinCameraXYZ[i] = new GLUI_Spinner(cameraPositionPanel, cString, &cameraPositionXYZ[i]);
		spinSubjectXYZ[i] = new GLUI_Spinner(subjectPositionPanel, cString, &cameraSubjectXYZ[i]);
	}
	spinNear = new GLUI_Spinner(cameraRoll, "Near", &near);
	spinFar = new GLUI_Spinner(cameraRoll, "Far", &far);
	new GLUI_Button(cameraRoll, "Add Camera Node", ADD_CAMERA, control_cb);
}*/

static void createEditingPanel()
{
	editRoll = new GLUI_Rollout(verticalSubWindow, "Edit Node", false);
	getNodeID = new GLUI_Spinner(editRoll, "Edit ID", &findID);
	getNode = new GLUI_Button(editRoll, "Get Node", GET_NODE, control_cb);
	GLUI_Panel* nodeEditingPanel = new GLUI_Panel(editRoll, "Current Node");
	editNodeID = new GLUI_StaticText(nodeEditingPanel, "ID: ");
	editType = new GLUI_StaticText(nodeEditingPanel, "Type: ");
	new GLUI_Button(editRoll, "Edit Node", EDIT_NODE, control_cb);
}

static void createDeletePanel()
{
	deleteRoll = new GLUI_Rollout(verticalSubWindow, "Delete Node", false);
	deleteNodeID = new GLUI_Spinner(deleteRoll, "Delete ID", &deleteID);
	deleteButton = new GLUI_Button(deleteRoll, "Delete", DELETE_NODE, control_cb);
}
