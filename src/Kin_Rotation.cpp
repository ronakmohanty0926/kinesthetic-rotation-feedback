// ABCSketch1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <io.h>
#include <fcntl.h>
#include <cstdio>
#include <fstream>
#include <crtdbg.h>


#include "SketchManager.h"
#include "HapticsEventManager.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "opencv2\opencv.hpp"

#define GL_WIN_SIZE_X 1280
#define GL_WIN_SIZE_Y 960

using namespace std;
using namespace midl;

// Event Manager
static HapticsEventManagerGeneric *hapticsEvent = 0;
static ABCSketchManager *skEvent = 0;
static Mesh *meshEvent = 0;;

// Video and snapshots
int snapID = 0;
int isVideo, isHaptics;
bool isRecord = false;
cv::VideoWriter capture;

int randNum,prevrandNum;
int pcount, prevpcount;
vector<int>_rand;
string a, b, c;

float eye[] = { 0.0,0.0,5.0 };
float center[] = { 0.0,0.0,0.0 };
float head[] = { 0.0, 1.0, 0.0 };

//---- Open GL View
PerspectiveView view;

//---- Open GL Lighting
Light light1, light2;
GLfloat lightPos[] = { 0.0, 0.0, 10.0, 1.0 };
GLfloat diffuse1[] = { 0.54, 0.0, 0.0, 1.0 };
GLfloat diffuse2[] = { 0.0, 0.8, 0.0, 0.5 };
GLfloat ambient[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };

float scale[] = { 1.0 ,1.0, 1.0 };


void CleanupAndExit()
{
	if (hapticsEvent)
	{
		hapticsEvent->Cleanup();
		HapticsEventManagerGeneric::Delete(hapticsEvent);
	}
	//if (skEvent)delete skEvent;
	
	if (isVideo > 0)capture.release();
	exit(0);
}

float follower[3];
GLdouble trans[16];
Transformation T;
//bool rotation = skEvent->RotationOn();
void glutDisplay(void)
{
	hapticsEvent->UpdateState();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	view.Bind();


	
	/*if (skEvent->shapeIdentity == 1 || skEvent->shapeIdentity == 2 || skEvent->shapeIdentity == 3 || skEvent->shapeIdentity == 4 || skEvent->shapeIdentity == 5 || skEvent->shapeIdentity == 6 || skEvent->shapeIdentity == 7 )
	{*/
	if (skEvent->shapeIdentity == 1 || skEvent->shapeIdentity == 2 || skEvent->shapeIdentity == 3 || skEvent->shapeIdentity == 4)
	{
		light2.Bind();
		skEvent->DrawBaseMesh();
		light2.Unbind();

		light1.Bind();
		skEvent->DrawTargetMesh();
		light1.Unbind();
	}
	
	glPolygonMode(GL_FRONT, GL_FILL);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(2.0f, 2.0f);		
	
	skEvent->Render();

	glDisable(GL_POLYGON_OFFSET_LINE);

	if (isVideo > 0)
	{
		cv::Mat img(GL_WIN_SIZE_Y, GL_WIN_SIZE_X, CV_8UC3);
		glPixelStorei(GL_PACK_ALIGNMENT, (img.step & 3) ? 1 : 4);
		glPixelStorei(GL_PACK_ROW_LENGTH, img.step / img.elemSize());
		//cerr << img.cols << " " << img.rows << endl;
		glReadPixels(0, 0, img.cols, img.rows, GL_BGR_EXT, GL_UNSIGNED_BYTE, img.data);
		cv::Mat flipped(img);
		cv::flip(img, flipped, 0);
		capture.write(img);
	}

	view.Unbind();

	glutSwapBuffers();
}

void glutReshape(int w, int h)
{
	// Just set the viewport and get out
	// All view processing in displayCallback
	// glViewport (0, 0, (GLsizei)w, (GLsizei)h);

	// glMatrixMode (GL_PROJECTION);
	// glLoadIdentity();
	// gluPerspective (prj_fov, (GLfloat)w / (GLfloat)h, prj_near, prj_far);
	// glMatrixMode (GL_MODELVIEW);
	view.Reshape(w, h);
}

