#pragma once

//#define IDD_JPROPERTPAGE		0xFF12

// CJPropertyPage �Ի���

class CJPropertyPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CJPropertyPage)

public:
	CJPropertyPage(UINT nIDTemplate, UINT nIDCaption = 0, DWORD dwSize = sizeof(PROPSHEETPAGE));
	virtual ~CJPropertyPage();

// �Ի�������
	//enum { IDD = IDD_JPROPERTPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
