/*******************************************************************
           Multi-Part Model Construction and Manipulation
********************************************************************/
//heh
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <gl/glut.h>
#include <stdlib.h>
#include <malloc.h> 
#include "Vector3D.h"
#include "QuadMesh.h"
GLubyte fish[] = {
  0x00, 0x60, 0x01, 0x00,
  0x00, 0x90, 0x01, 0x00,
  0x03, 0xf8, 0x02, 0x80,
  0x1c, 0x37, 0xe4, 0x40,
  0x20, 0x40, 0x90, 0x40,
  0xc0, 0x40, 0x78, 0x80,
  0x41, 0x37, 0x84, 0x80,
  0x1c, 0x1a, 0x04, 0x80,
  0x03, 0xe2, 0x02, 0x40,
  0x00, 0x11, 0x01, 0x40,
  0x00, 0x0f, 0x00, 0xe0,
};
struct Boid {
	float x, y, z, weight, radius;
	
}boid1;


//float data(Boid *boid1); 
struct SampleData {
	int N;
	int M;
	int sample_name;
	int speaker;
};

bool data(struct SampleData *samples)
{
	samples->N = 10;
	samples->M = 20;
	// etc.
}

float x = 0.0f;
const int meshSize = 16;    // Default Mesh Size
const int vWidth = 2560;     // Viewport width in pixels
const int vHeight = 1375;    // Viewport height in pixels

static int currentButton;
static unsigned char currentKey;

// Lighting/shading and material properties for drone - upcoming lecture - just copy for now

// Light properties
static GLfloat light_position0[] = { -6.0F, 12.0F, 0.0F, 1.0F };
static GLfloat light_position1[] = { 6.0F, 12.0F, 0.0F, 1.0F };
static GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
static GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
static GLfloat light_ambient[] = { 0.2F, 0.2F, 0.2F, 1.0F };

// Material properties
static GLfloat drone_mat_ambient[] = { 0.4F, 0.2F, 0.0F, 1.0F };
static GLfloat drone_mat_specular[] = { 0.1F, 0.1F, 0.0F, 1.0F };
static GLfloat drone_mat_diffuse[] = { 0.9F, 0.5F, 0.0F, 1.0F };
static GLfloat drone_mat_shininess[] = { 0.0F };

static GLfloat PAVEMENT_ambient[] = { 0.5F, 0.5F, 0.5F, 1.0F };
static GLfloat PAVEMENT_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
static GLfloat PAVEMENT_diffuse[] = { 0.0f, 0.0f, 0.0f, 0.0f };
static GLfloat PAVEMENT_shininess[] = { 0.0F };

static GLfloat PARKINGLINES_ambient[] = { 1.0F, 1.0F, 0.0F, 1.0F };
static GLfloat PARKINGLINES_specular[] = { 0.0F, 0.0F, 0.0F, 1.0F };
static GLfloat PARKINGLINES_diffuse[] = { 0.0F, 0.0F, 0.0F, 0.0F };
static GLfloat PARKINGLINES_shininess[] = { 1.0F };

static GLfloat CARS_ambient[] = { 0.0F, 0.0F, 1.0F, 1.0F };
static GLfloat CARS_specular[] = { 0.1F, 0.1F, 0.1F, 0.1F };
static GLfloat CARS_diffuse[] = { 0.2F, 0.2F, 0.2F, 1.0F };
static GLfloat CARS_shininess[] = { 0.0F };

// A quad mesh representing the ground
static QuadMesh groundMesh;

// Structure defining a bounding box, currently unused
struct BoundingBox {
    Vector3D min;
    Vector3D max;
} BBox_World;

// Prototypes for functions in this module
void initOpenGL(int w, int h);
void display(void);
void reshape(int w, int h);
void mouse(int button, int state, int x, int y);
void mouseMotionHandler(int xMouse, int yMouse);
void keyboardd(unsigned char key, int x, int y);
void functionKeys(int key, int x, int y);

