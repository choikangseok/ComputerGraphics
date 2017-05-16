#include<stdio.h>
#include<GL/glut.h>

double xmin=200,ymin=200,xmax=300,ymax=300;//클리핑 윈도우의 변수
bool bPressed = false;//마우스 클릭
bool Cbutton =false;//키보드 C를 누를 경우에
double Cx0, Cx1, Cy0, Cy1;
double StartLeftX, StartLeftY, EndRightX, EndRightY;

const int RIGHT= 8; //오른쪽에 대한 비트 코드 
const int TOP=4;    //위에 대한 비트 코드
const int LEFT =2;  //왼쪽에 대한 비트 코드
const int BOTTOM=1; //아래에 대한 비트 코드

int ComputeOutCode(double x,double y); // used to compute bit codes of a point

void CohenFunc(double x0,double y0,double x1,double y1)
{
	int outcode0,outcode1,outcodeOut;
	int done = 0, accept = 0;
	//accept는 선분의 좌표가 0000의 위치에 있을 경우에 1로 바뀐다.
	//절단좌표들을 0으로 초기화 해준다.
	Cx0=0;
	Cy0=0;
	Cx1=0;
	Cy1=0;

	outcode0= ComputeOutCode(x0,y0); //시작점에 대한 위치정보 
	outcode1= ComputeOutCode(x1,y1); //끝점에 대한 위치정보
	do
	{
		if(!(outcode0 | outcode1)) 
		{//위치에대한 비트OR연산을 통해 0000일 경우 
			done=1;//빠져나올 수 있게 설정.
			accept=1;//선분의 좌표가 0000의 위치에 있으므로 1로 설정
		}
		else
			if(outcode0 & outcode1) 
				//위치에 대한 비트AND연산을 통해 0000값이 아닐 경우
				done=1;//빠져나올 수 있게 설정.
			else
			{
				double x,y;

				outcodeOut= outcode0 ? outcode0 : outcode1;
				

				if(outcodeOut & TOP) //위쪽에 대한 AND비트연산
				{//교차점 계산에 의해 절단.
					x= x0+(x1-x0)*(ymax-y0)/(y1-y0);
					y=ymax;
				}
				else
					if(outcodeOut & BOTTOM) //아래에 대한 AND비트 연산
					{//교차점 계산에 의한 절단.
						x= x0+(x1-x0)*(ymin-y0)/(y1-y0);
						y=ymin;
					}
					else
						if(outcodeOut & RIGHT) //우측에 대한 AND비트 연산
						{//교차점 계산에 의한 절단.
							y= y0+(y1-y0)*(xmax-x0)/(x1-x0);
							x=xmax;
						}
						else                   
						{//왼쪽
							y= y0+(y1-y0)*(xmin-x0)/(x1-x0);
							x=xmin;
						}

						if(outcodeOut == outcode0) 
						{ //절단한 좌표를 대입
							x0=x;                           
							y0=y;
							outcode0 = ComputeOutCode(x0,y0);
						}
						else                            
						{ //절단한 좌표를 대입                          
							x1=x;
							y1=y;
							outcode1 = ComputeOutCode(x1,y1);

						}
			}
	}while(!done);
	//전역변수에 자른 선분의 정보들을 대입.
	if(accept){
		//좌표의 정보들이 해당되는 절단 사각형 안에 있을 경우에 적용
		Cx0=x0;
		Cy0=y0;
		Cx1=x1;
		Cy1=y1;
	}

}
int ComputeOutCode(double x,double y)
{
	int code =0;
	//해당하는 위치에 대한 OR비트 연산을 해준다.
	if(y>ymax)   
		code |=TOP;//위
	if(y<ymin)   
		code |=BOTTOM;//아래
	if(x>xmax)      
		code |=RIGHT;//우
	if(x<xmin)  
		code |=LEFT;//좌
	return code;
}
void Mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);//빨간색

	glBegin(GL_LINE_LOOP);//사각형을 그려준다.(클리핑 윈도우 영역)
	glVertex2f(xmin,ymin);
	glVertex2f(xmax,ymin);
	glVertex2f(xmax,ymax);
	glVertex2f(xmin,ymax);
	glEnd();

	//현재의 선분에 대한 코헨서덜랜드 함수의 적용
	

	glColor3f(0.0,0.0,1.0);//파란색
	if(Cbutton!=true){//C버튼이 아닌 경우
		glBegin(GL_LINES);//마우스의 위치에따른 선분을 출력
		glVertex2d(StartLeftX, 500-StartLeftY);
		glVertex2d(EndRightX,  500-EndRightY);
		glEnd();
	}
	if(Cbutton==true ) 
	{//C버튼일 경우에는 서덜랜드 함수를 적용시켜 클립핑된 선분들을 넣어준다.
		CohenFunc(StartLeftX, 500-StartLeftY, EndRightX, 500-EndRightY);
		glBegin(GL_LINES);
		glVertex2d(Cx0, Cy0);
		glVertex2d(Cx1, Cy1);
		glEnd();
	}

	glFlush();
	Cbutton=false;
}
void myinit()
{//초기설정
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);//좌0,우500, 하0, 상500
}
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
		bPressed = true;//버튼을 눌렀을 경우 참의 값으로 설정을 한다.
		StartLeftX = X;//처음의 X축 좌표
		StartLeftY = Y;//처음의 Y축 좌표
	}
	else
		bPressed = false;//눌르지 않았을 경우 false로 설정
}

// mouseMove
void MyMouseMove(GLint X, GLint Y) {
	if( bPressed) {
		//누르고 있는 상태일 경우
		EndRightX = X;//나중의 X좌표
		EndRightY = Y;//나중의 Y좌표
		//좌표를 출력해줍니다.
		glutPostRedisplay();//현재창을 다시 디스플레이해준다.
	}
}
void MyKeyboard(unsigned char KeyPressed, int x, int y){
	//키보드 버튼을 누르면 해당되는 함수가 실행된다

	switch (KeyPressed)
	{
	case 'c'://C를 누르게되면 Cbutton이 true가 되면서 메인에서는 클립핑된 선분이 나온다.
		Cbutton= true;
		glutPostRedisplay();
		break;
	}
}
int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);//사이즈
	glutInitWindowPosition(0,0);//위치
	glutCreateWindow("컴퓨터그래픽스 실습_과제8 ");
	glutDisplayFunc(Mydisplay);//디스플레이
	glutKeyboardFunc(MyKeyboard);//키보드 콜백
	glutMouseFunc(MyMouseClick);//마우스 클릭 콜백
	glutMotionFunc(MyMouseMove);//마우스 움직임 콜백
	myinit();
	glutMainLoop();
	return 0;
}
