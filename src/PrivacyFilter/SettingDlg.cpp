// SettingDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "PrivacyFilter.h"
#include "SettingDlg.h"


// CSettingDlg ダイアログ

IMPLEMENT_DYNAMIC(CSettingDlg, CDialog)

CSettingDlg::CSettingDlg(CWnd* pParent)
	: CDialog(CSettingDlg::IDD, pParent)
	, m_ValEdit(_T(""))
	, m_ValSlider(0)
{
	m_lpMain = (CPrivacyFilterDlg*)AfxGetMainWnd();
}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_Slider);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
	DDX_Text(pDX, IDC_EDIT1, m_ValEdit);
	DDX_Slider(pDX, IDC_SLIDER1, m_ValSlider);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialog)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CSettingDlg::OnNMCustomdrawSlider1)
	ON_BN_CLICKED(IDOK, &CSettingDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSettingDlg メッセージ ハンドラ

void CSettingDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	
	SetDlgItemInt(IDC_EDIT1,m_Slider.GetPos());
	m_lpMain->m_bAlpha = m_Slider.GetPos();
	m_lpMain->FilterUpdate();

	*pResult = 0;
}

void CSettingDlg::OnBnClickedOk()
{
	m_lpMain->m_bAlpha = m_Slider.GetPos();
	m_lpMain->FilterUpdate();
	OnOK();
}

BOOL CSettingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Slider.SetRange(0, 255);
    m_Slider.SetPos(m_lpMain->m_bAlpha);
	SetDlgItemInt(IDC_EDIT1,m_lpMain->m_bAlpha);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
