// MainDevice.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProxyClient3.h"
#include "MainDevice.h"
#include "Login.h"
#include "DeviceADD.h"
#include "ChildView.h"
#include "DeviceFind.h"
#include "resource.h"
#include "log.h"


// CMainDevice �Ի���
extern CManage gManage;
IMPLEMENT_DYNAMIC(CMainDevice, CDialog)

CMainDevice::CMainDevice(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDevice::IDD, pParent)
	, m_tag_firstpage(1)
	, m_factoryName(_T(""))
	, m_machineType(-1)
	, m_sdkVersion(_T(""))
	, m_offset(0)
	, m_count(0)
{


	m_showFlag = false;


}

CMainDevice::~CMainDevice()
{
}

void CMainDevice::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADD, m_add_btn);
	DDX_Control(pDX, IDC_DEL, m_del_btn);
	DDX_Control(pDX, IDC_MODIFY, m_modify_btn);
	//DDX_Control(pDX, IDC_DEVICELIST, m_DeviceList);
	DDX_Control(pDX, IDC_FIND, m_find_btn);
	DDX_Control(pDX, IDC_BACK, m_back_btn);
	DDX_Control(pDX, IDC_NEXT, m_next_btn);
	DDX_Control(pDX, IDC_GOTO, m_goto_btn);
	DDX_Control(pDX, IDC_PAGECOUNT, m_page_edit);

	DDX_Control(pDX, IDC_SHOWPAGE, m_showpage_static);
	DDX_Control(pDX, IDC_DEVICELIST, m_DeviceList);
	DDX_Control(pDX, IDC_FIRST, m_first_btn);
	DDX_Control(pDX, IDC_TAIL, m_tail_btn);
}


BEGIN_MESSAGE_MAP(CMainDevice, CDialog)
	ON_WM_SIZE()
//	ON_WM_CREATE()
//	ON_BN_CLICKED(IDC_BUTTON2, &CMainDevice::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_ADD, &CMainDevice::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_FIND, &CMainDevice::OnBnClickedFind)
	ON_BN_CLICKED(IDC_DEL, &CMainDevice::OnBnClickedDel)
	ON_BN_CLICKED(IDC_MODIFY, &CMainDevice::OnBnClickedModify)
	ON_NOTIFY(NM_DBLCLK, IDC_DEVICELIST, &CMainDevice::OnNMDblclkList1)
	ON_BN_CLICKED(IDC_BACK, &CMainDevice::OnBnClickedBack)
	ON_BN_CLICKED(IDC_NEXT, &CMainDevice::OnBnClickedNext)
	ON_BN_CLICKED(IDC_GOTO, &CMainDevice::OnBnClickedGoto)
	ON_WM_PAINT()
	ON_NOTIFY(NM_RCLICK, IDC_DEVICELIST, &CMainDevice::OnNMRClickDevicelist)
	ON_COMMAND(ID_DEVICE_UPDATE, &CMainDevice::OnDeviceUpdate)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_FIRST, &CMainDevice::OnBnClickedFirst)
	ON_BN_CLICKED(IDC_TAIL, &CMainDevice::OnBnClickedTail)
	ON_COMMAND(ID_DEVICE_ADD, &CMainDevice::OnDeviceAdd)
	ON_COMMAND(ID_DEVICE_DEL, &CMainDevice::OnDeviceDel)
	ON_COMMAND(ID_DEVICE_MODIFY, &CMainDevice::OnDeviceModify)
	ON_COMMAND(ID_DEVICE_QUERY, &CMainDevice::OnDeviceQuery)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMainDevice ��Ϣ�������

