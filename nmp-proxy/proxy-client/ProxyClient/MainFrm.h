
// MainFrm.h : CMainFrame ��Ľӿ�
//

/*
 * @Author: Microsoft
 * @Date  : 2003-03-04 
 * @Detail: ���ڵ��ĵ�ģ���������Ի��� 
 *			
 */

#pragma once
#include "ChildView.h"

class CMainFrame : public CFrameWndEx
{
	
public:
	CMainFrame();
	CMFCStatusBar     m_wndStatusBar;
protected: 
	DECLARE_DYNAMIC(CMainFrame)
	

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CChildView    m_wndView;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnNcPaint();
	int m_heart_elapse;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_timeout;
	void ShowTime(CString);
	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


