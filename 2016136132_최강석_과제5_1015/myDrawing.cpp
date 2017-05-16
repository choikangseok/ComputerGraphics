#include <GL/glut.h>


void drawBody()
{
	glPushMatrix();
	{
		glScalef(1.0, 2.0, 1.0);
		glutWireCube(0.35);//몸통을 그려줍니다.
		glTranslatef(0.3, 0.05, 0.0);
		glutWireCube(0.2);//왼팔을 그려줍니다.
		glTranslatef(-0.6, 0.0, 0.0);
		glutWireCube(0.2);//오른팔을 그려줍니다.
	}
	glPopMatrix();
}

void drawHead()
{
	glPushMatrix();
	{
		glTranslatef(0.0, 0.5, 0.0);
		glutWireSphere(0.2, 16, 16);//둥근 머리를 그려줍니다.
	}
	glPopMatrix();
}

void drawLeg()
{
	glPushMatrix();
	{
		glScalef(1.0, 2.0, 1.0);//y축을 2배 늘려줍니다.
		glTranslatef(0.1, -0.25, 0.0);
		glutWireCube(0.15);//오른쪽 다리를 그려줍니다.
		glTranslatef(-0.2, 0.0, 0.0);
		glutWireCube(0.15);//오른쪽 다리를 그려줍니다.
		
	}
	glPopMatrix();
}

void drawMyRobot( )
{
	glPushMatrix();
	{
		drawHead();//머리
		drawBody();//몸통
		drawLeg();//다리
	}
	glPopMatrix();
}


