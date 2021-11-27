/* Carrom board disgn , Hash minner :) */

#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <stdio.h>
#include "box.h"
#include <sstream>
#include <string.h>
using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)

void init();
void initRendering();
void handleResize(int w,int h);
void handleKeypress1(int key, int x, int y);
void handleKeypress2(unsigned char key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);
void update(int value);
void update1(int value);
void drawScene();
void drawBoxes();
void drawHoles();
void drawRings();
void drawCoins();

std::string score,w1,b1;

Box outerBox(0,6.0f),innerBox(0,5.50f),innerBox1(1,4.50f);
ScoreBoard scoreBoard(2.0f,1.5f);
Hole holes[4];
Circle rings[4],centre,powerBall;
Coin coins[9];
Striker strike;
float lx = 0.0f;
float ly = 0.16f;
float theta = 0.0f;
int flag,white=0,black=0,red=0;

int main(int argc, char **argv) {
  char str[20];
    printf("Select your coin color : w/b ?\n");
    scanf("%s",str);
    if (strcmp(str,"w")==0)
      flag = 0;
    else if (strcmp(str,"b") == 0)
      flag = 1;
    else
    {
      printf("wrong input\n");
      exit(0);
    }
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    int w = glutGet(GLUT_SCREEN_WIDTH);
    int h = glutGet(GLUT_SCREEN_HEIGHT);
    int windowWidth = w * 2 / 3;
    int windowHeight = h * 2 / 3;
   // printf("%d %d %d %d\n",w,h,windowWidth,windowHeight );
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

    glutCreateWindow("Carrom Board");  // Setup the window
    initRendering();

    init();
    // Register callbacks
    glutDisplayFunc(drawScene);
    glutIdleFunc(drawScene);
    glutReshapeFunc(handleResize);
    glutSpecialFunc(handleKeypress1);
    glutKeyboardFunc(handleKeypress2);
    glutMouseFunc(handleMouseclick);
    glutTimerFunc(10, update, 0);
    glutTimerFunc(1000,update1,0);

    glutMainLoop();
    return 0;
}

