
// ProxyClient3.h : ProxyClient3 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CProxyClient3App:
// �йش����ʵ�֣������ ProxyClient3.cpp
//

class CProxyClient3App : public CWinAppEx
{
public:
	CProxyClient3App();


// ��д
public:
	int m_heart_elapse;
	virtual BOOL InitInstance();
	virtual ~CProxyClient3App();
// ʵ��

public:
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	
};

extern CProxyClient3App theApp;
