#if !defined(AFX_DRAWBUTTON_H__BD431877_52EE_41C5_9036_E4A5254C5CF7__INCLUDED_)
#define AFX_DRAWBUTTON_H__BD431877_52EE_41C5_9036_E4A5254C5CF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DrawButton.h : header file
//

/*
 * @author: xiaohe
 * @date: 2003/03/04 
 * @detail: ���Ըı䰴ť��������ɫ���Զ��尴ť����������"��¼����"��"��½"��"ȡ��"
 *			������ť�������豸�Ի�������ƶԻ����е�"ȷ��"��"ȡ��"��ť 
 *
 */

/////////////////////////////////////////////////////////////////////////////
// CDrawButton window

//�Զ��尴ť�ؼ�
class CDrawButton : public CButton
{
private:
	int m_nBtnState;	//��ť״̬
// Construction
public:
	CDrawButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	LRESULT OnMouseLeave(WPARAM,LPARAM);
	virtual ~CDrawButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDrawButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	void ChangeWindowRgn(CDC* pDC);
//	afx_msg void OnPaint();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWBUTTON_H__BD431877_52EE_41C5_9036_E4A5254C5CF7__INCLUDED_)
