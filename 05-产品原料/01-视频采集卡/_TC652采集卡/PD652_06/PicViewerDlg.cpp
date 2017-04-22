// PicViewerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dlgDemo.h"
#include "PicViewerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PicViewerDlg dialog


PicViewerDlg::PicViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(PicViewerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(PicViewerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void PicViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PicViewerDlg)
	DDX_Control(pDX, IDC_PIC, m_ctrlPic);
	DDX_Control(pDX, IDC_LIST2, m_ctrlList2);
	DDX_Control(pDX, IDC_LIST1, m_ctrlList1);
	DDX_Control(pDX, IDC_BTNPREV, m_ctrlBtnPrev);
	DDX_Control(pDX, IDC_BTNNEXT, m_ctrlBtnNext);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PicViewerDlg, CDialog)
	//{{AFX_MSG_MAP(PicViewerDlg)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	ON_LBN_DBLCLK(IDC_LIST2, OnDblclkList2)
	ON_BN_CLICKED(IDC_BTNPREV, OnBtnprev)
	ON_BN_CLICKED(IDC_BTNNEXT, OnBtnnext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PicViewerDlg message handlers

BOOL PicViewerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	//��ʼ����Ա����
	list2ItemCount=0;
	list2Index=0;
	
	m_bFullScreen=false;
	// TODO: Add extra initialization here






	//���ð�ťͼ��
//��һ�� ��ť
//	m_ctrlBtnNext.m_bIsCheckBox=true;
	m_ctrlBtnNext.SetWindowText("");   //��հ�ť�ϵ�����
	m_ctrlBtnNext.SetAlign(0);
	m_ctrlBtnNext.SetIcon(IDI_NEXTBTN2,IDI_NEXTBTN1);
	m_ctrlBtnNext.SetFlat(true);
	m_ctrlBtnNext.DrawTransparent(TRUE);
	m_ctrlBtnPrev.MoveWindow(0,248,62,80);
	
//��һ�� ��ť	
	m_ctrlBtnPrev.SetAlign(0);	
	m_ctrlBtnPrev.SetIcon(IDI_PREVBTN2,IDI_PREVBTN1);	
	m_ctrlBtnPrev.SetFlat(true);
	m_ctrlBtnPrev.DrawTransparent(TRUE);	
	m_ctrlBtnNext.MoveWindow(656,248,62,80);
	

	
	//���ô����С
	this->SetWindowText("ͼƬ���");
	this->MoveWindow(106,145,1026,606);
	
	m_ctrlPic.MoveWindow(0,0,720,576);
//	m_ctrlPic.MoveWindow(0,0,1200,800);  //just for test 20161020
	//�����б���λ�� 
	m_ctrlList1.MoveWindow(720,0,300,287);
	m_ctrlList2.MoveWindow(720,289,300,287);
	//�����б���������
	CFont font;
	font.CreatePointFont(200,"����");     //�б��������趨
	m_ctrlList1.SetFont(&font);
	m_ctrlList2.SetFont(&font);
	font.Detach();

	
	

	
	CString fileName="";
	
	CString AppPath; 
	//�õ���ǰ����·��
	GetModuleFileName(NULL,AppPath.GetBufferSetLength(1023),1024); 
	AppPath.ReleaseBuffer(); 
	int nPos; 
	nPos = AppPath.ReverseFind('\\'); 
	AppPath = AppPath.Left(nPos); 
	//ini�ļ��洢·��
	fileName=AppPath+"\\res\\ODLog720x576.jpg";
	if (m_ctrlPic.Load(fileName) )
		m_ctrlPic.Draw();
	
//	HBITMAP hBitmap;
//	hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_ODLOG480)); 
//	m_ctrlPic.SetBitmap(hBitmap); 

	//ˢ���б�1
	TCHAR szPath[MAX_PATH];
	_tcscpy(szPath, RootPath);   //CString to TCHAR
	//	TCHAR szPath[MAX_PATH] ={"C:\\CRABUserData"} ; 
	//�ú�������ָ�����ļ���ƥ��������ļ�����������б��
	int nReslt = DlgDirList(szPath , IDC_LIST1 ,NULL,DDL_EXCLUSIVE|DDL_DIRECTORY );    //ֻ��ʾĿ¼�ļ�
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void PicViewerDlg::OnDblclkList1() 
{
	// TODO: Add your control notification handler code here
	CString str;
	int index=m_ctrlList1.GetCurSel();
	m_ctrlList1.GetText(index,str);

	//��ȡlist2��Item��Ŀ
	str.Replace("[", NULL);
	str.Replace("]", NULL);	

	PicPath=RootPath+"\\"+str+"\\Pic";	

	TCHAR szPath[MAX_PATH];
	_tcscpy(szPath, PicPath);   //CString to TCHAR

	//�ú�������ָ�����ļ���ƥ��������ļ�����������б��
	int nReslt = DlgDirList(szPath , IDC_LIST2 ,NULL,DDL_EXCLUSIVE|DDL_ARCHIVE );   //��ʾ�ļ�

	//���list2����ܻ�ȡ���������
	list2ItemCount = m_ctrlList2.GetCount();
	list2Index=0;		//��������װlist2������list2Index��������ס��һ���б���ֵ��
	
}

void PicViewerDlg::OnDblclkList2() 
{
	// TODO: Add your control notification handler code here
	CString str;
	list2Index=m_ctrlList2.GetCurSel();
	m_ctrlList2.GetText(list2Index,str);	
	
	m_PicFilePath=PicPath+"\\"+str;
	
	
	ShowPicture();  //��ʾͼƬ
	
	m_ctrlBtnNext.ShowWindow(SW_SHOW);
	m_ctrlBtnPrev.ShowWindow(SW_SHOW);
	m_ctrlBtnNext.DrawTransparent(TRUE);	//ÿ���ػ�ǰ����������͸����
	m_ctrlBtnPrev.DrawTransparent(TRUE);	//ÿ���ػ�ǰ����������͸����
	
	Invalidate();
	
	UpdateData(FALSE);
}

void PicViewerDlg::OnBtnprev() 
{
	// TODO: Add your control notification handler code here
	if(list2ItemCount==0)
		return ;
	
	CString str;
	
	if(list2Index==0)   //�Ѿ������һ��
	{
		list2Index=list2ItemCount-1;
	}
	else
	{
		list2Index--;
	}
	
	
	m_ctrlList2.GetText(list2Index,str);
	m_ctrlList2.SetCurSel(list2Index);	
	
	m_PicFilePath=PicPath+"\\"+str;	
	
	ShowPicture();  //��ʾͼƬ
	
	m_ctrlBtnNext.ShowWindow(SW_SHOW);
	m_ctrlBtnPrev.ShowWindow(SW_SHOW);
	
	m_ctrlBtnNext.DrawTransparent(TRUE);	//ÿ���ػ�ǰ����������͸����
	m_ctrlBtnPrev.DrawTransparent(TRUE);	//ÿ���ػ�ǰ����������͸����
	
	Invalidate();
	
	
}

void PicViewerDlg::OnBtnnext() 
{
	// TODO: Add your control notification handler code here
		if(list2ItemCount==0)
		return ;
	
	CString str;

	if(list2Index==list2ItemCount-1)   //�Ѿ������һ��
	{
		list2Index=0;
	}
	else
	{
		list2Index++;
	}


	m_ctrlList2.GetText(list2Index,str);
	m_ctrlList2.SetCurSel(list2Index);	

	m_PicFilePath=PicPath+"\\"+str;	
	
	ShowPicture();  //��ʾͼƬ
	
		m_ctrlBtnNext.DrawTransparent(TRUE);	//ÿ���ػ�ǰ����������͸����
	m_ctrlBtnPrev.DrawTransparent(TRUE);	//ÿ���ػ�ǰ����������͸����
	m_ctrlBtnNext.ShowWindow(SW_SHOW);
	m_ctrlBtnPrev.ShowWindow(SW_SHOW);

	
	Invalidate();
	
}


void PicViewerDlg::ShowPicture()
{
	
//just for test 20161020
/*	CRect rc =CRect(100,400,150,450);
	m_ctrlPic.MoveWindow(&rc,true);*/
//end of test

		if (m_ctrlPic.Load(m_PicFilePath))
		m_ctrlPic.Draw();

}

BOOL PicViewerDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

        if (WM_LBUTTONDBLCLK == pMsg->message) // 1 ���˫����Ӧ
        {
			//��ȡ���λ��
            CPoint ptCursor;
            GetCursorPos(&ptCursor);
			
            CRect rc;
            GetDlgItem(IDC_PIC)->GetWindowRect(&rc);

			//���������Ϊ�˱ܿ���һ�Ű�ť����������
////////////////////
			CRect rcButtonPrev;
			GetDlgItem(IDC_BTNPREV)->GetWindowRect(&rcButtonPrev);
			CRect rcButtonNext;
			GetDlgItem(IDC_BTNNEXT)->GetWindowRect(&rcButtonNext);
			
			rc.left=rc.left+rcButtonPrev.Width();
			rc.right=rc.right-rcButtonNext.Width();
///////////////////
            //1.1 ˫��ʱ���λ��Picture�ؼ���Χ�ڲ���Ӧ
            if (rc.PtInRect(ptCursor))
            {
                if (FALSE == m_bFullScreen)
                {
                    FullScreenShow(); //ȫ����ʾ
                }
                else
                {
                    NormalShow();  //�ָ�Ĭ����ʾ
                }
				
            }
        } //end of if (WM_LBUTTONDBLCLK == pMsg->message)
		else if(WM_LBUTTONUP==pMsg->message)  //2 ��������
		{
			//��ȡ���λ��
            CPoint ptCursor;
            GetCursorPos(&ptCursor);
			
            CRect rc;
            GetDlgItem(IDC_PIC)->GetWindowRect(&rc);
			
            //1.1 ˫��ʱ���λ��Picture�ؼ���Χ�ڲ���Ӧ
            if (rc.PtInRect(ptCursor))
            {
				//
            }
		}
        else if (WM_KEYDOWN == pMsg->message) // 3 ����������Ӧ
        {
            // 2.1��������Esc
            if (VK_ESCAPE == pMsg->wParam)
            {
				if (TRUE == m_bFullScreen)
				{
					NormalShow();  //�ָ�Ĭ����ʾ
				}                
            }
			
            // 2.2��������Enter
            if (VK_RETURN == pMsg->wParam)
            {
                if (FALSE == m_bFullScreen)
                {
                    FullScreenShow(); //ȫ����ʾ
                }
                else
                {
                    NormalShow();  //�ָ�Ĭ����ʾ
                }
            }
        } //end of if (WM_KEYDOWN == pMsg->message)

	
	
	return CDialog::PreTranslateMessage(pMsg);
}

