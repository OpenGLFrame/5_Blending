#include "Example.h"											/**< ����ͷ�ļ� */

#include <gl\gl.h>												/**< ����OpenGLͷ�ļ� */
#include <gl\glu.h>												
#include <gl\glaux.h>	 
#include <gl/glut.h>
#include <math.h>                                 
#include <Windows.h>
#include <stdio.h>

#pragma comment(lib, "opengl32.lib")							/**< ����OpenGL���ӿ��ļ� */
#pragma comment(lib, "glu32.lib")							
#pragma comment(lib, "glaux.lib")							

/** �����Դ������ֵ */
GLfloat LightAmbient[]= { 1.0f, 1.0f, 1.0f, 1.0f }; 	/**< ��������� */
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };		/**< �������� */
GLfloat LightSpecular[]= { 1.0f, 1.0f, 1.0f, 1.0f };	/**< �������� */
GLfloat LightPosition[]= { 0.0f, 0.0f, 0.0f, 1.0f };	/**< ��Դλ�� */

GLfloat globel_ambient[] = { 0.0 , 0.0 , 0.0 , 1.0 };

HGLRC hRC = NULL;   //������ɫ������
HDC hDC = NULL;  //˽��GDI�豸������
HWND hWnd = NULL;   //�������ǵĴ��ھ��
HINSTANCE hInstance;  //��������ʵ��

bool keys[256];   //���ڼ������̵�����
bool active = true;     //���ڵĻ��־��ȱʡΪtrue
bool fullscreen = false;

bool twinkle;   //��˸������
bool tp;        //t�Ƿ���



float zoom = -15.0f; //������۲��ߵľ���
float tilt = 90.0f;    //���ǵ����
float spin;   //���ǵ���ת
GLuint texture[1];  //����



float star[2000][3];
/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	Example * example = new Example(class_name);
	return reinterpret_cast<GLApplication *>(example);
}


/** ���캯�� */
Example::Example(const char * class_name) : GLApplication(class_name)
{
  /// ��ʼ���û��Զ���ĳ������
	rot = 0.0;
	day = 0.0;
	year = 0.0;
	ellx = 0.0;
	elly = 0.0;
	ellz = 0.0;
	deltay = 0.0;
	earthy = 1.0;

}
///** ����һ������ */
//void Example::DrawBox(float r)
//{
//	glBindTexture(GL_TEXTURE_2D, Texture.ID);                      /**< ������ */
//	/** ��ʼ�����ı��� */
//	glBegin(GL_QUADS);												
//		/// ǰ����
//		glNormal3f( 0.0f, 0.0f, 1.0f);								/**< ָ������ָ��۲��� */
//		glTexCoord2f(0.0f, 0.0f); glVertex3f(-r, -r,  r);	
//		glTexCoord2f(1.0f, 0.0f); glVertex3f( r, -r,  r);	
//		glTexCoord2f(1.0f, 1.0f); glVertex3f( r,  r,  r);	
//		glTexCoord2f(0.0f, 1.0f); glVertex3f(-r,  r,  r);	
//		/// �����
//		glNormal3f( 0.0f, 0.0f,-1.0f);								/**< ָ�����߱���۲��� */
//		glTexCoord2f(1.0f, 0.0f); glVertex3f(-r, -r, -r);	
//		glTexCoord2f(1.0f, 1.0f); glVertex3f(-r,  r, -r);	
//		glTexCoord2f(0.0f, 1.0f); glVertex3f( r,  r, -r);	
//		glTexCoord2f(0.0f, 0.0f); glVertex3f( r, -r, -r);	
//		/// ����
//		glNormal3f( 0.0f, 1.0f, 0.0f);								/**< ָ���������� */
//		glTexCoord2f(0.0f, 1.0f); glVertex3f(-r,  r, -r);	
//		glTexCoord2f(0.0f, 0.0f); glVertex3f(-r,  r,  r);	
//		glTexCoord2f(1.0f, 0.0f); glVertex3f( r,  r,  r);	
//		glTexCoord2f(1.0f, 1.0f); glVertex3f( r,  r, -r);	
//		/// ����
//		glNormal3f( 0.0f,-1.0f, 0.0f);								/**< ָ�����߳��� */
//		glTexCoord2f(1.0f, 1.0f); glVertex3f(-r, -r, -r);	
//		glTexCoord2f(0.0f, 1.0f); glVertex3f( r, -r, -r);	
//		glTexCoord2f(0.0f, 0.0f); glVertex3f( r, -r,  r);	
//		glTexCoord2f(1.0f, 0.0f); glVertex3f(-r, -r,  r);	
//		/// �Ҳ���
//		glNormal3f( 1.0f, 0.0f, 0.0f);								/**< ָ�����߳��� */
//		glTexCoord2f(1.0f, 0.0f); glVertex3f( r, -r, -r);	
//		glTexCoord2f(1.0f, 1.0f); glVertex3f( r,  r, -r);	
//		glTexCoord2f(0.0f, 1.0f); glVertex3f( r,  r,  r);	
//		glTexCoord2f(0.0f, 0.0f); glVertex3f( r, -r,  r);	
//		/// �����
//		glNormal3f(-1.0f, 0.0f, 0.0f);								/**< ָ�����߳��� */
//		glTexCoord2f(0.0f, 0.0f); glVertex3f(-r, -r, -r);	
//		glTexCoord2f(1.0f, 0.0f); glVertex3f(-r, -r,  r);	
//		glTexCoord2f(1.0f, 1.0f); glVertex3f(-r,  r,  r);	
//		glTexCoord2f(0.0f, 1.0f); glVertex3f(-r,  r, -r);	
//	glEnd();
//}

