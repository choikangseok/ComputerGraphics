
#ifdef  WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "BVH.h"

static float   camera_yaw = 0.0f;      
static float   camera_pitch = -45.0f;  
static float   camera_distance = 20.0f; 


static int     drag_mouse_r = 0;
static int     drag_mouse_l = 0;
static int     drag_mouse_m = 0;
static int     last_mouse_x, last_mouse_y;
static int     win_width, win_height;
static int Loption=0;
static int Moption=0;
float windowX = 640;
float windowY = 640;

int drawS=0;
int drawO=0;
bool drawD=false;
static bool View4Option=false;

bool   on_animation = true;
float  animation_time = 0.0f;
int    frame_no = 0;
int Lookset=0;
BVH *   bvh = NULL;


void  drawMessage( int line_no, const char * message )
{
	int   i;
	if ( message == NULL )
		return;

	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D( 0.0, win_width, win_height, 0.0 );

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();

	glDisable( GL_DEPTH_TEST );
	glDisable( GL_LIGHTING );

	glColor3f( 1.0, 1.0, 0.0 );
	glRasterPos2i( 8, 24 + 18 * line_no );
	for ( i=0; message[i]!='\0'; i++ )
		glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, message[i] );

	glEnable( GL_DEPTH_TEST );
	glEnable( GL_LIGHTING );
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();
}
/*
void setCamera(float EyeX, float EyeY, float EyeZ, float AtX, float AtY, float AtZ, float UpX, float UpY, float UpZ){
camEyeX = EyeX;
camEyeY = EyeY;
camEyeZ = EyeZ;
camAtX = AtX;
camAtY = AtY;
camAtZ = AtZ;
camUpX = UpX;
camUpY = UpY;
camUpZ = UpZ;
}
*/

void plate(){

	float  size = 1.5f;
	int  num_x = 10, num_z = 10;
	double  ox, oz;

	glPushMatrix();
	glBegin( GL_QUADS );
	glNormal3d( 1.0, 1.0, 0.0 );
	ox = -(num_x * size) / 2;
	for ( int x=0; x<num_x; x++, ox+=size )
	{
		oz = -(num_z * size) / 2;
		for ( int z=0; z<num_z; z++, oz+=size )
		{
			if ( ((x + z) % 2) == 0 )
				glColor3f( 1.0, 0.4, 0.1 );
			else
				glColor3f( 0.8, 0.8, 0.8 );
			glVertex3d( ox, -0.5, oz );
			glVertex3d( ox, -0.5, oz+size );
			glVertex3d( ox+size, -0.5, oz+size );
			glVertex3d( ox+size, -0.5, oz );
		}
	}
	glEnd();
	glPopMatrix();
}
void drawRobot(){
	//float  light0_position[] = { 10.0, 10.0, 10.0, 1.0 };
	//glLightfv( GL_LIGHT0, GL_POSITION, light0_position );

	if ( bvh )
		bvh->RenderFigure(drawS, frame_no, 0.02f );

	char  message[ 64 ];
	if ( bvh )
		sprintf( message, "%.2f (%d)", animation_time, frame_no );

}


