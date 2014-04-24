#include "Example.h"											/**< 包含头文件 */

#include <gl\gl.h>												/**< 包含OpenGL头文件 */
#include <gl\glu.h>												
#include <gl\glaux.h>	 
#include <gl/glut.h>
#include <math.h>                                 
#include <Windows.h>
#include <stdio.h>

#pragma comment(lib, "opengl32.lib")							/**< 包含OpenGL链接库文件 */
#pragma comment(lib, "glu32.lib")							
#pragma comment(lib, "glaux.lib")							

/** 定义光源的属性值 */
GLfloat LightAmbient[]= { 1.0f, 1.0f, 1.0f, 1.0f }; 	/**< 环境光参数 */
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };		/**< 漫射光参数 */
GLfloat LightSpecular[]= { 1.0f, 1.0f, 1.0f, 1.0f };	/**< 镜面光参数 */
GLfloat LightPosition[]= { 0.0f, 0.0f, 0.0f, 1.0f };	/**< 光源位置 */

GLfloat globel_ambient[] = { 0.0 , 0.0 , 0.0 , 1.0 };

HGLRC hRC = NULL;   //永久着色描述表
HDC hDC = NULL;  //私有GDI设备描述表
HWND hWnd = NULL;   //保存我们的窗口句柄
HINSTANCE hInstance;  //保存程序的实例

bool keys[256];   //用于键盘例程的数组
bool active = true;     //窗口的活动标志，缺省为true
bool fullscreen = false;

bool twinkle;   //闪烁的星星
bool tp;        //t是否按下



float zoom = -15.0f; //星星离观察者的距离
float tilt = 90.0f;    //星星的倾角
float spin;   //星星的自转
GLuint texture[1];  //纹理



float star[2000][3];
/** 创建一个程序的实例 */
GLApplication * GLApplication::Create(const char * class_name)
{
	Example * example = new Example(class_name);
	return reinterpret_cast<GLApplication *>(example);
}


