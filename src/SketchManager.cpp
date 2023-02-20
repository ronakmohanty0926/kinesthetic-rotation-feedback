#include "SketchManager.h"
#include "Renderer.h"

using namespace midl;

float _squareset[4], _rectBset[4], _rectHset[4], _trapeziumset[4], _curr_stylus[3], _hapcurr_stylus[3], altnormal_[3], altnormal1_[3], altnormal2_[3];
vector<Tuple3f>styl;
vector<Tuple3f>hapstyl;
vector<Tuple3f>_altnormals;
vector<Tuple3f>_altnormal1s;
vector<Tuple3f>_altnormal2s;
vector<clock_t>_stylusmov;
float normal1[3], normal2[3];
float centbase[3], centtarget[3];

//void ABCSketchManager::DrawCurve(Curve3 &C)
//{	
//	//glColor3fv(Blue3f);	
//	float p1[3], p2[3];
//	for (int i = 1; i < C.GetNumVertices(); i++)
//	{	
//		C.GetVertex(i - 1, p1);
//		C.GetVertex(i, p2);		
//		glEnable(GL_LINE_SMOOTH);
//		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
//		glLineWidth(6);		
//		glBegin(GL_LINES);
//		float r = maxZ - minZ;
//		float c1, c2;
//		c1 = 1 - (0.3*((p1[2] - minZ) / r) + 0.5);
//		c2 = 1 - (0.3*((p2[2] - minZ) / r) + 0.5);
//		glColor3f(c1, c1, c1);
//		glVertex3f(p1[0], p1[1], p1[2]);
//		glColor3f(c2, c2, c2);
//		glVertex3f(p2[0], p2[1], p2[2]);
//		glEnd();	
//	}
//}

//void _DrawQuadShaded(float* datapoints1, float* datapoints2, float* datapoints3, float* datapoints4, float *center, bool isFilled, float *color1, float *color2, float *color3, float *color4, float transparency)
//{
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glPushMatrix();
//	glTranslatef(center[0], center[1], center[2]);
//
//	if (isFilled) glBegin(GL_QUADS);
//	else glBegin(GL_LINE_LOOP);
//	glColor4f(color1[0], color1[1], color1[2], transparency);
//	glNormal3f(0.0, 0.0, 1.0);
//	glVertex3fv(datapoints1);
//	glColor4f(color2[0], color2[1], color2[2], transparency);
//	glNormal3f(0.0, 0.0, 1.0);
//	glVertex3fv(datapoints2);
//	glColor4f(color3[0], color3[1], color3[2], transparency);
//	glNormal3f(0.0, 0.0, 1.0);
//	glVertex3fv(datapoints3);
//	glColor4f(color4[0], color4[1], color4[2], transparency);
//	glNormal3f(0.0, 0.0, 1.0);
//	glVertex3fv(datapoints4);
//	glEnd();
//	glPopMatrix();
//	glDisable(GL_BLEND);
//}

void _UpdateStylus(float *stylus)
{
	
	clock_t x;
	x = clock();
	_stylusmov.push_back(x);

	Tuple3f _stylus;

	_curr_stylus[0] = stylus[0];
	_curr_stylus[1] = stylus[1];
	_curr_stylus[2] = stylus[2];

	_stylus.data[0] = _curr_stylus[0];
	_stylus.data[1] = _curr_stylus[2];
	_stylus.data[2] = _curr_stylus[1];

	styl.push_back(_stylus);
}

void _UpdateHapStylus(float *stylus)
{
	/*clock_t x;
	x = clock();
	stylusmov.push_back(x);*/

	Tuple3f _hapstylus;

	_hapcurr_stylus[0] = stylus[0];
	_hapcurr_stylus[1] = stylus[1];
	_hapcurr_stylus[2] = stylus[2];

	_hapstylus.data[0] = _hapcurr_stylus[0];
	_hapstylus.data[1] = _hapcurr_stylus[2];
	_hapstylus.data[2] = _hapcurr_stylus[1];

	hapstyl.push_back(_hapstylus);
}

void _UpdateNormal(float *normal)
{
	/*clock_t x;
	x = clock();
	stylusmov.push_back(x);*/

	Tuple3f _normal;

	altnormal_[0] = normal[0];
	altnormal_[1] = normal[1];
	altnormal_[2] = normal[2];

	_normal.data[0] = altnormal_[0];
	_normal.data[1] = altnormal_[2];
	_normal.data[2] = altnormal_[1];

	//cerr << "NormZx->" << altnormal_[0] << endl;
	//cerr << "NormZy->" << altnormal_[1] << endl;
	//cerr << "NormZz->" << altnormal_[2] << endl;

	_altnormals.push_back(_normal);
}
void _UpdateNormal1(float *normal)
{
	/*clock_t x;
	x = clock();
	stylusmov.push_back(x);*/

	Tuple3f _normal;

	altnormal1_[0] = normal[0];
	altnormal1_[1] = normal[1];
	altnormal1_[2] = normal[2];

	_normal.data[0] = altnormal1_[0];
	_normal.data[1] = altnormal1_[2];
	_normal.data[2] = altnormal1_[1];

	/*cerr << "NormYx->" << altnormal1_[0] << endl;
	cerr << "NormYy->" << altnormal1_[1] << endl;
	cerr << "NormYz->" << altnormal1_[2] << endl;*/

	_altnormal1s.push_back(_normal);
}
void _UpdateNormal2(float *normal)
{
	/*clock_t x;
	x = clock();
	stylusmov.push_back(x);*/

	Tuple3f _normal;

	altnormal2_[0] = normal[0];
	altnormal2_[1] = normal[1];
	altnormal2_[2] = normal[2];

	_normal.data[0] = altnormal2_[0];
	_normal.data[1] = altnormal2_[2];
	_normal.data[2] = altnormal2_[1];

	//cerr << "NormXx->" << altnormal2_[0] << endl;
	//cerr << "NormXy->" << altnormal2_[1] << endl;
	//cerr << "NormXz->" << altnormal2_[2] << endl;

	_altnormal2s.push_back(_normal);
}
//void _drawFloor(float side, float *color)
//{
//	glColor4fv(color);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	//glEnable(GL_DEPTH_TEST);
//	glTranslatef(0.0, -0.9, 0.0);
//	glBegin(GL_QUADS);
//	glNormal3f(0.0, 0.0, 1.0);
//	glVertex3f(0.5*side, 0.0, -0.5*side);
//	glNormal3f(0.0, 0.0, 1.0);
//	glVertex3f(0.5*side, 0.0, 0.5*side);
//	glNormal3f(0.0, 0.0, 1.0);
//	glVertex3f(-0.5*side, 0.0, 0.5*side);
//	glNormal3f(0.0, 0.0, 1.0);
//	glVertex3f(-0.5*side, 0.0, -0.5*side);
//	glEnd();
//	glTranslatef(0.0, 0.9, 0.0);
//	//glDisable(GL_DEPTH_TEST);
//	glDisable(GL_BLEND);	
//}

