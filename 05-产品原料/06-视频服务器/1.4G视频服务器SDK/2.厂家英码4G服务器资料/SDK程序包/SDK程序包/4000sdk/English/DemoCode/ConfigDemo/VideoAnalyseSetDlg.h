#pragma once
//#include "Interface/DlgSetBase.h"
//#include "DlgRuleArea.h"
#include "afxcmn.h"

// CVideoAnalyseSetDlg �Ի���

class CVideoAnalyseSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CVideoAnalyseSetDlg)

public:
	CVideoAnalyseSetDlg(SDK_RULECONFIG* pRule,int nChannelNum,int nModuleType,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CVideoAnalyseSetDlg();
	SDK_RULECONFIG m_Rule;
	SDK_RULECONFIG m_oldRule;
	int m_nChannelNum;
	int m_nRule;
	int m_nModuleType;
	CSliderCtrl m_sliderRangeMin;
	CSliderCtrl m_sliderTimeMin;	
	HINSTANCE OldResourceHanlde;
	virtual BOOL OnInitDialog();
// �Ի�������
	enum { IDD = IDD_DLG_ALARM_PEARULE_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedBtnRuleSet();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCheckShowtrace();
	afx_msg void OnCbnSelchangeComboSensitivityLevel();
	afx_msg void OnBnClickedRadioUrpTripwire();
	afx_msg void OnBnClickedRadioUrpPerimeter();
	afx_msg void OnNMReleasedcaptureSliderRangeMin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderTimeMin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
