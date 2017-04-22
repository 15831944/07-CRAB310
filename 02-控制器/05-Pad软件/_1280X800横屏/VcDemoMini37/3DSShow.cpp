// 3DSShow.cpp : implementation file
//

#include "stdafx.h"
#include "dlgDemo.h"
#include "3DSShow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C3DSShow

C3DSShow::C3DSShow()
{

	m_rotateAngleX=0;
	m_rotateAngleY=0;
	m_lButtonDown=false;

//	Width=800;//GetSystemMetrics(SM_CXSCREEN);
//	Height=600;//GetSystemMetrics(SM_CYSCREEN);
//	MoveWindow(0,0,Width,Height);//���ڶ�λ
//////////////////////////////////////////////////////////
//	glViewport(0, 0,Width,Height);// reset the viewport to new dimensions
//	glMatrixMode(GL_PROJECTION);	// set projection matrix current matrix
//	gluPerspective(45.0f,(GLfloat)Width/(GLfloat)(Height-0),1.0f,2000.0f);
//	glMatrixMode(GL_MODELVIEW);		// set modelview matrix
//	glLoadIdentity();				// reset modelview matrix
//	glEnable(GL_TEXTURE_2D);	// ��������ӳ��(����)
//	glShadeModel(GL_SMOOTH);
//	GLfloat light_position[] = {1.0,1.0,1.0,0.0};
//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_COLOR_MATERIAL);
//////////////////////////////////////////////////////////
//	m_3ds=new CLoad3DS();
//	m_3ds_compass=new CLoad3DS();
//
//	load3dobj("data/","dipan.3ds",0);
	//	SetTimer(1,100,NULL);
}

C3DSShow::~C3DSShow()
{
}


BEGIN_MESSAGE_MAP(C3DSShow, CStatic)
	//{{AFX_MSG_MAP(C3DSShow)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C3DSShow message handlers


void C3DSShow::load3dobj(char* dir,char* cn,int a)
{	char	appdir[256];
	GetCurrentDirectory(256,appdir);
	SetCurrentDirectory(dir);
	m_3ds->Init(cn,a);

	//	m_3ds->Init("luopan1.3ds",1);
	//	m_3ds_compass->Init("luopan1.3ds",1);
	SetCurrentDirectory(appdir);
}


BOOL C3DSShow::Scene(int obj,float x,float h,float z,float r,int re,float size)//��ʾ����
{		//				 ���   ,λ��x  ,�߶�   ,λ��y  ,�뾶   ,�Ƕ�  ,��С
	glPushAttrib(GL_CURRENT_BIT);	//����������ɫ��ʵ��
	glPushMatrix();//glPopMatrix();
	glTranslatef(x,h,z);	//�ɻ���λ

	//	m_3ds->show3ds(1,0.0f,0.0f,r,size);//��ʾ3dsģ�ͷɻ�
	//	m_3ds_compass->show3ds(1,0.0f,0.0f,r,size);//��ʾ3dsģ�ͷɻ�

	glRotatef(m_rotateAngleX,1.0, 0, 0);	//����������ת
	glRotatef(m_rotateAngleY,0, 0, 1.0);	//����������ת


	glRotatef(re,0.0, 0.0, 1.0);	//�ɻ�����ת
	
	m_3ds->show3ds(obj,0.0f,r,0.0f,size);//��ʾ3dsģ�ͷɻ�
	
	glPopMatrix();
	glPopAttrib();//�ָ�ǰһ����
	return TRUE;
}

int C3DSShow::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;


	
	return 0;
}



BOOL C3DSShow::SetWindowPixelFormat(HDC hDC)/////////////////////////
{	static PIXELFORMATDESCRIPTOR pfd =
	{	sizeof(PIXELFORMATDESCRIPTOR),	//��ʽ�������Ĵ�С
		1,								// �汾��
		PFD_DRAW_TO_WINDOW |			// ��ʽ����֧�ִ���
		PFD_SUPPORT_OPENGL |			// ��ʽ����֧��OpenGL
		PFD_DOUBLEBUFFER|PFD_STEREO_DONTCARE,// ����֧��˫����
		PFD_TYPE_RGBA,					// ���� RGBA ��ʽ
		16,								// ѡ��ɫ�����
		0, 0, 0, 0, 0, 0,				// ���Ե�ɫ��λ
		0,								// ��Alpha����
		0,								// ����Shift Bit
		0,								// �޾ۼ�����
		0, 0, 0, 0,						// ���Ծۼ�λ
		32,								// 16λ Z-���� (��Ȼ���) 
		0,								// ��ģ�建��
		0,								// �޸�������
		PFD_MAIN_PLANE,					// ����ͼ��
		0,								// ����
		0, 0, 0							// ���Բ�����
	};
	m_GLPixelIndex = ChoosePixelFormat(hDC,&pfd);
	if(m_GLPixelIndex==0) // Choose default
	{	m_GLPixelIndex = 1;
		if(DescribePixelFormat(hDC,m_GLPixelIndex,
		sizeof(PIXELFORMATDESCRIPTOR),&pfd)==0)
		{return FALSE;}
	}
	SetPixelFormat(hDC, m_GLPixelIndex, &pfd);//set pixel format to device context
	return TRUE;
}
BOOL C3DSShow::CreateViewGLContext(HDC hDC)/////////////////////
{	m_hGLContext = wglCreateContext(hDC);
	if(m_hGLContext==NULL)	return FALSE;
	if(wglMakeCurrent(hDC,m_hGLContext)==FALSE)	return FALSE;
	return TRUE;
}