void ABCSketchManager::DrawStylusShadow()
{
	glColor3fv(Gray3f);
	float p1[3];
	float planePt1[] = { 0.0, -0.55, 0.0 };
	float dist1 = PointToPlaneDist(curr_stylus, planePt1, Yaxis);
	p1[0] = curr_stylus[0]; p1[1] = curr_stylus[1]; p1[2] = curr_stylus[2];
	p1[1] -= dist1;

	
DrawSphere(p1, 0.03f, Gray3f, 0.5F);	
}
//
//void ABCSketchManager::DrawShapeShadow(float width, float height, float *center)
//{	
//	float v1[3], v2[3];
//	if (shapeIdentity == 1 || shapeIdentity == 2 || shapeIdentity == 3)
//	{
//		v1[0] = -0.5*width;  v1[1] = -0.5*height; v1[2] = 0.0;
//		v2[0] = 0.5*width;  v2[1] = -0.5*height; v2[2] = 0.0;		
//	}
//	else
//	{
//		v1[0] = 0.3;  v1[1] = -0.3; v1[2] = 0.0;
//		v2[0] = -0.5;  v2[1] = -0.3; v2[2] = 0.0;
//	}
//	
//	float planePt[] = { 0.0, -0.55, 0.0 };
//	float dist1 = PointToPlaneDist(v1, planePt, Yaxis);
//	float dist2 = PointToPlaneDist(v2, planePt, Yaxis);
//
//	v1[1] -= dist1;
//	v2[1] -= dist2;
//
//	glLineWidth(1.0);
//	glPushMatrix();
//	//glTranslatef(center[0], 0.0, center[2]);	
//	glColor3fv(Gray3f);
//	//glEnable(GL_BLEND);
//	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glEnable(GL_LINE_SMOOTH);
//	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
//	glBegin(GL_LINES);	
//	glVertex3f(v1[0], v1[1],v1[2]);
//	glVertex3f(v2[0], v2[1], v2[2]);
//	glEnd();
//	//glTranslatef(center[0], 0.0, center[2]);
//	glPopMatrix();
//	//glDisable(GL_BLEND);	
//}

void ABCSketchManager::RenderGrid()
{	
	float color[] = { 0.7,0.7,0.7 };
	float cent[] = { 0.0, -0.6, 0.0 };
	glTranslatef(0.0, -0.8, 0.0);	
	//glDisable(GL_DEPTH_TEST);
	DrawGrid(GRID_PLANE::ZX, 2.0f, 1, color);	
	//glEnable(GL_DEPTH_TEST);
	glTranslatef(0.0, 0.8, 0.0);
}

