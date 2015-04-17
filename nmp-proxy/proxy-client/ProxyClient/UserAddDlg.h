/************************************************************************ 
* �ļ�����    UserAddDlg.h   
* �ļ�������  �����û��ĶԻ���
* �����ˣ�    XiaoHe, 2013��03��2��
* �汾�ţ�    1.0 
************************************************************************/ 


#pragma once
#include "skinbtn.h"


// CUserAddDlg �Ի���

class CUserAddDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserAddDlg)

public:
	CUserAddDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserAddDlg();

	// �Ի�������
	enum { IDD = IDD_USER_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CSkinBtn m_idok_btn;
public:
	CSkinBtn m_idcancel_btn;
	CString m_name;
	CString m_pwd;
	CString m_pwd_confirm;
//	afx_msg void OnBnClickedOk();
protected:
//	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	void OnClose(void);
	void DrawRangeImage(int i, CDC *pDC, CRect rc);

protected:
	virtual void OnOK();
public:
	afx_msg void OnNcPaint();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnBnClickedClose();
	CSkinBtn m_close_btn;
	void* m_pParent;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
};