void Example::init_stars()  
{  
	for ( int i=0; i < 2000; i++ )  
	{  
		for(int j=0;j<3;j++)  
		{  
			star[i][j]=rand()%20-10;  
		}  
	}  
}  


void Example::AStar()  
{  

	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1.0,1.0,1.0);
	glVertex3f(1.0,1.0,-7.0);
	glVertex3f(1.0,-1.0,-7.0);
	glVertex3f(-1.0,-1.0,-7.0);
	glVertex3f(-1.0,1.0,-7.0);
	glEnd();
	glPopMatrix();

}  


void Example::DrawStars()  
{  

	for (int ii = 0;ii<100;ii++)
	{
		glPushMatrix();
		float starx = rand()%50+1.5;
		float stary = rand()%50+1;
		glTranslatef(starx,stary,0);
		glScalef(0.02,0.02,1);

		glPushMatrix();
		glBegin(GL_QUADS);
		glColor3f(1.0,1.0,1.0);
		glVertex3f(1.0,1.0,-7.0);
		glVertex3f(1.0,-1.0,-7.0);
		glVertex3f(-1.0,-1.0,-7.0);
		glVertex3f(-1.0,1.0,-7.0);
		glEnd();
		glPopMatrix();

		glPopMatrix();
	}

	for (int ii = 0;ii<100;ii++)
	{
		glPushMatrix();
		float starx = (-1)*rand()%50+1.5;
		float stary = rand()%50+1;
		glTranslatef(starx,stary,0);
		glScalef(0.02,0.02,1);

		glPushMatrix();
		glBegin(GL_QUADS);
		glColor3f(1.0,1.0,1.0);
		glVertex3f(1.0,1.0,-7.0);
		glVertex3f(1.0,-1.0,-7.0);
		glVertex3f(-1.0,-1.0,-7.0);
		glVertex3f(-1.0,1.0,-7.0);
		glEnd();
		glPopMatrix();

		glPopMatrix();
	}

	for (int ii = 0;ii<100;ii++)
	{
		glPushMatrix();
		float starx = rand()%50+1.5;
		float stary = (-1)*rand()%50+1;
		glTranslatef(starx,stary,0);
		glScalef(0.02,0.02,1);

		glPushMatrix();
		glBegin(GL_QUADS);
		glColor3f(1.0,1.0,1.0);
		glVertex3f(1.0,1.0,-7.0);
		glVertex3f(1.0,-1.0,-7.0);
		glVertex3f(-1.0,-1.0,-7.0);
		glVertex3f(-1.0,1.0,-7.0);
		glEnd();
		glPopMatrix();

		glPopMatrix();
	}

	for (int ii = 0;ii<100;ii++)
	{
		glPushMatrix();
		float starx = (-1)*rand()%50+1.5;
		float stary = (-1)*rand()%50+1;
		glTranslatef(starx,stary,0);
		glScalef(0.02,0.02,1);

		glPushMatrix();
		glBegin(GL_QUADS);
		glColor3f(1.0,1.0,1.0);
		glVertex3f(1.0,1.0,-7.0);
		glVertex3f(1.0,-1.0,-7.0);
		glVertex3f(-1.0,-1.0,-7.0);
		glVertex3f(-1.0,1.0,-7.0);
		glEnd();
		glPopMatrix();

		glPopMatrix();
	}
	Sleep(50);

}  
void Example::DrawEarth(float er)
{
	glPushMatrix();

	glRotatef(day,1.0f,1.0f,7.0f);
	glTranslatef(-1.0f, 1.0f, -7.0f);
	//glRotatef(year,0.0f,-0.6f,7.0f);
	//glTranslatef(0.0f,deltay,0.0f);

	glEnable(GL_TEXTURE_2D);
	GLUquadricObj *quadPlanetearth = gluNewQuadric();  //����һ��������������
	gluQuadricTexture(quadPlanetearth, 2); //�����ö������������
	glBindTexture(GL_TEXTURE_2D, 1); //������
	gluSphere(quadPlanetearth, er ,20,16);//����һ������
	gluDeleteQuadric(quadPlanetearth);  //ɾ�������������
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

}

void Example::DrawSun(float sr)
{
	glPushMatrix();
		glTranslatef(-1.0f, 0.0f, -7.0f);
		glRotatef(150,1.0f,0.0f,0.0f);
		glRotatef(15,0.0f,1.0f,0.0f);

		glPushMatrix();
			glRotatef((-1)*day,0.0f,1.0f,1.0f);
			glEnable(GL_TEXTURE_2D);
			GLUquadricObj *quadPlanetsun = gluNewQuadric();  //����һ��������������
			gluQuadricTexture(quadPlanetsun,GL_TRUE); //�����ö������������
			glBindTexture(GL_TEXTURE_2D, 1); //������
			gluSphere(quadPlanetsun, sr ,20,16);//����һ������
			gluDeleteQuadric(quadPlanetsun);  //ɾ�������������

		glPopMatrix();
	
		glPushMatrix();

			glRotatef((-1)*day,0.0f,0.8f,1.0f);	
			glTranslatef(1.5f, 0.0f,0.0f);
			glRotatef((-1)*day,0.0f,0.8f,1.0f);

			GLUquadricObj *quadPlanetearth = gluNewQuadric();  //����һ��������������
			gluQuadricTexture(quadPlanetearth, 1); //�����ö������������
			glBindTexture(GL_TEXTURE_2D, 2); //������
			gluSphere(quadPlanetearth, 0.2 ,20,16);//����һ������
			gluDeleteQuadric(quadPlanetearth);  //ɾ�������������
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	glPopMatrix();
}