void keyOperations(void);
void keyPressed(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void drawParkingSpot(float x, float y, float z);
void drawParkingLot(float startx, float starty, float startz, int rows, int cols);
void drawCar(float x, float y, float z);

void cow(float x, float y, float z);
void hunter(float x, float y, float z);
void chase(float x, float y, float z);

bool start = true;
float cowX = 0.0f;
double cowY = 1.0f;
float cowZ = -20.0f;
//float boid1.x = -30.0f;
//float boid1.x = 0.0f;
//double boid1.y = 1.0f;
//float boid1.z = 0.0f;

//float boid1.z = -20.0f;
Vector3D location;
Vector3D ScreenToWorld(int x, int y);

void whamdoleSun();
float whamsunX = 20.0f;
float whamsunY = 4.0f;
float whamsunZ = -10.0f;


float v = 0;
float carX = 0.0f;
float carY = 1.0f;
float carZ = 0.0f;
float carAngle = 0.0f;
float acceleration = 0.0f;

float eyex = -10.0f;
double eyey = 15.0f;
float eyez = 15.0f;

float whamX = 0.0f;
double whamY = 0.0f;
float whamZ = 0.0f;
float parkSpeed = 0.05f;
float hAngle = 1.0f;
float hAngleY = 20.0f;

float turnAngle = 0.0f;

float leftPointX = 0.0f;
float leftPointY = 1.0f;
float leftPointZ = 0.0f;

float RighttPointX = 0.0f;
float RighttPointY = 1.0f;
float RighttPointZ = 0.0f;

int randInt = 1;
bool slowing = false;
bool parking = false;


//bool* keyStates = new bool[256]; // Create an array of boolean values of length 256 (0-255)
bool keyStates[256] = { false };
bool modes[12] = { false };
////MODES////
/*
0 - PARKING(P)
1 - REVERSE(R)
2 - NEUTRAL(N)
3 - DRIVE(D)
	3.1 - d1
4 - LOW(L)
*/


void myInit(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);



	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 640.0 / 480.0, 1.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0.0, 0.0, -4.0); // move camera back from default position

}
void spinner(void)
{
	keyOperations();

	display();
}

int main(int argc, char **argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(vWidth, vHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Physics engine");

	boid1.x =  0.0f;
	boid1.y = 1.0f;
	boid1.z = 0.0f;

	struct SampleData samples;
	data(&samples);
	printf("%i\n", samples.N);
	// Initialize GL
    initOpenGL(vWidth, vHeight);

    // Register callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotionHandler);
	glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses
	glutKeyboardUpFunc(keyUp); // Tell GLUT to use the method "keyUp" for key up events    
	glutSpecialFunc(functionKeys);
	glutIdleFunc(spinner);


    // Start event loop, never returns
    glutMainLoop();

    return 0;
}


// Set up OpenGL. For viewport and projection setup see reshape(). */
void initOpenGL(int w, int h)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);


    // Set up and enable lighting
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);   // This light is currently off

    // Other OpenGL setup
    glEnable(GL_DEPTH_TEST);   // Remove hidded surfaces
    glShadeModel(GL_SMOOTH);   // Use smooth shading, makes boundaries between polygons harder to see 
    glClearColor(0.6F, 0.6F, 0.6F, 0.0F);  // Color and depth for glClear
    glClearDepth(1.0f);
    glEnable(GL_NORMALIZE);    // Renormalize normal vectors 
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);   // Nicer perspective

    // Set up ground quad mesh
	Vector3D origin = NewVector3D(-60.0f, 0.0f, 60.0f);
	Vector3D dir1v = NewVector3D(8.0f, 0.0f, 0.0f);
	Vector3D dir2v = NewVector3D(0.0f, 0.0f, -8.0f);
    groundMesh = NewQuadMesh(meshSize);
    InitMeshQM(&groundMesh, meshSize, origin, 16.0, 16.0, dir1v, dir2v);

    Vector3D ambient = NewVector3D(0.0f, 0.05f, 0.0f);
    Vector3D diffuse = NewVector3D(0.4f, 0.8f, 0.4f);
    Vector3D specular = NewVector3D(0.04f, 0.04f, 0.04f);
    SetMaterialQM(&groundMesh, ambient, diffuse, specular, 0.2);





	//gluLookAt(0, 20, 0, 0, 0, 0, 0, 1, 0);

	//glDisable(GL_TEXTURE_2D);
    // Set up the bounding box of the scene
    // Currently unused. You could set up bounding boxes for your objects eventually.
    Set(&BBox_World.min, -30.0f, 3.0, -30.0f);
    Set(&BBox_World.max, 30.0f, 10.0, 30.0f);
}