void C3DSShow::Render()
{//////////////////////////////////////////////////////////////////
	glEnable(GL_DEPTH_TEST);			// enable depth testing
	glClearColor(0.2714f,0.196f,0.196f,0);//����ˢ�±���ɫ
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
	glLoadIdentity();
	////////////////////////////////////////////////////
		glEnable(GL_TEXTURE_2D);

//		BOOL C3DSShow::Scene(int obj,float x,float h,float z,float r,int re,float size)//��ʾ����
//{		//				 ���   ,λ��x  ,�߶�   ,λ��y  ,�뾶   ,�Ƕ�  ,��С

			Scene(0,0,0,-1.2,0,0,0.5f);//��ʾ����
			Scene(1,0,0,-1.2,0,r,0.5f);//��ʾ����

		glDisable(GL_TEXTURE_2D);
		r+=1;if(r>360) r=0;
	glFlush();			//���´���
	SwapBuffers(hDC);	//���´���
}

void C3DSShow::InitCWnd()
{

	HWND hWnd = GetSafeHwnd();
	hDC = ::GetDC(hWnd);
	///////////////////////////////////////////////////////
	if(SetWindowPixelFormat(hDC)==FALSE) return ;	
	if(CreateViewGLContext(hDC)==FALSE)  return ;

	r=0;
	Width=163;//GetSystemMetrics(SM_CXSCREEN);
				Height=163;//GetSystemMetrics(SM_CYSCREEN);
				MoveWindow(0,600,Width,Height);//���ڶ�λ
				////////////////////////////////////////////////////////////
				glViewport(0, 0,Width,Height);// reset the viewport to new dimensions
				glMatrixMode(GL_PROJECTION);	// set projection matrix current matrix
				gluPerspective(28.0f,(GLfloat)Width/(GLfloat)(Height-0),1.0f,2000.0f);
				glMatrixMode(GL_MODELVIEW);		// set modelview matrix
				glLoadIdentity();				// reset modelview matrix
				glEnable(GL_TEXTURE_2D);	// ��������ӳ��(����)
				glShadeModel(GL_SMOOTH);
				GLfloat light_position[] = {1.0,1.0,1.0,0.0};
				glLightfv(GL_LIGHT0, GL_POSITION, light_position);
				glEnable(GL_LIGHTING);
				glEnable(GL_LIGHT0);
				glEnable(GL_DEPTH_TEST);
				glEnable(GL_COLOR_MATERIAL);
				////////////////////////////////////////////////////////////
				m_3ds=new CLoad3DS();
				m_3ds_compass=new CLoad3DS();
				
				load3dobj("data/","luopan.3ds",0);
				load3dobj("data/","dipan.3ds",1);


}



void C3DSShow::setRotateParm(GLfloat angleX, GLfloat angleY)
{
	m_rotateAngleX+=angleX;
	if(m_rotateAngleX>360)
		m_rotateAngleX=0;

	m_rotateAngleY+=angleY;
	if(m_rotateAngleY>360)
		m_rotateAngleY=0;
}



////////////////////////////////////////////Mouse Event///////////////////////////////////////////////////////////

void C3DSShow::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	if(m_lButtonDown)
	{		
		m_pointTerminal=point;
		int cx=m_pointTerminal.x-m_pointOrigin.x;
		int cy=m_pointTerminal.y-m_pointOrigin.y;		
		
		setRotateParm( (float)cy /20 ,(float)cx/30 );
		
		Render();	
		
	}
		
	CStatic::OnMouseMove(nFlags, point);
}




void C3DSShow::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	m_lButtonDown=true;
	m_pointOrigin=point;

	CStatic::OnLButtonDown(nFlags, point);
}

void C3DSShow::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	m_lButtonDown=false;
	
	CStatic::OnLButtonUp(nFlags, point);
}

//////////////////////////////////////end of Mouse Event//////////////////////////////////////////////////////////////