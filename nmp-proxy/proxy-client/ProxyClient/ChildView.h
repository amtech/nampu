
// ChildView.h : CChildView ��Ľӿ�
//

/*
 * @author: xiaohe
 * @date: 2003/03/04 
 * @detail: �ô��������û���½�ɹ��Ժ�չ�ָ��û��Ĵ��ڣ�������������ѯ���豸����.  
 *
 */

#pragma once

#include "maindevice.h"
#include "mainuser.h"
#include "skinbtn.h"
#include "afxwin.h"


// CChildView ����

class CChildView : public CWnd
{
// ����
public:
	CChildView();

// ����
public:

// ����
public:

// ��д
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CChildView();

	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
private:
 	CSkinBtn m_DeviceBtn;
 	CSkinBtn m_UserBtn;
	CSkinBtn m_config_btn;
	CSkinBtn m_logout_btn;
	CSkinBtn m_data_btn;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMainDevice();
	afx_msg void OnMainUser();
	CMainDevice m_MainDevice;
	CMainUser m_MainUser;
	S_Prameter *m_prameter;
	
	int m_timeout;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_heart_elapse;
	
	void OnLogout(void);
	void OnConfig(void);
	void OnData(void);
};

