// JComboBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "JComboBox.h"


// CJComboBox

IMPLEMENT_DYNAMIC(CJComboBox, CComboBox)

CJComboBox::CJComboBox()
{
	m_lArrowWidth = GetSystemMetrics(SM_CXHTHUMB);
	m_bSelect = FALSE;
	m_bMoseHover = FALSE;
}

CJComboBox::~CJComboBox()
{
}


BEGIN_MESSAGE_MAP(CJComboBox, CComboBox)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_MOUSELEAVE()
	ON_WM_SETCURSOR()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CJComboBox ��Ϣ�������

void CJComboBox::SetImage(const char* szNormalName, const char* szSelectName)
{
	//m_imgNormal.Detach();
	//m_imgSelect.Detach();
	JLoadImage(szNormalName, m_imgNormal);
	JLoadImage(szSelectName, m_imgSelect);
}

void CJComboBox::SetImage(const CImage* pImgNormal, const CImage* pImgSel)
{
	m_imgNormal.Destroy();
	m_imgSelect.Destroy();
	m_imgNormal = *pImgNormal;
	m_imgSelect = *pImgSel;
}

void CJComboBox::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CComboBox::OnPaint()

	CComboBox::DefWindowProc(WM_PAINT, (WPARAM)dc.m_hDC, 0);

	if(m_bMoseHover)
	{
		if(!m_imgSelect.IsNull())
		{
			DrawComboBox(&dc, m_imgSelect, RGB(255, 0, 0));
		}
	}
	else
	{
		if(!m_imgNormal.IsNull())
		{
			DrawComboBox(&dc, m_imgNormal, RGB(0, 0, 0));
		}
	}
}

void CJComboBox::DrawComboBox(CDC* pDC, CImage& img, COLORREF cr)
{
	CRect rc;
	GetClientRect(&rc);
	rc.top += 1;
	rc.left = rc.right - m_lArrowWidth - 2;
	//pDC->FillSolidRect(&rc, cr);
	img.Draw(pDC->GetSafeHdc(), rc.left, rc.top);
}

void CJComboBox::OnSetFocus(CWnd* pOldWnd)
{
	CComboBox::OnSetFocus(pOldWnd);

	// TODO: �ڴ˴������Ϣ����������

}

void CJComboBox::OnMouseLeave()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bMoseHover = FALSE;
	Invalidate();
	CComboBox::OnMouseLeave();
}

BOOL CJComboBox::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(!m_bMoseHover)
	{
		CRect rc;
		CPoint pt;
		GetCursorPos(&pt);
		ScreenToClient(&pt);
		GetClientRect(&rc);
		rc.top += 2;
		rc.left = rc.right - m_lArrowWidth - 2;
		if(rc.PtInRect(pt))
		{
			m_bMoseHover = TRUE;
			InvalidateRect(&rc);

			SetTimer(1, 10, NULL);
			OnTimer(1);
		}
	}
	return CComboBox::OnSetCursor(pWnd, nHitTest, message);
}

void CJComboBox::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nIDEvent == 1)
	{
		CRect rc;
		CPoint pt(GetMessagePos());
		ScreenToClient(&pt);
		GetClientRect(rc);
		rc.left = rc.right - m_lArrowWidth - 2;
		if(!rc.PtInRect(pt))
		{
			KillTimer(1);
			m_bMoseHover = FALSE;
			InvalidateRect(&rc);
		}
	}
	CComboBox::OnTimer(nIDEvent);
}