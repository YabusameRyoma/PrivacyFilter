// PrivacyFilterDlg.h : ヘッダー ファイル
//

#pragma once


// CPrivacyFilterDlg ダイアログ
class CPrivacyFilterDlg : public CDialog
{
// コンストラクション
public:
	CPrivacyFilterDlg(CWnd* pParent = NULL);	// 標準コンストラクタ

// ダイアログ データ
	enum { IDD = IDD_PRIVACYFILTER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// フィルター濃度
	BYTE m_bAlpha;
	// フィルター更新
	void FilterUpdate(void);
private:
	// アイコンデータ
	NOTIFYICONDATA m_stNotifyIcon;
public:
	afx_msg void OnDestroy();
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnFilterColorSetting();
	// フィルター色
	COLORREF m_FilterColor;
	afx_msg void OnExit();
	afx_msg void OnFilterAlphaSetting();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void On32777();
};
