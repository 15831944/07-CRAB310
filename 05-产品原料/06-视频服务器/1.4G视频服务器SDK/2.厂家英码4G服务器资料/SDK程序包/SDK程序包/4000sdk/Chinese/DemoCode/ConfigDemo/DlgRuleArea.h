#pragma once
#include "afxwin.h"


// CDlgRuleArea �Ի���
class CDlgRuleArea : public CDialog
{
	DECLARE_DYNAMIC(CDlgRuleArea)

public:
	CDlgRuleArea(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgRuleArea();

	virtual BOOL OnInitDialog();
	TCHAR m_strFileName[256];
	HINSTANCE OldResourceHanlde;
	void CatchPic();
	void StartUpPreview(BOOL bPreview);
	BOOL GetAppPath(char *szPath);
	void ReInit();
	bool StructToWinData();
	bool StructToWinData(int nChannelNum, bool bCopy = false);	

	BOOL InitWndShow();
	void DrawRules(CDC *pDC, SDK_URP_TRIPWIRE_RULE_PARA_S *pRules);
	void DrawRules(CDC *pDC, SDK_URP_PERIMETER_RULE_PARA_S *pRules);
	int PointToLine( URP_SDK_POINT_S, URP_SDK_POINT_S startPoint, URP_SDK_POINT_S endPoint);
	bool CheckOutArea(CPoint point);
	void drawline(CDC *pDC, URP_SDK_POINT_S ptStart, URP_SDK_POINT_S ptEnd);
	bool CheckSelect(CPoint pt);
	void Drawarrows(CDC* pDC,URP_SDK_POINT_S point1, URP_SDK_POINT_S point2);
	//���浱ǰ����
	bool SaveCurRule();
	int m_nChannelNum;
	int m_nwidth;
	int m_nheight;
	CStatic m_bkPic;
	CMenu m_contextMenu;
	void InitDlgInfo( SDK_RULECONFIG* pRule,int nRule,int nChannelNum);
	
	int		m_nRule;		//
	int		m_nLineType;	// 0 ֱ�� 1 ���� 2 ���� 3 ���������
	int        m_nTripwireNum;
	int        m_nPerimeterNum;
	bool m_bGet[NET_MAX_CHANNUM];			//��¼ÿ��ͨ���Ƿ��ȡ������
	bool m_bGetType;			//��ȡ����ͨ������

	
	int m_nCurIndex;		//��ǰѡ�й����±�
	
	SDK_URP_TRIPWIRE_S m_curTripwire;	//��¼��ǰ�����ӵĹ���
	SDK_URP_TRIPWIRE_RULE_PARA_S m_curTripwireRule;	
	SDK_URP_PERIMETER_RULE_PARA_S m_curPerimeterRule;
	//��¼��ʾͼƬλ����Ի���ľ��룬���㻭��
	int m_nPicLeft;
	int m_nPicTop;
	CPen m_pen;
	CPen m_SelectPen;
	bool m_MouseDown;
	CPoint m_ptOrigin;
	CPoint m_ptEnd;
	CBitmap m_bmpBack_Up;
	bool m_bSelected;		//�Ƿ�ѡ��һ������
	bool m_bDrawLine;		//�Ƿ��ڵȴ�����״̬
	bool m_bCanDraw;
	int m_nPicWidth;
	int m_nPicHeight;
// �Ի�������
	enum { IDD = IDD_DIALOG_RULE_AREA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	
	afx_msg void OnMenucontextMenuEdit();
	afx_msg void OnMenucontextMenuDelete();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
