// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A6EF1E93_33EB_476A_B556_185C5C5C1935__INCLUDED_)
#define AFX_STDAFX_H__A6EF1E93_33EB_476A_B556_185C5C5C1935__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <windowsx.h>
#include "DeviceControl.h"
//	#include "BtnST.h"
class CChannelWnd;
extern bool SnapOk;
extern RECT			 g_rcShowWin ;

extern	DWORD dwCard ;


//����·��
extern CString RootPath;     //�ļ���Ŀ¼

extern CString PicSavePath;    //�ļ�1��Ŀ¼����ÿ�ε�¼������Ŀ¼
extern CString RecSavePath;

extern CString PicPath;        //�ļ�2��Ŀ¼��������Ŀ�µ�����Pic��VideoĿ¼
extern CString VideoPath;

extern CString strIniFile;

//�����¼��Ϣ
extern CString customsUint;
extern CString address;
extern CString name;
extern int nComboUintIndex;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A6EF1E93_33EB_476A_B556_185C5C5C1935__INCLUDED_)