void glutIdle(void)
{
	// We just set the backgournd to White!
	// and do nothing.
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutPostRedisplay();
}

void mouseClickCallback(int button, int state, int x, int y)
{
	// Example usage:
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			// When the left button is pressed
			// down, do something
		}
		else if (state == GLUT_UP)
		{
			// When the left button is lifted
			// up, do something else
		}
	}
}

void mouseActiveMotionCallback(int x, int y)
{
	// You can define anythging here
	// Right now, we do not want to 
	// do anything when the mouse moves!
	// So, let us leave this function empty!
}

void mousePassiveMotionCallback(int x, int y)
{
}

void glutKeyboard(unsigned char key, int x, int y)
{
	char filename1[1000], filename2[1000];
	string s1, s2;

	switch (key)
	{
	case 27: // 27 is ASCII code for the "Esc" key
		CleanupAndExit();
		break;
	case 'a':	
		
		if (!_rand.empty())
		{
			skEvent->ComputeError();
			skEvent->SaveLog();
			//skEvent->SaveMesh();

			prevrandNum = _rand[_rand.size() - 1];
			skEvent->hapticstylusmov.clear();
			skEvent->stylusmov.clear();

			srand(time(0));
			randNum = (rand() % 4) + 1;
			while (randNum == prevrandNum) { randNum = (rand() % 4) + 1; }
			_rand.push_back(randNum);
			skEvent->shapeCounts(randNum);
			skEvent->shapeIdentity = randNum;
			skEvent->generateRand();

			if (skEvent->shapeIdentity == 1)
			{
				s1 = "PuzzlePipe.ply";
				s2 = "PuzzleTarget.ply";
				strcpy(filename1, s1.c_str());
				strcpy(filename2, s2.c_str());
				skEvent->ReadTargetMesh(filename2);
				skEvent->ReadBaseMesh(filename1);
			}

			else if (skEvent->shapeIdentity == 2)
			{
				s1 = "TrapPipe.ply";
				s2 = "TrapTarget.ply";
				strcpy(filename1, s1.c_str());
				strcpy(filename2, s2.c_str());
				skEvent->ReadTargetMesh(filename2);
				skEvent->ReadBaseMesh(filename1);
			}

			else if (skEvent->shapeIdentity == 3)
			{
				s1 = "JayPipe.ply";
				s2 = "JayTarget.ply";
				strcpy(filename1, s1.c_str());
				strcpy(filename2, s2.c_str());
				skEvent->ReadTargetMesh(filename2);
				skEvent->ReadBaseMesh(filename1);
			}
			else if (skEvent->shapeIdentity == 4)
			{
				s1 = "ShoePipe.ply";
				s2 = "ShoeTarget.ply";
				strcpy(filename1, s1.c_str());
				strcpy(filename2, s2.c_str());
				skEvent->ReadTargetMesh(filename2);
				skEvent->ReadBaseMesh(filename1);
			}
			/*if (randNum == 1) { skEvent->resetSquare(); }
			else if (randNum == 2) { skEvent->resetRectangleB(); }
			else if (randNum == 3) { skEvent->resetRectangleH(); }
			else if (randNum == 4) { skEvent->resetTrapezium(); }*/

			a = skEvent->rotationType;
			b = skEvent->shapeName;
			c = skEvent->shapeIteration;
		}
		else
		{
			//cerr << "Empty" << endl;
			skEvent->hapticstylusmov.clear();
			skEvent->stylusmov.clear();
			//skEvent->isNewShape();

			srand(time(0));
			randNum = (rand() % 4) + 1;
			_rand.push_back(randNum);
			skEvent->shapeCounts(randNum);
			skEvent->generateRand();
			skEvent->shapeIdentity = randNum;

			if (skEvent->shapeIdentity == 1)
			{
				s1 = "PuzzlePipe.ply";
				s2 = "PuzzleTarget.ply";
				strcpy(filename1, s1.c_str());
				strcpy(filename2, s2.c_str());
				skEvent->ReadBaseMesh(filename1);
				skEvent->ReadTargetMesh(filename2);
			}

			else if (skEvent->shapeIdentity == 2)
			{
				s1 = "TrapPipe.ply";
				s2 = "TrapTarget.ply";
				strcpy(filename1, s1.c_str());
				strcpy(filename2, s2.c_str());
				skEvent->ReadBaseMesh(filename1);
				skEvent->ReadTargetMesh(filename2);
			}

			else if (skEvent->shapeIdentity == 3)
			{
				s1 = "JayPipe.ply";
				s2 = "JayTarget.ply";
				strcpy(filename1, s1.c_str());
				strcpy(filename2, s2.c_str());
				skEvent->ReadBaseMesh(filename1);
				skEvent->ReadTargetMesh(filename2);
			}
			else if (skEvent->shapeIdentity == 4)
			{
				s1 = "ShoePipe.ply";
				s2 = "ShoeTarget.ply";
				strcpy(filename1, s1.c_str());
				strcpy(filename2, s2.c_str());
				skEvent->ReadBaseMesh(filename1);
				skEvent->ReadTargetMesh(filename2);
			}
			/*if (randNum == 1) { skEvent->resetSquare(); }
			else if (randNum == 2) { skEvent->resetRectangleB(); }
			else if (randNum == 3) { skEvent->resetRectangleH(); }
			else if (randNum == 4) { skEvent->resetTrapezium(); }*/
		}
			
		break;

	case 'p':
		//srand(time(0));
		prevpcount = pcount;
		pcount = (rand() % 3) + 1;
		while (pcount == prevpcount) { pcount = (rand() % 3) + 1; }
		cerr << "pcount->" << pcount << endl;
		if (pcount == 1)
		{
			s1 = "SquarePipe.ply";
			s2 = "SquareTarget.ply";
			strcpy(filename1, s1.c_str());
			strcpy(filename2, s2.c_str());
			skEvent->ReadBaseMesh(filename1);
			skEvent->ReadTargetMesh(filename2);
		}
		if (pcount == 2)
		{
			s1 = "TrianglePipe.ply";
			s2 = "TriangleTarget.ply";
			strcpy(filename1, s1.c_str());
			strcpy(filename2, s2.c_str());
			skEvent->ReadBaseMesh(filename1);
			skEvent->ReadTargetMesh(filename2);
		}
		if (pcount == 3)
		{
			s1 = "QuartPipe.ply";
			s2 = "QuartTarget.ply";
			strcpy(filename1, s1.c_str());
			strcpy(filename2, s2.c_str());
			skEvent->ReadBaseMesh(filename1);
			skEvent->ReadTargetMesh(filename2);
		}
		break;
	
	case 'g':
		skEvent->~ABCSketchManager();
		skEvent->option = "g";
		cerr << "Global" << endl;
		break;
	case 'G':
		skEvent->~ABCSketchManager();
		skEvent->option = "G";
		cerr << "Global" << endl;
		break;
	case 'l':
		skEvent->~ABCSketchManager();
		skEvent->option = "l";
		cerr << "Differential" << endl;
		break;
	case 'L':
		skEvent->~ABCSketchManager();
		skEvent->option = "L";
		cerr << "Differential" << endl;
		break;
	case 'e':
		skEvent->~ABCSketchManager();
		skEvent->option = "e";
		cerr << "Elastic" << endl;
		break;
	case 'E':
		skEvent->~ABCSketchManager();
		skEvent->option = "E";
		cerr << "Elastic" << endl;
		break;
	case 'r': //Let us Reset the scene
		pcount = prevpcount = 0;
		skEvent->~ABCSketchManager();		
		break;
	case 'R':
		pcount = prevpcount = 0;
		skEvent->~ABCSketchManager();
		break;
	case 's':
		skEvent->SaveLog();
		break;
	}
}