/**************************************ȫ����ʾ����***************************************************/
void PicViewerDlg::FullScreenShow()
{

	 if ( FALSE == m_bFullScreen )
    {
        m_bFullScreen = TRUE;



        //��ȡ�Ի���ԭʼλ��
        GetWindowPlacement(&m_OldWndPlacement);
		GetDlgItem(IDC_PIC)->GetWindowPlacement(&m_OldPicPlacement);

        CRect WindowRect;
        GetWindowRect(&WindowRect);

        CRect ClientRect;
        RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &ClientRect);
        ClientToScreen(&ClientRect);

        //��ȡ��Ļ�ķֱ���
        int nFullWidth  = GetSystemMetrics(SM_CXSCREEN);
        int nFullHeight = GetSystemMetrics(SM_CYSCREEN);

        //�Ի���ȫ����ʾ
        m_FullScreenRect.left = WindowRect.left - ClientRect.left;
        int m_top = WindowRect.top - ClientRect.top;
        m_FullScreenRect.top    = m_top;
        m_FullScreenRect.right  = WindowRect.right - ClientRect.right + nFullWidth;
        m_FullScreenRect.bottom = WindowRect.bottom - ClientRect.bottom + nFullHeight;

        m_NewWndPlacement.length           = sizeof(WINDOWPLACEMENT);
        m_NewWndPlacement.flags            = 0;
        m_NewWndPlacement.showCmd          = SW_SHOWNORMAL;
        m_NewWndPlacement.rcNormalPosition = m_FullScreenRect;
        SetWindowPlacement(&m_NewWndPlacement);
		
        //Picture�ؼ�ȫ����ʾ
	//	GetDlgItem(IDC_PIC)->MoveWindow(CRect(0, 0, 100, 600));

     //  GetDlgItem(IDC_PIC)->MoveWindow(CRect(0, 0, nFullWidth, nFullHeight));
	  // 	m_ctrlPic.MoveWindow(100,0,1000,800);

	
		AdjustPositon(CRect(0, 0, nFullWidth, nFullHeight) );	
/*m_ctrlPic.SetBkColor(RGB(0,0,0));

		ShowPicture();  //��ʾͼƬ*/
		
		//Modified by wu 20161012

/*		m_ctrlODLogPic.MoveWindow(100,100,1280,550);
		HBITMAP hBitmap; 
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_ODLOG550)); 
		m_ctrlODLogPic.SetBitmap(hBitmap);  
*/

		//end of Modified
		
		
        //���ؿؼ�
		ShowOtherWidget(FALSE);
		//�ػ�
		Invalidate(FALSE);
		UpdateWindow();
        
    }
}

