
// ProxyClient3.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "log.h"
#include "afxwinappex.h"
#include "ProxyClient3.h"
#include "MainFrm.h"
#include "Login.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProxyClient3App

BEGIN_MESSAGE_MAP(CProxyClient3App, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CProxyClient3App::OnAppAbout)
END_MESSAGE_MAP()


// CProxyClient3App ����

CProxyClient3App::CProxyClient3App()
: m_heart_elapse(15)
{

	m_bHiColorIcons = TRUE;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CProxyClient3App ����

CProxyClient3App theApp;
CManage  gManage;
int      gCleanList_tag = 0;
//IJDCUCommand *m_pCommand= JDCUCreateCommand(); ///TEST


// CProxyClient3App ��ʼ��

CProxyClient3App:: ~CProxyClient3App()
{
	LOG("[INFO] Now Stop To Run ProxyClient\n");
}

BOOL CProxyClient3App::InitInstance()
{
	LOG("**************************************************************\n");
	LOG("[INFO] Now Start To Run ProxyClient\n");

	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ��Ҫ���������ڣ��˴��뽫�����µĿ�ܴ���
	// ����Ȼ��������ΪӦ�ó���������ڶ���
	
	
	CLogin dlg;
	int response = dlg.DoModal();


	if(response!=IDOK)
		return FALSE;
 	
	
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);
	
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	return TRUE;
}


// CProxyClient3App ��Ϣ�������




// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CProxyClient3App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CProxyClient3App �Զ������/���淽��

void CProxyClient3App::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CProxyClient3App::LoadCustomState()
{
}

void CProxyClient3App::SaveCustomState()
{
}

// CProxyClient3App ��Ϣ�������



