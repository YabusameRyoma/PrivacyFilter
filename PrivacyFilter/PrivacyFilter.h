// PrivacyFilter.h : PROJECT_NAME �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"		// ���C�� �V���{��
#define WM_USER_POPUP	WM_USER+100  // ���̂P�s��ǉ��I


// CPrivacyFilterApp:
// ���̃N���X�̎����ɂ��ẮAPrivacyFilter.cpp ���Q�Ƃ��Ă��������B
//

class CPrivacyFilterApp : public CWinApp
{
public:
	CPrivacyFilterApp();

// �I�[�o�[���C�h
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CPrivacyFilterApp theApp;