#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>

int gWindowWidth = 600; //초기화면 크기 지정변수 x축을 의미한다.
int gWindowHeight = 300; // 초기화면 크기 지정 변수 y축을 의미한다.
GLint Shape = 1;  //객체의 모양을 결정하는 변수.
GLfloat WidthFactor;//종횡비를 나타내기 위한 변수
GLfloat HeightFactor;//종횡비를 나타내기 위한 변수
GLfloat Delta = 0.2; // 오른쪽 viewport의 객체를 회전시키기 위한 변수
bool bPressed = false;//마우스 버튼의 눌림의 변수
int pX, pY;//마우스 클릭과 무브를 위한 좌표 변수.


void MynameDisplay(){
	//ㅊ을 울력합니다.
	glBegin(GL_POLYGON); //먼저 primitive의 실행을 알립니다.
	//이후 glVertext3f를 통해 각 vertex들의 위치를 정해줍니다.
	glVertex3f(-0.67, 0.28, 0);
	glVertex3f(-0.67, 0.33, 0);
	glVertex3f(-0.8, 0.33, 0);
	glVertex3f(-0.8, 0.28, 0);
	glVertex3f(-0.89, 0.28, 0);
	glVertex3f(-0.89, 0.23, 0);
	glVertex3f(-0.82, 0.23, 0);
	glVertex3f(-0.9, 0.05, 0);
	glVertex3f(-0.9, 0, 0);
	glVertex3f(-0.74, 0.2, 0);
	glVertex3f(-0.58, 0, 0);
	glVertex3f(-0.58, 0.05, 0);
	glVertex3f(-0.65, 0.23, 0);
	glVertex3f(-0.58, 0.23, 0);
	glVertex3f(-0.58, 0.28, 0);
	glEnd();//gl종료를 알립니다

	glBegin(GL_POLYGON);//ㅗ을 출력합니다.
	glVertex3f(-0.7, -0.1, 0);
	glVertex3f(-0.7, 0, 0);
	glVertex3f(-0.77, 0, 0);
	glVertex3f(-0.77, -0.1, 0);
	glVertex3f(-0.9, -0.1, 0);
	glVertex3f(-0.9, -0.15, 0);
	glVertex3f(-0.57, -0.15, 0);
	glVertex3f(-0.57, -0.1, 0);
	glEnd();

	glBegin(GL_QUADS); //l을 출력합니다.
	glVertex3f(-0.52, 0.34, 0);
	glVertex3f(-0.52, -0.17, 0);
	glVertex3f(-0.45, -0.17, 0);
	glVertex3f(-0.45, 0.34, 0);
	glEnd();


	//ㄱ을 출력합니다.
	glBegin(GL_POLYGON);
	glVertex3f(0.03, 0.31, 0);
	glVertex3f(-0.23, 0.31, 0);
	glVertex3f(-0.23, 0.25, 0);
	glVertex3f(-0.09, 0.25, 0);
	glVertex3f(-0.23, 0.05, 0);
	glVertex3f(-0.2, 0, 0);
	glEnd();

	//ㅏ을 출력합니다.
	glBegin(GL_POLYGON);
	glVertex3f(0.18, 0.2, 0);
	glVertex3f(0.18, 0.34, 0);
	glVertex3f(0.11, 0.34, 0);
	glVertex3f(0.11, 0, 0);
	glVertex3f(0.18, 0, 0);
	glVertex3f(0.18, 0.14, 0);
	glVertex3f(0.23, 0.14, 0);
	glVertex3f(0.23, 0.2, 0);
	glVertex3f(0.18, 0.19, 0);
	glEnd();

	//ㅇ을 출력합니다.
	glBegin(GL_QUADS); 
	glVertex3f(0.1,0,0);
	glVertex3f(-0.1,0,0);
	glVertex3f(-0.18,-0.05,0);
	glVertex3f(0.18,-0.05,0);

	glVertex3f(0.1,-0.15,0);
	glVertex3f(-0.1,-0.15,0);
	glVertex3f(-0.18,-0.1,0);
	glVertex3f(0.18,-0.1,0);


	glVertex3f(-0.18,-0.05,0);
	glVertex3f(-0.18,-0.1,0);
	glVertex3f(-0.1,-0.1,0);
	glVertex3f(-0.1,-0.05,0);

	glVertex3f(0.18,-0.05,0);
	glVertex3f(0.18,-0.1,0);
	glVertex3f(0.1,-0.1,0);
	glVertex3f(0.1,-0.05,0);

	glEnd();


	//ㅅ을 출력합니다.
	glBegin(GL_POLYGON);
	glVertex3f(0.55, 0.33, 0);
	glVertex3f(0.48, 0.33, 0);
	glVertex3f(0.35, 0.05, 0);
	glVertex3f(0.35, 0, 0);
	glVertex3f(0.51, 0.2, 0);
	glVertex3f(0.67, 0, 0);
	glVertex3f(0.67, 0.05, 0);
	glEnd();

	//ㅓ을 출력합니다.
	glBegin(GL_POLYGON);

	glVertex3f(0.73, 0.15, 0);
	glVertex3f(0.73, 0, 0);
	glVertex3f(0.80, 0, 0);
	glVertex3f(0.80, 0.34, 0);
	glVertex3f(0.73, 0.34, 0);
	glVertex3f(0.73, 0.20, 0);
	glVertex3f(0.68, 0.20, 0);
	glVertex3f(0.68, 0.15, 0);

	glEnd();
	//ㄱ을 출력 합니다.
	glBegin(GL_QUAD_STRIP);
	glVertex3f(0.4, -0.04, 0);
	glVertex3f(0.4, -0.1, 0);
	glVertex3f(0.8, -0.04, 0);
	glVertex3f(0.72, -0.1, 0);
	glVertex3f(0.8, -0.2, 0);
	glVertex3f(0.72, -0.2, 0);

	glEnd();
	//드라이버에 명령어를 쌓지 말고 현재까지
	//쌍인 명령어를 모두 프로세서에 전달하도록 해준다
}
void MyMainMenu(int entryID)
{
	// entryId 값을 이용하여 입력 된 값을 Shape 값을 변경하고
	// MyDisplay함수에서 Shape 값의 도형을 출력
	if(entryID == 1)
		Shape = 1;
	else if(entryID == 2)
		Shape = 2;
	else if(entryID == 3)
		Shape = 3;
	else if(entryID == 4)
		Shape = 4;
	else if(entryID == 5)
		Shape = 5;
	glutPostRedisplay();
}
// glutKeyboardFunc()에 의해 키보드 콜백함수 MyKeyboard() 가 등록된다.
// 콜백하수의 파라미터인 Keypressed, X, Y는 콜백함수 프로토타입의 key, x, y에 해당하는 것으로
// 프로그래머가 넘겨주는 것이 아니라 키보드 입력 이벤트 발생결과 GLUT로부터 넘겨 받는 것들이다.
void MyKeyboard(unsigned char KeyPressed, int x, int y){
	//각각의 키보드 버튼을 누르면 해당되는 함수가 실행된다
	//Q,q 27은 종료 C,S,T,N,P 는 객체를 바꾸어준다.
	switch (KeyPressed)
	{
	case 'Q':
		exit(0); 
		break;
	case 'q':
		exit(0); 
		break;
	case 27:  // ESC
		exit(0);
		break;
	case 'C':
		MyMainMenu(1); 
		break;
	case 'S':
		MyMainMenu(2); 
		break;
	case 'T':
		MyMainMenu(3); 
		break;
	case 'N':
		MyMainMenu(4); 
		break;
	case 'P':
		MyMainMenu(5); 
		break;
	}
}

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
//마우스 좌/우 버튼에따라 bpress값과 해당하는 좌표를 대입
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) { 
		bPressed = true;
		pX=X;
		pY=Y;
	}
	else bPressed = false; 
}
void MyMouseMove(GLint X, GLint Y) { 
	//dx, dy는 위치가 얼마나 변했는지 들어가게 된다.
	if( bPressed ) {
		int dx = X - pX;
		int dy = Y - pY;
		pX=X;	pY=Y;
		//glRotatef를 통해 회전이 된다.
		glRotatef( dx, 0.0, 1.0, 0.0 );
		glRotatef( dy, 1.0, 0.0, 0.0 ); 
		glutPostRedisplay();
	}
}
void MyDisplay( ) {
	
	
	glClear(GL_COLOR_BUFFER_BIT);
	// 왼쪽 view port
	glViewport( 0, 0, (int)gWindowWidth/2, gWindowHeight);
	glColor3f(0.2, 0.3, 1.0);
	//이는 파란색 배경을 만들어 주었다. 안해줘도 되지만 
	//이유는 뷰포트가 정확이 반으로 나뉘었다는 것을 보여주려고 만들었다.
	glBegin(GL_QUADS);
		glVertex3f(-1.0*WidthFactor, -1.0*HeightFactor, 0.0);
		glVertex3f(1.0*WidthFactor, -1.0*HeightFactor, 0.0);
		glVertex3f(1.0*WidthFactor, 1.0*HeightFactor, 0.0);
		glVertex3f(-1.0*WidthFactor, 1.0*HeightFactor, 0.0);
	glEnd();

	glColor3f(1.0, 0.5, 0.1);//이름의 색깔을 주황색으로 나타내기 위해서 해주었다.
	 
	MynameDisplay();
	

	// 오른쪽 view port

	glViewport( (int)gWindowWidth/2, 0, (int)gWindowWidth/2 , gWindowHeight);
	glColor3f(1.0, 0.9, 0);

	

	//Shape의 값에 따라 해당하는 glut객체가 나오도록 한다.
	
	if(Shape == 1){ 	//cube	
		glutWireCube(0.7);
	}
	else if(Shape == 2){	// Sphere 
		glutWireSphere(0.5, 20, 20);
	}
	else if(Shape == 3){ // torus
		glutWireTorus(0.2, 0.4, 10, 20);
	}
	else if(Shape == 4){ //cone
		glutWireCone(0.4, 0.9 , 10, 20);
	}
	else if(Shape == 5){ //teapot
		glutWireTeapot(0.5);
	}
	glFlush();	


}
void MyReshape(int NewWidth, int NewHeight)
{
	WidthFactor = (GLfloat)NewWidth / (GLfloat)600;
	HeightFactor = (GLfloat)NewHeight / (GLfloat)300;
	gWindowWidth = NewWidth;
	gWindowHeight = NewHeight;

	
	glLoadIdentity();
	glOrtho(-1* WidthFactor, 1 *WidthFactor, -1*HeightFactor, 1*HeightFactor, -1, 1);
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);		
	glutInitDisplayMode(GLUT_RGB); 	// 윈도우의 기본 컬러를 RGB모드로 설정한다
	glutInitWindowSize(gWindowWidth, gWindowHeight);   // 윈도우의 폭을 600, 높이를 300으로 설정
	glutInitWindowPosition(150,150); //창의 왼쪽 모서리 시작지점을 150, 150으로 설정한다.
	glutCreateWindow("2012136132_CHOIKS");

	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
	// 메뉴 팝업창에 나타날 항목을 설정한다.
	glutAddMenuEntry("Cube", 1);
	glutAddMenuEntry("Sphere", 2);
	glutAddMenuEntry("Torus", 3);
	glutAddMenuEntry("Corn", 4);
	glutAddMenuEntry("Teapot", 5);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	// glutAttachMenu()는 마우스 오른쪽버튼을 누를때 메뉴 팝업창이 나오도록 한다.
	glutDisplayFunc(MyDisplay);
	// glutDisplayFunc() MyDisplay라는 콜백함수 등록
	glutReshapeFunc(MyReshape);
	// glutReshapeFunc()는 종횡비 유지
	glutKeyboardFunc(MyKeyboard);
	// glutKeyboardFunc() 함수에 의해 MyKeyboard라는 콜백함수 등록
	glutMouseFunc(MyMouseClick); //glutmouseFunc()함수에 의해 MyMouseClcik라는 콜백 함수 등록
	glutMotionFunc(MyMouseMove); //glutMotionFunc()함수에 의해 MyMouseMove라는 마우스 좌표 콜백 함수 등록


	glutMainLoop( ); // 메인 루프 시작

	return 0;

}
