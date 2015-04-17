// DrawButton.cpp : implementation file
//

#include "stdafx.h"
#include "DrawButton.h"
#include "winuser.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawButton
extern "C" WINUSERAPI BOOL WINAPI TrackMouseEvent(LPTRACKMOUSEEVENT lpEventTrack); 

CDrawButton::CDrawButton()
{
	m_nBtnState = 0;
}

CDrawButton::~CDrawButton()
{
}


BEGIN_MESSAGE_MAP(CDrawButton, CButton)
	//{{AFX_MSG_MAP(CDrawButton)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
//	ON_WM_PAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawButton message handlers

void CDrawButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	
	//�жϿؼ������Ƿ�Ϊ��ť����
	if (lpDrawItemStruct->CtlType == ODT_BUTTON)
	{
		CDC dc;

		
		dc.Attach(lpDrawItemStruct->hDC);	//�����豸�����ľ��
		//��ȡ��ť״̬
		int nState = lpDrawItemStruct->itemState;
		//��ȡ��ť����
		CRect btnRC = lpDrawItemStruct->rcItem;
		CString szBtnText;
		GetWindowText(szBtnText);	//��ȡ��ť�ı�

		CPoint pt;
		GetCursorPos(&pt);
		ScreenToClient(&pt);
		
		COLORREF clrText;	//�ı���ɫ
		clrText = RGB(0, 0, 0);
		COLORREF clrBK = RGB(220, 220, 220);		//������ɫ

		if (nState & ODS_SELECTED || nState & ODS_FOCUS)
		{
			clrBK = RGB(222, 231, 239);
		}
		if (m_nBtnState == 1)
		{
			clrText = RGB(255, 0, 255);
		}
		
		dc.SetTextColor(clrText);

		dc.FillRect(btnRC, &CBrush(clrBK));
		dc.FrameRect(btnRC, &CBrush(RGB(140, 158, 176)));


		dc.SetBkMode(TRANSPARENT);
		dc.DrawText(szBtnText, btnRC, DT_SINGLELINE|DT_CENTER|DT_VCENTER|DT_WORD_ELLIPSIS);
		dc.Detach();	//������
	}	
}

void CDrawButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	m_nBtnState = 1;
	InvalidateRect(NULL, FALSE);

	TRACKMOUSEEVENT	TrackEvent;
	TrackEvent.cbSize = sizeof(TRACKMOUSEEVENT);
	TrackEvent.dwFlags = TME_LEAVE;
	TrackEvent.dwHoverTime = 0;
	TrackEvent.hwndTrack = m_hWnd;
	::TrackMouseEvent(&TrackEvent);

	
	CButton::OnMouseMove(nFlags, point);
}

void CDrawButton::PreSubclassWindow() 
{
	CButton::PreSubclassWindow();
	ModifyStyle(0, BS_OWNERDRAW);
	m_nBtnState = 0;

}

//����뿪���ڵ���
LRESULT CDrawButton::OnMouseLeave(WPARAM W,LPARAM L)
{
	m_nBtnState = 0;
	InvalidateRect(NULL, FALSE);
	return 0;
}

void CDrawButton::ChangeWindowRgn(CDC* pDC)
{

	COLORREF col = RGB(255,0,255);
	CRect rcClient;
	GetClientRect (rcClient);
	CRgn rgn;
	rgn.CreateRoundRectRgn (1, 1, rcClient.Width(), rcClient.Height(),6,6);

	SetWindowRgn (rgn, TRUE);
}

//void CDrawButton::OnPaint()
//{
//	CPaintDC dc(this); // device context for painting
//
//	//ChangeWindowRgn(&dc);
//}