void CMainDevice::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	CRect rect;
	GetClientRect(&rect);
	
	if(m_DeviceList.GetSafeHwnd()==NULL)
		return;

	m_DeviceList.SetWindowPos(NULL, 0, 0, 
		rect.right - rect.left, rect.bottom - rect.top-50, NULL);


	m_DeviceList.SetColumnWidth( 0, 60 );
	int width = ( rect.right - rect.left-65)/5;
	for ( int i=1; i<6; i++ )
		m_DeviceList.SetColumnWidth( i, width );
	TRACE("RECT: %d, %d\n", rect.Width(), rect.Height());



	//////
	if(m_first_btn.GetSafeHwnd())//��ҳ
	{
		m_first_btn.MoveWindow(rect.right - 50-27-42-32-42-42-42-27,rect.bottom-48+3/*statebar+*/,40,20);
	}
	
	if(m_back_btn.GetSafeHwnd())//��һҳ
	{
		m_back_btn.MoveWindow(rect.right - 50-27-42-32-42-42-27,rect.bottom-48+3/*statebar+*/,40,20);
	}

	if(m_showpage_static.GetSafeHwnd())//1/4
	{
		m_showpage_static.MoveWindow(rect.right - 50-27-42-42-32-27,rect.bottom-48+4/*statebar+*/,55,20);

	}
	if(m_next_btn.GetSafeHwnd())//��һҳ
	{
		m_next_btn.MoveWindow(rect.right - 50-27-42-42-2,rect.bottom-48+3/*statebar+*/,40,20);
	}
	if(m_tail_btn.GetSafeHwnd())//βҳ
	{
		m_tail_btn.MoveWindow(rect.right - 50-27-42-2,rect.bottom-48+3/*statebar+*/,40,20);
	}

	if(m_page_edit.GetSafeHwnd())//ҳ������
	{
		m_page_edit.MoveWindow(rect.right - 50-27,rect.bottom-48+3/*statebar+*/,30,20);
	}

	if(m_goto_btn.GetSafeHwnd())//��ת
	{
		m_goto_btn.MoveWindow(rect.right - 45,rect.bottom-48+3/*statebar+*/,37,20);
	}
	/////




	if(m_add_btn.GetSafeHwnd())
	{
		m_add_btn.MoveWindow(rect.left+80,rect.bottom-48+3/*statebar+*/,40,20);
	}

	if(m_del_btn.GetSafeHwnd())
	{
		m_del_btn.MoveWindow(rect.left+80+42,rect.bottom-48+3/*statebar+*/,40,20);
	}
	if(m_modify_btn.GetSafeHwnd())
	{
		m_modify_btn.MoveWindow(rect.left+80+42+42,rect.bottom-48+3/*statebar+*/,40,20);
	}

	if(m_find_btn.GetSafeHwnd())
	{
		m_find_btn.MoveWindow(rect.left+80+42+42+42,rect.bottom-48+3/*statebar+*/,60,20);
	}


	// TODO: �ڴ˴������Ϣ����������
}

//int CMainDevice::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CDialog::OnCreate(lpCreateStruct) == -1)
//		return -1;
//     m_DeviceList.Create(LVS_REPORT|LVS_SHOWSELALWAYS,
// 		CRect(0,0,0,0),this,IDC_DEVICELIST);
//
//	//m_DeviceList.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE,0,LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
//
//
//
//	//m_DeviceList.ShowWindow(SW_SHOW);
//
//
// 	CFont m_font1,m_font2;
// 	m_font1.CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("΢���ź�"));
// 	m_font2.CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("΢���ź�"));
// 	m_DeviceList.SetFont(&m_font2);
// 	
// 	m_DeviceList.SetTextColor(RGB(38,59,90));
//
//	//m_DeviceList.GetHeaderCtrl()->SetFont(&m_font1);
//	//m_DeviceList.GetHeaderCtrl()->SetTextColor(RGB(38,59,90));
//
//
//
//	
//		return 0;
//}

void CMainDevice::OnBnClickedAdd()
{
	CDeviceAdd dlg;
	dlg.m_pParent = this;
    dlg.DoModal();
	//m_device = dlg.device;
}

