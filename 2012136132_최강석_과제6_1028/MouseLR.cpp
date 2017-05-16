//2012136132 최강석 컴퓨터그래픽스 실습 6_1번째 과제
#include <gl/glut.h>//gl, glut함수를 쓰기 위해서.
#include <stdio.h>//printf를 출력하기 위해서

bool bPressed = false;//마우스 클릭한 것을 표현해주기 위한 변수
float StartX, StartY, EndX, EndY;
//StartX, StartY는 처음 위치의 좌표
//EndX, EndY는 나중 위치의 좌표를 나타내줄 변수
int mode=1;
//mode에 따라서 선분으로 표현할지
//사각형으로 표현할지 결정이된다.

// MyDisplay
void MyDisplay() {
   glClear(GL_COLOR_BUFFER_BIT);//프레임 버퍼를 초기화시킨다.
   glClearColor(1.0, 1.0, 1.0, 1.0);//배경색을 흰색으로 설정을한다.
   glColor3f(0.0, 0.0, 0.0);//선의 색을 검은색으로 하기위해 설정해준다.

   glBegin(GL_LINE_LOOP);//라인 루프로 설정을 해준다.

   if(mode==1) {
	   //모드가 1일 경우에는 두가지 버텍스가 표시가 되는데
	   //그게 하나는 좌상단을 나타내줄 버텍스,
	   //하나는 우하단을 나타내줄 버텍스이다.
      glVertex3f(StartX, StartY, 0.0);//처음의 좌표.
      glVertex3f(EndX, EndY, 0.0);//나중처의 좌표.
   }
   else if(mode==2){
	   //모드가 2일 경우에는 4가지 버텍스가 표시가 된다.
      glVertex3f(StartX, StartY, 0.0);// 처음의 좌표
      glVertex3f(EndX, StartY, 0.0);//처음의 좌표에서 x축을 나중의 좌표로 설정
      glVertex3f(EndX, EndY, 0.0);//나중의 좌표에서
      glVertex3f(StartX, EndY, 0.0);//나중의 좌표에서 x축을 처음의 좌표로 설정
   }
   glEnd();
   glFlush();
}

// mouseClick을 할경우
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
   if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
         bPressed = true;//버튼을 눌렀을 경우 참의 값으로 설정을 한다.
         StartX = (X-300)/300.0;//처음의 X축 좌표
         StartY = (300-Y)/300.0;//처음의 Y축 좌표
         printf("시작 : (%5.2f, %5.2f)\n", StartX, StartY);
		 //좌표를 출력해줍니다.
      }
      else
         bPressed = false;//눌르지 않았을 경우 false로 설정
}

// mouseMove
void MyMouseMove(GLint X, GLint Y) {
   if( bPressed) {
	   //누르고 있는 상태일 경우
      EndX = (X-300)/300.0;//나중의 X좌표
      EndY = (300-Y)/300.0;//나중의 Y좌표
      printf("종료 : (%5.2f, %5.2f)\n", EndX, EndY);
	  //좌표를 출력해줍니다.
      glutPostRedisplay();//현재창을 다시 디스플레이해준다.
   }
}


void MyMainMenu(int entryID) {
   if(entryID == 1){
      mode = 1; //mode를 1로 바꾸어준다.(선분)
   }
   else if(entryID == 2){ 
      mode = 2; //mode를 2로 바꾸어준다(사각형)
   }
   else if(entryID == 3){ 
      exit(0); //3일 경우에 종료를 시켜준다.
   }
   glutPostRedisplay();
}


int main() {
   glutInitWindowSize(600, 600); //윈도우 사이즈를 600, 600으로 설정을 합니다.
   glutCreateWindow("그래픽스 6_1번째 과제");//창의 제목을 설정합니다.

   GLint MyMainMenuID = glutCreateMenu(MyMainMenu); //메인메뉴를 만듭니다.
   glutAddMenuEntry("Draw Line", 1);//1에는 Draw Line을 넣어주고
   glutAddMenuEntry("Draw Rectangle", 2);//2에는 Draw Rectangle을 넣어줍니다.
   glutAddMenuEntry("Exit", 3); //3에는 exit을 넣어줍니다.
    glutAttachMenu(GLUT_RIGHT_BUTTON);//오른쪽버튼으로 메뉴를 보이게 합니다.

   glutDisplayFunc(MyDisplay);//콜백함수의 연결
   glutMouseFunc(MyMouseClick);//마우스 클릭 콜백
   glutMotionFunc(MyMouseMove);//마우스 움직임 콜백

   glutMainLoop();// 반복
   return 0;
}