void ABCSketchManager::RenderRotation()
{
	bool isFilled = true;
	//currentMode.clear();
	float planec[] = { 0.0, 0.0, -3.0 };
	float colorrotate[] = { 1.0, 1.0, 0.74 };
	float coloridle[] = { 0.98, 0.55, 0.35 };
	DrawQuad(6.0, 4.0, planec, isFilled, Gray3f, 0.2f);	
	DrawStylusShadow();

	//for (int i = 0; i < Sketch.size(); i++)DrawCurve(Sketch[i]);
	//if(!Sketch.empty())	for (int i = 0; i < Sketch.size(); i++)DrawShadow(Sketch[i]);
	//
	//if (isPrevStytlusSketching && isCurrStytlusSketching)
	//{
	//	isFilled = true;
	//	bool isFilledFrame = false;
	//	glDisable(GL_DEPTH_TEST);
	//	DrawSphere(cursor, 0.03f, Green3f, 1.0F);
	//	glEnable(GL_DEPTH_TEST);

	//	DrawQuad(1.5, 0.8, planeCenter, isFilled, Blue3f, 0.1f);
	//	DrawQuad(1.5, 0.8, planeCenter, isFilledFrame, Blue3f, 0.3f);
	//	//cerr << "Pz" << planeCenter[2] << endl;
	//}

	if (mode == MODE_ROTATION)
	{
		//isCurrStytlusSketching = false;
		//isPrevStytlusSketching = false;
		//cerr << "It is on" << endl;
		mode = MODE_ROTATION;
		currentMode.push_back(mode);
		usermode = mode;
		//currentMode.push_back(mode);
		
		if (option == "g" || option == "G")
		{
			rotationType = "Global";
			float angle, axis[3], gmatrix[9], radius[3], disp[3];
			DrawSphere(curr_stylus, 0.03f, Blue3f, 1.0F);
			float v1[3], v2[3], v[3], r[3], m[3], q[3];

			
			/*SubVectors3(_pivot, Origin, radius);
			float rad = Norm3(radius);
			float radius1 = rad - 1.2;
			float radius2 = rad + 0.3;		*/			

			int lastID = (int)(Traj[Traj.size() - 1].GetNumVertices()) - 1;

			if (lastID > -1)
			{
				Traj[Traj.size() - 1].GetVertex(lastID, r);
				m[0] = trailElasticity * curr_stylus[0] + (1 - trailElasticity)*r[0];
				m[1] = trailElasticity * curr_stylus[1] + (1 - trailElasticity)*r[1];
				m[2] = trailElasticity * curr_stylus[2] + (1 - trailElasticity)*r[2];

				SubVectors3(m, Origin, v1);
				SubVectors3(curr_stylus, Origin, v2);
				SubVectors3(curr_stylus, m, v);

				float normdist = Norm3(v1);

				GetAngleAxisBetweenDirections(v1, v2, axis, angle);
				//cerr << "The angle is->" << angle << endl;

				if (!isnan(angle))
				{					
						/*if (shapeIdentity == 1 || shapeIdentity == 2 || shapeIdentity == 3 || shapeIdentity == 4 || shapeIdentity == 5 || shapeIdentity == 6 || shapeIdentity == 7)*/
						meshEvent2->Rotate(angle, axis);
						AxisAngle(axis, angle, matrix);
						RotateVec3(altNormal, matrix);
						RotateVec3(altNormal1, matrix);
						RotateVec3(altNormal2, matrix);
					

					
						/*if (shapeIdentity == 1 || shapeIdentity == 2 || shapeIdentity == 3 || shapeIdentity == 4 || shapeIdentity == 5 || shapeIdentity == 6 || shapeIdentity == 7)*/
						meshEvent2->Rotate(angle, axis);
						AxisAngle(axis, angle, matrix);
						RotateVec3(altNormal, matrix);
						RotateVec3(altNormal1, matrix);
						RotateVec3(altNormal2, matrix);					
				
				}
				else 
				{
					angle = 0.0;
				}
			}
			else { m[0] = curr_stylus[0]; m[1] = curr_stylus[1]; m[2] = curr_stylus[2]; }

			Traj[Traj.size() - 1].AddPoint(m);

			cursor[0] = m[0];
			cursor[1] = m[1];
			cursor[2] = m[2];

			/*cerr << "The normals1->" << altNormal1[0] << "," << altNormal1[1] << "," << altNormal1[2] << endl;
			cerr << "The normals2->" << altNormal2[0] << "," << altNormal2[1] << "," << altNormal2[2] << endl;*/
		}

		else if (option == "l" || option == "L")
		{
			rotationType = "Differential";
			DrawSphere(curr_stylus, 0.03f, Blue3f, 1.0F);		

			Traj[Traj.size() - 1].AddPoint(curr_stylus);
			//cerr << "The size->" << Traj.size() << endl;

			int lastID = (int)(Traj[Traj.size() - 1].GetNumVertices()) - 2;
			//int seclastID = (int)(Traj[Traj.size() - 1].GetNumVertices()) - 4;

			float angle, area, axis[3];
			float v1[3], v2[3], v3[3], last[3], secLast[3];

			if (lastID > 0)
			{
				Traj[Traj.size() - 1].GetVertex(lastID, last);
				//Traj[Traj.size() - 1].GetVertex(seclastID, secLast);

				SubVectors3(curr_stylus, last, v1);//First and i -1
				//Normalize3(v1);

				axis[0] = -v1[1];
				axis[1] = v1[0];
				axis[2] = 0.0;

				Normalize3(axis);
				
				float distance[3], normal[3];
				SubVectors3(_pivot, Origin, distance);
				float dist = Norm3(distance);

				SubVectors3(curr_stylus, Origin, normal);
				float normdist = Norm3(normal);

				float diff = normdist - dist;
				//cerr << "PD->" << planeDist << endl;

				float displacement = PointToPlaneDist(curr_stylus, Origin, Zaxis);

				float dist2 = dist + 0.7;
				float dist1 = dist - 3.0;
			

				if (normdist <= dist)angle = 2.1*Norm3(v1);
				else if (normdist > dist)angle = 2.1*Norm3(v1);
				//else if (displacement > dist2 && displacement < dist1)angle = 1.6*Norm3(v1);
				else angle = 0.0;

				//cerr << "Angle->" << angle << endl;

				AxisAngle(axis, angle, matrix);

				meshEvent2->Rotate(angle, axis);
				RotateVec3(altNormal, matrix);
				RotateVec3(altNormal1, matrix);
				RotateVec3(altNormal2, matrix);
				/*}
				else
				{
					for (int i = 0; i < 9; i++)
					{
						matrix[i] = 0.0;
						matrix[0] = matrix[4] = matrix[4] = 1.0;
					}

					if (shapeIdentity == 1)
					{
						RotateVec3(altNormal, matrix);
						RotateVec3(altNormal1, matrix);
						RotateVec3(altNormal2, matrix);
						RotateVec3(square1, matrix);
						RotateVec3(square2, matrix);
						RotateVec3(square3, matrix);
						RotateVec3(square4, matrix);
					}

					else if (shapeIdentity == 2)
					{
						RotateVec3(altNormal, matrix);
						RotateVec3(altNormal1, matrix);
						RotateVec3(altNormal2, matrix);
						RotateVec3(rectB1, matrix);
						RotateVec3(rectB2, matrix);
						RotateVec3(rectB3, matrix);
						RotateVec3(rectB4, matrix);
					}
					else if (shapeIdentity == 3)
					{
						RotateVec3(altNormal, matrix);
						RotateVec3(altNormal1, matrix);
						RotateVec3(altNormal2, matrix);
						RotateVec3(rectH1, matrix);
						RotateVec3(rectH2, matrix);
						RotateVec3(rectH3, matrix);
						RotateVec3(rectH4, matrix);
					}
					else if (shapeIdentity == 4)
					{
						RotateVec3(altNormal, matrix);
						RotateVec3(altNormal1, matrix);
						RotateVec3(altNormal2, matrix);
						RotateVec3(trapeze1, matrix);
						RotateVec3(trapeze2, matrix);
						RotateVec3(trapeze3, matrix);
						RotateVec3(trapeze4, matrix);
					}

				}*/
			}
			
		}

		else if (option == "e" || option == "E")
		{
			rotationType = "Elastic";
			float Custom[] = { 0.5, 0.5, 0.5 };

			DrawCylinder(curr_stylus, _pivot, 0.1, Custom, 0.8F);
			DrawSphere(_pivot, 0.03f, Red3f, 1.0F);
			DrawSphere(curr_stylus, 0.03f, Blue3f, 1.0F);

			float _traj[3], temp[3], q[3];
			SubVectors3(curr_stylus, _pivot, _traj);

			axis[0] = _traj[1];
			axis[1] = -_traj[0];
			axis[2] = 0.0;

			bool b = Normalize3(axis);
			angle = -0.12*Norm3(_traj);
			//cerr << "angleOG:" << angle << endl;
			AxisAngle(axis, angle, matrix);
			meshEvent2->Rotate(angle, axis);
			RotateVec3(altNormal, matrix);
			RotateVec3(altNormal1, matrix);
			RotateVec3(altNormal2, matrix);

			/*if (shapeIdentity == 1 || shapeIdentity == 2 || shapeIdentity == 3 || shapeIdentity == 4 || shapeIdentity == 5 || shapeIdentity == 6 || shapeIdentity == 7)
			{
						


			}*/			
		}
	}

	else if (mode == MODE_IDLE)
	{
		//isFilled = true;
		//bool isFilledFrame = false;
		mode = MODE_IDLE;
		currentMode.push_back(mode);
		usermode = mode;
		//DrawQuad(1.5, 0.8, planeCenter, isFilled, Blue3f, 0.1f);
		//DrawQuad(1.5, 0.8, planeCenter, isFilledFrame, Blue3f, 0.3f);		
		//glDisable(GL_DEPTH_TEST);
		DrawSphere(curr_stylus, 0.03f, Red3f);
		//glEnable(GL_DEPTH_TEST);
	}
}

//bool ABCSketchManager::isNewShape()
//{
//	Sketch.clear();
//	return true;
//}

void ABCSketchManager::UpdateStylus(float *stylus)
{
	

	//Tuple3f _stylus;

	prev_stylus[0] = curr_stylus[0];
	prev_stylus[1] = curr_stylus[1];
	prev_stylus[2] = curr_stylus[2];	

	curr_stylus[0] = stylus[0];
	curr_stylus[1] = stylus[1];
	curr_stylus[2] = stylus[2];	

	//_stylus.data[0] = curr_stylus[0];
	//_stylus.data[1] = curr_stylus[2];
	//_stylus.data[2] = curr_stylus[1];
	//
	//sty.push_back(_stylus);
	
	displacement[0] = curr_stylus[0] - prev_stylus[0];
	displacement[1] = curr_stylus[1] - prev_stylus[1];
	displacement[2] = curr_stylus[2] - prev_stylus[2];	
}