//BOOL CMainDevice::PreTranslateMessage(MSG* pMsg)
//{
//	// TODO: �ڴ����ר�ô����/����û���
//
//		if (pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)
//		{
//			CString str;
//			GetClassName(pMsg->hwnd,str.GetBuffer(MAX_PATH),MAX_PATH);
//			if ("Edit"==str)
//			{
//				pMsg->wParam = VK_TAB;
//			}
//		}
//	
//
//	return CDialog::PreTranslateMessage(pMsg);
//}

void CMainDevice::OnOK()
{
	int page = GetDlgItemInt(IDC_PAGECOUNT);
	int total = (m_count-1)/COUNT_PER_PAG+1;
	if (page>total||page<1)
	{
		MessageBox(_T("û�и�ҳ��!"));
	}
	else{
		m_offset = (page-1)*COUNT_PER_PAG;
		m_DeviceList.DeleteAllItems();
		ShowDeviceList();
	}

	ShowPage();
}



void CMainDevice::OnBnClickedFind()
{

	CDeviceFind dlg;
	if (IDOK == dlg.DoModal())
          m_DeviceList.DeleteAllItems();
}

/*
 * OnBnClickedDel
 *
 * @Describe ɾ��һ���豸, ��ɾ��һҳ�е�һ���豸ʱ, ��ҳ���豸�б�����β�ȫ��
 * @Date 2013-7-6
 */
