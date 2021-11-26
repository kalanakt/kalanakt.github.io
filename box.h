#include <iostream>
#include <GL/glut.h>
using namespace std;
#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)

class Box
{
	public:
		float box_len;
		//translation vector coordinates
		float box_x,box_y,box_z;
		// color 
		float red,green,blue;
		int flag;
		Box (int f,float l)
		{
			flag = f;
			box_len = l;
		}
		void setColor(float r, float g , float b)
		{
			red = r;
			green = g;
			blue = b;
		}
		void setBoxLen(float l)
		{
			box_len = l;
		}
		void setTranslationMatrix(float x, float y, float z)
		{
			box_x = x;
			box_y = y;
			box_z = z;
		}
		void drawBox(float len)
		{
			glTranslatef(box_x,box_y,box_z);
			glColor3f(red,green,blue);
			if (flag == 0)
				glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
			else
				glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	    	glBegin(GL_QUADS);
	    	glVertex2f(-len / 2, -len / 2);
	    	glVertex2f(len / 2, -len / 2);
	    	glVertex2f(len / 2, len / 2);
	    	glVertex2f(-len / 2, len / 2);
    		glEnd();
    		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
};
class ScoreBoard
{
	public:
		float length,breadth;
		//translation vector coordinates
		float box_x,box_y,box_z;
		// color 
		float red,green,blue;
		int score;
		ScoreBoard(float l , float b)
		{
			length = l;
			breadth = b;
		}
		void setColor(float r, float g , float b)
		{
			red = r;
			green = g;
			blue = b;
		}
		void setTranslationMatrix(float x, float y, float z)
		{
			box_x = x;
			box_y = y;
			box_z = z;
		}
		void setBoxLen(float l,float b)
		{
			length = l;
			breadth = b;
		}
		void drawBox()
		{
			glTranslatef(box_x,box_y,box_z);
			glColor3f(red,green,blue);
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
			glBegin(GL_QUADS);
	    	glVertex2f(-length / 2, -breadth / 2);
	    	glVertex2f(length / 2, -breadth / 2);
	    	glVertex2f(length / 2, breadth / 2);
	    	glVertex2f(-length / 2, breadth / 2);
    		glEnd();
    		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		void drawText(const char *text,int length,float x, float y)
		{
			
			glRasterPos3f(x,y,0.0f);
			for(int i=0;i<length;i++)
    		{
        		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
    		}
		}
};
class Circle
{
	public:
		int flag;
		float radius;
		// translation matrix coordinates
		float cx,cy,cz;
		// color
		float red,green,blue;
		Circle()
		{
			radius = 0.0f;
		}
		void setTranslationMatrix(float x, float y, float z)
		{
			cx = x;
			cy = y;
			cz = z;
		}
		void setColor(float r, float g , float b)
		{
			red = r;
			green = g;
			blue = b;
		}
		void setRadius(float rad)
		{
			radius = rad;
		}
		void drawCircle(float rad,int f)
	 	{
	 		glTranslatef(cx,cy,cz);
	 		glColor3f(red,green,blue);
	 		flag = f;
	 		if (flag == 1)
	 			glBegin(GL_LINE_STRIP);
	 		else
	 			glBegin(GL_TRIANGLE_FAN);
   			for(int i=0 ; i<360 ; i++) {
       			glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
   			}
   			glEnd();
	 	}
};

class Coin : public Circle
{
public:
	int check;
	float velx;
	float vely;
	Coin()
	{
		check = 0;
		velx = 0.0f;
		vely = 0.0f;
	}
};
class  Hole: public Circle
{
public:
	 int checkPocketing(Coin *c)
	 {
	 	float d = sqrt(pow((c->cx - this->cx),2) + pow((c->cy - this->cy),2));
	 	if(d <= this->radius)
	 	{
	 		c->radius = 0.0f;
	 		c->velx = 0.0f;
	 		c->vely = 0.0f;
	 		return 0; //success
	 	}
	 	else
	 		return 1; //failed
	 }
};
class Striker : public Circle
{
public:
	float flag_vel;
	float velx;
	float vely;
	int wx,wy;
	GLdouble a,b,c;
	Striker()
	{
		flag_vel = 0;
		velx = 0.0f;
		vely = 0.0f;
	}
	void translateX(float x0)
	{
		cx += x0;
	}
	void reset()
	{
		velx = 0.0f;
		vely = 0.0f;
		cx = 0.0f;
		cy = -2.09f;
	}
	void window(float x,float y)
	{
		GLdouble model[16];
        GLdouble  proj[16];  
        GLint  view[4];
        glGetDoublev(GL_MODELVIEW_MATRIX, model);
        glGetDoublev(GL_PROJECTION_MATRIX, proj);
        glGetIntegerv(GL_VIEWPORT, view);
        gluProject(x,  y,  -8.0f,  model,  proj,  view,  &a,  &b,  &c);
	}
};
