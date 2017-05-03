#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <glut.h>

int stage=1;// 시작화면(1), 게임화면(2), 종료화면(3)으로 나눔, 첫 화면은 시작화면이므로 1로 초기화
int board[3][3];	// 게임 보드판
int turn;			// 현재의 턴(player1 or player2)
int result;			// 게임의 결과
bool over;			// 게임 종료 여부

/*
보드판을 초기화 함
*/
void Intialize()
{
	turn=1;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
			board[i][j]=0;
	}
}

/*
START 버튼으로 누르면 게임이 시작되도록 함
*/
void start(int x,int y)
{
	glColor3f(0,0,0);
	glBegin(GL_LINES);	
	glVertex2f(10,20);
	glVertex2f(60,20);
	glVertex2f(10,20);
	glVertex2f(10,90);
	glVertex2f(10,90);
	glVertex2f(60,90);
	glVertex2f(60,90);
	glVertex2f(60,160);
	glVertex2f(60,160);
	glVertex2f(10,160);
	glEnd();
	glBegin(GL_LINES);	
	glVertex2f(70,20);
	glVertex2f(120,20);
	glVertex2f(95,20);
	glVertex2f(95,160);
	glEnd();
	glBegin(GL_LINES);	
	glVertex2f(130,20);
	glVertex2f(130,160);
	glVertex2f(130,20);
	glVertex2f(175,20);
	glVertex2f(175,20);
	glVertex2f(175,160);
	glVertex2f(130,90);
	glVertex2f(175,90);
	glEnd();
	glBegin(GL_LINES);	
	glVertex2f(185,20);
	glVertex2f(185,160);
	glVertex2f(185,20);
	glVertex2f(230,20);
	glVertex2f(185,90);
	glVertex2f(230,90);
	glVertex2f(230,20);
	glVertex2f(230,90);
	glVertex2f(185,90);
	glVertex2f(230,160);
	glEnd();
	glBegin(GL_LINES);	
	glVertex2f(240,20);
	glVertex2f(290,20);
	glVertex2f(265,20);
	glVertex2f(265,160);
	glEnd();
}

/*
말선택 메뉴 부분 자리를 만들어 놓음
*/
void select(int x,int y,int r) 
{
	glBegin(GL_LINES);
	glColor3f(0,0,0);
	glVertex2f(10,340);
	glVertex2f(10,190);
	glVertex2f(10,190);
	glVertex2f(140,190);
	glVertex2f(140,190);
	glVertex2f(140,340);
	glVertex2f(140,340);
	glVertex2f(10,340);
	glEnd();

}

/*
규칙설명 메뉴 부분 자리를 만들어 놓음
*/
void rule(int x,int y) 
{
	glBegin(GL_LINES);
	glColor3f(0,0,0);
	glVertex2f(160,340);
	glVertex2f(160,190);
	glVertex2f(160,190);
	glVertex2f(290,190);
	glVertex2f(290,190);
	glVertex2f(290,340);
	glVertex2f(290,340);
	glVertex2f(160,340);
	glEnd();
}

/*
키보드함수 : y를 누르면 게임 다시 시작, n을 누르면 게임 종료, 다른 버튼 누르면 게임 종료
*/
void OnKeyPress(unsigned char key,int x,int y)
{
	switch(key)
	{
		case 'y':
		if(over==true)
		{
			over=false;
			Intialize();
			stage=2;
		}
		break;
		case 'n':
		if(over==true)
		{
			exit(0);
		}
		break;
		default:
			exit(0);
	}
}

/*
마우스함수 : stage가 1일때 start버튼을 누르면 게임 시작으로 stage가 2로 넘어감
	    stage가 2일때 player가 누른 자리에 아무 말도 놓여 있지 않을때 자신의 말을 놓고 turn을 넘겨줌
*/
void OnMouseClick(int button,int state,int x,int y)	
{
	if(stage==1)
	{
		if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN && x>10 && x<290 && y>20 && y<160)
		{
			stage=2;
			glutPostRedisplay();
		}

	}
	else if(stage==2)
	{
		if(over==false && button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
		{
			if(turn==1)
			{
				if(board[(y-50)/100][x/100]==0)
				{
					board[(y-50)/100][x/100]=1;
					turn=2;
				}
			}
			else if(turn==2)
			{
				if(board[(y-50)/100][x/100]==0)
				{
					board[(y-50)/100][x/100]=2;
					turn=1;
				}
			}
		}
	}
	
}

/*
누구의 순서인지 알려주거나 누가 이겼는지 알려줌
*/
void DrawString(void *font,const char s[],float x,float y)
{
	unsigned int i;
	glRasterPos2f(x,y);
	for(i=0;i<strlen(s);i++)
	{
		glutBitmapCharacter(font,s[i]);
	}
}

