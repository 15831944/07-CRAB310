// MyProgress.cpp : implementation file
//

#include "stdafx.h"
//#include "dlgDemoDlg.h"
#include "MyProgress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MyProgress

MyProgress::MyProgress()
{
	this->m_freeColor=RGB(255,0,0);
	this->m_prgsColor=RGB(0,255,0);
	this->m_freeTextColor=RGB(200,200,200);
	this->m_prgsTextColor=RGB(26,26,26);



}

MyProgress::~MyProgress()
{
}


BEGIN_MESSAGE_MAP(MyProgress, CProgressCtrl)
	//{{AFX_MSG_MAP(MyProgress)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MyProgress message handlers
int MyProgress::SetPos(int nPos)
{
	if (!::IsWindow(m_hWnd))
	{
		return -1;
	}
	int nOldPos = m_iPos;
	m_iPos = nPos;
	CRect rect;
	GetClientRect(rect);
	//�����ȼ���Ҫ��ʾ�Ľ�������ȣ������ͬһ���ȶ�λ��ƴ���
	double Fraction = (double)(m_iPos - m_iMin) / ((double)(m_iMax - m_iMin));
	int nBarWidth = (int) (Fraction * rect.Width());
	if (nBarWidth != m_nBarWidth)
	{
		m_nBarWidth = nBarWidth;
		RedrawWindow();
	}
	return nOldPos;
	
}

void MyProgress::SetRange(int nLower, int nUpper)
{
	m_iMax = nUpper;
	m_iMin = nLower;
	m_iPos = m_iMin;
	m_nBarWidth = 0;
}


void MyProgress::OnPaint()
{
	//�����ж������Ƿ���Ч
	if (m_iMin >= m_iMax) 
	{
		return;
	}
	CPaintDC dc(this); // device context for painting
	// ��Ϊ��ͼ��Ϣ���� CProgressCtrl::OnPaint()
	
	//��ȡ��Ч�Ľ�������λ�úʹ�С
	CRect LeftRect, RightRect, ClientRect;
	GetClientRect(ClientRect);
	LeftRect = RightRect = ClientRect;
	//������ʾ���ȵı���
	double Fraction = (double)(m_iPos - m_iMin) / ((double)(m_iMax - m_iMin));
	//���������������е���Ч����
	LeftRect.right = LeftRect.left + (int)((LeftRect.right - LeftRect.left) * Fraction);
	dc.FillSolidRect(LeftRect, m_prgsColor);
	//����ʣ�����
	RightRect.left = LeftRect.right;
	dc.FillSolidRect(RightRect, m_freeColor);
	
	CString str;
	str.Format(_T("%d%%"), (int)(Fraction*100.0));
	//�������ֱ�����ɫΪ͸��
	dc.SetBkMode(TRANSPARENT);
	//Ϊ���ܹ��ڽ��Ⱥ�ʣ���������ʾ��ͬ��ɫ�����壬��Ҫ�ֱ��������ߵ�������ɫ����ͼ
	CRgn rgn;
	rgn.CreateRectRgn(LeftRect.left, LeftRect.top, LeftRect.right, LeftRect.bottom);
	dc.SelectClipRgn(&rgn);
	dc.SetTextColor(m_prgsTextColor);
	dc.DrawText(str, ClientRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	rgn.DeleteObject();
	rgn.CreateRectRgn(RightRect.left, RightRect.top, RightRect.right, RightRect.bottom);
	dc.SelectClipRgn(&rgn);
	dc.SetTextColor(m_freeTextColor);
	dc.DrawText(str, ClientRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//�����������������ֻ��ʾһ��������ɫ����ô����ֱ�ӵ���
	//dc.SetTextColor(m_freeTextColor);
	//dc.DrawText(str, ClientRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);




}


void MyProgress::SetColor(COLORREF prgsColor,COLORREF freeColor,COLORREF prgsTextColor, COLORREF freeTextColor)
{
	m_prgsColor=prgsColor;
	m_freeColor=freeColor;
	m_prgsTextColor=prgsTextColor;
	m_freeTextColor=freeTextColor;


}