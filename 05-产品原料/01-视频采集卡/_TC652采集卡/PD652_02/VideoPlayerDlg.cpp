// VideoPlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dlgDemo.h"
#include "VideoPlayerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// VideoPlayerDlg dialog


char* EncodeToUTF8(const char* mbcsStr) 
{ 
	 wchar_t*  wideStr; 
	 char*   utf8Str; 
	 int   charLen; 

	 charLen = MultiByteToWideChar(CP_UTF8, 0, mbcsStr, -1, NULL, 0); 
	 wideStr = (wchar_t*) malloc(sizeof(wchar_t)*charLen); 
	 MultiByteToWideChar(CP_ACP, 0, mbcsStr, -1, wideStr, charLen); 

	 charLen = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, NULL, 0, NULL, NULL); 

	 utf8Str = (char*) malloc(charLen);

	 WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, utf8Str, charLen, NULL, NULL);

	 free(wideStr); 
	 return utf8Str;
} 





VideoPlayerDlg::VideoPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(VideoPlayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(VideoPlayerDlg)
	//}}AFX_DATA_INIT
}

VideoPlayerDlg::~VideoPlayerDlg()
{

}


void VideoPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(VideoPlayerDlg)
	DDX_Control(pDX, IDC_ODLOG_PIC, m_ctrlODLogPic);
	DDX_Control(pDX, IDC_VIDEOPLAYER_PIC, m_ctrlPic);
	DDX_Control(pDX, IDC_VIDEOPLAYER_PLAYTIME, m_ctrlSliderPlayTime);
	DDX_Control(pDX, IDC_VIDEOPLAYER_LIST2, m_ctrlList2);
	DDX_Control(pDX, IDC_VIDEOPLAYER_LIST1, m_ctrlList1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(VideoPlayerDlg, CDialog)
	//{{AFX_MSG_MAP(VideoPlayerDlg)
	ON_LBN_DBLCLK(IDC_VIDEOPLAYER_LIST1, OnDblclkVideoplayerList1)
	ON_LBN_DBLCLK(IDC_VIDEOPLAYER_LIST2, OnDblclkVideoplayerList2)
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// VideoPlayerDlg message handlers

BOOL VideoPlayerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

//��ʼ����Ա����
	m_bNew = true;
	m_vlcInst = NULL;
	m_vlcMedia = NULL;
	m_vlcMplay = NULL;

	m_bNew = true;
	m_bIsRtsp = false;
//	
	m_bOpen=true;

	m_bFullScreen=false;
	m_bIsPlay=false;

	m_TotalTime=0;
	
	// TODO: Add extra initialization here

	SetWindowText("��Ƶ�ط�");
	char *vlc_argv[100];
	int vlc_argc = 0;
	vlc_argv[vlc_argc++] = "--ignore-config";

	m_vlcInst = libvlc_new (vlc_argc, vlc_argv);

	m_ctrlSliderPlayTime.SetRange(0, 1000);
	m_ctrlSliderPlayTime.SetPos(0);


	//��ʼ������
	InitWidget();

	TCHAR szPath[MAX_PATH];
	_tcscpy(szPath, RootPath);   //CString to TCHAR
	//�ú�������ָ�����ļ���ƥ��������ļ�����������б��
	int nReslt = DlgDirList(szPath , IDC_VIDEOPLAYER_LIST1 ,NULL,DDL_EXCLUSIVE|DDL_DIRECTORY );    //ֻ��ʾĿ¼�ļ�


	
	
           
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void VideoPlayerDlg::InitWidget()
{

	this->MoveWindow(106,85,1074,630);
	m_ctrlPic.MoveWindow(0,0,768,550);
	m_ctrlList1.MoveWindow(768,0,300,299);
	m_ctrlList2.MoveWindow(768,301,300,300);
	m_ctrlSliderPlayTime.MoveWindow(0,560,768,30);

	//�����б���������
	CFont font;
	font.CreatePointFont(200,"����");     //�б��������趨
	m_ctrlList1.SetFont(&font);
	m_ctrlList2.SetFont(&font);
	font.Detach();

	//��ʾOD Log
	m_ctrlODLogPic.MoveWindow(0,0,768,550);

	HBITMAP hBitmap; 
	hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_ODLOG550)); 
	m_ctrlODLogPic.SetBitmap(hBitmap);   


}

/////////////////////////////////////////////////////////////��Ƶ����///////////////////////////////////////////////////////////////

