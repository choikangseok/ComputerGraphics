#pragma once

//#undef WIN32
#include <vector>
#include <map>
#include <string>
#include "ase.h"
#include <GL/glut.h>

using namespace  std;




class  BVH
{

public:
	Mesh *Head;        // 로봇의 몸 부위 객체
	Mesh *Body;
	Mesh *RightArm;
	Mesh *RightHand;
	Mesh *LeftArm;
	Mesh *LeftHand;
	Mesh *RightLeg;
	Mesh *RightFoot;
	Mesh *LeftLeg;
	Mesh *LeftFoot;
	Mesh *Sword;
	Mesh *Shield;
	Mesh *Diamond;
	int	 drawO;
	bool drawD;


	void meshLoad(){      // mesh 의 회전방향, 이동 위치 좌표를 초기화
		Head = new Mesh();
		Head->readAse("S_Head.ASE");

		Diamond = new Mesh();
		Diamond->readAse("S_Diamond.ASE");

		Shield = new Mesh();
		Shield->readAse("S_Shield.ASE");

		Sword = new Mesh();
		Sword->readAse("S_Sword.ASE");

		Body = new Mesh();
		Body->readAse("S_Body.ASE");

		RightArm = new Mesh();
		RightArm->readAse("S_RightArm.ASE");

		RightHand = new Mesh();
		RightHand->readAse("S_RightHand.ASE");

		LeftArm = new Mesh();
		LeftArm->readAse("S_LeftArm.ASE");

		LeftHand = new Mesh();
		LeftHand->readAse("S_LeftHand.ASE");

		RightLeg = new Mesh();
		RightLeg->readAse("S_RightLeg.ASE");

		RightFoot = new Mesh();
		RightFoot->readAse("S_RightFoot.ASE");

		LeftLeg = new Mesh();
		LeftLeg->readAse("S_LeftLeg.ASE");

		LeftFoot = new Mesh();
		LeftFoot->readAse("S_LeftFoot.ASE");
	}



	enum  ChannelEnum {
		X_ROTATION, Y_ROTATION, Z_ROTATION,
		X_POSITION, Y_POSITION, Z_POSITION
	};
	struct  Joint;

	struct  Channel {
		Joint *              joint;
		ChannelEnum          type;
		int                  index;
	};

	struct  Joint {
		string               name;
		int                  index;
		Joint *              parent;
		vector< Joint * >    children;
		double               offset[3];
		bool                 has_site;
		double               site[3];
		vector< Channel * >  channels;
	};

private:
	bool                     is_load_success;
	//int						 draws;
	//int						 drawO;
	string                   file_name;   
	string                   motion_name; 

	int                      num_channel; 
	vector< Channel * >      channels;    
	vector< Joint * >        joints;      
	map< string, Joint * >   joint_index; 

	int                      num_frame;   
	double                   interval;    
	double *                 motion;      


public:
	BVH();
	BVH( const char * bvh_file_name );
	~BVH();

	void  Clear();

	void  Load( const char * bvh_file_name );

public:
	bool  IsLoadSuccess() const { return is_load_success; }

	const string &  GetFileName() const { return file_name; }
	const string &  GetMotionName() const { return motion_name; }

	const int       GetNumJoint() const { return  joints.size(); }
	const Joint *   GetJoint( int no ) const { return  joints[no]; }
	const int       GetNumChannel() const { return  channels.size(); }
	const Channel * GetChannel( int no ) const { return  channels[no]; }

	const Joint *   GetJoint( const string & j ) const  {
		map< string, Joint * >::const_iterator  i = joint_index.find( j );
		return  ( i != joint_index.end() ) ? (*i).second : NULL; }
	const Joint *   GetJoint( const char * j ) const  {
		map< string, Joint * >::const_iterator  i = joint_index.find( j );
		return  ( i != joint_index.end() ) ? (*i).second : NULL; }

	int     GetNumFrame() const { return  num_frame; }
	double  GetInterval() const { return  interval; }
	double  GetMotion( int f, int c ) const { return  motion[ f*num_channel + c ]; }

