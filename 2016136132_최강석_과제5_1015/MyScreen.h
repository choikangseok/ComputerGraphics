#pragma once
extern void drawMyRobot( );

int entryID = 1;
int val=1;
GLboolean Control = false;
GLfloat Delta = 0.0;

class MyScreen
{
	bool	bPressed;
	int		pX, pY;

public:

	MyScreen(void):bPressed(false) { }
	~MyScreen(void) { }


	void display() {
		glClear(GL_COLOR_BUFFER_BIT);

		// 로봇 그리기 테스트 
		drawMyRobot( );
		/*
		// 기초적인 그리기 테스트
		glColor3f(1.0f, 0.0, 0.0);
		drawRect(1.0f);

		glColor3f(0.0f, 0.0, 1.0);
		glutSolidCube( 0.4f);

		glColor3f(0.0f, 1.0, 0.0);

		glPushMatrix();
		{
		myMat.printModelViewMatrix("기존 행렬 = ");
		//myMat.getShearZ( 0.1f, 0.2f);
		myMat.translate( 0.4f, 0.2f, 0.1f);
		//myMat.scale( 0.5f, 0.7f, 1.0f);

		myMat.mult();
		myMat.printModelViewMatrix("Shearing 후 행렬 = ");
		glutWireCube( 0.8f);
		}
		glPopMatrix();
		*/
		glFlush();
	}

	void mouseClick(GLint Button, GLint State, GLint X, GLint Y) {
		if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
			bPressed = true;
			pX = X;
			pY = Y;
		}
		else
			bPressed = false;
	}

	void mouseMove(GLint X, GLint Y) {
		if( bPressed ) {
			int dx = X - pX;
			int dy = Y - pY;
			pX = X;
			pY = Y;

			//val값에 따라 해당하는 옵션을 제공한다.

			if(val==1){
				glTranslatef( dx/100.0 , -dy/100.0 , 0);
				//x축과 y축을 이동을 시켜준다.
			}
			else if(val==2){
				//x값과 y값에 따라 x축으로 회전,
				//y축으로 회전할 수 있게 해준다.
				glRotatef( dx, 0.0, 1.0, 0.0 );
				glRotatef( dy, 1.0, 0.0, 0.0 );
			}
			else if(val==3){
				//x, y값에 따라 크기를 크게해준다.
				glScalef(1.0+dx/100.0, 1.0+dy/100.0, 1.0);
			}
			else if(val==4){
				Control=true;//애니메이션 on
			}
			else if(val==5){
				Control=false;//애니메이션 o ff 
			}

		glutPostRedisplay();
		
		}
	}
};

