#pragma once
#include "afxwin.h"
#include "drawbutton.h"

/*
 * @author: xiaohe
 * @date: 2003/03/04 
 * @detail: �����豸�ĶԻ���  
 *
 */

// CDeviceAdd �Ի���

class CDeviceAdd : public CDialog
{
	DECLARE_DYNAMIC(CDeviceAdd)

public:
	CDeviceAdd(UINT IDD1 = IDD_DEVICE_ADD,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeviceAdd();

	// �Ի�������
	enum { IDD = IDD_DEVICE_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	int m_result;
	CBitmap bit[2];
	


// 	CString m_device_port;	//�豸�˿�
// 	CString m_platform_port;	//ƽ̨�˿�
// 	CString m_device_id;		//�豸ID  ��
// 	CString m_type;      //�豸����
// 	CString m_factory;
// 	CString m_sdk_version;	//����汾
// 	CString m_device_ip;		//�豸IP ��ַ
// 	CString m_pu_id;			//PUID
// 	CString m_platform_ip;	//ƽ̨IP ��ַ
// 	CString m_username;		//�û���
// 	CString m_password;	//����

	device_info m_deviceinfo;
	int m_showtype;
	virtual BOOL OnInitDialog();
//	afx_msg void OnEnKillfocusDeviceport();
	afx_msg void OnEnKillfocusPlport();
	CComboBox m_factory_combox;
	CComboBox m_devicetype_combox;
	CComboBox m_version_combox;
	afx_msg void OnCbnSelchangeFactory();
	afx_msg void OnCbnSelchangeDevicetype();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnNcPaint();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void SetBackBitmap(void);
    void DrawRangeImage(int i, CDC *pDC, CRect rc);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	void ChangeWindowRgn(CDC* pDC);
	CSkinBtn m_close_btn;
	afx_msg void OnBnClickedClose();
	CMainDevice* m_pParent;
	CSkinBtn m_cancel_btn;
	CSkinBtn m_ok_btn;
	int m_deviceport_edit;
	afx_msg void OnEnKillfocusDeviceport();
	int m_plport_edit;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
