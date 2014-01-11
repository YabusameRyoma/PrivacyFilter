#pragma once
#include "afxcmn.h"
#include "privacyfilterdlg.h"
#include "afxwin.h"


// CSettingDlg �_�C�A���O

class CSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CSettingDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

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