/** 构造函数 */
Example::Example(const char * class_name) : GLApplication(class_name)
{
  /// 初始化用户自定义的程序变量
	rot = 0.0;
	day = 0.0;
	year = 0.0;
	ellx = 0.0;
	elly = 0.0;
	ellz = 0.0;
	deltay = 0.0;
	earthy = 1.0;

}
///** 绘制一个盒子 */
//void Example::DrawBox(float r)
//{
//	glBindTexture(GL_TEXTURE_2D, Texture.ID);                      /**< 绑定纹理 */
//	/** 开始绘制四边形 */
//	glBegin(GL_QUADS);												
//		/// 前侧面
//		glNormal3f( 0.0f, 0.0f, 1.0f);								/**< 指定法线指向观察者 */
//		glTexCoord2f(0.0f, 0.0f); glVertex3f(-r, -r,  r);	
//		glTexCoord2f(1.0f, 0.0f); glVertex3f( r, -r,  r);	
//		glTexCoord2f(1.0f, 1.0f); glVertex3f( r,  r,  r);	
//		glTexCoord2f(0.0f, 1.0f); glVertex3f(-r,  r,  r);	
//		/// 后侧面
//		glNormal3f( 0.0f, 0.0f,-1.0f);								/**< 指定法线背向观察者 */
//		glTexCoord2f(1.0f, 0.0f); glVertex3f(-r, -r, -r);	
//		glTexCoord2f(1.0f, 1.0f); glVertex3f(-r,  r, -r);	
//		glTexCoord2f(0.0f, 1.0f); glVertex3f( r,  r, -r);	
//		glTexCoord2f(0.0f, 0.0f); glVertex3f( r, -r, -r);	
//		/// 顶面
//		glNormal3f( 0.0f, 1.0f, 0.0f);								/**< 指定法线向上 */
//		glTexCoord2f(0.0f, 1.0f); glVertex3f(-r,  r, -r);	
//		glTexCoord2f(0.0f, 0.0f); glVertex3f(-r,  r,  r);	
//		glTexCoord2f(1.0f, 0.0f); glVertex3f( r,  r,  r);	
//		glTexCoord2f(1.0f, 1.0f); glVertex3f( r,  r, -r);	
//		/// 底面
//		glNormal3f( 0.0f,-1.0f, 0.0f);								/**< 指定法线朝下 */
//		glTexCoord2f(1.0f, 1.0f); glVertex3f(-r, -r, -r);	
//		glTexCoord2f(0.0f, 1.0f); glVertex3f( r, -r, -r);	
//		glTexCoord2f(0.0f, 0.0f); glVertex3f( r, -r,  r);	
//		glTexCoord2f(1.0f, 0.0f); glVertex3f(-r, -r,  r);	
//		/// 右侧面
//		glNormal3f( 1.0f, 0.0f, 0.0f);								/**< 指定法线朝右 */
//		glTexCoord2f(1.0f, 0.0f); glVertex3f( r, -r, -r);	
//		glTexCoord2f(1.0f, 1.0f); glVertex3f( r,  r, -r);	
//		glTexCoord2f(0.0f, 1.0f); glVertex3f( r,  r,  r);	
//		glTexCoord2f(0.0f, 0.0f); glVertex3f( r, -r,  r);	
//		/// 左侧面
//		glNormal3f(-1.0f, 0.0f, 0.0f);								/**< 指定法线朝左 */
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
	GLUquadricObj *quadPlanetearth = gluNewQuadric();  //创建一个二次曲面物体
	gluQuadricTexture(quadPlanetearth, 2); //启动该二次曲面的纹理
	glBindTexture(GL_TEXTURE_2D, 1); //绑定纹理
	gluSphere(quadPlanetearth, er ,20,16);//绘制一个球体
	gluDeleteQuadric(quadPlanetearth);  //删除二次曲面对象
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
			GLUquadricObj *quadPlanetsun = gluNewQuadric();  //创建一个二次曲面物体
			gluQuadricTexture(quadPlanetsun,GL_TRUE); //启动该二次曲面的纹理
			glBindTexture(GL_TEXTURE_2D, 1); //绑定纹理
			gluSphere(quadPlanetsun, sr ,20,16);//绘制一个球体
			gluDeleteQuadric(quadPlanetsun);  //删除二次曲面对象

		glPopMatrix();
	
		glPushMatrix();

			glRotatef((-1)*day,0.0f,0.8f,1.0f);	
			glTranslatef(1.5f, 0.0f,0.0f);
			glRotatef((-1)*day,0.0f,0.8f,1.0f);

			GLUquadricObj *quadPlanetearth = gluNewQuadric();  //创建一个二次曲面物体
			gluQuadricTexture(quadPlanetearth, 1); //启动该二次曲面的纹理
			glBindTexture(GL_TEXTURE_2D, 2); //绑定纹理
			gluSphere(quadPlanetearth, 0.2 ,20,16);//绘制一个球体
			gluDeleteQuadric(quadPlanetearth);  //删除二次曲面对象
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	glPopMatrix();
}


/** 装载纹理 */
bool Example::LoadTexture()
{
	glEnable(GL_TEXTURE_2D);                          /**< 启用纹理映射 */

	//sun贴图
	if(!Texture.LoadBitmap("image_sun.bmp"))              /**< 载入位图文件 */
	{
		MessageBox(NULL,"装载位图文件01失败！","错误",MB_OK);  /**< 如果载入失败则弹出对话框 */
		return false;
	}
	glGenTextures(1, &Texture.ID);        /**< 生成一个纹理对象名称 */
	glBindTexture(GL_TEXTURE_2D, Texture.ID); /**< 创建纹理对象 */
	/** 控制滤波 */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	/** 创建纹理 */
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, Texture.imageWidth,
		Texture.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
		Texture.image);


	//earth贴图

	if(!Texture.LoadBitmap("image_earth.bmp"))              /**< 载入位图文件 */
	{
		MessageBox(NULL,"装载位图文件01失败！","错误",MB_OK);  /**< 如果载入失败则弹出对话框 */
		return false;
	}
	glGenTextures(1, &Texture.ID);        /**< 生成一个纹理对象名称 */
	glBindTexture(GL_TEXTURE_2D, Texture.ID); /**< 创建纹理对象 */
	/** 控制滤波 */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    /** 创建纹理 */
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, Texture.imageWidth,
	                  Texture.imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
	                  Texture.image);


	

	
	glDisable(GL_TEXTURE_2D);
	return true;
}