	void  SetMotion( int f, int c, double v ) { motion[ f*num_channel + c ] = v; }

public:
	void  RenderFigure( int drawS, int frame_no, float scale = 1.0f );
	void  RenderFigure( int drawS, const Joint * root, const double * data, float scale = 1.0f );
	void  RenderBone(int flag, float x0, float y0, float z0, float x1, float y1, float z1, int drawS );


	void drawHead(){
		if(drawO == 0){
			glBegin(GL_LINES);
		}else if(drawO == 1){
			glBegin(GL_POINTS);
		}else{
			glBegin(GL_TRIANGLES);
		}
		glColor3f(1.0, 1.0, 1.0);
		for(int i=0; i<Head->faceNum; i++){

			glNormal3f(Head->normalList[i].faceNormal[0], Head->normalList[i].faceNormal[1], Head->normalList[i].faceNormal[2]);

			glVertex3f(Head->vertexList[Head->faceList[i].vertexIndex[0]].x /100 , 
				Head->vertexList[Head->faceList[i].vertexIndex[0]].y /100, 
				Head->vertexList[Head->faceList[i].vertexIndex[0]].z /100);	

			glVertex3f(Head->vertexList[Head->faceList[i].vertexIndex[1]].x /100, 
				Head->vertexList[Head->faceList[i].vertexIndex[1]].y /100, 
				Head->vertexList[Head->faceList[i].vertexIndex[1]].z /100);

			glVertex3f(Head->vertexList[Head->faceList[i].vertexIndex[2]].x /100, 
				Head->vertexList[Head->faceList[i].vertexIndex[2]].y /100, 
				Head->vertexList[Head->faceList[i].vertexIndex[2]].z /100);
		}
		glEnd( );
	}
	void drawRightArm(){
		if(drawO == 0){
			glBegin(GL_LINES);
		}else if(drawO == 1){
			glBegin(GL_POINTS);
		}else{
			glBegin(GL_TRIANGLES);
		}
		glColor3f(1.0, 1.0, 0.7);
		for(int i=0; i<RightArm->faceNum; i++){
			glNormal3f(RightArm->normalList[i].faceNormal[0], RightArm->normalList[i].faceNormal[1], RightArm->normalList[i].faceNormal[2]);

			glVertex3f(RightArm->vertexList[RightArm->faceList[i].vertexIndex[0]].x / 100, 
				RightArm->vertexList[RightArm->faceList[i].vertexIndex[0]].y / 100, 
				RightArm->vertexList[RightArm->faceList[i].vertexIndex[0]].z / 100);	

			glVertex3f(RightArm->vertexList[RightArm->faceList[i].vertexIndex[1]].x / 100, 
				RightArm->vertexList[RightArm->faceList[i].vertexIndex[1]].y / 100, 
				RightArm->vertexList[RightArm->faceList[i].vertexIndex[1]].z / 100);

			glVertex3f(RightArm->vertexList[RightArm->faceList[i].vertexIndex[2]].x / 100, 
				RightArm->vertexList[RightArm->faceList[i].vertexIndex[2]].y / 100, 
				RightArm->vertexList[RightArm->faceList[i].vertexIndex[2]].z / 100);
			glRotatef(90, 0.0, 1.0, 1.0);
		}
		glEnd( );
	}
	void drawBody(){
		if(drawO == 0){
			glBegin(GL_LINES);
		}else if(drawO == 1){
			glBegin(GL_POINTS);
		}else{
			glBegin(GL_TRIANGLES);
		}
		glColor3f(1.0, 1.0, 0.5);
		for(int i=0; i<Body->faceNum; i++){
			glNormal3f(Body->normalList[i].faceNormal[0], Body->normalList[i].faceNormal[1], Body->normalList[i].faceNormal[2]);

			glVertex3f(Body->vertexList[Body->faceList[i].vertexIndex[0]].x / 100, 
				Body->vertexList[Body->faceList[i].vertexIndex[0]].y / 100, 
				Body->vertexList[Body->faceList[i].vertexIndex[0]].z / 100);	

			glVertex3f(Body->vertexList[Body->faceList[i].vertexIndex[1]].x / 100, 
				Body->vertexList[Body->faceList[i].vertexIndex[1]].y / 100, 
				Body->vertexList[Body->faceList[i].vertexIndex[1]].z / 100);

			glVertex3f(Body->vertexList[Body->faceList[i].vertexIndex[2]].x / 100, 
				Body->vertexList[Body->faceList[i].vertexIndex[2]].y / 100, 
				Body->vertexList[Body->faceList[i].vertexIndex[2]].z / 100);
		}
		glEnd( );
	}
	void drawRightHand(){
		if(drawO == 0){
			glBegin(GL_LINES);
		}else if(drawO == 1){
			glBegin(GL_POINTS);
		}else{
			glBegin(GL_TRIANGLES);
		}
		glColor3f(0.9, 0.8, 0.6);
		for(int i=0; i<RightHand->faceNum; i++){
			glNormal3f(RightHand->normalList[i].faceNormal[0], RightHand->normalList[i].faceNormal[1], RightHand->normalList[i].faceNormal[2]);

			glVertex3f(RightHand->vertexList[RightHand->faceList[i].vertexIndex[0]].x / 100, 
				RightHand->vertexList[RightHand->faceList[i].vertexIndex[0]].y / 100, 
				RightHand->vertexList[RightHand->faceList[i].vertexIndex[0]].z / 100);	

			glVertex3f(RightHand->vertexList[RightHand->faceList[i].vertexIndex[1]].x / 100, 
				RightHand->vertexList[RightHand->faceList[i].vertexIndex[1]].y / 100, 
				RightHand->vertexList[RightHand->faceList[i].vertexIndex[1]].z / 100);

			glVertex3f(RightHand->vertexList[RightHand->faceList[i].vertexIndex[2]].x / 100, 
				RightHand->vertexList[RightHand->faceList[i].vertexIndex[2]].y / 100, 
				RightHand->vertexList[RightHand->faceList[i].vertexIndex[2]].z / 100);

		}
		glEnd( );
	}
	void drawLeftArm(){
		if(drawO == 0){
			glBegin(GL_LINES);
		}else if(drawO == 1){
			glBegin(GL_POINTS);
		}else{
			glBegin(GL_TRIANGLES);
		}
		glColor3f(1.0, 1.0, 0.7);
		for(int i=0; i<LeftArm->faceNum; i++){
			glNormal3f(LeftArm->normalList[i].faceNormal[0], LeftArm->normalList[i].faceNormal[1], LeftArm->normalList[i].faceNormal[2]);

			glVertex3f(LeftArm->vertexList[LeftArm->faceList[i].vertexIndex[0]].x / 100, 
				LeftArm->vertexList[LeftArm->faceList[i].vertexIndex[0]].y / 100, 
				LeftArm->vertexList[LeftArm->faceList[i].vertexIndex[0]].z / 100);	

			glVertex3f(LeftArm->vertexList[LeftArm->faceList[i].vertexIndex[1]].x / 100, 
				LeftArm->vertexList[LeftArm->faceList[i].vertexIndex[1]].y / 100, 
				LeftArm->vertexList[LeftArm->faceList[i].vertexIndex[1]].z / 100);

			glVertex3f(LeftArm->vertexList[LeftArm->faceList[i].vertexIndex[2]].x / 100, 
				LeftArm->vertexList[LeftArm->faceList[i].vertexIndex[2]].y / 100, 
				LeftArm->vertexList[LeftArm->faceList[i].vertexIndex[2]].z / 100);
		}
		glEnd( );
	}
	void drawLeftHand(){
		if(drawO == 0){
			glBegin(GL_LINES);
		}else if(drawO == 1){
			glBegin(GL_POINTS);
		}else{
			glBegin(GL_TRIANGLES);
		}
		glColor3f(0.9, 0.8, 0.6);
		for(int i=0; i<LeftHand->faceNum; i++){
			glNormal3f(LeftHand->normalList[i].faceNormal[0], LeftHand->normalList[i].faceNormal[1], LeftHand->normalList[i].faceNormal[2]);

			glVertex3f(LeftHand->vertexList[LeftHand->faceList[i].vertexIndex[0]].x / 100, 
				LeftHand->vertexList[LeftHand->faceList[i].vertexIndex[0]].y / 100, 
				LeftHand->vertexList[LeftHand->faceList[i].vertexIndex[0]].z / 100);	

			glVertex3f(LeftHand->vertexList[LeftHand->faceList[i].vertexIndex[1]].x / 100, 
				LeftHand->vertexList[LeftHand->faceList[i].vertexIndex[1]].y / 100, 
				LeftHand->vertexList[LeftHand->faceList[i].vertexIndex[1]].z / 100);

			glVertex3f(LeftHand->vertexList[LeftHand->faceList[i].vertexIndex[2]].x / 100, 
				LeftHand->vertexList[LeftHand->faceList[i].vertexIndex[2]].y / 100, 
				LeftHand->vertexList[LeftHand->faceList[i].vertexIndex[2]].z / 100);
		}
		glEnd( );
	}
	void drawRightLeg(){
		if(drawO == 0){
			glBegin(GL_LINES);
		}else if(drawO == 1){
			glBegin(GL_POINTS);
		}else{
			glBegin(GL_TRIANGLES);
		}
		glColor3f(1.0, 1.0, 0.7);
		for(int i=0; i<RightLeg->faceNum; i++){
			glNormal3f(RightLeg->normalList[i].faceNormal[0], RightLeg->normalList[i].faceNormal[1], RightLeg->normalList[i].faceNormal[2]);

			glVertex3f(RightLeg->vertexList[RightLeg->faceList[i].vertexIndex[0]].x / 100, 
				RightLeg->vertexList[RightLeg->faceList[i].vertexIndex[0]].y / 100, 
				RightLeg->vertexList[RightLeg->faceList[i].vertexIndex[0]].z / 100);	

			glVertex3f(RightLeg->vertexList[RightLeg->faceList[i].vertexIndex[1]].x / 100, 
				RightLeg->vertexList[RightLeg->faceList[i].vertexIndex[1]].y / 100, 
				RightLeg->vertexList[RightLeg->faceList[i].vertexIndex[1]].z / 100);

			glVertex3f(RightLeg->vertexList[RightLeg->faceList[i].vertexIndex[2]].x / 100, 
				RightLeg->vertexList[RightLeg->faceList[i].vertexIndex[2]].y / 100, 
				RightLeg->vertexList[RightLeg->faceList[i].vertexIndex[2]].z / 100);
		}
		glEnd( );
	}
	void drawSword(){

		if(drawO == 0){
			glBegin(GL_LINES);
		}else if(drawO == 1){
			glBegin(GL_POINTS);
		}else{
			glBegin(GL_TRIANGLES);
		}	
		glColor3f(1.0, 0.2, 0.3);

		for(int i=0; i<Sword->faceNum; i++){
			glNormal3f(Sword->normalList[i].faceNormal[0], Sword->normalList[i].faceNormal[1], Sword->normalList[i].faceNormal[2]);

			glVertex3f(Sword->vertexList[Sword->faceList[i].vertexIndex[0]].x / 50, 
				Sword->vertexList[Sword->faceList[i].vertexIndex[0]].y / 50, 
				Sword->vertexList[Sword->faceList[i].vertexIndex[0]].z / 50);	

			glVertex3f(Sword->vertexList[Sword->faceList[i].vertexIndex[1]].x / 50, 
				Sword->vertexList[Sword->faceList[i].vertexIndex[1]].y / 50, 
				Sword->vertexList[Sword->faceList[i].vertexIndex[1]].z / 50);

			glVertex3f(Sword->vertexList[Sword->faceList[i].vertexIndex[2]].x / 50, 
				Sword->vertexList[Sword->faceList[i].vertexIndex[2]].y / 50, 
				Sword->vertexList[Sword->faceList[i].vertexIndex[2]].z / 50);
		}
		glEnd( );

	}
	void drawShield(){
		if(drawO == 0){
			glBegin(GL_LINES);
		}else if(drawO == 1){
			glBegin(GL_POINTS);
		}else{
			glBegin(GL_TRIANGLES);
		}	
		glColor3f(0.2 , 0.2, 0.8);
		for(int i=0; i<Shield->faceNum; i++){
			glNormal3f(Shield->normalList[i].faceNormal[0], Shield->normalList[i].faceNormal[1], Shield->normalList[i].faceNormal[2]);

			glVertex3f(Shield->vertexList[Shield->faceList[i].vertexIndex[0]].x / 130, 
				Shield->vertexList[Shield->faceList[i].vertexIndex[0]].y / 130, 
				Shield->vertexList[Shield->faceList[i].vertexIndex[0]].z / 130);	

			glVertex3f(Shield->vertexList[Shield->faceList[i].vertexIndex[1]].x / 130, 
				Shield->vertexList[Shield->faceList[i].vertexIndex[1]].y / 130, 
				Shield->vertexList[Shield->faceList[i].vertexIndex[1]].z / 130);

			glVertex3f(Shield->vertexList[Shield->faceList[i].vertexIndex[2]].x / 130, 
				Shield->vertexList[Shield->faceList[i].vertexIndex[2]].y / 130, 
				Shield->vertexList[Shield->faceList[i].vertexIndex[2]].z / 130);
		}
		glEnd( );
	}
	void drawRightFoot(){
		if(drawO == 0){
			glBegin(GL_LINES);
		}else if(drawO == 1){
			glBegin(GL_POINTS);
		}else{
			glBegin(GL_TRIANGLES);
		}	
		glColor3f(0.9, 0.8, 0.6);
		for(int i=0; i<RightFoot->faceNum; i++){
			glNormal3f(RightFoot->normalList[i].faceNormal[0], RightFoot->normalList[i].faceNormal[1], RightFoot->normalList[i].faceNormal[2]);

			glVertex3f(RightFoot->vertexList[RightFoot->faceList[i].vertexIndex[0]].x / 100, 
				RightFoot->vertexList[RightFoot->faceList[i].vertexIndex[0]].y / 100, 
				RightFoot->vertexList[RightFoot->faceList[i].vertexIndex[0]].z / 100);	

			glVertex3f(RightFoot->vertexList[RightFoot->faceList[i].vertexIndex[1]].x / 100, 
				RightFoot->vertexList[RightFoot->faceList[i].vertexIndex[1]].y / 100, 
				RightFoot->vertexList[RightFoot->faceList[i].vertexIndex[1]].z / 100);

			glVertex3f(RightFoot->vertexList[RightFoot->faceList[i].vertexIndex[2]].x / 100, 
				RightFoot->vertexList[RightFoot->faceList[i].vertexIndex[2]].y / 100, 
				RightFoot->vertexList[RightFoot->faceList[i].vertexIndex[2]].z / 100);
		}
		glEnd( );
	}
	void drawLeftLeg(){
		if(drawO == 0){
			glBegin(GL_LINES);
		}else if(drawO == 1){
			glBegin(GL_POINTS);
		}else{
			glBegin(GL_TRIANGLES);
		}	
		glColor3f(1.0, 1.0, 0.7);
		for(int i=0; i<LeftLeg->faceNum; i++){
			glNormal3f(LeftLeg->normalList[i].faceNormal[0], LeftLeg->normalList[i].faceNormal[1], LeftLeg->normalList[i].faceNormal[2]);

			glVertex3f(LeftLeg->vertexList[LeftLeg->faceList[i].vertexIndex[0]].x / 100, 
				LeftLeg->vertexList[LeftLeg->faceList[i].vertexIndex[0]].y / 100, 
				LeftLeg->vertexList[LeftLeg->faceList[i].vertexIndex[0]].z / 100);	

			glVertex3f(LeftLeg->vertexList[LeftLeg->faceList[i].vertexIndex[1]].x / 100, 
				LeftLeg->vertexList[LeftLeg->faceList[i].vertexIndex[1]].y / 100, 
				LeftLeg->vertexList[LeftLeg->faceList[i].vertexIndex[1]].z / 100);

			glVertex3f(LeftLeg->vertexList[LeftLeg->faceList[i].vertexIndex[2]].x / 100, 
				LeftLeg->vertexList[LeftLeg->faceList[i].vertexIndex[2]].y / 100, 
				LeftLeg->vertexList[LeftLeg->faceList[i].vertexIndex[2]].z / 100);
		}
		glEnd();
	}
	void drawDiamond(){
		if(drawD==true){
			if(drawO == 0){
				glBegin(GL_LINES);
			}else if(drawO == 1){
				glBegin(GL_POINTS);
			}else{
				glBegin(GL_TRIANGLES);
			}	
			glColor3f(0.8, 0.8, 0.8);
			for(int i=0; i<Diamond->faceNum; i++){

				glNormal3f(Diamond->normalList[i].faceNormal[0], Diamond->normalList[i].faceNormal[1], Diamond->normalList[i].faceNormal[2]);
				glVertex3f(Diamond->vertexList[Diamond->faceList[i].vertexIndex[0]].x / 100, 
					Diamond->vertexList[Diamond->faceList[i].vertexIndex[0]].y / 100, 
					Diamond->vertexList[Diamond->faceList[i].vertexIndex[0]].z / 100);	
				glVertex3f(Diamond->vertexList[Diamond->faceList[i].vertexIndex[1]].x / 100, 
					Diamond->vertexList[Diamond->faceList[i].vertexIndex[1]].y / 100, 
					Diamond->vertexList[Diamond->faceList[i].vertexIndex[1]].z / 100);
				glVertex3f(Diamond->vertexList[Diamond->faceList[i].vertexIndex[2]].x / 100, 
					Diamond->vertexList[Diamond->faceList[i].vertexIndex[2]].y / 100, 
					Diamond->vertexList[Diamond->faceList[i].vertexIndex[2]].z / 100);
				glTranslatef(0.0, 1000.0, 0.0);

			}
			glEnd( );
		}
	}
	void drawLeftFoot(){
		if(drawO == 0){
			glBegin(GL_LINES);
		}else if(drawO == 1){
			glBegin(GL_POINTS);
		}else{
			glBegin(GL_TRIANGLES);
		}	
		glColor3f(0.9, 0.8, 0.6);
		for(int i=0; i<LeftFoot->faceNum; i++){

			glNormal3f(LeftFoot->normalList[i].faceNormal[0], LeftFoot->normalList[i].faceNormal[1], LeftFoot->normalList[i].faceNormal[2]);
			glVertex3f(LeftFoot->vertexList[LeftFoot->faceList[i].vertexIndex[0]].x / 100, 
				LeftFoot->vertexList[LeftFoot->faceList[i].vertexIndex[0]].y / 100, 
				LeftFoot->vertexList[LeftFoot->faceList[i].vertexIndex[0]].z / 100);	
			glVertex3f(LeftFoot->vertexList[LeftFoot->faceList[i].vertexIndex[1]].x / 100, 
				LeftFoot->vertexList[LeftFoot->faceList[i].vertexIndex[1]].y / 100, 
				LeftFoot->vertexList[LeftFoot->faceList[i].vertexIndex[1]].z / 100);
			glVertex3f(LeftFoot->vertexList[LeftFoot->faceList[i].vertexIndex[2]].x / 100, 
				LeftFoot->vertexList[LeftFoot->faceList[i].vertexIndex[2]].y / 100, 
				LeftFoot->vertexList[LeftFoot->faceList[i].vertexIndex[2]].z / 100);
			glTranslatef(0.0, 1000.0, 0.0);

		}
		glEnd( );
	}
};
