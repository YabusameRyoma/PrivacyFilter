// PrivacyFilterDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once


// CPrivacyFilterDlg �_�C�A���O
class CPrivacyFilterDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CPrivacyFilterDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^

// �_�C�A���O �f�[�^
	enum { IDD = IDD_PRIVACYFILTER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g


// ����
protected:
	HICON m_hIcon;

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// �t�B���^�[�Z�x
	BYTE m_bAlpha;
	// �t�B���^�[�X�V
	void FilterUpdate(void);
private:
	// �A�C�R���f�[�^
	NOTIFYICONDATA m_stNotifyIcon;
public:
	afx_msg void OnDestroy();
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnFilterColorSetting();
	// �t�B���^�[�F
	COLORREF m_FilterColor;
	afx_msg void OnExit();
	afx_msg void OnFilterAlphaSetting();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void On32777();
};