void initRendering() {

    glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
    glEnable(GL_COLOR_MATERIAL);    // Enable coloring
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);   // Setting a background color
}
void init()
{
	  outerBox.setTranslationMatrix(0.0f ,0.0f, -8.0f);
    outerBox.setColor(0.545f,0.270f,0.074f);

    innerBox.setTranslationMatrix(0.0f,0.0f,-8.0f);
    innerBox.setColor(0.8235f,0.5215f,0.2470f);

    innerBox1.setTranslationMatrix(0.0f,0.0f,-8.0f);
    innerBox1.setColor(0.0f,0.0f,0.0f);	

    // holes
    float x1 = -2.55f , y1 = 2.55f;
    for (int i = 0; i < 4; i++)
    {
    	holes[i].setTranslationMatrix(x1,y1,-8.0f);
    	holes[i].setColor(0.752f,0.752f,0.752f);
    	holes[i].setRadius(0.20f);
    	float temp = x1;
    	x1 = -(y1);
        y1 = (temp);
    }

    // rings
    x1 = -2.12f ; y1 = 2.12f;
    for (int i = 0; i < 4; i++)
    {
    	rings[i].setTranslationMatrix(x1,y1,-8.0f);
    	rings[i].setColor(0.545f,0.0f,0.0f);
    	rings[i].setRadius(0.13f);
    	float temp = x1;
    	x1 = -(y1);
        y1 = (temp);
    }
    
    //circle
 	centre.setTranslationMatrix(0.0f,0.0f,-8.0f);
 	centre.setColor(0.0,0.0,0.0);
 	centre.setRadius(0.50f);

    //coins
    x1 = 0.0f; y1 = 0.4f;
    float x0,y0;
    for (int i = 0; i < 9; ++i)
    {
    	if(i == 0)
    	{
    		coins[0].setTranslationMatrix(0.0f,0.0f,-8.0f);
	        coins[0].setColor(1.0f,0.0f,0.0f);
		    coins[0].setRadius(0.1f);
    	}
    	else
    	{
    		coins[i].setTranslationMatrix(x1,y1,-8.0f);
    		if (i%2==1)
    			coins[i].setColor(0.0f,0.0f,0.0f);
    		else
    			coins[i].setColor(1.0f,1.0f,1.0f);
    		coins[i].setRadius(0.1f);
    		x0 = (x1)*cos(DEG2RAD(45)) - (y1)*sin(DEG2RAD(45));
    		y0 = (x1)*sin(DEG2RAD(45)) + (y1)*cos(DEG2RAD(45));
    		x1 = x0;
    		y1 = y0;
    	}
    }

    //striker
    x1 = 0.0f; y1 = -2.09f;
    strike.setTranslationMatrix(x1,y1,-8.0f);
    strike.setColor(0.501f,0.501f,0.501f);
    strike.setRadius(0.16f);
    //powerBall
    powerBall.setTranslationMatrix(3.5f,-2.5f,-8.0f);
    powerBall.setColor(1.0f,0.0f,0.0f);
    powerBall.setRadius(0.08f);
    //score board
    scoreBoard.setTranslationMatrix(-4.5f,2.0f,-8.0f);
    scoreBoard.setColor(0.662f,0.662f,0.662f);
    scoreBoard.score = 30;
}
void drawScene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
    
  drawBoxes();
 	drawHoles();
 	drawRings();
 	// draw circle
 	glPushMatrix();
 	centre.setTranslationMatrix(centre.cx,centre.cy,centre.cz);
 	centre.setColor(centre.red,centre.green,centre.blue);
 	centre.drawCircle(centre.radius,1);
 	glPopMatrix();
 
  	drawCoins();
 	
 	//draw striker
 	glPushMatrix();
 	strike.setTranslationMatrix(strike.cx,strike.cy,strike.cz);
 	strike.setColor(strike.red,strike.green,strike.blue);
 	strike.drawCircle(strike.radius,0);
 	glPopMatrix();
 	// line on striker (indicating direction)
 	glPushMatrix();
  glTranslatef(strike.cx,strike.cy,strike.cz);
  glRotatef(theta, 0.0f, 0.0f, -1.0f);
	glColor3f(0.0f,0.0f,0.0f);
	glBegin(GL_LINES);
	glVertex2f(0.0f,0.0f);
	glVertex2f(lx,ly);
	glEnd();
	glPopMatrix();

	// power bar
	glPushMatrix();
	glTranslatef(+3.5f,-2.50f,-8.0f);
	glColor3f(0.0f,0.0f,0.0f);
	glBegin(GL_LINES);
	glVertex2f(0.0f,0.0f);
	glVertex2f(0.0f,5.0f);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	powerBall.drawCircle(powerBall.radius,0);
	glPopMatrix();
  //Scoreboard
  scoreBoard.drawBox();
  glColor3f(0.0f,0.0f,0.0f);
  char string[] = "scoreboard";
  scoreBoard.drawText(string,strlen(string),-0.7f,0.2f);
  ostringstream sc;
  sc<<scoreBoard.score;
  score = sc.str();
  scoreBoard.drawText(score.data(),score.size(),-0.2f,-0.4f); 
  // count
  char s1[] = "whites hit :";
  scoreBoard.drawText(s1,strlen(s1),-1.0f,-1.5f);
  ostringstream w;
  w<<white;
  w1= w.str();
  scoreBoard.drawText(w1.data(),w1.size(),0.5f,-1.5f);
  char s2[] = "blacks hit :";
  scoreBoard.drawText(s2,strlen(s2),-1.0f,-2.5f);
  ostringstream b;
  b<<black;
  b1 = b.str();
  scoreBoard.drawText(b1.data(),b1.size(),0.5f,-2.5f);
  glutSwapBuffers();
}
void drawBoxes()
{
	glPushMatrix();
    outerBox.setTranslationMatrix(outerBox.box_x,outerBox.box_y,outerBox.box_z);
    outerBox.setColor(outerBox.red,outerBox.green,outerBox.blue);
    outerBox.drawBox(outerBox.box_len);
    glPopMatrix();

    glPushMatrix();
    innerBox.setTranslationMatrix(innerBox.box_x,innerBox.box_y,innerBox.box_z);
    innerBox.setColor(innerBox.red,innerBox.green,innerBox.blue);
    innerBox.drawBox(innerBox.box_len);
    glPopMatrix();

    glPushMatrix();
    innerBox1.setTranslationMatrix(innerBox1.box_x,innerBox1.box_y,innerBox1.box_z);
    innerBox1.setColor(innerBox1.red,innerBox1.green,innerBox1.blue);
    innerBox1.drawBox(innerBox1.box_len);
    glPopMatrix();
}
void drawHoles()
{
 for (int i = 0; i < 4; i++)
	{
		glPushMatrix();
		holes[i].setTranslationMatrix(holes[i].cx,holes[i].cy,holes[i].cz);
		holes[i].setColor(holes[i].red,holes[i].green,holes[i].blue);
		holes[i].drawCircle(holes[i].radius,0);
		glPopMatrix();
	}
}
void drawRings()
{
	for (int i = 0; i < 4; i++)
	{
		glPushMatrix();
		rings[i].setTranslationMatrix(rings[i].cx,rings[i].cy,rings[i].cz);
		rings[i].setColor(rings[i].red,rings[i].green,rings[i].blue);
		rings[i].drawCircle(rings[i].radius,0);
		glPopMatrix();
	}
}
void drawCoins()
{
	for (int i = 0; i < 9; i++)
	{
		glPushMatrix();
		coins[i].setTranslationMatrix(coins[i].cx,coins[i].cy,coins[i].cz);
		coins[i].setColor(coins[i].red,coins[i].green,coins[i].blue);
		coins[i].drawCircle(coins[i].radius,0);
		glPopMatrix();
	}
}
void handleResize(int w,int h)
{
	glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void handleKeypress1(int key, int x, int y)
{
	if(key == GLUT_KEY_LEFT  && strike.cx > -2.07f)
		strike.cx -=0.1f;
	if (key == GLUT_KEY_RIGHT  && strike.cx < 2.07f)
		 strike.cx +=0.1f;
	if (key == GLUT_KEY_UP && powerBall.cy < 2.5f)
	{
		powerBall.cy +=0.25f;
	}
	if (key == GLUT_KEY_DOWN && powerBall.cy > -2.5f)
	{
		powerBall.cy -=0.25f;
	}
}
void handleKeypress2(unsigned char key, int x, int y) {

    if (key == 27) 
        exit(0);     // escape key is pressed
    if (key == 97)
    {
    	theta -= 5;
    //  printf("%f %f\n",lx,ly );
    }
    if (key == 99)
    	theta += 5;
    if(key == 32)
    {
    	//printf("space hit\n" );
    	// if(strike.flag_vel == 0)
    	// {
    	//	strike.flag_vel = 1;
    		strike.velx = ((2.5f+powerBall.cy)*1/20)*sin(DEG2RAD(theta));
    		strike.vely = ((2.5f+powerBall.cy)*1/20)*cos(DEG2RAD(theta));
    	//}
    }
    if (key == 114)
    {
      theta = 0.0f;
      strike.reset();
    }
}
void handleMouseclick(int button, int state, int x, int y) 
{
  //printf("%d %d\n",x,y );
  if (state == GLUT_DOWN)
  {
    if (button == GLUT_LEFT_BUTTON)
    {
      int w = glutGet(GLUT_SCREEN_WIDTH);
      int h = glutGet(GLUT_SCREEN_HEIGHT);
      float windowWidth = (float) w * 2 /3;
      float windowHeight = (float) h * 2 / 3;
      // float xx = ((float)x - windowWidth)/windowWidth;
      // float yy = ((float)y - windowHeight)/-windowHeight;
      //printf("%f %f\n",xx,yy );
      // float yo = yy - strike.cy;
      // float xo = xx - strike.cx;
      // float str_angle = atan(yo/xo) * 180/PI ;
      // if(str_angle < 0.0)
      // {
      //   str_angle += 180.0f;
      // }
      float xx = ((float)x - windowWidth/2 )/ windowWidth/2;
      float yy = ((float)y - windowHeight/2)/-windowHeight/2;
      printf("%f %f\n",xx,yy );
      float dx = xx - strike.cx;
      float dy = yy - strike.cy;
      float angle = (atan2(dy,dx))*180/PI;
      if(angle < 0.0)
      {
        angle += 180.0f;
      }
      printf("%f\n",angle );
    }
  }   
}
void update(int value)
{
	//if (strike.velx != 0.00f || strike.vely != 0.00f)
	//{ //wall collision
   		if (strike.cx + strike.radius > innerBox.box_len/2 || strike.cx - strike.radius < -innerBox.box_len/2)
   			strike.velx *=-1;
   		if (strike.cy + strike.radius > innerBox.box_len/2 || strike.cy - strike.radius < -innerBox.box_len/2)
   			strike.vely *=-1;
   		for (int i = 0; i < 9; ++i)
   		{
   			if (coins[i].cx + coins[i].radius > innerBox.box_len/2 || coins[i].cx - coins[i].radius < -innerBox.box_len/2)
   				coins[i].velx *=-1;
   			if (coins[i].cy + coins[i].radius > innerBox.box_len/2 || coins[i].cy - coins[i].radius < -innerBox.box_len/2)
   				coins[i].vely *=-1;
   		}
   		// stiker-coin collision
   		for (int i = 0; i < 9; ++i)
   		{
   			float dx = strike.cx - coins[i].cx;
   			float dy = strike.cy - coins[i].cy;
   			float sumRad = strike.radius + coins[i].radius;
   			float sqrRad = sumRad * sumRad;
   			float sqrDistance = pow(dx,2) + pow(dy,2);
   			if (sqrDistance <= sqrRad)
   			{
   				float d = sqrt(sqrDistance);
   				float collision[2];
   				collision[0] = (dx)/d; collision[1] = (dy)/d; // cos and sin respectively
   				float new1[2],new2[2];
   				new1[0] = (strike.velx)*collision[0] + (strike.vely)*collision[1];
   				new2[0] = (coins[i].velx)*collision[0] + (coins[i].vely)*collision[1];
   				new1[1] = (strike.vely)*collision[0] - (strike.velx)*collision[1];
   				new2[1] = (coins[i].vely)*collision[0] - (coins[i].velx)*collision[1];
   				// similar to 1-d collision along line joining centre
   				float a1 = (new1[0] + new2[0]*2)/3; //v1n
   				float a2 = (4*new1[0] - new2[0])/3; // v2n
   				float final1[2],final2[2];
   				final1[0] = a1*collision[0] - new1[1]*collision[1];
   				final1[1] = a1*collision[1] + new1[1]*collision[0];
   				final2[0] = a2*collision[0] - new2[1]*collision[1];
   				final2[1] = a2*collision[1] + new2[1]*collision[0];
   				strike.velx = final1[0];
   				strike.vely = final1[1];
   				coins[i].velx = final2[0];
   				coins[i].vely = final2[1];
   			}
   		}
   		//ball-ball collision
		for (int i = 0; i < 9; ++i)
		{
			for (int j = i + 1 ; j < 9; ++j)
			{
				float dx = coins[i].cx - coins[j].cx;
				float dy = coins[i].cy - coins[j].cy;
				float d = sqrt(pow(dx,2) + pow(dy,2));
				float sumRad = coins[i].radius + coins[j].radius;
				if (d <= sumRad)
				{
					float collision[2];
   					collision[0] = (dx)/d; collision[1] = (dy)/d; // cos and sin respectively
   					float new1[2],new2[2];
   					new1[0] = (coins[i].velx)*collision[0] + (coins[i].vely)*collision[1];
   					new2[0] = (coins[j].velx)*collision[0] + (coins[j].vely)*collision[1];
   					new1[1] = (coins[i].vely)*collision[0] - (coins[i].velx)*collision[1];
   					new2[1] = (coins[j].vely)*collision[0] - (coins[j].velx)*collision[1];
   					// similar to 1-d collision along line joining centre
   					float a1 = new2[0]; //v1n
   					float a2 = new1[0]; //v2n
   					float final1[2],final2[2];
   					final1[0] = a1*collision[0] - new1[1]*collision[1];
   					final1[1] = a1*collision[1] + new1[1]*collision[0];
   					final2[0] = a2*collision[0] - new2[1]*collision[1];
   					final2[1] = a2*collision[1] + new2[1]*collision[0];
   					coins[i].velx = final1[0];
   					coins[i].vely = final1[1];
   					coins[j].velx = final2[0];
   					coins[j].vely = final2[1];
				}
			}
		}
		// pocketing
		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				int temp = holes[j].checkPocketing(&coins[i]);
        if (temp == 0 && coins[i].check == 0) // success
        {
          coins[i].check = 1;
          if (i%2 == 0 && i!=0)
          {
            white +=1;
            if(flag == 0)
              scoreBoard.score +=10;
            else
              scoreBoard.score -=5;
          }
          else if(i%2 == 1)
          {
            black +=1;
            if (flag == 0)
              scoreBoard.score -=5;
            else
              scoreBoard.score +=10;
          }
          else if (i == 0)
          {
            red = 1;
            scoreBoard.score +=50;
           // printf("Final Score is %d\n",scoreBoard.score );
           // exit(0);
          }
        }
			}
		}
    if (red == 1)
    {
      if ((flag == 0 && white == 4) || (flag == 1 && black ==4))
      {
        printf("Final score : %d\n",scoreBoard.score);
        exit(0);
      }
    }
    if (strike.velx != 0.00f)
      strike.velx /=1.01f;
    if (strike.vely != 0.00f)
      strike.vely /= 1.01f;
    for (int i = 0; i < 9; ++i)
    {
      if (coins[i].velx != 0.00f)
        coins[i].velx /=1.01f;
      if (coins[i].vely != 0.00f)
        coins[i].vely /= 1.01f;
    }
  //}
    // int count=0;
    // for(int i=0;i<9;i++)
    // {
    //   if(strike.velx < 0.001f && strike.vely < 0.001f && coins[i].velx < 0.001f && coins[i].vely < 0.001f && strike.velx > -0.001f && strike.vely > -0.001f && coins[i].velx > -0.001f && coins[i].vely > -0.001f)
    //   {
    //     count +=1;              
    //   }
    // }
    // if(count ==9)
    // {
    //   // strike.velx=0.0f;
    //   // strike.vely=0.0f;
    //   strike.reset();
    // }
    for (int i = 0; i < 9; ++i)
    {
      coins[i].cx +=coins[i].velx;
      coins[i].cy +=coins[i].vely;
    }
    strike.cx += strike.velx;
    strike.cy += strike.vely;
	glutTimerFunc(10, update, 0);
}
void update1(int value)
{
  scoreBoard.score -=1;
  glutTimerFunc(1000,update1,0);
}

