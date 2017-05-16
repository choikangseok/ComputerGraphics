#include <GL/glut.h>
#include "MyScreen.h"

MyScreen screen;//MyScreen 클래스 객체 선언

void MyDisplay() {
	screen.display();
	if (Control==true){
		//Control값이 참일때는 아래와 같은 회전(애니메이션)효과가
		//적용될 수 있게 해준다.
		glRotatef(Delta, 1.0f, 1.0f, 1.0f);
	}
}

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
	screen.mouseClick(Button, State, X, Y);
	//마우스 클릭이벤트
}

void MyMouseMove(GLint X, GLint Y) {
	screen.mouseMove(X, Y);
	//마우스 움직임이벤트
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
		Control=true;//애니메이션
		val=4;
	}
	else if(entryID == 5){
		Control =false;//애니메이션 중지
		val=5;
	}
	glutPostRedisplay();
}

void MyTimer(int Value)
{
	// Control 이 1이면 
	if(Control == 1) 
		Delta += 0.05;	// Delta 값을 증가시킨다.

	glutPostRedisplay(); // 이 함수는 현재의 윈도우를 재생하도록 요구하는 것이다.
	glutTimerFunc(40, MyTimer, 1); // 다시 glutTimerFunc()을 호출하여 타이머 콜백함수를 40msec마다 호출한다.
}



int main() {
    glutCreateWindow("그래픽스 5번과제");
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
	// 메뉴 팝업창에 나타날 항목을 설정한다.
	glutAddMenuEntry("Move", 1);//움직임
	glutAddMenuEntry("Rotate", 2);//회전
	glutAddMenuEntry("ChangeSize", 3);//사이즈변경
	glutAddMenuEntry("Animation", 4);//에니메이션효과
	glutAddMenuEntry("No Action", 5);//에니메이션효과 중지

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	// glutAttachMenu()는 마우스 오른쪽버튼을 누를때 메뉴 팝업창이 나오도록 한다.

	glutDisplayFunc(MyDisplay);//디스플레이
	glutMouseFunc(MyMouseClick);//마우스클릭
	glutMotionFunc(MyMouseMove);//마우스움직임
	glutTimerFunc(40, MyTimer, 1);//타이머콜백

    glutMainLoop();
    return 0;
}