void ABCSketchManager::UpdateHapticStylus(float *stylus)
{
	clock_t x;
	x = clock();
	hapticstylusmov.push_back(x);

	hapcurr_stylus[0] = stylus[0];
	hapcurr_stylus[1] = stylus[1];
	hapcurr_stylus[2] = stylus[2];

	//Tuple3f _hstylus;

	/*_hstylus.data[0] = hapcurr_stylus[0];
	_hstylus.data[1] = hapcurr_stylus[2];
	_hstylus.data[2] = hapcurr_stylus[1];

	hapsty.push_back(_hstylus);*/
}

//void ABCSketchManager::UpdateSketch()
//{	
//		isPrevStytlusSketching = isCurrStytlusSketching;
//		if (Zdistance > -0.08 && Zdistance < 0.15 && curr_stylus[1] > -2.00 && curr_stylus[1] < 2.00 && curr_stylus[0] > -1.5 && curr_stylus[0] < 1.5 && isSketchOn)
//		{isCurrStytlusSketching = true;}
//		else isCurrStytlusSketching = false;
//
//		if (isCurrStytlusSketching && isPrevStytlusSketching && !Sketch.empty())
//		{
//			float p[] = { curr_stylus[0],curr_stylus[1],curr_stylus[2] };
//
//			int lastID = (int)(Sketch[Sketch.size() - 1].GetNumVertices()) - 1;
//
//			if (lastID > -1)
//			{			
//				float temp[3];
//				Sketch[Sketch.size() - 1].GetVertex(lastID, temp);
//				p[0] = trailElasticity*curr_stylus[0] + (1 - trailElasticity)*temp[0];
//				p[1] = trailElasticity*curr_stylus[1] + (1 - trailElasticity)*temp[1];
//			}
//			else
//			{
//				p[0] = curr_stylus[0]; p[1] = curr_stylus[1];
//			}
//			p[2] = planeCenter[2];
//			Sketch[Sketch.size() - 1].AddPoint(p);
//			
//			cursor[0] = p[0];
//			cursor[1] = p[1];
//			cursor[2] = p[2];
//			mode = MODE_SKETCH;
//			currentMode.push_back(mode);
///*
//			myfile2 << mode << " " << curr_stylus[0] << " " << curr_stylus[1] << " " << curr_stylus[2] << " " << stylusmov[stylusmov.size() - 1];
//			myfile2 << endl;*/
//		}
//		else if (isCurrStytlusSketching && !isPrevStytlusSketching)
//		{
//				Curve3 c;
//				Sketch.push_back(c);
//				mode = MODE_IDLE;
//				currentMode.push_back(mode);
//
//				/*myfile2 << mode << " " << curr_stylus[0] << " " << curr_stylus[1] << " " << curr_stylus[2] << " " << stylusmov[stylusmov.size() - 1];
//				myfile2 << endl;*/
//
//			//cerr << "Sketch" << Sketch.size() - 1 << "Pushed back" << endl;	
//		}	
//			
//	}

void ABCSketchManager::SortSketchZ(float *datapoints1, float*datapoints2, float *datapoints3, float *datapoints4)
{
	minZ = FLT_MAX;
	maxZ = -FLT_MAX;
	float temp[] = { datapoints1[2], datapoints2[2], datapoints3[2], datapoints4[2] };
	//float p[3];
	for (int i = 0; i < 5; i++)
	{
			if (temp[i] < minZ) minZ = temp[i];
			if (temp[i] > maxZ) maxZ = temp[i];
	}
	/*cerr << "The max coord is->" << maxZ << endl;
	cerr << "The min coord is->" << minZ<<endl;*/
}

ABCSketchManager::ABCSketchManager()
{
	mode = MODE_IDLE;
	trailElasticity = 0.5;
	angle = 0.0;
	shapeIdentity = 0;	
	

	isCurrStytlusSketching = false;
	isPrevStytlusSketching = false;	

	SketchOff();

	planeCenter[0] = planeCenter[1] = planeCenter[2] = 0.0;  
	undoPress = 0;
	redoPress = 0;	

	shapeCountPuzzle = 0;
	shapeCountJay = 0;
	shapeCountShoe = 0;
	shapeCountTrapeze = 0;	
	clicks = 0;
	//square1[0] = square1[1] = square1[2] = 0.0;
}

ABCSketchManager::~ABCSketchManager()
{	
	mode = MODE_IDLE;
	trailElasticity = 0.5;
	styl.clear();
	hapstyl.clear();
	_altnormals.clear();
	_altnormal1s.clear();
	_altnormal2s.clear();
	Sketch.clear();		
	Traj.clear();		

/*	isCurrStytlusSketching = false;
	isPrevStytlusSketching = false;*/
		
	//SketchOff();

	planeCenter[0] = planeCenter[1] = planeCenter[2] = 0.0;	

	shapeIdentity = 0;

	shapeCountPuzzle = 0;
	shapeCountJay = 0;
	shapeCountShoe = 0;
	shapeCountTrapeze = 0;	
	shapeCount = 0;
}

void ABCSketchManager::InitShaders()
{
	diffuseShader.Initialize(".//Shaders//diffuseShader.vert", ".//Shaders//diffuseShader.frag");
	//textureShader.Initialize(".//Shaders//colorShader.vert", ".//Shaders//colorShader.frag");
}

bool ABCSketchManager::RotationOn()
{	
	mode = MODE_ROTATION;
	
	Curve3 t;
	Traj.push_back(t);

	clicks++;
	if (option == "e" || option == "E" || option == "g" || option == "G") { _pivot[0] = prev_stylus[0]; _pivot[1] = prev_stylus[1]; _pivot[2] = prev_stylus[2]; }
	//SortSketchZ();
	return true;
}

bool ABCSketchManager::RotationOff()
{
	mode = MODE_IDLE;
	//currentMode.push_back(mode);

	return true;
}

void ABCSketchManager::ReadBaseMesh(const char*fName)
{
	if (meshEvent1 != NULL)
	{
		meshEvent1->DeleteMesh();
		delete meshEvent1;
		cerr << "Mesh1" << endl;
	}	
	
	meshEvent1 = new Mesh();
	meshEvent1->InitMesh();
	meshEvent1->FromPly((char*)fName);	

	meshEvent1->ComputeBoundingBox();
	meshEvent1->ComputeCentroid();
	meshEvent1->TranslateTo(Origin);
	//meshEvent1->ComputeCentroid();
	//meshEvent1->ScaleToUnitBox();
	//meshEvent1->Scale(0.6, 0.6, 0.6);
	
	/*float xRng[2], yRng[2], zRng[2];
	meshEvent1->GetBBox(xRng, yRng, zRng);
	float sx = 0.5 / (xRng[1]-xRng[0]);
	float sy = 0.5 / (yRng[1] - yRng[0]);
	float sz = 1.0 / (zRng[1] - zRng[0]);*/
	//meshEvent1->Scale(sx, sy, sz);

	
}