void CMainDevice::OnBnClickedDel()
{
	int nItem=m_DeviceList.GetNextItem(-1,LVNI_SELECTED);	
	CString temp_name = m_DeviceList.GetItemText(nItem,0);   	
	int ret = -1;
	if (-1==nItem)
	{
		MessageBox(_T("��ѡ��Ҫɾ�����豸"));
		return ;
	}
	if (MessageBox(_T("�Ƿ�Ҫɾ���豸"),_T("��ȷ��"),MB_YESNO)==IDYES)
	{
		ret = gManage.DelDevice(temp_name);
		if (0==ret)
		{			
			int currentpage = m_offset/COUNT_PER_PAG+1;    // ����m_offset��ȡ��ǰ��ҳ��, m_offset��ά���൱��Ҫ
			int itemcount = m_DeviceList.GetItemCount();
			m_DeviceList.DeleteItem(nItem);				   // ɾ�������豸��Ϣ
			if (1==itemcount)							   //��ֻ��һ��ʱ�� ɾ�����˻�ǰҳ��
			{
				CString strCurrent;
				strCurrent.Format(_T("%d"),currentpage-1); // ҳ���1
				m_offset-=COUNT_PER_PAG;				   // m_offset�ǵ�ҳ�ĵ�һ�豸, �������豸ID
				SetDlgItemText(IDC_PAGECOUNT,strCurrent);
				if (currentpage!=1)						   // ��ǰҳֻ��һ���豸ʱ, ��ֻ��һҳ, ɾ������豸��,���ù���
				{										   // �����ֻһ���豸, ��ȥ��strCurrent, ����ȡ�豸�б�
				     OnBnClickedGoto();
				}
			}
			else	
			{
				// ��ֻһ��, ɾ���Ժ�, ҳ�벻��, m_offsetҲ����, ͨ��m_offset��count���»�ȡ�豸�б�, 
				// ��ȡ�Ļ�����m_offsetΪ������һҳ�豸
				CString strCurrent;
				strCurrent.Format(_T("%d"),currentpage);
				SetDlgItemText(IDC_PAGECOUNT,strCurrent);
				OnBnClickedGoto();
			}
			MessageBox(_T("ɾ���豸�ɹ���"));
		}
		else
			MessageBox(_T("ɾ���豸ʧ�ܣ�"));
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CMainDevice::OnBnClickedModify()
{
    gManage.UnReg(gManage.m_devicelistID);
	
	int nItem=m_DeviceList.GetNextItem(-1,LVNI_SELECTED);	

	if (-1==nItem)
	{
		MessageBox(_T("��ѡ��Ҫ�޸ĵ��豸"));
		return ;
	}
	CString deviceid = m_DeviceList.GetItemText(nItem,0); 


	device_info deviceinfo;
	deviceinfo = gManage.GetDeviceInfo(deviceid);

    CDeviceAdd dlg;
	dlg.m_pParent = this ; 
	dlg.m_deviceinfo = deviceinfo;
	dlg.m_showtype = 2;
	dlg.DoModal();
	gManage.RegCallBackDeviceList(this);//��дע���豸�б�ص�  ��Ϊֻ�ṩһ����������  ����ֻ����������

}

void CMainDevice::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{

	int nItem=m_DeviceList.GetNextItem(-1,LVNI_SELECTED);	
	if (-1!=nItem)
	{
		OnBnClickedModify();
	}
	
	
}

BOOL CMainDevice::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_DeviceList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_TWOCLICKACTIVATE|LVS_EX_SUBITEMIMAGES);
	m_DeviceList.InsertColumn(0,_T("�豸���"),LVCFMT_LEFT,80,-1);
	m_DeviceList.InsertColumn(1,_T("PUID"),LVCFMT_LEFT,80,-1);
	m_DeviceList.InsertColumn(2,_T("�豸����"),LVCFMT_LEFT,80,-1);
	m_DeviceList.InsertColumn(3,_T("�豸����"),LVCFMT_LEFT,80,-1);
	m_DeviceList.InsertColumn(4,_T("�豸�汾��"),LVCFMT_LEFT,80,-1);
	m_DeviceList.InsertColumn(5,_T("�豸״̬"),LVCFMT_LEFT,80,-1);

	CImageList   m_ImageList; 
	m_ImageList.Create(1,19,ILC_COLOR24,1,1); 
	m_DeviceList.SetImageList(&m_ImageList,LVSIL_SMALL); 

	gManage.m_pCommand->RegCmdCallback("BroadcastDeviceStatus",Call_back_deviceState,this);
	
	m_Timer = SetTimer(1, 10, NULL);   // ÿ10msȡһ���豸״̬

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CMainDevice::OnBnClickedBack()
{
	if (m_offset>0)
	{
		if (m_offset>=COUNT_PER_PAG)
			m_offset-=COUNT_PER_PAG;
		else
			m_offset = 0;
		m_DeviceList.DeleteAllItems();
        ShowDeviceList();
	}
    ShowPage();
}

void CMainDevice::OnBnClickedNext()
{
	if ((m_offset+COUNT_PER_PAG)<m_count)		// �����˵�����������һҳ
	{
		m_offset+=COUNT_PER_PAG;
		m_DeviceList.DeleteAllItems();
        ShowDeviceList();
	}
ShowPage();
}

void CMainDevice::OnBnClickedGoto()
{
	int page = GetDlgItemInt(IDC_PAGECOUNT);
	int total = (m_count-1)/COUNT_PER_PAG+1;
	if (page>total||page<1)
	{
	   MessageBox(_T("û�и�ҳ��!"));
	}
	else
	{
		m_offset = (page-1)*COUNT_PER_PAG;
		m_DeviceList.DeleteAllItems();
        ShowDeviceList();
	}

	ShowPage();

	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CMainDevice::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	CRect rcClient;
	GetClientRect(&rcClient);
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BOTTOMBK);
	CDC memdc;
	memdc.CreateCompatibleDC(&dc);
	BITMAP bit;
	bitmap.GetBitmap(&bit);
	memdc.SelectObject(&bitmap);
	// rcClient.InflateRect(1,1,1,1);
	dc.StretchBlt(0,0,rcClient.Width(),rcClient.Height(),&memdc,0,0,bit.bmWidth,bit.bmHeight,SRCCOPY);

	if (m_showFlag == FALSE)
	{
		m_DeviceList.DeleteAllItems();//��ա�������
		ShowDeviceList();     // ��һ�λ�ȡ�豸�б�, ��ʱm_offset==0, ���Ի�ȡ���ǵ�һҳ
		
		m_showFlag = TRUE;
	}
	
	
	ShowPage();

}

