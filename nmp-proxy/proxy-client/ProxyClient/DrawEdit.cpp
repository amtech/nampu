// DrawEdit.cpp : implementation file
//

#include "stdafx.h"
#include "DrawEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawEdit

CDrawEdit::CDrawEdit()
{
	m_BoundColor = RGB(140, 158, 176);	//Ĭ��Ϊ��ɫ
}

CDrawEdit::~CDrawEdit()
{
}


BEGIN_MESSAGE_MAP(CDrawEdit, CEdit)
	//{{AFX_MSG_MAP(CDrawEdit)
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawEdit message handlers

HBRUSH CDrawEdit::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	CDC* dc = GetDC(); //��ȡ��������
	CRect rect;
	GetClientRect(rect); //��ȡ�ͻ�����
	rect.InflateRect(1, 1, 1, 1);//���ͻ���������һ������
	CPen pen(PS_SOLID, 1, m_BoundColor); //��������
	dc->SelectObject(&pen);
	CBrush brush(m_BoundColor);//������ˢ
	dc->FrameRect(rect, &brush);//���Ʊ߿�
	return NULL;
}

void CDrawEdit::PreSubclassWindow() 
{	
	CEdit::PreSubclassWindow();
	ModifyStyleEx(WS_EX_CLIENTEDGE, 0);
	SetWindowPos(NULL, 0, 0, 0, 0, SWP_DRAWFRAME|SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER);
}

BOOL CDrawEdit::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.dwExStyle=cs.dwExStyle+~WS_BORDER;	
	return CEdit::PreCreateWindow(cs);
}

void CDrawEdit::SetBoundColor(COLORREF color)
{
	m_BoundColor = color;
}