void ABCSketchManager::ReadTargetMesh(const char*fName)
{
	if (meshEvent2 != NULL)
	{
		meshEvent2->DeleteMesh();
		delete meshEvent2;
		cerr << "Mesh2" << endl;
	}
	
	
	//float temp[3];
	meshEvent2 = new Mesh();
	meshEvent2->InitMesh();
	meshEvent2->FromPly((char*)fName);

	meshEvent2->ComputeCentroid();
	meshEvent2->ComputeBoundingBox();
	meshEvent2->TranslateTo(Origin);
	//meshEvent2->ScaleToUnitBox();
	//meshEvent2->Scale(0.55, 0.55, 0.55);
	
	//meshEvent1->GetCentroid(centbase);
	//meshEvent2->GetCentroid(centtarget);	

	/*float xRng[2], yRng[2], zRng[2];
	meshEvent2->GetBBox(xRng, yRng, zRng);
	float sx = 0.5 / (xRng[1]-xRng[0]);
	float sy = 0.5 / (yRng[1] - yRng[0]);
	float sz = 0.5 / (zRng[1] - zRng[0]);
	*///meshEvent2->Scale(sx, sy, sz);

	float angle = AngleBetweenVectors3(Zaxis, altNormal);
	float axis[3], matrix[9];
	Cross(Zaxis, altNormal, axis);
	Normalize3(axis);
	//AxisAngle(axis, angle, matrix);
	if (!isnan(angle))meshEvent2->Rotate(angle, axis);
}

void ABCSketchManager::DrawTargetMesh()
{
	if (shapeCountPuzzle < 13 && shapeCountTrapeze < 13 && shapeCountJay < 13 && shapeCountShoe < 13)DrawMesh((*meshEvent2), Red3f, MESH_DISPLAY::SOLID_FLAT);	
}

void ABCSketchManager::DrawBaseMesh()
{	
	if (shapeCountPuzzle < 13 && shapeCountTrapeze < 13 && shapeCountJay < 13 && shapeCountShoe < 13)DrawMesh((*meshEvent1), Red3f, MESH_DISPLAY::SOLID_SMOOTH);
}

bool ABCSketchManager::generateRand()
{
	//_altnormals.clear();

	srand(time(0));
	float _altNormal[3];
	_altNormal[0] = (float)(((rand() % 10) + 1));
	_altNormal[1] = (float)(((rand() % 10) + 1));
	_altNormal[2] = (float)(((rand() % 10) + 1));
	
	float rngX, rngY, rngZ;
	rngX = (0.5 + 0.5) / (10 - 1);
	rngY = (0.5 + 0.5) / (10 - 1);
	rngZ = (0.5) / (10 - 1);

	altNormal[0] = (_altNormal[0] - 1)*rngX - 0.5;
	altNormal[1] = (_altNormal[1] - 1)*rngY - 0.5;
	altNormal[2] = (_altNormal[2] - 1)*rngZ;	
	
	Normalize3(altNormal);	
	float axis[3], matrix[9], Angle;

	Angle = AngleBetweenVectors3(Zaxis, altNormal);
	Cross(Zaxis, altNormal, axis);
	AxisAngle(axis, Angle, matrix);

	RotateVec3(Yaxis, matrix, altNormal2);
	Normalize3(altNormal2);

	RotateVec3(Xaxis, matrix, altNormal1);
	Normalize3(altNormal2);
	//cerr << "NormZx->" << altNormal2[0] << endl;
	//cerr << "NormZy->" << altNormal2[1] << endl;
	//cerr << "NormZz->" << altNormal2[2] << endl;

	/*Tuple3f temp;
	temp.data[0] = altNormal[0];
	temp.data[1] = altNormal[1];
	temp.data[2] = altNormal[2];

	altNormals.push_back(temp);
*/
	initNormal[0] = altNormal[0];
	initNormal[1] = altNormal[1];
	initNormal[2] = altNormal[2];

	initNormal1[0] = altNormal1[0];
	initNormal1[1] = altNormal1[1];
	initNormal1[2] = altNormal1[2];

	initNormal2[0] = altNormal2[0];
	initNormal2[1] = altNormal2[1];
	initNormal2[2] = altNormal2[2];

	return true;
}

void ABCSketchManager::generateNormals()
{
	float axis[3], axisX[3], matrix[9], Angle;

	Angle = AngleBetweenVectors3(Zaxis, altNormal);
	Cross(Zaxis, altNormal, axis);
	AxisAngle(axis, angle, matrix);

	RotateVec3(Yaxis, matrix, altNormal2);
	Normalize3(altNormal2);
	RotateVec3(Xaxis, matrix, altNormal1);
	Normalize3(altNormal2);
}