/*
보드판 선을 그림
*/
void DrawLines()
{
	glBegin(GL_LINES);
	glColor3f(0,0,0);
	
	glVertex2f(100,50);
	glVertex2f(100,340);
	glVertex2f(200,340);
	glVertex2f(200,50);
	
	glVertex2f(0,150);
	glVertex2f(300,150);
	glVertex2f(0,250);
	glVertex2f(300,250);
	
	glEnd();		
}

/*
Player2 말 모양인 O를 
*/
void DrawCircle(float cx, float cy, float r, int num_segments) 
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; i++)   
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);//get the current angle 
        float x = r * cosf(theta);//calculate the x component 
        float y = r * sinf(theta);//calculate the y component 
        glVertex2f(x + cx, y + cy);//output vertex 
    }
    glEnd();
}

/*
	Function to draw the cross and circle of Tic Tac Toe
*/
void DrawXO()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(board[i][j]==1)
			{
				glBegin(GL_LINES);
				glVertex2f(50 + j * 100 - 25, 100 + i * 100 - 25);
				glVertex2f(50 + j * 100 + 25, 100 + i * 100 + 25);
				glVertex2f(50 + j * 100 - 25, 100 + i * 100 + 25);
				glVertex2f(50 + j * 100 + 25, 100 + i * 100 - 25);
				glEnd();
			}
			else if(board[i][j]==2)
			{
				
				DrawCircle(50 + j*100 , 100 + i*100 , 25 , 15);
			}
		}
	}
}

/*
	Function to check if there is any winner 
*/
bool CheckWinner()
{
	int i, j;
	// horizontal check
	for(i=0;i<3;i++)
	{
		for(j=1;j<3;j++)
		{
			if(board[i][0]!=0 && board[i][0]==board[i][j])
			{
				if(j==2)
				{
					return true;
				}
			}
			else
				break;
		}
	}
	// vertical check
	for(i=0;i<3;i++)
	{
		for(j=1;j<3;j++)
		{
			if(board[0][i]!=0 && board[0][i]==board[j][i])
			{
				if(j==2)
					return true;
			}
			else
				break;
		}
	}
	// Diagonal check
	if((board[0][0]!=0 && board[0][0]==board[1][1] && board[0][0]==board[2][2]) 
	|| (board[2][0]!=0 && board[2][0]==board[1][1] && board[2][0]==board[0][2]))
		return true;
	return false;
}

/*
	function to check if there is draw
*/
bool CheckIfDraw()
{
	int i, j;
	bool draw;
	for(i=0;i<3;i++)
	{ 
		for(j=0;j<3;j++)
		{ 
			if(board[i][j]==0)
				return false;
		}
	}
	return true;	
}

/*
	Function to display up everything
*/
void Display()
{
	if(stage==1)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1,1,1,1);
		select(0,0,0);
		rule(0,0);
		start(0,0);
	}
	else if(stage==2)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1, 1, 1, 1);
		glColor3f(0, 0, 0);
		if(turn == 1)
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player1's turn", 100, 30);	
		else
			DrawString(GLUT_BITMAP_HELVETICA_18, "Player2's turn", 100, 30);	
	
		DrawLines();
		DrawXO();
	
		if(CheckWinner() == true)
		{
			if(turn == 1)
			{
				over = true;
				result = 2;
			}
			else
			{
				over = true;
				result = 1; 
			}
		}
		else if(CheckIfDraw() == true)
		{
			over = true;
			result = 0;
		}
		if(over == true)
		{
			stage=3;
			
		}
	}
	else if(stage==3)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1,1,1,1);
	DrawString(GLUT_BITMAP_HELVETICA_18, "Game Over", 100, 160);
				if(result == 0)
					DrawString(GLUT_BITMAP_HELVETICA_18, "It's a draw", 110, 185);
				if(result == 1)
					DrawString(GLUT_BITMAP_HELVETICA_18, "Player1 wins", 95, 185);
				if(result == 2)
					DrawString(GLUT_BITMAP_HELVETICA_18, "Player2 wins", 95, 185);
				DrawString(GLUT_BITMAP_HELVETICA_18, "Do you want to continue (y/n)", 40, 210);

	}
	glutSwapBuffers();
}

/*
	Function to reshape
*/
void Reshape(int x, int y)
{
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, x, y, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}

/*
	Driver Function
*/
int main(int argc, char **argv)
{
	Intialize();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowPosition(550,200);
	glutInitWindowSize(300,350);
	glutCreateWindow("Tic Tac Toe");
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutKeyboardFunc(OnKeyPress);
	glutMouseFunc(OnMouseClick);
	glutIdleFunc(Display);
    glutMainLoop();
    return 0;
}
