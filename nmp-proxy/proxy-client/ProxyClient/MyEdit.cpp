// MyEdit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProxyClient3.h"
#include "MyEdit.h"


// CMyEdit

IMPLEMENT_DYNAMIC(CMyEdit, CEdit)

CMyEdit::CMyEdit()
{
	m_Colour = RGB(240, 245, 249);

}

CMyEdit::~CMyEdit()
{
}


BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
//	ON_WM_PAINT()
ON_WM_CTLCOLOR()
ON_WM_DRAWITEM()
ON_WM_PAINT()
ON_WM_NCPAINT()
END_MESSAGE_MAP()



// CMyEdit ��Ϣ�������



//void CMyEdit::OnPaint()
//{
//	CPaintDC dc(this); // device context for painting
//
//	COLORREF col = RGB(255,0,255);
//	CRect rcClient;
//	GetClientRect (rcClient);
//	CRgn rgn;
//	rgn.CreateRoundRectRgn (1, 1, rcClient.Width(), rcClient.Height(),6,6);
//
//	SetWindowRgn (rgn, TRUE);
//
//}

HBRUSH CMyEdit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//HBRUSH hbr = CEdit::OnCtlColor(pDC, pWnd, nCtlColor);

		  CDC* dc = GetDC(); //��ȡ��������
	      CRect rect;
	      GetClientRect(rect); //��ȡ�ͻ�����
	      rect.InflateRect(1,1,1,1);//���ͻ���������һ������
	      CBrush brush (m_Colour);//������ˢ
	      dc->FrameRect(rect,&brush);//���Ʊ߿�
	
	      return NULL;

	//return hbr;
}

void CMyEdit::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ


	CDC* dc = GetDC(); //��ȡ��������
	CRect rect;
	GetClientRect(rect); //��ȡ�ͻ�����
	rect.InflateRect(1,1,1,1);//���ͻ���������һ������
	CBrush brush (m_Colour);//������ˢ
	dc->FrameRect(rect,&brush);//���Ʊ߿�
	CEdit::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CMyEdit::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	    CRect rect; 
		GetWindowRect(rect); 
		rect.left += 1; 
		rect.right -= 1; 
		rect.top += 1; 
		rect.bottom -= 1; 
        rect.InflateRect(1,1,1,1);
		ScreenToClient(rect); 
		dc.Draw3dRect(rect, RGB(68,129,2), RGB(68,129,2)); 
		Invalidate(); 
		Default(); 

}

void CMyEdit::PreSubclassWindow()
{
	// TODO: �ڴ����ר�ô����/����û���

	CEdit::PreSubclassWindow();

	//ModifyStyle(0, BS_OWNERDRAW);
}

void CMyEdit::OnNcPaint()
{
	CWindowDC dc(this); // device context for painting
	CRect rect; 
	GetWindowRect(rect); 
	rect.left += 1; 
	rect.right -= 1; 
	rect.top += 1; 
	rect.bottom -= 1; 

	ScreenToClient(rect); 
	dc.Draw3dRect(rect, RGB(68,129,2), RGB(68,129,2)); 
	Invalidate(); 
	Default(); 
}