//bool ABCSketchManager::resetSquare()
//{
//	square1[0] = 0.3;
//	square1[1] = 0.3;
//	square1[2] = 0.0;
//	square2[0] = 0.3;
//	square2[1] = -0.3;
//	square2[2] = 0.0;
//	square3[0] = -0.3;
//	square3[1] = -0.3;
//	square3[2] = 0.0;
//	square4[0] = -0.3;
//	square4[1] = 0.3;
//	square4[2] = 0.0;
//
//	initsquare1[0] = 0.3; initsquare1[1] = 0.3; initsquare1[2] = 0.0;
//	initsquare2[0] = 0.3; initsquare2[1] = -0.3; initsquare2[2] = 0.0;
//	initsquare3[0] = -0.3; initsquare3[1] = -0.3; initsquare3[2] = 0.0;
//	initsquare4[0] = -0.3; initsquare4[1] = 0.3; initsquare4[2] = 0.0;
//
//	float axis[3], angle, matrix[9];		
//
//	GetAngleAxisBetweenDirections(Zaxis, altNormal, axis, angle);
//	
//	AxisAngle(axis, angle, matrix);
//	RotateVec3(square1, matrix);
//	RotateVec3(square2, matrix);
//	RotateVec3(square3, matrix);
//	RotateVec3(square4, matrix);
//
//	//cerr << "Vertex 1->" << square1[0] << "," << square1[1] << "," << square1[2] << endl;
//	//cerr << "Vertex 2->" << square2[0] << "," << square2[1] << "," << square2[2] << endl;
//	//cerr << "Vertex 3->" << square3[0] << "," << square3[1] << "," << square3[2] << endl;
//	//cerr << "Vertex 4->" << square4[0] << "," << square4[1] << "," << square4[2] << endl;
//	return true;
//}
//
//bool ABCSketchManager::resetRectangleB()
//{
//	rectB1[0] = 0.4;
//	rectB1[1] = 0.2;
//	rectB1[2] = 0.0;
//	rectB2[0] = 0.4;
//	rectB2[1] = -0.2;
//	rectB2[2] = 0.0;
//	rectB3[0] = -0.4;
//	rectB3[1] = -0.2;
//	rectB3[2] = 0.0;
//	rectB4[0] = -0.4;
//	rectB4[1] = 0.2;
//	rectB4[2] = 0.0;
//
//	initrectB1[0] = rectB1[0]; initrectB1[1] = rectB1[1]; initrectB1[2] = rectB1[2];
//	initrectB2[0] = rectB2[0]; initrectB2[1] = rectB2[1]; initrectB2[2] = rectB2[2];
//	initrectB3[0] = rectB3[0]; initrectB3[1] = rectB3[1]; initrectB3[2] = rectB3[2];
//	initrectB4[0] = rectB4[0]; initrectB4[1] = rectB4[1]; initrectB4[2] = rectB4[2];
//
//	float axis[3], angle, matrix[9];
//
//	GetAngleAxisBetweenDirections(Zaxis, altNormal, axis, angle);
//
//	AxisAngle(axis, angle, matrix);
//	RotateVec3(rectB1, matrix);
//	RotateVec3(rectB2, matrix);
//	RotateVec3(rectB3, matrix);
//	RotateVec3(rectB4, matrix);
//
//	return true;
//}
//
//bool ABCSketchManager::resetRectangleH()
//{
//	rectH1[0] = 0.2;
//	rectH1[1] = 0.4;
//	rectH1[2] = 0.0;
//	rectH2[0] = 0.2;
//	rectH2[1] = -0.4;
//	rectH2[2] = 0.0;
//	rectH3[0] = -0.2;
//	rectH3[1] = -0.4;
//	rectH3[2] = 0.0;
//	rectH4[0] = -0.2;
//	rectH4[1] = 0.4;
//	rectH4[2] = 0.0;
//
//	initrectH1[0] = rectH1[0]; initrectH1[1] = rectH1[1]; initrectH1[2] = rectH1[2];
//	initrectH2[0] = rectH2[0]; initrectH2[1] = rectH2[1]; initrectH2[2] = rectH2[2];
//	initrectH3[0] = rectH3[0]; initrectH3[1] = rectH3[1]; initrectH3[2] = rectH3[2];
//	initrectH4[0] = rectH4[0]; initrectH4[1] = rectH4[1]; initrectH4[2] = rectH4[2];
//
//	float axis[3], angle, matrix[9];
//
//	GetAngleAxisBetweenDirections(Zaxis, altNormal, axis, angle);
//
//	AxisAngle(axis, angle, matrix);
//	RotateVec3(rectH1, matrix);
//	RotateVec3(rectH2, matrix);
//	RotateVec3(rectH3, matrix);
//	RotateVec3(rectH4, matrix);
//
//	return true;
//}
//
//bool ABCSketchManager::resetTrapezium()
//{
//	trapeze1[0] = 0.3;
//	trapeze1[1] = 0.3;
//	trapeze1[2] = 0.0;
//	trapeze2[0] = 0.3;
//	trapeze2[1] = -0.3;
//	trapeze2[2] = 0.0;
//	trapeze3[0] = -0.5;
//	trapeze3[1] = -0.3;
//	trapeze3[2] = 0.0;
//	trapeze4[0] = -0.3;
//	trapeze4[1] = 0.3;
//	trapeze4[2] = 0.0;
//
//	float axis[3], angle, matrix[9];
//
//	GetAngleAxisBetweenDirections(Zaxis, altNormal, axis, angle);
//	
//	AxisAngle(axis, angle, matrix);
//	RotateVec3(trapeze1, matrix);
//	RotateVec3(trapeze2, matrix);
//	RotateVec3(trapeze3, matrix);
//	RotateVec3(trapeze4, matrix);
//	
//	return true;
//}

void ABCSketchManager::UpdatePointToPlaneDist()
{
	Zdistance = PointToPlaneDist(curr_stylus, planeCenter, Zaxis);
}

bool ABCSketchManager::SketchOn()
{
	isSketchOn = true;
	cerr << "On" << endl;
	return isSketchOn;
}
bool ABCSketchManager::SketchOff()
{
	isSketchOn = false;
	return isSketchOn;
}

void ABCSketchManager::ManipulationOff()
{
	mode = MODE_IDLE;
}

//bool ABCSketchManager::TranslationOn()
//{
//	mode = MODE_TRANSLATION;	
//	return true;
//}

bool ABCSketchManager::SetHaptics()
{
	needForce = true;
	return true;
}

bool ABCSketchManager::CheckHapticsForce()
{
	return true;
}

//float ABCSketchManager::SetPlaneCenter(float *newCenter)
//{
//	newCenter[0] = planeCenter[0];
//	newCenter[1] = planeCenter[1];
//	newCenter[2] = planeCenter[2];
//
//	return newCenter[3];
//}

float ABCSketchManager::SetPivot(float *pivot)
{
	pivot[0] = _pivot[0];
	pivot[1] = _pivot[1];
	pivot[2] = _pivot[2];

	return pivot[3];
}


//bool ABCSketchManager::UndoSketch()
//{
//	if (!Sketch.empty())
//	{
//		mode = UNDO;
//		currentMode.push_back(mode);
//		undoPress++;
//
//		Undo.push_back(Sketch[Sketch.size() - 1]);
//		Sketch[Sketch.size() - 1].Clear();
//		Sketch.erase(Sketch.begin()+Sketch.size()-1);
//		return true;
//	}
//	else return false;
//}

//bool ABCSketchManager::RedoSketch()
//{
//	if (!Undo.empty())
//	{
//		mode = REDO;
//		currentMode.push_back(mode);
//		redoPress++;
//		
//		Curve3 newCrv;
//		Undo.back().CopyTo(newCrv);
//		Sketch.push_back(newCrv);
//		DrawCurve(newCrv);
//		Undo.back().Clear();
//		Undo.erase(Undo.begin() + Undo.size()-1);
//		return true;		
//	}
//	else return false;	
//}

void ABCSketchManager::Render()
{

	
	_UpdateStylus(curr_stylus);
	_UpdateHapStylus(hapcurr_stylus);

	/*cerr << "NormZx->" << altNormal2[0] << endl;
	cerr << "NormZy->" << altNormal2[1] << endl;
	cerr << "NormZz->" << altNormal2[2] << endl;*/

	_UpdateNormal(altNormal);
	_UpdateNormal1(altNormal1);
	_UpdateNormal2(altNormal2);
	//generateNormals();
	RenderRotation();
	//RenderNormals();	

	if (shapeIdentity == 1)shapeName = "Puzzle";
	else if (shapeIdentity == 2)shapeName = "Trapezium";
	else if (shapeIdentity == 3)shapeName = "Jay";
	else if (shapeIdentity == 4)shapeName = "Shoe";	
	
	//float color[4] = { 0.8,0.8,0.8, 0.6 };
	//_drawFloor(3, color);	
	//Render the 3D Depth Grid
	//RenderGrid();	
	//Update();
}

