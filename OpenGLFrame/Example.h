#ifndef __EXAMPLE_H__
#define __EXAMPLE_H__


#include "GLFrame.h"            /**< ���������Ŀ���� */
#include "CBMPLoader.h"         /**< ����λͼ������ */    

typedef struct
{
	int r,g,b;
	float dist;
	float angle;
}sruct_Stars;

/** ��GL_Application������һ������ */
class Example : GLApplication								
{
public:
	bool	Init();										/**< ִ�����еĳ�ʼ������������ɹ���������true */
	void	Uninit();										/**< ִ�����е�ж�ع��� */
	void	Update(DWORD milliseconds);							/**< ִ�����еĸ��²���������Ĳ���Ϊ���β���������ʱ�䣬�Ժ���Ϊ��λ */
	void	Draw();												/**< ִ�����еĻ��Ʋ��� */

	bool    LoadTexture();                                        /**< װ������ */
	void    DrawBox(float r);                                     /**< ����һ������ */
	void DrawEarth(float er);
	void DrawSun(float sr);
	void init_stars();
	void DrawStars();
	void AStar();



private:
	friend class GLApplication;								/**< ����Ϊ����һ����Ԫ�࣬�����������������ʵ����������GL_Application * GL_Application::Create(const char * class_name) */
	Example(const char * class_name);						/**< ���캯�� */

	/** �û��Զ���ĳ������ */
	CBMPLoader  Texture;          /**< λͼ������Ķ��� */
	float rot;					  /**< ������ת���� */
	float day,year;
	float ellx;
	float elly;
	float ellz;
	float deltay;
	float earthy;
};

#endif	// __EXAMPLE_H__