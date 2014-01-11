#pragma once
#include "afxcmn.h"
#include "privacyfilterdlg.h"
#include "afxwin.h"


// CSettingDlg ダイアログ

class CSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CSettingDlg();

// ダイアログ データ
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	CSliderCtrl m_Slider;
	CPrivacyFilterDlg *m_lpMain;
	virtual BOOL OnInitDialog();
	CEdit m_Edit;
	CString m_ValEdit;
	int m_ValSlider;
};