void ABCSketchManager::RenderNormals()
{	
	if (shapeCountPuzzle < 13 && shapeCountTrapeze < 13 && shapeCountJay < 13 && shapeCountShoe < 13)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		DrawCylinder(Origin, Zaxis, 0.08, Red3f, 0.4f, false);
		DrawCylinder(Origin, Yaxis, 0.08, Blue3f, 0.4f, false);
		DrawCylinder(Origin, Xaxis, 0.08, Green3f, 0.4f, false);
		glDisable(GL_BLEND);

		//glBegin(GL_LINES);
		//glColor3fv(Red3f);
		//glVertex3fv(Origin);
		//glVertex3fv(Zaxis);
		//glColor3fv(Green3f);
		//glVertex3fv(Origin);
		//glVertex3fv(Xaxis);
		//glColor3fv(Blue3f);
		//glVertex3fv(Origin);
		//glVertex3fv(Yaxis);
		//glEnd();

		Normalize3(altNormal);
		Normalize3(altNormal1);
		Normalize3(altNormal2);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		DrawCylinder(Origin, altNormal, 0.1, Red3f, 0.6f, true);
		DrawCylinder(Origin, altNormal2, 0.1, Blue3f, 0.6f, true);
		DrawCylinder(Origin, altNormal1, 0.1, Green3f, 0.6f, true);
		glDisable(GL_BLEND);
	}

	//glBegin(GL_LINES);
	//glColor3fv(Red3f);
	//glVertex3fv(Origin);
	//glVertex3fv(altNormal);
	//glColor3fv(Green3f);
	//glVertex3fv(Origin);
	//glVertex3fv(altNormal2);
	//glColor3fv(Blue3f);
	//glVertex3fv(Origin);
	//glVertex3fv(altNormal1);
	//glEnd();
}

int ABCSketchManager::Update()
{

	//UpdatePointToPlaneDist();
	//return mode;
	return 0;
}

int ABCSketchManager::Listen(float *stylus)
{
	UpdateStylus(stylus);
	return Update();
}

int ABCSketchManager::HapListen(float *stylus)
{
	
	UpdateHapticStylus(stylus);

	return 0;
}

void  ABCSketchManager::ComputeError()
{	
	errA = 1 - abs(Dot3(Xaxis, altNormal1));
	errB = 1 - abs(Dot3(Yaxis, altNormal2));
	errC = 1 - abs(Dot3(Zaxis, altNormal));
	//cerr << "Error->" << abs(Dot3(Xaxis, altNormal1)) << endl;

	float NormX, NormY, NormZ, NormAlt;
	NormX = Norm3(Xaxis);
	NormY = Norm3(Yaxis);
	NormZ = Norm3(Zaxis);
	NormAlt = Norm3(altNormal);

	alpha = acosf(Dot3(Xaxis, altNormal) / (NormX*NormAlt));
	beta = acosf(Dot3(Yaxis, altNormal) / (NormY*NormAlt));
	gamma = acosf(Dot3(Zaxis, altNormal) / (NormZ*NormAlt));	
	//cerr << "Direction Cosines are," << "alpha->" << alpha << ",beta->" << beta << ",gamma->" << gamma << endl;
}

bool ABCSketchManager::shapeCounts(int shape)
{
	if (shape == 1 && shapeCountPuzzle < 13)
	{
		shapeCountPuzzle++;
		shapeIteration = to_string(shapeCountPuzzle);
		/*if (shapeCountsquare < 16)
		{			
			cerr << "Square Count->" << shapeCountsquare << endl;
			if (shapeCountsquare == 1) shapeIteration = "1";
			else if (shapeCountsquare == 2) shapeIteration = "2";
			else if (shapeCountsquare == 3) shapeIteration = "3";
		}*/	
		//else { cerr << "Square trials are over" << endl; }
	}
	else if (shape == 2 && shapeCountTrapeze < 13)
	{
		shapeCountTrapeze++;
		shapeIteration = to_string(shapeCountJay);
	/*	if (shapeCountRectB < 16)
		{			
			cerr << "RectB Count->" << shapeCountRectB << endl;
			if (shapeCountRectB == 1) shapeIteration = "1";
			else if (shapeCountRectB == 2) shapeIteration = "2";
			else if (shapeCountRectB == 3) shapeIteration = "3";			
		}*/
		//else { cerr << "RectB trials are over" << endl; }
	}		
	else if (shape == 3 && shapeCountJay < 13)
	{
		shapeCountJay++;
		shapeIteration = to_string(shapeCountJay);
		/*if (shapeCountRectH < 16)
		{			
			cerr << "RectH Count->" << shapeCountRectH << endl;
			if (shapeCountRectH == 1) shapeIteration = "1";
			else if (shapeCountRectH == 2) shapeIteration = "2";
			else if (shapeCountRectH == 3) shapeIteration = "3";
		}*/
		//else { cerr << "RectH trials are over" << endl; }
	}

	else if (shape == 4 && shapeCountShoe < 13)
	{
		shapeCountShoe++;
		shapeIteration = to_string(shapeCountShoe);
		/*if (shapeCountTrapeze < 16)
		{			
			cerr << "Trapezium Count->" << shapeCountTrapeze << endl;
			if (shapeCountTrapeze == 1) shapeIteration = "1";
			else if (shapeCountTrapeze == 2) shapeIteration = "2";
			else if (shapeCountTrapeze == 3) shapeIteration = "3";			
		}*/
		//else { cerr << "Trapezium trials are over" << endl; }
	}
	else if (shapeCountPuzzle > 12 && shapeCountTrapeze > 12 && shapeCountJay > 12 && shapeCountShoe > 12)
	{ 
		cerr << "Puzzle->" << shapeCountPuzzle << endl;
		cerr << "Trz->" << shapeCountTrapeze << endl;
		cerr << "Jay->" << shapeCountJay << endl;
		cerr << "Shoe->" << shapeCountShoe << endl;
		cerr << "All Trials are over" << endl; 
	}
	return true;
}

