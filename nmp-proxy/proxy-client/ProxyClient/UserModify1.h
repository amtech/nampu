/************************************************************************ 
* �ļ�����    UserModify1.h 
* �ļ�������  �޸��û�����ĶԻ���֮һ
* �����ˣ�    XiaoHe, 2013��03��2��
* �汾�ţ�    1.0 
************************************************************************/ 

#pragma once
#include "skinbtn.h"
#include "drawbutton.h"


// CUserModify1 �Ի���

class CUserModify1 : public CDialog
{
	DECLARE_DYNAMIC(CUserModify1)

public:
	CUserModify1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserModify1();

// �Ի�������
	enum { IDD = IDD_USER_MODIFY1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void DrawRangeImage(int i, CDC *pDC, CRect rc);
	CString m_name;
	afx_msg void OnNcPaint();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedClose();
	CSkinBtn m_close_btn;
	CSkinBtn m_cancel_btn;
	CSkinBtn m_ok_btn;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
