/*
 * @Author: XiaoHe
 * @Date  : 2003-03-04 
 * @Detail: ����һ���м��࣬���ڶ�CDialog�ķ�װ���ػ��˶Ի���ı������ͶԻ���ı߿�, �ػ�󣬱߿��Ǻ�ɫ 
 *			
 */


#pragma once

#ifndef _PROXYCLIENT_531 
#define CLOSE_BTN  WM_USER+6
#endif

// CMyBlackDlg �Ի���

class CMyBlackDlg : public CDialog
{
	DECLARE_DYNAMIC(CMyBlackDlg)

public:
	CMyBlackDlg(UINT IDD1,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyBlackDlg();

// �Ի�������
	//enum { IDD = xxxx };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_title;
	CBitmap bit[2];
	CSkinBtn m_close_btn;
	void DrawRangeImage(int i, CDC *pDC, CRect rc);
	void ChangeWindowRgn(CDC* pDC);
	afx_msg void OnNcPaint();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	virtual BOOL OnInitDialog();
	void SetTitle(CString str);
	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
//	afx_msg void OnSize(UINT nType, int cx, int cy);
};
