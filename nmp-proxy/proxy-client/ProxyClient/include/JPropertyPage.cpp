// JPropertPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "JPropertyPage.h"


// CJPropertyPage �Ի���

IMPLEMENT_DYNAMIC(CJPropertyPage, CPropertyPage)

CJPropertyPage::CJPropertyPage(UINT nIDTemplate, UINT nIDCaption, DWORD dwSize)
	: CPropertyPage(nIDTemplate)
{

}

CJPropertyPage::~CJPropertyPage()
{
}

void CJPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CJPropertyPage, CPropertyPage)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CJPropertyPage ��Ϣ�������

BOOL CJPropertyPage::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	RECT rc;
	GetClientRect(&rc);
	CBrush br(RGB(235, 236, 237));
	pDC->FillRect(&rc, &br);
	return TRUE;//CPropertyPage::OnEraseBkgnd(pDC);
}
