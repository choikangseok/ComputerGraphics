#include <gl/glut.h>
#include <gl/GLU.h>
#include <gl/GL.h>
#include <stdio.h>

int Width, Height;
bool   bPressed;//bool형 bPressed변수를 private형으로 선언
float      pX, pY;//int형 변수 pX,pY를 private형으로 선언
float     dx,dy;
int     val;
float size=1.0;

void DrawBody() { //몸을 그립니다.
	glPushMatrix();
	{
		glTranslatef(0.0, 0.2, 0.0);
		// 중심을 (0.0, 0.2)에 놓습니다.
		glScalef(0.5, 1.0, 0.5);
		//x축을 0.5배로 하고 y축을 1.0배로 설정합니다.
		glutWireCube(0.8);
		// 반지름이 한변의 길이가 0.8인
		// 사각형을 생성합니다.

	}
	glPopMatrix();
}//몸을 그려준다.//몸을 그려준다
void DrawHead() { //머리를 그립니다.
	glPushMatrix();
	{
		glTranslatef(0.0, 0.8, 0.0);//(0, 0.8)의 위치를 중점으로 이동시킵니다.
		glRotatef(90, 0.0, 1.0, 0.0);//y축으로 90도를 회전시켜줍니다.
		glutWireTeapot(0.27);//크기가 0.27인 주전자 머리를 그려줍니다.
	}
	glPopMatrix();
}//머리를 그려준다.// 
void DrawRecCir(float x, float y, float angle, int sym) {//팔을 그립니다
	glPushMatrix();
	{
		glTranslatef(x, y, 0.0);//(x,y)를 중점으로 잡습니다.

		glRotatef(angle, 0.0, 0.0, 1.0);//해당되는 각도만큼 돌려줍니다.
		glutWireSphere(0.1, 16, 16);//반지름이 0.1, 위선, 경선이 16인 구를 만들어 줍니다.
		if(sym==0){
			glTranslatef(0.2, 0.1, 0.0);//x축으로 0.2 y축으로 0.1 이동을 합니다.
		}else if(sym==1){
			glTranslatef(0.2, -0.1, 0.0);//x축으로 0.2 y축으로 0.1 이동을 합니다.
		}
		glScalef(1.0, 1.0, 1.0);//길이들을 설정합니다.
		glutWireCube(0.2);//변의 길이가 0.2인 큐브를 만들어줍니다.
		glTranslatef(0.15, 0.0, 0.0);//x축으로 0.15이동을 합니다.
		glutWireSphere(0.05, 16, 16);
		glTranslatef(0.15, 0.0, 0.0);//x축으로 0.15이동을 합니다.
		glutWireCube(0.2);//변의 길이가 0.2인 큐브를 만들어줍니다.
	}
	glPopMatrix();
}
void DrawRobot() {//각각 도형을 그린 함수들을 이 함수에서 호출한다.
	glColor3f(0.7, 0.7, 0.7);

	if(val==1){
		glTranslatef( dx/100.0 , -dy/100.0 , 0.0);
		//x축과 y축을 이동을 시켜준다.
	}
	else if(val==2){
		//x값과 y값에 따라 x축으로 회전,
		//y축으로 회전할 수 있게 해준다.
		glRotatef( dx, 0.0, 1.0, 0.0 );
		glRotatef( dy, 1.0, 0.0, 0.0 );
	}
	else if(val==3){
		if(dx>0){//x의 변화값이 양인 경우에는
			size += 0.01;//사이즈에 0.01을 더해줍니다.
		}else{//x의 변화값이 음인 경우에는
			size -= 0.01;//사이즈에 0.01을 빼줍니다.
			if(size<0)//사이즈가 음의 경우가 될 때
				size= 0.01;//사이즈를 0.01로 설정해줍니다.
		}
		glScalef(size, size, size);//사이즈를 조절
	}else if(val==4){
		dx=0;//x의 변화량을 0으로 설정
		dy=0;//y의 변화량을 0으로 설정
		size=1.0;//사이즈의 값을 1.0으로 선언해서 기존크기로 설정해줍니다.
	}
	glPushMatrix();
	glTranslatef(0.0, -1.0, 0.0);
	glBegin(GL_QUADS);//밑에 바닥을 그려줍니다.
	glVertex3f(2.0, 0.0, 2.0);
	glVertex3f(2.0, 0.0, -2.0);
	glVertex3f(-2.0, 0.0, -2.0);
	glVertex3f(-2.0, 0.0, 2.0);
	glEnd();
	glPopMatrix();
	//이때 이 함수는 display함수에서 호출하게 되며 전체적으로 모든 도형을 한번에 그리게 된다.
	glPushMatrix();//행렬 스택 함수로 꼭대기 노드의 복사본을 스택에 푸시하는 것이다.
	{
		glColor3f(0.0, 0.0, 0.0);
		DrawHead();
		DrawBody();
		DrawRecCir(0.3, 0.5, 270.0, 0);//오른쪽 팔
		DrawRecCir(-0.3, 0.5, 270.0, 1);//왼쪽 팔
		DrawRecCir(-0.1, -0.3, 270.0, 1);//왼쪽 다리
		DrawRecCir(0.1, -0.3, 270.0, 0);//오른 쪽 다리


	}
	glPopMatrix();//꼭대기 노드를 지우는 것이다.
}
void Init() {//초기
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity( );

	glOrtho(-2.0, 2.0, -2.0, 2.0, 0.5, 5.0);//화면 비율을 설정합니다.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity( );
}
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	
	//위에서 아래를 쳐다보는 첫번째 뷰포트
	glViewport(0, Height/2, Width/2, Height/2);
	glPushMatrix();
	gluLookAt(0.0, 1.0, 0.0,   0.0, 0.0, 0.0,   0.0, 0.0, -1.0);
	DrawRobot();
	glPopMatrix();
	//원근투상을 적용하는 두번째 뷰포트
	glViewport(Width/2, Height/2, Width/2, Height/2);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(30, 1.0, 3.0, 50.0);//원근투상
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	gluLookAt(5.0, 5.0, 5.0,  0.0, 0.0, 0.0,  0.0, 1.0, 0.0);
	DrawRobot();
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	//앞에서 쳐다보는 세번째 뷰포트
	glViewport(0, 0, Width/2, Height/2);
	glPushMatrix();
	gluLookAt(0.0, 0.0, 1.0,   0.0, 0.0, 0.0,   0.0, 1.0, 0.0);

	DrawRobot();
	glPopMatrix();
	//측면을 보는 네번째 뷰포트
	glViewport(Width/2, 0, Width/2, Height/2);
	glPushMatrix();
	gluLookAt(1.0, 0.0, 0.0, 0.0, 0.0, 0.0,  0.0, 1.0, 0.0);
	DrawRobot();
	glPopMatrix();
	
	glFlush();
}
void MyReshape(int w, int h) {//높이와 너비를 재설정합니다.
	Width = w;
	Height = h;
}
//마우스를 클릭했을 경우의 이벤트
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
	//마우스 클릭이벤트
	//마우스 왼쪽버튼을 누르게 되면 bPressed를 참값으로 설정
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
		bPressed = true;
		//매개변수로 받은 좌표의 값들을 넣어준다.
		pX = X;
		pY = Y;
	}
	else//마우스 버튼이 떼어질 경우
		bPressed = false;
}
void MyMouseMove(GLint X, GLint Y){
	//마우스 움직임이벤트
	//만약에 bPressed가 참값일 경우에는
	if( bPressed) {
		dx = X - pX;
		dy = Y - pY;
		if(val==3){
			pX = X;
			pY = Y;   
		}
		glutPostRedisplay();
	}
}
void MyMainMenu(int entryID)
{
	// entryId 값을 이용하여 입력 된 값을 val 값을 변경하고
	// val 값에 따라 옵션이 바뀌게 된다.
	if(entryID == 1)
		val = 1;//이동
	else if(entryID == 2)
		val = 2;//회전
	else if(entryID == 3)
		val = 3;//크기변환
	else if(entryID == 4){
		val = 4;//원상복귀
	}
	else if(entryID==0){
		exit(0);
	}
	glutPostRedisplay();
}
int main(int argc, char** argv) {
	Width = 500;
	Height = 500;
	glutInitDisplayMode(GLUT_SINGLE |GLUT_RGBA);
	glutInitWindowSize(Width, Height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("그래픽스 과제7");
	Init();

	//메뉴 콜백
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
	glutAddMenuEntry("Move",1);//움직임
	glutAddMenuEntry("Rotate", 2);//회전
	glutAddMenuEntry("ChangeSize", 3);//사이즈조정
	glutAddMenuEntry("ReturnBegin",4);//원래대로
	glutAddMenuEntry("Exit", 0);//종료
	glutAttachMenu(GLUT_RIGHT_BUTTON);//오른쪽 클릭으로 메뉴 콜

	//마우스 콜백
	glutMouseFunc(MyMouseClick);//마우스 클릭
	glutMotionFunc(MyMouseMove);//마우스 움직임

	glutDisplayFunc(MyDisplay);//디스플레이
	glutReshapeFunc(MyReshape);//크기 재설정
	glutMainLoop();
	return 0;
}