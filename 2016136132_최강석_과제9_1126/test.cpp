#include <stdio.h>
#include <gl/glut.h>

GLfloat firstX, firstY, lastX, lastY;//처음선분을 나타낼 좌표들의 변수들
unsigned char key; //키보드 콜백을 위한 변수
int start_drawing = 0; //그릴 것 인지에 대한 변수

//디스플레이 함수
void MyDisplay() {
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();

	// 배경을 사각형(폴리곤)곤으로 그린다.
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(10, 10, 0);
	glVertex3f(0, 10, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(10, 0, 0);
	glEnd();

	//화소를 나타내줄 선을 그려준다.
	glColor3f(1, 1, 1);
	for (int i = 0; i < 10; i++) {
		glBegin(GL_LINES);
		glVertex3f(i + 0.5, 0, 0);
		glVertex3f(i + 0.5, 10, 0);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(0, i + 0.5, 0);
		glVertex3f(10, i + 0.5, 0);
		glEnd();
	}

	// 마우스를 클릭할 경우 start drawing이 1로 바뀌게 된다.
	if (start_drawing == 1) {
		int fx, fy, lx, ly;

		fx = (int)(firstX + 0.5);
		fy = (int)(firstY + 0.5);
		lx = (int)(lastX + 0.5);
		ly = (int)(lastY + 0.5);
		
		int temp;
		// 첫 x좌표의 값이 나중의 x값보다 크면 해당 위치를 바꿔준다.
		
		if (lx < fx) {
			temp = fx;
			fx = lx;
			lx = temp;
			temp = fy;
			fy = ly;
			ly = temp;
		}

		// first clicked pixel
		glColor3f(0.9, 0.8, 0.8);//분홍색을 표시하기 위해서
		//첫 좌표에 대한 대한 사각형을 넣어준다
		glBegin(GL_POLYGON);
		glVertex3f(fx + 0.5, fy + 0.5, 0);
		glVertex3f(fx - 0.5, fy + 0.5, 0);
		glVertex3f(fx - 0.5, fy - 0.5, 0);
		glVertex3f(fx + 0.5, fy - 0.5, 0);
		glEnd();

		//브레센 햄의 알고리즘의 적용
		int x = fx, y = fy;
		int dx, dy, incrE, incrNE, D;
		// D : 변수를 결정, incrE : 우측 , incrNE :우상측을 나타냄
		dx = lx - fx;
		dy = ly - fy;

		// dy/dx가 1보다 작고 음수가 아닐 때 
		if (dy < dx && dy >= 0) {
			D = 2 * dy - dx; // F(x+1, y+1/2) = 2dy - dx
			incrE = 2 * dy; // F(x+1, y) - F(x, y) = 2dy
			incrNE = 2 * dy - 2 * dx; // F(x+1, y+1) - F(x, y) = 2dy - 2dx

			while (x < lx) {
				if (D <= 0) { 
					D += incrE; //우측을 적용한 것을 더해준다.
					x++;
				}
				else { // next mid point is lower than the line
					D += incrNE;//우상측을 적용한 것을 더해준다.
					x++;
					y++;
				}
				/*
				P0 = 2 * dy - dx
				P0
				*/
				// drawing pixels
				glBegin(GL_POLYGON);
				glVertex3f(x + 0.5, y + 0.5, 0);
				glVertex3f(x - 0.5, y + 0.5, 0);
				glVertex3f(x - 0.5, y - 0.5, 0);
				glVertex3f(x + 0.5, y - 0.5, 0);
				glEnd();
			}
		}
		// dy/dx가 1 이상, 음수가 아닐 때
		else if (dy >= dx && dy >= 0) {
			D = 2 * dx - dy;
			incrE = 2 * dx;
			incrNE = 2 * dx - 2 * dy;

			while (y < ly) {
				if (D <= 0) {
					D += incrE;//상측을 적용한 것을 더해준다.
					y++;
				}
				else {
					D += incrNE;//좌우측을 적용한 것을 더해준다.
					x++;
					y++;
				}
				glBegin(GL_POLYGON);
				glVertex3f(x + 0.5, y + 0.5, 0);
				glVertex3f(x - 0.5, y + 0.5, 0);
				glVertex3f(x - 0.5, y - 0.5, 0);
				glVertex3f(x + 0.5, y - 0.5, 0);
				glEnd();
			}
		}
		// dy/dx가 –1 이하, 음수일 경우
		else if (-dy >= dx && dy < 0) {
			D = 2 * dx + dy;
			incrE = 2 * dx;
			incrNE = 2 * dx + 2 * dy;

			while (y > ly) {//하측을 적용한 것을 더해준다.
				if (D <= 0) {
					D += incrE;
					y--;
				}
				else {
					D += incrNE;//하우측을 적용한 것을 더해준다.
					x++;
					y--;
				}
				glBegin(GL_POLYGON);
				glVertex3f(x + 0.5, y + 0.5, 0);
				glVertex3f(x - 0.5, y + 0.5, 0);
				glVertex3f(x - 0.5, y - 0.5, 0);
				glVertex3f(x + 0.5, y - 0.5, 0);
				glEnd();
			}
		}
		// dy/dx가 –1보다 크고 음수일 경우
		else if (-dy < dx && dy < 0) {
			D = -2 * dy - dx;
			incrE = -2 * dy;
			incrNE = -2 * dy - 2 * dx;

			while (x < lx) {//좌측을 적용한 것을 더해준다.
				if (D <= 0) {
					D += incrE;
					x++;
				}
				else {//좌 하측을 적용한 것을 더해준다.
					D += incrNE;
					x++;
					y--;
				}
				glBegin(GL_POLYGON);// 브레센햄을 적용한 사각형들을 반복해서 그려준다.
				glVertex3f(x + 0.5, y + 0.5, 0);
				glVertex3f(x - 0.5, y + 0.5, 0);
				glVertex3f(x - 0.5, y - 0.5, 0);
				glVertex3f(x + 0.5, y - 0.5, 0);
				glEnd();
			}
		}
		//마지막 위치에대한 사각형을 그려준다.
		glBegin(GL_POLYGON);
		glVertex3f(lx + 0.5, ly + 0.5, 0);
		glVertex3f(lx - 0.5, ly + 0.5, 0);
		glVertex3f(lx - 0.5, ly - 0.5, 0);
		glVertex3f(lx + 0.5, ly - 0.5, 0);
		glEnd();

		//마우스를 통해 선분을 그려준다.
		if (firstX != lastX || firstY != lastY) { // if the line is just a point, this window doesn't draw it
			glColor3f(0.8, 0.7, 0.9);
			glBegin(GL_LINES);
			glVertex3f(fx, fy, 0); // first point
			glVertex3f(lx, ly, 0); // last point
			glEnd();
		}
	}

	glFlush();
}

//마우스클릭 콜백
void MyMouseClick(GLint button, GLint state, GLint x, GLint y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//뷰포트가 300, 300 인 것을 적용하여 표현해준다.
		firstX = x / 30.0;
		firstY = (300 - y) / 30.0;
	}
	start_drawing = 1;//폴리곤들을 적용할 수 있게 1로 바꾸어준다.
}

//마우스 움직임 콜백
void MyMouseMove(GLint x, GLint y) {

	//뷰포트가 300, 300 인 것을 적용하여 표현해준다.
	lastX = x / 30.0;
	lastY = (300 - y) / 30.0;

	glutPostRedisplay();
}

//키보드 콜백
void MyKeyboard(unsigned char key, int x, int y) {
	if (key == 'q')//q를 누르면 종료된다.
		exit(0);
	else if (key == 'c') {//c를 누르면 초기화 된다.
		start_drawing = 0;
		firstX = firstY = lastX = lastY = 0;
	}

	glutPostRedisplay();
}

int main(int argc, char **argv) {
	// initializaing window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(100, 10);
	glutCreateWindow("Practice 10"); // init 안하고 윈도우부터 만들면 좌표계가 안맞을 수 있으니 꼭 주의하세요.

	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 10, 0, 10, -1, 1); // volume rectangle's length is 10

	glutKeyboardFunc(MyKeyboard); // 키보드콜백
	glutMouseFunc(MyMouseClick); // 마우스클릭 콜백
	glutMotionFunc(MyMouseMove); //마우스움직임 콜백
	glutDisplayFunc(MyDisplay); // 디스플레이
	glutMainLoop();
	return 0;
}