void specialKeyCallback(unsigned char key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_RIGHT:
		break;
	}
}

void glInit(int * pargc, char ** argv)
{
	glutInit(pargc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	
	//glBlendFunc(GL_ONE_MINUS_DST_ALPHA, GL_DST_ALPHA);
	// Create a window of size GL_WIN_SIZE_X, GL_WIN_SIZE_Y
	// See where GL_WIN_SIZE_X and GL_WIN_SIZE_Y are defined!!
	glutInitWindowSize(GL_WIN_SIZE_X, GL_WIN_SIZE_Y);

	// Create a window with some name
	glutCreateWindow("JCISE");

	// GLEW is another library that
	// will be used as a standard for
	// initializing Shaders. 
	// Do not worry about this now!
	GLenum err = glewInit();
	if (GLEW_OK != err) // If GLEW was not properly initialized, we create a pop-up window and tell the user!
	{
		printf("Error: %s\n", glewGetErrorString(err));
		MessageBox(NULL, L"GLEW unable to initialize.", L"ERROR", MB_OK);
		return;
	}

	//---- Initialize Haptics device
	hapticsEvent = HapticsEventManager::Initialize();
	hapticsEvent->Setup(skEvent);
	
	//---- Initialize the openGL camera 
	//---- and projection parameters
	view.SetParameters(35, 0.1, 10000.0);
	view.SetCameraCenter(0.0, 0.0, 0.0);
	view.SetCameraEye(0.0, 0.2, 2.0);
	view.SetCameraHead(0.0, 1.0, 0.0);

	// Shader Initialization:
	skEvent->InitShaders();

	light1.SetPosition(lightPos);
	light1.SetDiffuseColor(diffuse1);
	light1.SetAmbientColor(ambient);
	light1.SetSpecularColor(specular);

	light2.SetPosition(lightPos);
	light2.SetDiffuseColor(diffuse2);
	light2.SetAmbientColor(ambient);
	light2.SetSpecularColor(specular);

	glutReshapeFunc(glutReshape);
	glutDisplayFunc(glutDisplay);
	glutKeyboardFunc(glutKeyboard);
	//glutPassiveMotionFunc(mousePassiveMotionCallback);
	glutIdleFunc(glutIdle);

}

int main(int argc, char** argv)
{
	pcount = 0;
	prevpcount = 0;
	
	skEvent = new ABCSketchManager();
	//char filename[1000];

	cerr << "UserID: ";
	cin >> skEvent->userID;	
	
	cerr << "Capture video (0/1)? ";
	cin >> isVideo;

	//cerr << "Select Mode [Pratice(P)/Test(T)]";
	// >> skEvent->testmode;
	
	//skEvent->testmode = "t";

	cerr << "Select Rotation (G/L/E)";
	cin >> skEvent->option;

	int video = 0;

	if (skEvent->option == "G" || skEvent->option == "g")
	{
		if (isVideo > 0)
		{
			video++;

			//---- Video writer initialization
			string _videoName;
			char videoName[10000];
			sprintf(videoName, "Global_User_%s.avi", skEvent->userID);
			_videoName.append(videoName);
			cv::Size _sss(GL_WIN_SIZE_X, GL_WIN_SIZE_Y);
			capture.open(_videoName, CV_FOURCC('M', 'P', 'E', 'G'), 30, _sss, true);
		}
	}

	else if (skEvent->option == "E" || skEvent->option == "e")
	{
		if (isVideo > 0)
		{
			video++;

			//---- Video writer initialization
			string _videoName;
			char videoName[10000];
			sprintf(videoName, "Elastic_User_%s.avi", skEvent->userID);
			_videoName.append(videoName);
			cv::Size _sss(GL_WIN_SIZE_X, GL_WIN_SIZE_Y);
			capture.open(_videoName, CV_FOURCC('M', 'P', 'E', 'G'), 30, _sss, true);
		}
	}

	else if (skEvent->option == "L" || skEvent->option == "l")
	{
		if (isVideo > 0)
		{
			video++;

			//---- Video writer initialization
			string _videoName;
			char videoName[10000];
			sprintf(videoName, "Differential_User_%s.avi", skEvent->userID);
			_videoName.append(videoName);
			cv::Size _sss(GL_WIN_SIZE_X, GL_WIN_SIZE_Y);
			capture.open(_videoName, CV_FOURCC('M', 'P', 'E', 'G'), 30, _sss, true);
		}
	}
	
	atexit(CleanupAndExit);

	glInit(&argc, argv);
	glutMainLoop();

	return 0;
}