void  display( void )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
	
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	if(Lookset==1){
		gluLookAt(6.0, 4.0, 5.0,  4.0, 3.0, -2.0,  0.0, 1.0, 0.0);
	}
	if(Lookset==2){
		gluLookAt(-6.0, 4.0, 5.0,  -4.0, 3.0, -2.0,  0.0, 1.0, 0.0 );

	}
	if(View4Option==false){

		glViewport(0, 0, windowX, windowY);
		glPushMatrix();

		glPushMatrix();

		glTranslatef( 0.0, 0.0, - camera_distance );
		glRotatef(-45, 1.0, 0.0, 0.0);

		glRotatef(  -camera_pitch, 1.0, 0.0, 0.0 );
		glRotatef( - camera_yaw, 0.0, 1.0, 0.0 );
		glTranslatef( 0.0, -0.5, 0.0 );

		drawRobot();                  // 로봇 출력
		plate();
		glPopMatrix();

		glPopMatrix();
	}
	//시점 변환

	if(View4Option==true){
		glViewport(0, windowY/2, windowX/2, windowY/2);        // 1 뷰포트

		glPushMatrix();

		glPushMatrix();

		glTranslatef( 0.0, 0.0, - camera_distance );
		glRotatef(-45, 1.0, 0.0, 0.0);

		glRotatef(  -camera_pitch, 1.0, 0.0, 0.0 );
		glRotatef( - camera_yaw, 0.0, 1.0, 0.0 );
		glTranslatef( 0.0, -0.5, 0.0 );

		drawRobot();                  // 로봇 출력
		plate();
		glPopMatrix();

		glPopMatrix();

		glViewport(windowX/2, windowY/2, windowX/2, windowY/2);  // 2 뷰포트
		glPushMatrix();

		glPushMatrix();

		glTranslatef( 0.0, 0.0, - camera_distance );
		glRotatef(-90, 0.0, 1.0, 0.0);
		glRotatef(-45, 1, 0.0, 0.0);
		glRotatef( -camera_pitch, 1.0, 0.0, 0.0 );
		glRotatef( - camera_yaw, 0.0, 1.0, 0.0 );
		glTranslatef( 0.0, -0.5, 0.0 );

		drawRobot();                  // 로봇 출력
		plate();
		glPopMatrix();

		glPopMatrix();

		glViewport(0, 0, windowX/2, windowY/2);  // 3 뷰포트
		glPushMatrix();

		glPushMatrix();

		glTranslatef( 0.0, 0.0, - camera_distance );
		glRotatef(45, 1.0, 0.0, 0.0);
		glRotatef( -camera_pitch, 1.0, 0.0, 0.0 );
		glRotatef( - camera_yaw, 0.0, 1.0, 0.0 );
		glTranslatef( 0.0, -0.5, 0.0 );

		drawRobot();                  // 로봇 출력
		plate();
		glPopMatrix();

		glPopMatrix();


		glViewport(windowX/2, 0, windowX/2, windowY/2);  // 4 뷰포트
		glPushMatrix();

		glPushMatrix();

		glTranslatef( 0.0, 0.0, - camera_distance );
		glRotatef( - camera_pitch, 1.0, 0.0, 0.0 );
		glRotatef( - camera_yaw, 0.0, 1.0, 0.0 );
		glTranslatef( 0.0, -0.5, 0.0 );

		drawRobot();                  // 로봇 출력
		plate();
		glPopMatrix();

		glPopMatrix();
	}
	glutSwapBuffers();
}



void  reshape( int w, int h )
{
	glViewport(0, 0, w, h);

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 45, (double)w/h, 1, 500 );

	windowX = w;
	windowY = h;
}


void  mouse( int button, int state, int mx, int my )
{
	if ( ( button == GLUT_LEFT_BUTTON ) && ( state == GLUT_DOWN ) )
		drag_mouse_l = 1;
	else if ( ( button == GLUT_LEFT_BUTTON ) && ( state == GLUT_UP ) )
		drag_mouse_l = 0;

	if ( ( button == GLUT_RIGHT_BUTTON ) && ( state == GLUT_DOWN ) )
		drag_mouse_r = 1;
	else if ( ( button == GLUT_RIGHT_BUTTON ) && ( state == GLUT_UP ) )
		drag_mouse_r = 0;

	if ( ( button == GLUT_MIDDLE_BUTTON ) && ( state == GLUT_DOWN ) )
		drag_mouse_m = 1;
	else if ( ( button == GLUT_MIDDLE_BUTTON ) && ( state == GLUT_UP ) )
		drag_mouse_m = 0;

	glutPostRedisplay();

	last_mouse_x = mx;
	last_mouse_y = my;
}


void  motion( int mx, int my )
{
	if ( drag_mouse_r )
	{
		camera_yaw -= ( mx - last_mouse_x ) * 1.0;
		if ( camera_yaw < 0.0 )
			camera_yaw += 360.0;
		else if ( camera_yaw > 360.0 )
			camera_yaw -= 360.0;

		camera_pitch -= ( my - last_mouse_y ) * 1.0;
		if ( camera_pitch < -90.0 )
			camera_pitch = -90.0;
		else if ( camera_pitch > 90.0 )
			camera_pitch = 90.0;
	}

	if ( drag_mouse_l )
	{
		camera_distance += ( my - last_mouse_y ) * 0.2;
		if ( camera_distance < 2.0 )
			camera_distance = 2.0;
	}

	last_mouse_x = mx;
	last_mouse_y = my;

	glutPostRedisplay();
}