GLfloat randomFloat() {
  return (GLfloat)rand() / RAND_MAX;
}
// Callback, called whenever GLUT determines that the window should be redisplayed
// or glutPostRedisplay() has been called.
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	keyOperations();

	//boid1.x = 10;

	glMaterialfv(GL_FRONT, GL_AMBIENT, drone_mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, drone_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, drone_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, drone_mat_shininess);

	glLoadIdentity();
	gluLookAt(0, 25, 35, 0, 0, 0, 0, 1, 0);
	//gluLookAt(10, 15, 15, 0, 0, 0, 0, 1, 0);

	cow(cowX, cowY, cowZ);
	//glPushMatrix();

	//glRotatef(hAngle, 0, 1, 0);

	hunter(boid1.x, boid1.y, boid1.z);
	//glPopMatrix();

	//chase(cowX, cowY, cowZ);
	glPushMatrix();

	 glTranslatef(0, 8, 0);
	 glScalef(60, 16, 60);
	 glutWireCube(1);


	 glPopMatrix();


	 ///
	// for (int i = 0; i < 20; i++) {
	//	 glColor3f(randomFloat(), randomFloat(), randomFloat());
	//	 glRasterPos3f(boid1.x, 2, boid1.z);
	//	 glBitmap(27, 11, 0, 0, 0, 0, fish);
	 //}
	 ///
	
	 //
	 glPushMatrix();
	 glTranslatef(boid1.x, boid1.y, boid1.z);
	 glRotatef(hAngle, 0, 1, 0);
	 //glRotatef(-hAngleY, 1, 0, 0);

	 glScalef(1, 1, 1);
	 //glutWireCube(1);

	 glBegin(GL_LINES);
	 glVertex3f(0, 0, -5);
	 glVertex3f(0, 0, -10);
	 glEnd();

	 glBegin(GL_LINES);
	 glVertex3f(0, 0, -5);
	 glVertex3f(2, 0, -10);
	 glEnd();

	 glBegin(GL_LINES);
	 glVertex3f(0, 0, -5);
	 glVertex3f(-2, 0, -10);
	 glEnd();

	 glPopMatrix();
	
	 //
    DrawMeshQM(&groundMesh, meshSize);

    glutSwapBuffers();   // Double buffering, swap buffers
}

void cow(float x, float y, float z) {

	 ////leftPointX = boid1.x - 2;
	 //leftPointY = boid1.y;
	 //leftPointZ = boid1.z;

	 //RighttPointX = boid1.x + 2;
	 //RighttPointY = boid1.y;
	 //RighttPointZ = boid1.z;

	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(1, 1, 1);
	glutSolidCube(5);

	//glutSolidCone(2, 5, 10, 10);


	glPopMatrix();

	
}

void hunter(float x, float y, float z) {
	turnAngle = 60.0f;
	while (turnAngle > 0.0f)
	{
		if (boid1.x > BBox_World.max.x)
		{
			hAngle -= 0.0005f;
			//glRotatef(hAngle, 0, 1, 0);

		}
		if (boid1.x < BBox_World.min.x)
		{
			hAngle -= 0.0005f;
			//glRotatef(hAngle, 0, 1, 0);

		}
		if (boid1.z > BBox_World.max.z)
		{
			hAngle -= 0.0005f;
		}
		if (boid1.z < BBox_World.min.z)
		{
			hAngle -= 0.0005f;
		}
		if (boid1.y > BBox_World.max.y)
		{
			hAngleY += 0.00007f;

		}
		if (boid1.y < BBox_World.min.y)
		{
			hAngleY -= 0.00007f;
			//boid1.y -= cos(hAngleY) * 0.0005;

		}
		if ((boid1.x > cowX- 7.5 && boid1.x < cowX + 7.5) && (boid1.z > cowZ - 7.5 && boid1.z < cowZ + 7.5) && (boid1.y > cowY - 5 && boid1.y < cowY + 5))
		{
			hAngle -= 0.0008f;

		}
		turnAngle -= 0.5f;

	}
	turnAngle = 60.0f;

	
	//boid1.y -= hAngleY * 0.00003;

	boid1.x -= sin(3.14 * hAngle / 180) * 0.005f;
	boid1.z -= cos(3.14 * hAngle / 180) * 0.005f;

	glPushMatrix();

	
	//gluLookAt(cowX, cowY, cowZ, boid1.x, boid1.y, boid1.z, 0, 1, 0);

	glTranslatef(x, y, z);  
	glRotatef(180, 0, 1, 0);
	//glRotatef(30, 1, 0, 0);


	//glRotatef(atan2(cowX, cowZ) * 180 / 3.14, 0, 1, 0);
	glRotatef(hAngle, 0, 1, 0);
	//glRotatef(hAngleY, 1, 0, 0);
	//glRotatef(hAngle, 1, 0, 0);


	//glRotatef(hAngleY, 0, 1, 0);

	glScalef(1, 1, 1);

	//glutWireCube(1);


	glutWireCone(2, 5, 10, 10);

	
	
	//glLoadIdentity();
	glPopMatrix();
	//boid1.x -= 0.005;
	//boid1.z -= 0.005;
	glPushMatrix();
	glTranslatef(x + 3, y, z);

	//glRotatef(180, 0, 1, 0);
	glRotatef(hAngle, 0, 1, 0);

	//glTranslatef(-x, -y, -z);

	//glScalef(2, 2, 4);
	glutSolidCube(1);
	//glTranslatef(-(x + 3), -y, -z);

	glPopMatrix();


	

}
void chase(float X, float Y, float Z) {
	Vector3D chaserToTarget = NewVector3D(cowX, cowY, cowZ);
	//Set(result, v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
	chaserToTarget.x = boid1.x - cowX;
	chaserToTarget.y = boid1.y - cowY;
	chaserToTarget.z = boid1.z - cowZ;

	float d = sqrt(pow(boid1.x - cowX, 2) +
		pow(boid1.y - cowY, 2) +
		pow(boid1.z - cowZ, 2) * 1.0);

	chaserToTarget.x /= d;
	chaserToTarget.y /= d;
	chaserToTarget.z /= d;

	chaserToTarget.x *= 0.1;
	chaserToTarget.y *= 0.1;
	chaserToTarget.z *= 0.1;
	if (boid1.x > BBox_World.max.x )
	{
		boid1.x = BBox_World.max.x;
	}
	if (boid1.x < BBox_World.min.x)
	{
		boid1.x = BBox_World.min.x;
	}
	if (boid1.z > BBox_World.max.z)
	{
		boid1.z = BBox_World.max.z;
	}
	if (boid1.z < BBox_World.min.z)
	{
		boid1.z = BBox_World.min.z;
	}

	if (d > 15)
	{
		boid1.x -=  chaserToTarget.x * 0.1;
		boid1.y -= chaserToTarget.y * 0.1;
		boid1.z -= chaserToTarget.z * 0.1;
	}
	else
	{
		boid1.x -= chaserToTarget.x * 0.05;
		boid1.y -= chaserToTarget.y * 0.05;
		boid1.z -= chaserToTarget.z * 0.05;
	}
	
	printf("%f\n", chaserToTarget.x);

	printf("%f\n", chaserToTarget.z);


}