void PicViewerDlg::NormalShow()
{
	if (TRUE == m_bFullScreen)
    {
        //�ָ�Ĭ�ϴ���
        SetWindowPlacement(&m_OldWndPlacement);
		GetDlgItem(IDC_PIC)->SetWindowPlacement(&m_OldPicPlacement);
		
		AdjustPositon(CRect(0, 0, 720, 576));

		
        m_bFullScreen = FALSE;
		
        //��ʾ�ؼ�
		ShowOtherWidget(TRUE);

		//�ػ�
		Invalidate(FALSE);
       
    }
}

//ȫ���л�ʱ������ʾ��������������
void PicViewerDlg::ShowOtherWidget(bool SWMode)
{


	//��ʾ
	if(SWMode)
	{
		m_ctrlList1.ShowWindow(SW_SHOW);
		m_ctrlList2.ShowWindow(SW_SHOW);

		m_ctrlBtnPrev.ShowWindow(SW_SHOW);
		m_ctrlBtnNext.ShowWindow(SW_SHOW);




	
		
	}
	//����
	else
	{
		m_ctrlList1.ShowWindow(SW_HIDE);
		m_ctrlList2.ShowWindow(SW_HIDE);

		m_ctrlBtnPrev.ShowWindow(SW_HIDE);
		m_ctrlBtnNext.ShowWindow(SW_HIDE);
	}
}

//���溯���ɹ�����ʱ����
void PicViewerDlg::AdjustPositon(CRect rect)
{
	
	m_ctrlPic.SetPaintRect(&rect);
	m_ctrlPic.MoveWindow(&rect, TRUE);		
	
}