void  idle( void )
{
	if ( on_animation )
	{
#ifdef  WIN32
		static DWORD  last_time = 0;
		DWORD  curr_time = timeGetTime();
		float  delta = ( curr_time - last_time ) * 0.001f;
		if ( delta > 0.03f )
			delta = 0.03f;
		last_time = curr_time;
		animation_time += delta;
#else
		animation_time += 0.03f;
#endif
		if ( bvh )
		{
			frame_no = animation_time / bvh->GetInterval();
			frame_no = frame_no % bvh->GetNumFrame();
		}
		else
			frame_no = 0;

		glutPostRedisplay();
	}
}

void  initEnvironment( void )
{
	float  light0_position[] = { 100.0, 100.0, 100.0, 0.0};
	float  light0_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	float  light0_specular[] = { 0.3, 0.3, 0.3, 1.0 };
	float  light0_ambient[] = { 0.2, 0.2, 0.2, 0.2 };

	glLightfv( GL_LIGHT0, GL_POSITION, light0_position );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, light0_diffuse );
	glLightfv( GL_LIGHT0, GL_SPECULAR, light0_specular );
	glLightfv( GL_LIGHT0, GL_AMBIENT, light0_ambient );

	glEnable( GL_LIGHT0 );
	glEnable( GL_LIGHTING );

	glEnable( GL_COLOR_MATERIAL );

	glEnable( GL_DEPTH_TEST );

	glCullFace( GL_BACK );
	glEnable( GL_CULL_FACE );

	glClearColor( 0.5, 0.5, 0.8, 0.0 );

	//	bvh = new BVH( "B02.bvh" );
	bvh = new BVH( "bvh_Female1/Female1_A01_Stand.bvh" );

}