/** 初始化OpenGL */
bool Example::Init()									
{
/** 用户自定义的初始化过程 */
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);	
	glClearDepth(1.0f);											
	glDepthFunc(GL_LEQUAL);										
	glEnable(GL_DEPTH_TEST);									
	glShadeModel(GL_SMOOTH);									
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			
	//gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
	ResizeDraw(true);											/**< 改变OpenGL窗口大小，直接调用子类的函数 */
	/** 载入纹理 */
	if( !LoadTexture() )
		MessageBox(NULL,"载入纹理错误!","错误",MB_OK);

    /** 设置光源的属性值 */
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);				/**< 设置环境光 */
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);				/**< 设置漫射光 */
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);			/**< 设置漫射光 */
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);			/**< 设置光源位置 */
	/** 启用光照和光源 */
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT1);     

  	return true;           /**< 成功返回 */
}

/** 用户自定义的卸载函数 */
void Example::Uninit()									
{
    Texture.FreeImage();              /** 释放纹理图像占用的内存 */
	glDeleteTextures(1, &Texture.ID); /**< 删除纹理对象 */
}

/** 程序更新函数 */
void Example::Update(DWORD milliseconds)						
{
	if (m_Keys.IsPressed(VK_ESCAPE) == true)					/**< 按ESC退出 */
	{
		TerminateApplication();									
	}

	///if (m_Keys.IsPressed(VK_F1) == true)						/**< 按F1切换窗口/全屏模式 */
	///{
	///	ToggleFullscreen();										
	///}
 /** 用户自定义的更新过程 */
	rot += milliseconds/20.0;
	day += milliseconds/20.0;
	year += milliseconds/30.0;



	    
}

/** 绘制函数// */
void Example::Draw()											
{
/** 用户自定义的绘制过程 */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	 /**< 清楚缓存 */		
	glLoadIdentity();	

    /** 绘制内部不透明的木箱 */	
	//glPushMatrix();
    // glTranslatef(0.0f, 0.0f, -5.0f);
	//  glRotatef(rot,1.0f,1.0f,0.0f);
    // DrawBox(0.5);
	//glPopMatrix();

 //   /** 绘制外面透明的木箱 */
	//glPushMatrix();
	//  glTranslatef(0.0f, 0.0f, -5.0f);
	//  glRotatef(rot,1.0f,1.0f,0.0f);
	//  glEnable(GL_BLEND);	               /**< 打开混合 */
	//  glDisable(GL_DEPTH_TEST);            /**< 关闭深度测试 */
	//  glColor4f(1.0f,1.0f,1.0f,0.5f);	   /**< 全亮度， 50% Alpha 混合 */
	//  glBlendFunc(GL_SRC_ALPHA,GL_ONE);	   /**< 基于源象素alpha通道值的半透明混合函数 */
 //     DrawBox(1.0);	
	//  glEnable(GL_DEPTH_TEST);             /**< 启用深度测试 */
	//  glDisable(GL_BLEND);		           /**< 关闭混合 */
	// glPopMatrix();

	//DrawStars();
	DrawSun(0.5);
	//DrawEarth(0.25);


   glFlush();				    /**< 强制执行所有的OpenGL命令 */
}