// Callback, called at initialization and whenever user resizes the window.
void reshape(int w, int h)
{
    // Set up viewport, projection, then change to modelview matrix mode - 
    // display function will then set up camera and do modeling transforms.
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80.0, (GLdouble)w / h, 0.3, 80.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set up the camera at position (0, 6, 22) looking at the origin, up along positive y axis
}

// Callback, handles input from the keyboard, non-arrow keys
void keyboardd(unsigned char key, int x, int y)
{
 
    glutPostRedisplay();   // Trigger a window redisplay
}

void keyOperations(void) {
	
	if (keyStates['q']) {
		exit(0);
	}
	if (keyStates['i']) { //up
		cowZ -= 0.03;
	}
	if (keyStates['k']) { //down
		cowZ += 0.03;
	}
	if (keyStates['j']) { //left
		cowX -= 0.03;
	}
	if (keyStates['l']) { //right
		cowX += 0.03;
	}
	


	
}

void keyPressed(unsigned char key, int x, int y) {
	keyStates[key] = true; // Set the state of the current key to pressed
}

void keyUp(unsigned char key, int x, int y) {
	keyStates[key] = false; // Set the state of the current key to not pressed
}

// Callback, handles input from the keyboard, function and arrow keys
void functionKeys(int key, int x, int y)
{
    // Help key
    if (key == GLUT_KEY_UP)
    {
		cowX += 1.0;
    }
	if (key == GLUT_KEY_DOWN)
	{
		cowX -= 1.0;
	}   
	if (key == GLUT_KEY_RIGHT)
	{
		cowZ += 1.0;

	}  
	if (key == GLUT_KEY_LEFT)
	{
		cowZ -= 1.0;

	}
    // Do transformations with arrow keys
    //else if (...)   // GLUT_KEY_DOWN, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_LEFT
    //{
    //}

    glutPostRedisplay();   // Trigger a window redisplay
}


// Mouse button callback - use only if you want to 
void mouse(int button, int state, int x, int y)
{
    currentButton = button;

    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
        {
			location = ScreenToWorld(x, y);
			cowX = location.x;
			cowZ = location.z;


			cow(cowX, cowY, cowZ);
        }
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
        {
            ;
        }
        break;
    default:
        break;
    }

    glutPostRedisplay();   // Trigger a window redisplay
}

void mode(int selector) {

}
// Mouse motion callback - use only if you want to 
void mouseMotionHandler(int xMouse, int yMouse)
{
	 //location = ScreenToWorld(xMouse, yMouse);

    if (currentButton == GLUT_LEFT_BUTTON)
    {
		location = ScreenToWorld(xMouse, yMouse);
		cowX = location.x;
		cowZ = location.z;
		cow(cowX, cowY, cowZ);
	}

    glutPostRedisplay();   // Trigger a window redisplay
}


Vector3D ScreenToWorld(int x, int y)
{

	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	winX = x;
	winY = (float)viewport[3] - y;
	glReadPixels(x, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	return NewVector3D(posX, posY, posZ);
}



