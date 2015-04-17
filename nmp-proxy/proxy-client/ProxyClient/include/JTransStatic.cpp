// JTransStatic.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "JTransStatic.h"


// CJTransStatic

IMPLEMENT_DYNAMIC(CJTransStatic, CStatic)

CJTransStatic::CJTransStatic()
{
	m_brNULL.CreateStockObject(NULL_BRUSH);
	m_crText = RGB(0, 0, 0);
}

CJTransStatic::~CJTransStatic()
{
	m_brNULL.UnrealizeObject();
}


BEGIN_MESSAGE_MAP(CJTransStatic, CStatic)
	ON_MESSAGE(WM_SETTEXT, &CJTransStatic::OnSetText)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



void CJTransStatic::SetTxtColor(COLORREF cr)
{
	m_crText = cr;
	JRefresh();
}

LRESULT CJTransStatic::OnSetText(WPARAM wParam, LPARAM lParam)
{
	LRESULT ret = DefWindowProc(WM_SETTEXT, wParam, lParam);
	m_strText = (LPCTSTR)lParam;
	JRefresh();
	return ret;
}

void CJTransStatic::JRefresh()
{
	CRect rc;
	GetWindowRect(&rc);
	CWnd* pParent = GetParent();
	pParent->ScreenToClient(&rc);
	pParent->InvalidateRect(&rc);
}

HBRUSH CJTransStatic::CtlColor(CDC* pDC, UINT nCtlColor)
{
	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  �����Ӧ���ø����Ĵ�������򷵻ط� null ����
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(m_crText);
	return m_brNULL;//hbr;
	return NULL;
}
