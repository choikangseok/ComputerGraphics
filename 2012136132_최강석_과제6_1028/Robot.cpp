//2012136132 최강석 컴퓨터그래픽스 실습 6_2번째 과제
#include <gl/glut.h>
#include <stdio.h>

void DrawBody() { //몸을 그립니다.
	glPushMatrix();
	{
		glTranslatef(0.0, 0.2, 0.0);
		// 중심을 (0.0, 0.2)에 놓습니다.
		glScalef(0.5, 1.0, 0.0);
		//x축을 0.5배로 하고 y축을 1.0배로 설정합니다.
		glutWireCube(0.8);
		// 반지름이 한변의 길이가 0.8인
		// 사각형을 생성합니다.

	}
	glPopMatrix();
}

void DrawHead() { //머리를 그립니다.
	glPushMatrix();
	{
		glTranslatef(0.0, 0.8, 0.0);
		//(0, 0.8)의 위치를 중점으로 이동시킵니다.
		glutWireSphere(0.2, 20, 20); 
		//반지를이 0.2, 경선, 위선이 20인 구를 그려줍니다.
	}
	glPopMatrix();
}

void DrawRecCir(float x, float y, float angle) {//팔을 그립니다
	glPushMatrix();
	{
		glTranslatef(x, y, 0.0);//(x,y)를 중점으로 잡습니다.
		glRotatef(angle, 0.0, 0.0, 1.0);//해당되는 각도만큼 돌려줍니다.
		glutWireSphere(0.1, 16, 16);//반지름이 0.1, 위선, 경선이 16인 구를 만들어 줍니다.
		glTranslatef(0.4, 0.0, 0.0);//x축으로 0.4이동을 합니다.
		glScalef(3.0, 1.0, 0.0);//x축을 3배로 늘려줍니다.
		glutWireCube(0.2);//변의 길이가 0.2인 큐브를 만들어줍니다.
	}
	glPopMatrix();
}

void DrawRobot() {
	glPushMatrix();
	{
		DrawHead();//머리를 그려줍니다.
		DrawBody();//몸통을 그려줍니다.
		DrawRecCir(0.3, 0.5, 0.0);//오른쪽 팔
		DrawRecCir(-0.3, 0.5, 225.0);//왼쪽 팔
		DrawRecCir(-0.1, -0.3, 225.0);//왼쪽 다리
		DrawRecCir(0.1, -0.3, 315.0);//오른 쪽 다리
	}
	glPopMatrix();
}

//디스플레이함수
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);//버퍼정리
	DrawRobot();//로봇그리기
	glFlush();//플러시
}


int main() {
	glutInitWindowSize(400, 400);
	//400, 400사이즈 크기의 윈도우를 만들어줌
	glutCreateWindow("그래픽스 6_2번째 과제");
	//창 제목을 설정한다.
	glutDisplayFunc(MyDisplay);//디스플레이
	glutMainLoop();//반복
	return 0;
}