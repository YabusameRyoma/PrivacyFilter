// PrivacyFilter.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル
#define WM_USER_POPUP	WM_USER+100  // この１行を追加！


// CPrivacyFilterApp:
// このクラスの実装については、PrivacyFilter.cpp を参照してください。
//

class CPrivacyFilterApp : public CWinApp
{
public:
	CPrivacyFilterApp();

// オーバーライド
	public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CPrivacyFilterApp theApp;