bool ABCSketchManager::SaveLog()
{
	ofstream myfile;
	myfile.open(rotationType + "_User_" + userID + "_" + shapeName + "_" + shapeIteration + ".txt");
	time_elapsed = float(_stylusmov[_stylusmov.size() - 1] - _stylusmov[0]) / CLOCKS_PER_SEC;
	myfile << "mode->" << currentMode.size() << endl;
	//myfile << "Normal->" << _altnormals.size() << endl;
	myfile << "Time Elapsed " << time_elapsed << " " << "secs" << endl;
	myfile << "ErrorZ " << errC << endl;
	myfile << "ErrorY " << errB << endl;
	myfile << "ErrorX " << errA << endl;
	myfile << "DirCos: " << alpha << "," << beta << "," << gamma << endl;
	myfile << "InitNormalVecZ " << initNormal[0] << "," << initNormal[1] << "," << initNormal[2] << endl;
	myfile << "FinNormalVecZ " << altNormal[0] << "," << altNormal[1] << "," << altNormal[2] << endl;
	myfile << "InitNormalVecY " << initNormal2[0] << "," << initNormal2[1] << "," << initNormal2[2] << endl;
	myfile << "FinNormalVecY " << altNormal2[0] << "," << altNormal2[1] << "," << altNormal2[2] << endl;
	myfile << "InitNormalVecX " << initNormal1[0] << "," << initNormal1[1] << "," << initNormal1[2] << endl;
	myfile << "FinNormalVecX " << altNormal1[0] << "," << altNormal1[1] << "," << altNormal1[2] << endl;
	myfile << "Total Rotation " << clicks << endl;
	
	myfile << "Mode_TYPE" << " " << "StyX" << " " << "StyY" << " " << "StyZ" << " " << "HapStyX" << " " << "HapStyY" << " " << "HapStyZ" <<" "<< "NormalZx"<<" "<<"NormalZy"<<" "<<"NormalZz"<<" "<<"NormalXx" <<" "<<"NormalXy"<< " " << "NormalXz" << "NormalYx" << " " << "NormalYy" << " " << "NormalYz" << " "<<"Stylus_TimeStamp" << endl;
	for (int i = 0; i < currentMode.size(); i++)
	{

		myfile << currentMode[i] << " " << styl[i].data[0] << " " << styl[i].data[1] << " " << styl[i].data[2] << " " << hapstyl[i].data[0] << " " << hapstyl[i].data[1] << " " << hapstyl[i].data[2] << " "<<_altnormals[i].data[0]<<" "<<_altnormals[i].data[1]<<" "<<_altnormals[i].data[2]<<" "<< _altnormal2s[i].data[0] << " " << _altnormal2s[i].data[1] << " " << _altnormal2s[i].data[2] << " "<<_altnormal1s[i].data[0] << " " << _altnormal1s[i].data[1] << " " << _altnormal1s[i].data[2] << " "<<_stylusmov[i] << endl;
	}
	/*for (int i = 0; i < currentMode.size(); i++)
	{*/
		
	styl.clear();
	hapstyl.clear();
	currentMode.clear();
	_altnormals.clear();
	_altnormal1s.clear();
	_altnormal2s.clear();


		//myfile << currentMode[i] << " " << sty[i].data[0] << " " << sty[i].data[1] << " " << sty[i].data[2] << " " << hapsty[i].data[0] << " " << hapsty[i].data[1] << " " << hapsty[i].data[2] << " " << stylusmov[i] << endl;
		//myfile << altNormals[i].data[0] << " " << altNormals[i].data[1] << " " << altNormals[i].data[2] << " " << altNormal1s[i].data[0] << " " << altNormal1s[i].data[1] << " " << altNormal1s[i].data[2] << " " << stylusmov[i] << endl;
	
	//}
	//myfile << "Event" << " " << "Traj" << "Xl" << "Yl" << "Zl" << " " << "Xg" << "Yg" << "Zgl" << " " << "NormZX" << "NormZY" << " " << "NormZZ" << "NormXX" << " " << "NormXY" << "NormXZ" << endl;
	/*for (int i = 0; i < currentMode.size(); i++)
	{
		if (currentMode[i] == 0)
		{
			myfile << currentMode[i] << " " << " " << " " << sty[i].data[0] << " " << sty[i].data[1] << " " << sty[i].data[2] << " " <<
				hapsty[i].data[0] << " " << hapsty[i].data[1] << " " << hapsty[i].data[2] << " " <<
				altNormals[i].data[0] << " " << altNormals[i].data[1] << " " << altNormals[i].data[1] << " " <<
				altNormal1s[i].data[0] << " " << altNormal1s[i].data[1] << " " << altNormal1s[i].data[2] << endl;
		}
		else if (currentMode[i] == 2)
		{
			for (int j = 0; j < Traj.size(); i++)
			{
				myfile << currentMode[i] << " " << j << " " << sty[i].data[0] << " " << sty[i].data[1] << " " << sty[i].data[2] << " " <<
					hapsty[i].data[0] << " " << hapsty[i].data[1] << " " << hapsty[i].data[2] << " " <<
					altNormals[i].data[0] << " " << altNormals[i].data[1] << " " << altNormals[i].data[1] << " " <<
					altNormal1s[i].data[0] << " " << altNormal1s[i].data[1] << " " << altNormal1s[i].data[2] << endl;
			}
		}
}

		
	/*myfile << "Rotation Coordinates are->" << endl;
	for (int i = 0; i < Traj.size(); i++)
	{
		myfile << "Traj "<< i+1 << endl;
		for (int j = 0; j < Traj[i].GetNumVertices(); j++)
		{
			float temp[3];
			Traj[i].GetVertex(j, temp);			
			myfile << temp[0] << "," << temp[1] << "," << temp[2] << endl;
		}
	}*/
	return true;
}

bool ABCSketchManager::SaveMesh()
{
	ofstream myfile;
	myfile.open(rotationType + "_User_" + userID + "_" + shapeName + "_" + shapeIteration + ".ply");
	myfile << "ply" << endl;
	myfile << "format ascii 1.0" << endl;
	myfile << "comment VCGLIB generated" << endl;
	myfile << "element vertex" << " " << meshEvent2->GetNumVert() << endl;
	myfile << "property float x" << endl;
	myfile << "property float y" << endl;
	myfile << "property float z" << endl;
	myfile << "property float nx" << endl;
	myfile << "property float ny" << endl;
	myfile << "property float nz" << endl;
	myfile << "element face" << " " << meshEvent2->GetNumFaces() << endl;
	myfile << "property list uchar int vertex_indices" << endl;
	myfile << "end_header" << endl;
	for (int i = 0; i < meshEvent2->GetNumVert(); i++)
	{
		float pos[3], norm[3];
		meshEvent2->GetVertPosition(i, pos);
		meshEvent2->GetVertNormal(i, norm);
		myfile << pos[0] << " " << pos[1] << " " << pos[2] << " " << norm[0] << " " << norm[1] << " " << norm[2] << endl;
	}
	for (int j = 0; j < meshEvent2->GetNumFaces(); j++)
	{
		int temp[3];
		meshEvent2->GetVertIdxForFace(j, temp);
		myfile << "3" << " " << temp[0] << " " << temp[1] << " " << temp[2] << endl;
	}
	return true;
}