/** װ������ */
bool Example::LoadTexture()
{
	glEnable(GL_TEXTURE_2D);                          /**< ��������ӳ�� */

	//sun��ͼ
	if(!Texture.LoadBitmap("image_sun.bmp"))              /**< ����λͼ�ļ� */
	{
		MessageBox(NULL,"װ��λͼ�ļ�01ʧ�ܣ�","����",MB_OK);  /**< �������ʧ���򵯳��Ի��� */
		return false;
	}
	glGenTextures(1, &Texture.ID);        /**< ����һ������������� */
	glBindTexture(GL_TEXTURE_2D, Texture.ID); /**< ����������� */
	/** �����˲� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	/** �������� */
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, Texture.imageWidth,
		Texture.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
		Texture.image);


	//earth��ͼ

	if(!Texture.LoadBitmap("image_earth.bmp"))              /**< ����λͼ�ļ� */
	{
		MessageBox(NULL,"װ��λͼ�ļ�01ʧ�ܣ�","����",MB_OK);  /**< �������ʧ���򵯳��Ի��� */
		return false;
	}
	glGenTextures(1, &Texture.ID);        /**< ����һ������������� */
	glBindTexture(GL_TEXTURE_2D, Texture.ID); /**< ����������� */
	/** �����˲� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    /** �������� */
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, Texture.imageWidth,
	                  Texture.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
	                  Texture.image);


	

	
	glDisable(GL_TEXTURE_2D);
	return true;
}

/** ��ʼ��OpenGL */
bool Example::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);	
	glClearDepth(1.0f);											
	glDepthFunc(GL_LEQUAL);										
	glEnable(GL_DEPTH_TEST);									
	glShadeModel(GL_SMOOTH);									
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			
	//gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
	ResizeDraw(true);											/**< �ı�OpenGL���ڴ�С��ֱ�ӵ�������ĺ��� */
	/** �������� */
	if( !LoadTexture() )
		MessageBox(NULL,"�����������!","����",MB_OK);

    /** ���ù�Դ������ֵ */
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);				/**< ���û����� */
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);				/**< ��������� */
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);			/**< ��������� */
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);			/**< ���ù�Դλ�� */
	/** ���ù��պ͹�Դ */
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT1);     

  	return true;           /**< �ɹ����� */
}

/** �û��Զ����ж�غ��� */
void Example::Uninit()									
{
    Texture.FreeImage();              /** �ͷ�����ͼ��ռ�õ��ڴ� */
	glDeleteTextures(1, &Texture.ID); /**< ɾ��������� */
}

/** ������º��� */
void Example::Update(DWORD milliseconds)						
{
	if (m_Keys.IsPressed(VK_ESCAPE) == true)					/**< ��ESC�˳� */
	{
		TerminateApplication();									
	}

	///if (m_Keys.IsPressed(VK_F1) == true)						/**< ��F1�л�����/ȫ��ģʽ */
	///{
	///	ToggleFullscreen();										
	///}
 /** �û��Զ���ĸ��¹��� */
	rot += milliseconds/20.0;
	day += milliseconds/20.0;
	year += milliseconds/30.0;



	    
}

/** ���ƺ���// */
void Example::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	 /**< ������� */		
	glLoadIdentity();	

    /** �����ڲ���͸����ľ�� */	
	//glPushMatrix();
    // glTranslatef(0.0f, 0.0f, -5.0f);
	//  glRotatef(rot,1.0f,1.0f,0.0f);
    // DrawBox(0.5);
	//glPopMatrix();

 //   /** ��������͸����ľ�� */
	//glPushMatrix();
	//  glTranslatef(0.0f, 0.0f, -5.0f);
	//  glRotatef(rot,1.0f,1.0f,0.0f);
	//  glEnable(GL_BLEND);	               /**< �򿪻�� */
	//  glDisable(GL_DEPTH_TEST);            /**< �ر���Ȳ��� */
	//  glColor4f(1.0f,1.0f,1.0f,0.5f);	   /**< ȫ���ȣ� 50% Alpha ��� */
	//  glBlendFunc(GL_SRC_ALPHA,GL_ONE);	   /**< ����Դ����alphaͨ��ֵ�İ�͸����Ϻ��� */
 //     DrawBox(1.0);	
	//  glEnable(GL_DEPTH_TEST);             /**< ������Ȳ��� */
	//  glDisable(GL_BLEND);		           /**< �رջ�� */
	// glPopMatrix();

	//DrawStars();
	DrawSun(0.5);
	//DrawEarth(0.25);


   glFlush();				    /**< ǿ��ִ�����е�OpenGL���� */
}