void CMainDevice::OnNMRClickDevicelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	DWORD dwPos = GetMessagePos();
	CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

	CMenu menu;
	VERIFY( menu.LoadMenu(IDR_DEVICE));
	CMenu* popup = menu.GetSubMenu(0);

	ASSERT( popup != NULL );

	if (popup)
	{
		int nItem=m_DeviceList.GetNextItem(-1,LVNI_SELECTED);	
		CString temp_name = m_DeviceList.GetItemText(nItem,0);   	
		int ret = -1;
		if (-1==nItem)
		{
			popup->EnableMenuItem(ID_DEVICE_DEL, MF_GRAYED);
			popup->EnableMenuItem(ID_DEVICE_MODIFY, MF_GRAYED);

		}
		else
		{
			popup->EnableMenuItem(ID_DEVICE_DEL, MF_ENABLED);
			popup->EnableMenuItem(ID_DEVICE_MODIFY, MF_ENABLED);
		}

		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}

	*pResult = 0;
}

void CMainDevice::OnDeviceUpdate()
{

    m_factoryName = _T("");
	m_machineType = -1;

	m_sdkVersion = _T("");


	m_DeviceList.DeleteAllItems();//��ա�������
	m_offset = 0;
    ShowDeviceList();
	

}

extern int gCleanList_tag;
void CMainDevice::ShowDeviceList(void)
{

	gCleanList_tag = 0;
	for (int i=0;i<TIMES;i++)
	{
		gManage.GetDeviceList(this,m_factoryName,m_machineType,m_sdkVersion,i*5+m_offset);
	}
}

HBRUSH CMainDevice::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(nCtlColor==CTLCOLOR_STATIC)
	{  
		pDC->SetBkMode(TRANSPARENT);  
		//pDC->SetTextColor(RGB(68,129,2));
		return  (HBRUSH)GetStockObject(NULL_BRUSH); 

	}

	return hbr;
}

void CMainDevice::OnBnClickedFirst()
{
	m_factoryName = _T("");
	m_machineType = -1;

	m_sdkVersion = _T("");


	m_DeviceList.DeleteAllItems();//��ա�������
	m_offset = 0;
	ShowDeviceList();

}

void CMainDevice::OnBnClickedTail()
{
	int totaltcount = (m_count-1)/COUNT_PER_PAG+1;
	m_offset = (totaltcount-1)*COUNT_PER_PAG;
	m_DeviceList.DeleteAllItems();
	ShowDeviceList();

	ShowPage();
}

void CMainDevice::ShowPage(void)
{
	CString str;
	int totaltcount = (m_count-1)/COUNT_PER_PAG+1;
	int currentpage = m_offset/COUNT_PER_PAG+1;
	str.Format(_T("%d / %d"),currentpage,totaltcount);
	SetDlgItemText(IDC_SHOWPAGE,str);
}

void  CMainDevice::SetDevceState(int  index,CString StateId,CString errCode)
{
	if (StateId == "0")
	{
		if (errCode == ":0")
			m_DeviceList.SetItemText(index, 5, _T("δ�����豸"));
		else
			m_DeviceList.SetItemText(index, 5, _T("�����豸ʧ��") + errCode);
	}
	else if (StateId == "1")
	{
		if (errCode = ":0")
			m_DeviceList.SetItemText(index, 5, _T("���������豸"));
		else
			m_DeviceList.SetItemText(index, 5, _T("���ڵǳ��豸"));
	}
	else if (StateId == "2")
	{
		if (errCode == ":0")
			m_DeviceList.SetItemText(index, 5, _T("�������豸"));
		else
		{
			CString csRet = m_DeviceList.GetItemText(index, 5);
			if (csRet == "����ע��CMS")
				m_DeviceList.SetItemText(index, 5, _T("ע��CMSʧ��") + errCode);
			else
				m_DeviceList.SetItemText(index, 5, _T("����CMSʧ��") + errCode);	
		}
	}
	else if (StateId == "3")
	{
		m_DeviceList.SetItemText(index, 5, _T("����ע��CMS"));
	}
	else if (StateId == "4")
	{
		m_DeviceList.SetItemText(index, 5, _T("ע��CMS�ɹ�"));
	}
}

