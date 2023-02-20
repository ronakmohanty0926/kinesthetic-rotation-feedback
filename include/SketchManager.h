#pragma once

#include <queue>
#include <deque>
#include "Core.h"
#include "Renderer.h"
#include "Curve.h"
#include "Mesh.h"

#include "MeshRenderer.h"
#include "HapticsEventManager.h"
#include <time.h>

#define MODE_IDLE 0
//#define MODE_SKETCH 0
//#define MODE_TRANSLATION 1
#define MODE_ROTATION 1
//#define UNDO 3
//#define REDO 4

namespace midl {
	class Mesh;

	class ABCSketchManager
	{
	private:
		Shader diffuseShader, textureShader;//Shaders
		int mode;
		float trailElasticity;//curve-smoothing
		float Zdistance, Xdistance, Ydistance, planeCenter[3];//plane properties
		float curr_stylus[3], prev_stylus[3], displacement[3], cursor[3], hapcurr_stylus[3];//stylus properties
		float angle , axis[3], matrix[9];//rotation 
			
		bool isCurrStytlusSketching;//sketch status
		bool isPrevStytlusSketching;
		

		float minZ, maxZ;//sketch shading

		clock_t start, end;
		double time_elapsed;
				

		vector<Tuple3f>meshvert;
		vector<Tuple3f>meshedge;
		Tuple3f vertex;
		vector<Tuple3f>edges;
		vector<Tuple3f>vertices;
		vector<Tuple3f>points;//ellipse		

		vector<Curve3> Sketch;
		vector<Curve3> Traj;

		deque<Curve3>Undo;		

		vector<int> currentMode;

	/*	vector<Tuple3f>sty;
		vector<Tuple3f>hapsty;
		vector<Tuple3f>altNormals;
		vector<Tuple3f>altNormal1s;
		vector<Tuple3f>altNormal2s;*/

		float square1[3], square2[3], square3[3], square4[4];
		float rectB1[3], rectB2[3], rectB3[3], rectB4[4];
		float rectH1[3], rectH2[3], rectH3[3], rectH4[4];
		float trapeze1[3], trapeze2[3], trapeze3[3], trapeze4[4];

		float initsquare1[3], initsquare2[3], initsquare3[3], initsquare4[4], initsquare5[4], initsquare6[4], initsquare7[4], initsquare8[4] ;
		float initrectB1[3], initrectB2[3], initrectB3[3], initrectB4[4];
		float initrectH1[3], initrectH2[3], initrectH3[3], initrectH4[4];
		float inittrapeze1[3], inittrapeze2[3], inittrapeze3[3], inittrapeze4[4];

		float altNormal[3], initNormal[3], altNormal1[3], altNormal2[3],  initNormal1[3], initNormal2[3];
		float _pivot[3];
		float squareset[4], rectBset[4], rectHset[4], trapezeset[4];
		float errA, errB, errC, alpha, beta, gamma;
		float clicks;
		

		//void DrawCurve(Curve3 &C);
		

		void DrawShadow(float *datapoints1, float *datapoints2, float *datapoints3, float *datapoints4);
		void DrawStylusShadow();
		void DrawShapeShadow(float width, float height, float *center);
		void RenderGrid();
		void RenderRotation();
		void RenderNormals();

		void UpdateStylus(float *stylus);
		void UpdateHapticStylus(float *stylus);

		//void UpdateSketch();
		void SortSketchZ(float *datapoints1, float*datapoints2, float *datapoints3, float *datapoints4);
	
		//GLuint materialID;

		//Deviation vector
		//vector<float> min_deviation;//RMS error
		//vector<Tuple2i> meshEdges;
		//float RMS;//Root-Mean-Square Error
	
	public:
		//char *userID;

		ABCSketchManager();
		~ABCSketchManager();

		vector<clock_t>stylusmov;
		vector<clock_t>hapticstylusmov;

		Curve3 c;
		Mesh *meshEvent1;
		Mesh *meshEvent2;
		int undoPress;
		int redoPress;
		string option, testmode;
		int usermode;

		void InitShaders();
		void Render();
		//void RenderTargetShape(float* datapoints1, float* datapoints2, float* datapoints3, float* datapoints4);

		void UpdatePointToPlaneDist();//For Force-feedback
		void ReadBaseMesh(const char*fName);
		void ReadTargetMesh(const char*fName);
		void DrawTargetMesh();
		void DrawBaseMesh();

		bool SketchOn();
		bool SketchOff();
		bool isSketchOn;
		bool RotationOn();
		bool RotationOff();
		//bool TranslationOn();
		void ManipulationOff();	
				
		//float SetPlaneCenter(float *newCenter);
		float SetPivot(float *pivot);
	
		int Update();
		int Listen(float *stylus);
		int HapListen(float *stylus);
		int shapeIdentity, trialshapeIdentity;
		int shapeCountPuzzle, shapeCountTrapeze, shapeCountShoe, shapeCountJay, shapeCount;
		string userID, shapeName, shapeIteration, rotationType;

		bool needForce = false;
		bool shapeCounts(int shape);
		//bool isNewShape();
		bool generateRand();
		void generateNormals();	
		
		bool CheckHapticsForce();
		bool SetHaptics();
		//bool UndoSketch();
		//bool RedoSketch();
		

		void ComputeError();
		bool SaveLog();		
		bool SaveMesh();
	};
}