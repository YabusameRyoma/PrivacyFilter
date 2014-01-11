// PrivacyFilterDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "PrivacyFilter.h"
#include "PrivacyFilterDlg.h"
#include "SettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

LRESULT CALLBACK LowLevelMouseProc(int aCode, WPARAM wParam, LPARAM lParam);
CPrivacyFilterDlg *lpcMain;
HHOOK hHook;

// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

// ����
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult);
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK1, &CAboutDlg::OnNMClickSyslink1)
END_MESSAGE_MAP()


// CPrivacyFilterDlg �_�C�A���O




CPrivacyFilterDlg::CPrivacyFilterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrivacyFilterDlg::IDD, pParent)
	, m_bAlpha(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPrivacyFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPrivacyFilterDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_COMMAND(ID_FILTER_COLOR_SETTING, &CPrivacyFilterDlg::OnFilterColorSetting)
	ON_COMMAND(ID_EXIT, &CPrivacyFilterDlg::OnExit)
	ON_COMMAND(ID_FILTER_ALPHA_SETTING, &CPrivacyFilterDlg::OnFilterAlphaSetting)
	ON_WM_CREATE()
	ON_COMMAND(ID_32777, &CPrivacyFilterDlg::On32777)
END_MESSAGE_MAP()


// CPrivacyFilterDlg ���b�Z�[�W �n���h��

BOOL CPrivacyFilterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "�o�[�W�������..." ���j���[���V�X�e�� ���j���[�ɒǉ����܂��B

	// IDM_ABOUTBOX �́A�V�X�e�� �R�}���h�͈͓̔��ɂȂ���΂Ȃ�܂���B
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�


	lpcMain = this;

	m_stNotifyIcon.cbSize = sizeof(NOTIFYICONDATA);
	m_stNotifyIcon.uID = 0;
	m_stNotifyIcon.hWnd = m_hWnd;
	m_stNotifyIcon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO;
	m_stNotifyIcon.hIcon = AfxGetApp()->LoadIcon( IDR_MAINFRAME );
	m_stNotifyIcon.uCallbackMessage = WM_USER_POPUP;
	lstrcpy( m_stNotifyIcon.szTip, _T("�v���C�o�V�[�t�B���^�[" ));

	lstrcpy(m_stNotifyIcon.szInfo,_T("����ɃJ�[�\���������Ă����A�}�E�X�z�C�[������]������ƃt�B���^�[�Z�x���ς��܂��B"));
	m_stNotifyIcon.uTimeout = 30000;
	lstrcpy(m_stNotifyIcon.szInfoTitle,_T("�v���C�o�V�[�t�B���^�["));
	m_stNotifyIcon.dwInfoFlags = NIIF_INFO;

	::Shell_NotifyIcon( NIM_ADD, &m_stNotifyIcon );

	int iResolutionX=GetSystemMetrics(SM_CXSCREEN);
	int iResolutionY=GetSystemMetrics(SM_CYSCREEN);
	SetWindowPos(&wndTopMost,0,0,iResolutionX,iResolutionY,SWP_SHOWWINDOW | SWP_NOSIZE);
	ShowWindow(SW_SHOWMAXIMIZED);

	m_bAlpha = GetPrivateProfileInt(_T("Setting"),_T("Alpha"),100,_T("./config.ini"));
	m_FilterColor = (COLORREF)GetPrivateProfileInt(_T("Setting"),_T("Color"),0x00000000,_T("./config.ini"));

	if(m_bAlpha < 0){
		m_bAlpha = 0;
	}
	if(m_bAlpha > 255){
		m_bAlpha = 255;
	}

	FilterUpdate();

	HINSTANCE hInst = GetModuleHandle(NULL);

	hHook = SetWindowsHookExW(WH_MOUSE_LL,LowLevelMouseProc,hInst,0);


	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}

void CPrivacyFilterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CPrivacyFilterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CPrivacyFilterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// �t�B���^�[�X�V
void CPrivacyFilterDlg::FilterUpdate(void)
{
	CDC *pDC = GetDC();

	RECT Rect;
	Rect.left = 0;
	Rect.top = 0;
	Rect.right = GetSystemMetrics(SM_CXSCREEN);
	Rect.bottom = GetSystemMetrics(SM_CYSCREEN);

	SetLayeredWindowAttributes(0,m_bAlpha,LWA_ALPHA);

	HBRUSH hBrush = CreateSolidBrush(m_FilterColor);
	FillRect(pDC->GetSafeHdc(),&Rect,hBrush);

	TRACE("Alpha=%d\n",m_bAlpha);

	DeleteObject(hBrush);
}

LRESULT CALLBACK LowLevelMouseProc(int aCode, WPARAM wParam, LPARAM lParam)
{
	if (aCode != HC_ACTION)
		return CallNextHookEx(hHook, aCode, wParam, lParam);

	MSLLHOOKSTRUCT *pmsllhook = (MSLLHOOKSTRUCT *)lParam;
	short wheel_delta;

        switch (wParam)
        {
		case WM_MOUSEHWHEEL:
		case WM_MOUSEWHEEL:
			if(pmsllhook->pt.x <= 10 && pmsllhook->pt.y <= 10){
				wheel_delta = GET_WHEEL_DELTA_WPARAM(pmsllhook->mouseData);
				if(wheel_delta >= 0){
					if(lpcMain->m_bAlpha + 10 <= 255){
						lpcMain->m_bAlpha+=10;
						lpcMain->FilterUpdate();
					}
				}
				else{
					if(lpcMain->m_bAlpha - 10 >= 0){
						lpcMain->m_bAlpha-=10;
						lpcMain->FilterUpdate();
					}
				}
                break;
        }
    }

    return 0;
}
void CPrivacyFilterDlg::OnDestroy()
{
	CDialog::OnDestroy();

	::Shell_NotifyIcon( NIM_DELETE, &m_stNotifyIcon );

}

LRESULT CPrivacyFilterDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if( message == WM_USER_POPUP ) {
		// �J�[�\���̌��݈ʒu���擾
		POINT point;
		::GetCursorPos(&point);

		CSettingDlg settingDlg(this);

		switch(lParam) {
			case WM_LBUTTONDBLCLK:
				settingDlg.DoModal();
				break;
			case WM_RBUTTONDOWN:
				SetForegroundWindow();	// ���̏�����Y�ꂸ�ɁI
				CMenu menu;
				VERIFY(menu.LoadMenu(IDR_MENU1));
				CMenu* pPopup = menu.GetSubMenu(0);
				ASSERT(pPopup != NULL);
				pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
				PostMessage(WM_NULL);	// ���̏������Y�ꂸ�ɁI
				break;
		}
	}

	return CDialog::WindowProc(message, wParam, lParam);
}

void CPrivacyFilterDlg::OnFilterColorSetting()
{
	CColorDialog colorDlg(m_FilterColor);
	if(colorDlg.DoModal() == IDOK){
		m_FilterColor = colorDlg.GetColor();
		FilterUpdate();
	}
}

void CPrivacyFilterDlg::OnFilterAlphaSetting()
{
	CSettingDlg settingDlg(this);
	settingDlg.DoModal();
}

void CPrivacyFilterDlg::OnExit()
{
	CString strTmp;
	strTmp.Format(_T("%d"),m_bAlpha);
	WritePrivateProfileString(_T("Setting"),_T("Alpha"),strTmp,_T("./config.ini"));
	strTmp.Format(_T("%ld"),m_FilterColor);
	WritePrivateProfileString(_T("Setting"),_T("Color"),strTmp,_T("./config.ini"));
	OnOK();
}


int CPrivacyFilterDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	FilterUpdate();

	return 0;
}

void CPrivacyFilterDlg::On32777()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CAboutDlg::OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult)
{
	 ShellExecute( NULL , NULL , _T("http://komars.dip.jp/software/"), NULL, NULL, SW_SHOWNORMAL);
	*pResult = 0;
}