void VideoPlayerDlg::OnDblclkVideoplayerList1() 
{
	// TODO: Add your control notification handler code here
	CString str;
	int index=m_ctrlList1.GetCurSel();
	m_ctrlList1.GetText(index,str);
	
	//ȥ��������
	str.Replace("[", NULL);
	str.Replace("]", NULL);
	
	
//	m_player.SetUrl(str);
//	CString VideoPath;
	VideoPath=RootPath+"\\"+str+"\\Video";
//	AfxMessageBox(VideoPath);
	
	//	TCHAR szPath[MAX_PATH] ={"C:\\CRABUserData"} ; 
	TCHAR szPath[MAX_PATH];
	_tcscpy(szPath, VideoPath);

	//�ú�������ָ�����ļ���ƥ��������ļ�����������б��
	int nReslt = DlgDirList(szPath , IDC_VIDEOPLAYER_LIST2 ,NULL,DDL_EXCLUSIVE|DDL_ARCHIVE );   //��ʾ�ļ�
	
}

void VideoPlayerDlg::OnDblclkVideoplayerList2() 
{
	// TODO: Add your control notification handler code here
	m_bNew=true;
	CString str;
	int index=m_ctrlList2.GetCurSel();
	m_ctrlList2.GetText(index,str);
	
	
	//	m_player.SetUrl(str);
	m_VideoFilePath=VideoPath+"\\"+str;
	
	UpdateData(FALSE);
	StopVideo();
	PlayVideo();
}

void VideoPlayerDlg::PlayVideo()
{
		m_bIsPlay=true;

	UpdateData(true);
	if (m_VideoFilePath == "")
	{
		return;
	}
	if(m_bNew == true)
	{
		if(m_vlcMplay != NULL)
		{
			libvlc_media_player_release(m_vlcMplay);
		}
		//	AfxMessageBox(m_VideoFilePath);
		if (m_bIsRtsp == false)
		{
			//�����ļ�
			m_vlcMedia = libvlc_media_new_path (m_vlcInst, EncodeToUTF8(m_VideoFilePath.GetBuffer(0)));
		}
		else
		{
			m_vlcMedia = libvlc_media_new_location(m_vlcInst,m_VideoFilePath.GetBuffer(0));
		}
		
		
		m_vlcMplay = libvlc_media_player_new_from_media (m_vlcMedia);

		//��libVLC���Ŷ�������gPlayHwnd Ϊ���Ŵ��ھ��������libVLC���Ŵ��ھͳ�ΪIDC_PLAYWND�ؼ����Ӵ��ڣ�
		hwndVideoPlayer = GetDlgItem(IDC_VIDEOPLAYER_PIC)->GetSafeHwnd();
		libvlc_media_player_set_hwnd (m_vlcMplay, hwndVideoPlayer);
		libvlc_media_release(m_vlcMedia);
		m_bNew = false;
	}

	libvlc_media_player_play (m_vlcMplay);

	//��ʼ���ź󴴽�һ����ʱ�������ڹر�Picture����������Ӧ�¼�
	SetTimer(1,500,NULL);   

	//��ȡ��Ƶ�ļ���ʱ��
	if (m_bIsRtsp == false)
	{ 
		//��֪��Ϊʲô�����m_TotalTime����0�������ڶ�ʱ����Ĳ���0
		m_TotalTime = libvlc_media_player_get_length(m_vlcMplay);

		//	if(m_TotalTime>0)
		m_playerTimer = SetTimer(100,1*100,NULL);
	}

}

void VideoPlayerDlg::PauseVideo()
{
	
	m_bIsPlay=false;
	if(m_vlcMplay != NULL)
		libvlc_media_player_pause(m_vlcMplay);
}

void VideoPlayerDlg::StopVideo()
{
	if (m_vlcMplay == NULL)
	{
		return;
	}
	libvlc_media_player_stop(m_vlcMplay);
	m_bNew = true;
	m_vlcMplay = NULL;
	//libvlc_exception_clear(&m_vlcEx);
	if (m_vlcMedia != NULL)
	{
		libvlc_media_release(m_vlcMedia);
	}
	if (m_vlcMplay != NULL)
	{
		libvlc_media_player_release(m_vlcMplay);
	}

	KillTimer(100);
	m_ctrlSliderPlayTime.SetPos(0);
	OnPaint();
	
}

void VideoPlayerDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	if (nIDEvent == 100)
	{
		libvlc_time_t m_CurTime = libvlc_media_player_get_time(m_vlcMplay);
		//float fPos = libvlc_media_player_get_position(m_vlcMplay, &m_vlcEx);
		m_TotalTime = libvlc_media_player_get_length(m_vlcMplay);

		int m_npos=0;
		if(m_TotalTime>0)
			m_npos = m_CurTime*1000/m_TotalTime;
		m_ctrlSliderPlayTime.SetPos(m_npos);
		
		//��ȡ����״̬�ĺ���,����ǽ����ͷ���stop�������״̬��
		if(libvlc_Ended == libvlc_media_player_get_state(m_vlcMplay))
		{
			StopVideo();
			
		}
			
	}
	
	//���ڹر�VLC����Ϣ��Ӧ, Ŀ����Ϊ���öԻ��������Ϣ��Ӧ
	if(nIDEvent == 1)
	{
//		TCHAR szWndTitle[1024];
//		int nLen = GetWindowText(hwnd , szWndTitle, 1024);
//		if (0 != nLen)
//		{
			//���������Ϣ
			CWnd* pWnd =GetDlgItem(IDC_VIDEOPLAYER_PIC);
			pWnd->EnableWindow(FALSE);
			KillTimer(1);
		//	}
	}


	
	CDialog::OnTimer(nIDEvent);
}

void VideoPlayerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	if (pScrollBar->GetSafeHwnd() == m_ctrlSliderPlayTime.GetSafeHwnd())
	{
		if (m_vlcMplay != NULL)
		{
			libvlc_time_t m_CurTime;
			m_TotalTime = libvlc_media_player_get_length(m_vlcMplay);
			double pos = m_ctrlSliderPlayTime.GetPos()/1000.0;
			m_CurTime = m_TotalTime * pos;
			libvlc_media_player_set_time(m_vlcMplay,m_CurTime);
		}
	}
	
	else
	{
		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	}
}

////////////////////////////////////////////////////////FullScreen////////////////////////////////////////////////////////////////

//ȫ���л�ʱ������ʾ��������������
void VideoPlayerDlg::ShowOtherWidget(bool SWMode)
{


	//��ʾ
	if(SWMode)
	{
		m_ctrlList1.ShowWindow(SW_SHOW);
		m_ctrlList2.ShowWindow(SW_SHOW);
		m_ctrlSliderPlayTime.ShowWindow(SW_SHOW);


	
		
	}
	//����
	else
	{
		m_ctrlList1.ShowWindow(SW_HIDE);
		m_ctrlList2.ShowWindow(SW_HIDE);
		m_ctrlSliderPlayTime.ShowWindow(SW_HIDE);
	
	}
}




void VideoPlayerDlg::FullScreenShow()
{
    // TODO: Add your command handler code here

    if ((TRUE == m_bOpen) && (FALSE == m_bFullScreen))
    {
        m_bFullScreen = TRUE;

        //��ȡ�Ի���ԭʼλ��
        GetWindowPlacement(&m_OldWndPlacement);
		GetDlgItem(IDC_VIDEOPLAYER_PIC)->GetWindowPlacement(&m_OldPicPlacement);

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
        GetDlgItem(IDC_VIDEOPLAYER_PIC)->MoveWindow(CRect(0, 0, nFullWidth, nFullHeight));
		
		//Modified by wu 20161012

/*		m_ctrlODLogPic.MoveWindow(100,100,1280,550);
		HBITMAP hBitmap; 
		hBitmap = LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_ODLOG550)); 
		m_ctrlODLogPic.SetBitmap(hBitmap);  
*/

		//end of Modified
		
		
        //���ؿؼ�
		ShowOtherWidget(FALSE);

		//��ʾODLog 
		//�������Ƶ���ڲ��ţ�������ODLogPic
		if(m_vlcMplay==NULL)
		{
			m_ctrlODLogPic.MoveWindow(0,0,1280,800);
			ShowODLogPic(CRect(0,0,1280,800));
		}
		else
		{
			m_ctrlODLogPic.ShowWindow(SW_HIDE);
		}
		//�ػ�
		Invalidate(FALSE);
		UpdateWindow();
        
    }
}
//
void VideoPlayerDlg::NormalShow(void)
{
    if ((TRUE == m_bOpen) && (TRUE == m_bFullScreen))
    {
        //�ָ�Ĭ�ϴ���
        SetWindowPlacement(&m_OldWndPlacement);
		GetDlgItem(IDC_VIDEOPLAYER_PIC)->SetWindowPlacement(&m_OldPicPlacement);


        m_bFullScreen = FALSE;

        //��ʾ�ؼ�
		ShowOtherWidget(TRUE);

		//��ʾODLog
		//�������Ƶ���ڲ��ţ�������ODLogPic
		if(m_vlcMplay==NULL)
		{
			m_ctrlODLogPic.MoveWindow(0,0,768,550);
			ShowODLogPic(CRect(0,0,768,550));	
		}
		else
		{
			m_ctrlODLogPic.ShowWindow(SW_HIDE);	
		}


		//�ػ�
		Invalidate(FALSE);
       
    }
}