BOOL WINAPI CMainDevice::Call_back_deviceState(IJDCUCommand* pJDCUCommand,DWORD dwMsgID, IJXmlDocument* pXmlDoc,void* pParam)
{
//return TRUE;
	CMainDevice* pMainDevice = (CMainDevice*)pParam;

	if (pMainDevice->m_showFlag == false)
	{
		return TRUE;
	}

	IJXmlElement* pEleMsg = pXmlDoc->FirstChild(XMLMSG);
	IJXmlElement* pDeviceEle= NULL;
	IJXmlElement* pEle= NULL;
	pDeviceEle = pEleMsg->FirstChild("device");
	CString deviceId,status,errCode;
	if (pDeviceEle)
	{
		deviceId =  pDeviceEle->GetAttribute("id");
		status = pDeviceEle->FirstChild("status")->GetText();
		errCode = pDeviceEle->FirstChild("errCode")->GetText();
	}

	DeviceState *state = new DeviceState(deviceId, status, errCode);
	pMainDevice->m_DeviceStateList.m_lock.Lock();
	pMainDevice->m_DeviceStateList.m_list.AddTail(state);
	pMainDevice->m_DeviceStateList.m_lock.Unlock();
/*
	int iCount = pMainDevice->m_DeviceList.GetItemCount();

	CString strId;
	for (int i = 0;i<iCount;i++)
	{
		strId = pMainDevice->m_DeviceList.GetItemText(i,0);
		if (strId == deviceId)
		{
			pMainDevice->SetDevceState(i,status,_T(":")+errCode);
		}		
	}
*/
	
	return TRUE;
}

void CMainDevice::OnDeviceAdd()
{
	OnBnClickedAdd();
}

void CMainDevice::OnDeviceDel()
{
	OnBnClickedDel();
}

void CMainDevice::OnDeviceModify()
{
	OnBnClickedModify();
}

void CMainDevice::OnDeviceQuery()
{
	OnBnClickedFind();
}

BOOL CMainDevice::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN 
		&& (pMsg->wParam ==VK_RETURN || pMsg->wParam == VK_ESCAPE))
	{
		TRACE("PreTranslateMessage wParam:%d lParam:%d\n", pMsg->wParam, pMsg->lParam);
		//MessageBox(_T("PreTranslateMessage"), NULL, MB_OK);
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

int CMainDevice::GetLimitDeviceId(CString &startDeviveId, CString &endDeviceId)
{
	int nItemCount;
	nItemCount = m_DeviceList.GetItemCount();
	startDeviveId = m_DeviceList.GetItemText(0, 0);
	endDeviceId = m_DeviceList.GetItemText(nItemCount - 1, 0);
	return 0;
}
void CMainDevice::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		m_DeviceStateList.m_lock.Lock();
		for (int i = 0; i < m_DeviceStateList.m_list.GetCount(); i++)
		{
			
			DeviceState *state = m_DeviceStateList.m_list.GetHead();
			CString deviceId = state->m_id;
			CString status = state->m_status;
			CString errCode = state->m_errCode;

			int iCount = m_DeviceList.GetItemCount();

			CString strId;
			for (int i = 0;i<iCount;i++)
			{
				strId = m_DeviceList.GetItemText(i,0);
				if (strId == deviceId)
				{
					SetDevceState(i,status,_T(":")+errCode);
				}		
			}
			m_DeviceStateList.m_list.RemoveHead();
		}
		m_DeviceStateList.m_lock.Unlock();
	}

	CDialog::OnTimer(nIDEvent);
}