void changelight(){
	float  light0_position[] = { 100.0, 100.0, 100.0, 0.0};
	float  light0_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	float  light0_specular[] = { 0.3, 0.3, 0.3, 1.0 };
	float  light0_ambient[] = { 0.2, 0.2, 0.2, 0.2 };
	
	if(Loption==1){
		light0_position[0] = -100.0 ;
		
	} else if(Loption==2)
	{
		light0_position[3] = -100.0 ;
	}else if(Loption==3){
		light0_position[0] = -100.0 ;
		light0_position[3] = -100.0 ;
	}

	if(Moption==1){
		
		light0_diffuse[0] = 0.3 ;
		light0_diffuse[1] = 0.7 ;
		light0_diffuse[2] = 0.3 ;
		
	} else if(Moption==2)
	{
		light0_diffuse[0] = 0.7 ;
		light0_diffuse[1] = 0.3 ;
		light0_diffuse[2] = 0.3 ;
	}else if(Moption==3){
		light0_diffuse[0] = 0.3 ;
		light0_diffuse[1] = 0.7 ;
		light0_diffuse[2] = 0.3 ;
	}

	glLightfv( GL_LIGHT0, GL_POSITION, light0_position );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, light0_diffuse );
	glLightfv( GL_LIGHT0, GL_SPECULAR, light0_specular );
	glLightfv( GL_LIGHT0, GL_AMBIENT, light0_ambient );

	glEnable( GL_LIGHT0 );
	glEnable( GL_LIGHTING );

	glEnable( GL_COLOR_MATERIAL );

	glEnable( GL_DEPTH_TEST );

	glCullFace( GL_BACK );
	glEnable( GL_CULL_FACE );

	glClearColor( 0.5, 0.5, 0.8, 0.0 );

}
void  keyboard( unsigned char key, int mx, int my )
{
	if ( key == 'A' ){//에니메이션 중지// 재개
		on_animation = !on_animation;
	}
	/*
	if ( ( key == 'P' ) && !on_animation )
	{
		animation_time += bvh->GetInterval();
		frame_no ++;
		frame_no = frame_no % bvh->GetNumFrame();
	}

	if ( ( key == 'L' ) && !on_animation && ( frame_no > 0 ) && bvh )
	{
		animation_time -= bvh->GetInterval();
		frame_no --;
		frame_no = frame_no % bvh->GetNumFrame();
	}*/
	if ( key == 'S' )//애니메이션이 처음부터 실행
	{
		animation_time = 0.0f;
		frame_no = 0;
	}
	if(key == 'D'){
		View4Option= (!View4Option);
	}
	if ( key == 'Z' )
	{
		delete bvh;
		bvh = new BVH( "bvh_Female1/Female1_B03_Walk1.bvh" );
	}
	if ( key == 'X' )
	{
		delete bvh;
		bvh = new BVH( "bvh_Female1/Female1_C25_SideStepRight.bvh" );
	}
	if ( key == 'C' )
	{
		delete bvh;
		bvh = new BVH( "bvh_Female1/Female1_B04_StandToWalkBack.bvh" );
	}
	if ( key == 'V' )
	{
		delete bvh;
		
		
		//bvh = new BVH( "bvh_Female1/Female1_C18_RunChangeDirection.bvh" );
		bvh = new BVH( "bvh_Female1/Female1_C12_RunTurnLeft45.bvh" );
	}
	if ( key == 'B' )
	{
		delete bvh;
		bvh = new BVH( "bvh_Female1/Female1_C07_RunBackwards.bvh" );
	}
	if ( key == 'N' )
	{
		delete bvh;
		bvh = new BVH( "bvh_Female1/Female1_B01_StandToWalk.bvh" );
	}
	if ( key == 'M' )
	{
		delete bvh;
		bvh = new BVH( "bvh_Female1/Female1_A01_Stand.bvh" );
	}
	if( key == 'Q'){
		Loption++;
		if(Loption==4){
			Loption = 0;
		}
		changelight();
	}
	if(key == 'W'){
		Moption++;
		if(Moption==4){
			Moption = 0;
		}
		changelight();
	}
	if(key == 'E'){
		Lookset=1;
	}
	if(key == 'R'){
		Lookset=2;
	}
	if(key == 'T'){
		Lookset=0;
	}
	if(key == 'P'){
		drawD=!drawD;
		bvh->drawD=drawD;
	}
	if(key == 'Y'){
		drawS++;
		if(drawS>3){
			drawS=0;
		}
	}
	if(key == 'U'){
		drawO++;
		if(drawO==3){
			drawO=0;
		}
		bvh->drawO=drawO;
	}
	glutPostRedisplay();
}

int  main( int argc, char ** argv )
{
	/*
	#ifdef  WIN32
	locale::global( locale("japanese") );
	#endif
	*/

	printf("+-----------------------------------------+\n");
	printf("| 2016년 2학기 컴퓨터그래픽스 TermProject |\n");
	printf("|     발표날짜 : 2016. 12. 06             |\n");
	printf("|         학번 : 2012136132               |\n");
	printf("|         이름 : 최강석                   |\n");
	printf("+-----------------------------------------+\n");  // 학번, 이름, 주차 출력\

	printf("\n+-------------------동작버튼----------------+\n");
	printf("|       조명/재질 : Q, W                    |\n");
	printf("|          카메라 : E, R, T                 |\n");
	printf("| 로봇그리기 설정 : U                       |\n");
	printf("|     뷰포트 분할 : D                       |\n");
	printf("|      애니메이션 : Z~M                     |\n");
	printf("|          컨트롤 : A(중지/재개) S(처음부터)|\n");
	printf("|       무기/방패 : Y                       |\n");
	printf("|     방어막 설정 : P                       |\n");
	printf("|          마우스 : 확대 및 회전            |\n");
	printf("+-------------------------------------------+\n");  // 학번, 이름, 주차 출력

	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL );
	glutInitWindowSize( windowX, windowY );
	glutInitWindowPosition( 0, 0 );
	glutCreateWindow("BVH Player Sample");
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);



	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); //주변광, 발산광 재질에 대해서만

	glutDisplayFunc( display );
	glutReshapeFunc( reshape );
	glutMouseFunc( mouse );
	glutMotionFunc( motion );
	glutKeyboardFunc( keyboard );
	glutIdleFunc( idle );
	initEnvironment();

	glutMainLoop();


	return 0;
}