BOOL VideoPlayerDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (TRUE == m_bOpen)
    {
        if (WM_LBUTTONDBLCLK == pMsg->message) // 1 ���˫����Ӧ
        {
			//��ȡ���λ��
            CPoint ptCursor;
            GetCursorPos(&ptCursor);
			
            CRect rc;
            GetDlgItem(IDC_VIDEOPLAYER_PIC)->GetWindowRect(&rc);
			
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
            GetDlgItem(IDC_VIDEOPLAYER_PIC)->GetWindowRect(&rc);
			
            //1.1 ˫��ʱ���λ��Picture�ؼ���Χ�ڲ���Ӧ
            if (rc.PtInRect(ptCursor))
            {
				if(false==m_bIsPlay)
				{
					PlayVideo();
					m_bIsPlay=true;
				}
				else
				{
					PauseVideo();
					
				}
				//��ͣ����
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
    } // end of if (TRUE == m_bOpen)
	
	
    return 0;
}

//��ʾODLog������ȫ������С��ʾ
//2016 1027
void VideoPlayerDlg::ShowODLogPic(CRect rect)
{		
	CDC * pDC=m_ctrlODLogPic.GetDC();  
    CDC memDC;  
    memDC.CreateCompatibleDC(pDC);  

    CBitmap *avatarBmp=new CBitmap();  
    CBitmap*oldBmp;  
    BITMAP bmInfo;  

    avatarBmp->LoadBitmap(IDB_ODLOG550);  
    avatarBmp->GetObject(sizeof(bmInfo),&bmInfo);  
    oldBmp=memDC.SelectObject(avatarBmp);
	
    pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0,bmInfo.bmWidth,bmInfo.bmHeight,SRCCOPY);  
    if (oldBmp)  
    {  
        memDC.SelectObject(oldBmp);  
    }    
	
    ReleaseDC(pDC); 
}

/////////////////////////////////////////////////end of fullScreen////////////////////////////////////////////////////////////////////////

void VideoPlayerDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	StopVideo();
	
	CDialog::OnClose();
}


//����CStaticû���ֳɵĽӿڣ�Ҫô�Լ��̳�CStaticȻ����дWM_CTLCOLOR����Ӧ������
//Ҫô�ڸ�������дWM_CTLCOLOR����Ӧ������Ȼ�������Ӧ�Ľӿ����ı�������ɫ��ԭ�����£�
//���ڻ��ƿؼ�ǰ��Windows��ÿؼ��ĸ����ڷ���һ��WM_CTLCOLOR��Ϣ��Ŀ���ǻ�øÿؼ�����ɫ�����ڸ���Ӧ�������޸���ɫ�Ĳ���
HBRUSH VideoPlayerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	

	// TODO: Change any attributes of the DC here
	/*
	if (nCtlColor == CTLCOLOR_STATIC)
	{

		switch(pWnd->GetDlgCtrlID())
        {

            case IDC_VIDEOPLAYER_PIC:
                {
                   pDC->SetBkMode(RGB(255,0,0));
                  // pDC->SetTextColor(RGB(0,69, 214));
                   break;
                }
            default:
                break;
        }

	}
	*/
//IDC_VIDEOPLAYER_PIC   IDC_VIDEOPLAYER_LIST2
	if(pWnd->GetDlgCtrlID()==IDC_VIDEOPLAYER_PIC)
	{
		/*
		pDC->SetTextColor(RGB(0,0,0));
		//	pDC->SetBkMode(TRANSPARENT);
		pDC->SetBkColor(RGB(255,0,0));
	//	AfxMessageBox("pWnd->GetDlgCtrlID()==IDC_ODLOG_PI");

		m_brush.DeleteObject();//������ɾ��Ȼ���ٴ�����ˢ
		m_brush.CreateSolidBrush(RGB(250,0,0));
		return m_brush;	
		*/
   pDC->SetBkMode(TRANSPARENT);
   pDC->SetTextColor(RGB(255,255, 0));

   HBRUSH B = CreateSolidBrush(RGB(125,125,255));
   return (HBRUSH) B;

	}


	// TODO: Return a different brush if the default is not desired
	return hbr;
}
