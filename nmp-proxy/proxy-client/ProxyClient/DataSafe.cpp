// DataSafe.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "network.h"
#include "DataSafe.h"

#define MY_TIMER 1000
// CDataSafe �Ի���
extern CManage gManage;

IMPLEMENT_DYNAMIC(CDataSafe, CMyBlackDlg)

CDataSafe::CDataSafe(UINT IDD1, CWnd* pParent /*=NULL*/)
	: CMyBlackDlg(IDD1, pParent)
	, m_hThreadBg(NULL)
	, m_hThreadUl(NULL)
	, m_hTreadBgExit(FALSE)
	, m_hTreadUlExit(FALSE)
{	
	m_bProcessUl = FALSE;
	m_bProcessBg = FALSE;
}

CDataSafe::~CDataSafe()
{
	//KillTimer(m_dl_timer);
}

void CDataSafe::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BACKUP, m_backup_btn);
	DDX_Control(pDX, IDC_UPLOAD, m_upload_btn);
	DDX_Control(pDX, IDC_PROGRESS_BG, m_ProgressBg);
	DDX_Control(pDX, IDC_PROGRESS_UL, m_ProgressUl);
}


BEGIN_MESSAGE_MAP(CDataSafe, CDialog)
	ON_WM_NCHITTEST()
	ON_WM_NCPAINT()
	ON_WM_CTLCOLOR()
	ON_COMMAND(CLOSE_BTN, OnClose)
	ON_BN_CLICKED(IDC_BACKUP, OnBnClickedBackup)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_UPLOAD, OnBnClickedUpload)
END_MESSAGE_MAP()


// CDataSafe ��Ϣ�������

LRESULT CDataSafe::OnNcHitTest(CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return CMyBlackDlg::OnNcHitTest(point);
}

void CDataSafe::OnNcPaint()
{
	CMyBlackDlg::OnNcPaint();
}

HBRUSH CDataSafe::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMyBlackDlg::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

BOOL CDataSafe::OnInitDialog()
{
	CMyBlackDlg::OnInitDialog();
	m_dl_timer = SetTimer(MY_TIMER, 1000, NULL);  // 1s����һ��

	m_backup_btn.SetImage(_T("images/normal_black_btn.bmp"),_T("images/sel_black_btn.bmp"),
		_T("images/sel_black_btn.bmp"),_T("images/sel_black_btn.bmp"));
	m_upload_btn.SetImage(_T("images/normal_black_btn.bmp"),_T("images/sel_black_btn.bmp"),
		_T("images/sel_black_btn.bmp"),_T("images/sel_black_btn.bmp"));

	m_backup_btn.SetTextPos(CPoint(12,4));
	m_upload_btn.SetTextPos(CPoint(12,4));

	m_ProgressBg.SetRange(0, 100);
	m_ProgressUl.SetRange(0, 100);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDataSafe::OnClose()
{
	//if (m_bProcessUl)
	//{
	//	MessageBox(_T("�������ڽ��лָ�"), NULL, MB_OK);
	//	return;
	//}

	//if (m_bProcessBg)
	//{
	//	MessageBox(_T("�������ڽ��б���"), NULL, MB_OK);
	//	return;
	//}

	if (m_bProcessUl && m_hThreadBg)
	{
		m_hTreadBgExit = TRUE;
		MessageBox(_T("ȡ�����ݱ���"), NULL, MB_OK);
		CannelBackup();
	}

	if (m_bProcessBg && m_hThreadUl)
	{
		m_hTreadUlExit = TRUE;
		MessageBox(_T("ȡ�����ݻָ�"), NULL, MB_OK);
		CannelUpload();
	}

	EndDialog(2);
}

CString GetBackupFileName()
{
	CString strFileName;

	SYSTEMTIME curTime;;
	GetLocalTime(&curTime);
	strFileName.Format(_T("proxyclient%4d%02d%02d%02d%02d%02d.dat"), curTime.wYear, curTime.wMonth, curTime.wDay, curTime.wHour, curTime.wMinute, curTime.wSecond);

	return strFileName;
}

int CDataSafe::SetDataSavePath(CString &path)
{
	
	CFileDialog dlg(FALSE, _T("*.*"), GetBackupFileName(), OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, _T("��������"), this);
	
	CString strModuleBaseName;
	GetModuleFileName(NULL, strModuleBaseName.GetBufferSetLength(MAX_PATH), MAX_PATH);
	strModuleBaseName.ReleaseBuffer();
	int iPos = strModuleBaseName.ReverseFind(_T('\\'));
	CString strFile = strModuleBaseName.Left(iPos + 1);

	dlg.m_ofn.lpstrInitialDir = strFile;
	if (dlg.DoModal() == IDOK)  //�����Ƿ���
	{
		CStdioFile file;
		CString ss = dlg.GetPathName();
		BOOL res = file.Open(ss, CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		if(!res)
		{
			MessageBox(ss + _T("��ʧ�ܣ�"));
			return -1;
		}
		else
		{
			path = ss;  // ��ȡ�����ļ�·��
			file.Close();
			return 0;
		}
	}

	TRACE1("CFileDialog  %d\n", GetLastError());

	return -2;
}

DWORD WINAPI BackupDataPromptThread(LPVOID lpParameter)
{
	CDataSafe *pThis = (CDataSafe *)lpParameter;

	pThis->BackupDataPromptThread1(pThis);
	return 0;
}

void CDataSafe::BackupDataPromptThread1(void *pThis)
{
	//if (MessageBox(_T("�������ڽ��б�����..."), NULL, MB_OK) != MB_OK);
}

void* WINAPI BackupDataThread(void* lpParameter)
{
	CDataSafe *pThis = (CDataSafe *)lpParameter;

	pThis->BackupDataThread1(pThis);
	return NULL;
}

void CDataSafe::BackupDataThread1(void *pThis)
{
	int ret;
	CString port, magic, fileSize;
	CString filePath;
	int nPort;
	int nMagic;
	int nFileSize;

	ret = gManage.DownloadData(port, magic, fileSize);
	if (ret < 0)
	{
		MessageBox(_T("��������ʧ��"), NULL, MB_OK);
		goto _error;
	}

	ret = SetDataSavePath(filePath);
	if (ret == -1)
	{
		MessageBox(_T("��ȡ�ļ�·��ʧ��"), NULL, MB_OK);
		goto _error;
	}
	else if (ret == -2)
	{
		goto _error;
	}

	TRACE("%s\n", filePath);

	nPort = StringToLong(StringUnicodeToAscii((LPCTSTR)port).c_str());
	nMagic = StringToLong(StringUnicodeToAscii((LPCTSTR)magic).c_str());
	nFileSize = StringToLong(StringUnicodeToAscii((LPCTSTR)fileSize).c_str());

	RecvAndSaveFile(nPort, nMagic, nFileSize, filePath);

_error:
	m_bProcessBg = FALSE;
	return;
}

int	
CDataSafe::CannelBackup() // ȡ������
{
	if (m_hThreadBg)
	{
		WaitThread(m_hThreadBg);
	}

	return 0;
}
int	
CDataSafe::CannelUpload() //ȡ���ϴ�
{
	if (m_hThreadUl)
	{
		WaitThread(m_hThreadUl);
	}

	return 0;
}

void CDataSafe::OnBnClickedBackup()
{	
	if (m_bProcessBg)
	{
		MessageBox(_T("�������ڱ�����"), NULL, MB_OK);
		return;
	}

	if (m_bProcessUl)
	{
		MessageBox(_T("�������ڻָ���"), NULL, MB_OK);
		return;
	}

	m_hThreadBg = CreateThreadEx(BackupDataThread, this);
	if (!m_hThreadBg)
	{
		MessageBox(_T("���������߳�ʧ��"), NULL, MB_OK);
		return;
	}

	m_bProcessBg = TRUE;
}

void CDataSafe::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nIDEvent == MY_TIMER)
	{
	
	}

	CMyBlackDlg::OnTimer(nIDEvent);
}

#define MAX_BUFFER_SIZE (1 * 1024)

int CDataSafe::RecvAndSaveFile(int port, int magic, int fileSize, CString path)
{
	int wRet;
	int fd, ret;
	ULONGLONG total = 0;
	int nMaigc = 0;
	char buf[MAX_BUFFER_SIZE] = {0};

	FILE *file = fopen(StringUnicodeToAscii((LPCTSTR)path).c_str(), "wb");
	if (!file)
	{
		MessageBox(_T("���������ļ�ʧ��"), NULL, MB_OK);
		goto _error;
	}

	fd = socket_connect(gManage.m_IP, port);
	if (fd < 0)
	{
		MessageBox(_T("���ӱ��ݷ�����ʧ��"), NULL, MB_OK);
		goto _error;
	}

	magic = htonl(magic);
	ret = socket_write(fd, (char *)&magic, 4);
	if (ret != 4)
	{
		TRACE("socket_write magic error, ret:%d", ret);
		goto _error;
	}
	
	for (;;)
	{
		if (m_hTreadBgExit  == TRUE)
		{
			break;
		}

		if (total >= fileSize)
		{
			if (total > fileSize)
			{
				MessageBox(_T("���ݴ�С�쳣"), NULL, MB_OK);
				goto _finish;			
			}
			m_ProgressBg.SetPos(100);
			MessageBox(_T("���ݳɹ�"), NULL, MB_OK);
			
			goto _finish;
		}
		ret = socket_read(fd, buf, MAX_BUFFER_SIZE);
		if (ret < 0)
		{
			MessageBox(_T("��������ʧ��"), NULL, MB_OK);
			goto _error;
		}

		total += ret;
		wRet = fwrite(buf, 1, ret, file);
		if (wRet != ret)
		{
			MessageBox(_T("д���ļ�ʧ��"), NULL, MB_OK);
			goto _error;
		}
		// ���ý���
		m_ProgressBg.SetPos((int)(total  * 100 / fileSize));
	}
	
	return 0;

_error:
	if (fd > 0)
		closesocket(fd);
	
	if (file)
		fclose(file);

	m_bProcessBg = FALSE;
	return -1;

_finish:
	closesocket(fd);
	if (file)
		fclose(file);
	m_ProgressBg.SetPos(0);
	m_bProcessBg = FALSE;
	return 0;
}

int CDataSafe::UploadAndSendFile(int port, int magic, int fileSize, CString path)
{
	int fd = 0, ret;
	ULONGLONG total = 0;
	char buf[MAX_BUFFER_SIZE] = {0};
	FILE *file = NULL;

	if (fileSize <= 0)
	{
		MessageBox(_T("�쳣���ļ���С"), NULL, MB_OK);
		goto _error;
	}

	file = fopen(StringUnicodeToAscii((LPCTSTR)path).c_str(), "rb");
	if (!file)
	{
		MessageBox(_T("��ȡ�����ļ�ʧ��"), NULL, MB_OK);
		goto _error;
	}

	fd = socket_connect(gManage.m_IP, port);
	if (fd < 0)
	{
		MessageBox(_T("�����ϴ�������ʧ��"), NULL, MB_OK);
		goto _error;
	}
	
	/* ���ӳɹ���, ����Ϊ������ */
	//if(socket_set_noblock(fd) < 0)
	//{
	//	goto _error;
	//}

	magic = htonl(magic);
	ret = socket_write(fd, (char *)&magic, 4);
	if (ret != 4)
	{
		TRACE("socket_write magic error, ret:%d", ret);
		goto _error;
	}

	for (;;)
	{
		if (m_hTreadUlExit  == TRUE)
		{
			break;
		}

		ret = fread(buf, 1, MAX_BUFFER_SIZE, file);
		if (ret != MAX_BUFFER_SIZE)
		{
			if (feof(file))
			{
				
			}
			else
			{
				MessageBox(_T("��ȡ����ʧ��"), NULL, MB_OK);
				goto _error;
			}
		}

		ret = socket_write(fd, buf, ret);
		if (ret < 0)
		{
			MessageBox(_T("�ϴ�����ʧ��"), NULL, MB_OK);
			goto _error;
		}
		
		total += ret;
		m_ProgressUl.SetPos((int)(total * 100 / fileSize));
		if (total == fileSize)
		{
			m_ProgressUl.SetPos(100);
			MessageBox(_T("�ָ��ɹ�, �����µ�¼�ͻ���"), NULL, MB_OK);
			closesocket(fd);
			if (file)
				fclose(file);
			
			m_ProgressUl.SetPos(0);
			m_bProcessUl = FALSE;
			return 0;
		}
	}

_error:
	if (fd > 0)
		closesocket(fd);

	if (file)
		fclose(file);
	
	m_bProcessUl = FALSE;	
	return -1;
}

int CDataSafe::GetFileLength(CString file)
{
	CFile *pFile;
	ULONGLONG fileLength;
	
	pFile = new CFile(file, CFile::modeRead | CFile::shareDenyNone);
	if (!pFile)
	{
		MessageBox(_T("���ļ�ʧ��"), NULL, MB_OK);
		return -1 ;
	}

	fileLength = pFile->GetLength();
	if (pFile)
	{
		pFile->Close();
	}

	return (int)fileLength;
}

//DWORD WINAPI UploadDataThread(LPVOID lpParameter)
void * WINAPI UploadDataThread(void *lpParameter)
{
	CDataSafe *pThis = (CDataSafe *)lpParameter;
	
	pThis->UploadDataThread1(pThis);
	return 0;
}

void CDataSafe::UploadDataThread1(void *pThis)
{
	int ret;
	CFile  file;
	CString filePath;
	CString fileSize, port, magic;
	ULONGLONG fileLength;
	
	ret = GetDataPath(filePath);
	if (ret == -1)
	{
		MessageBox(_T("��ȡ�ļ���ַʧ��"), NULL, MB_OK);
		goto _error;
	}
	else if (ret == -2)
	{
		goto _error;
	}

	fileLength = GetFileLength(filePath);
	if (fileLength < 0)
	{
		MessageBox(_T("��ȡ�ļ���Сʧ��"), NULL, MB_OK);
		goto _error;	
	}

	fileSize.Format(_T("%d"), fileLength); // ��4���ֽڵ�magic����
	ret = gManage.UploadData(fileSize, port, magic);
	if (ret < 0)
	{
		MessageBox(_T("�ָ��ļ�ʧ��"), NULL, MB_OK);
		goto _error;
	}

	ret = UploadAndSendFile(StringToLong(StringUnicodeToAscii((LPCTSTR)port).c_str()), StringToLong(StringUnicodeToAscii((LPCTSTR)magic).c_str()), (int)fileLength, filePath);
	if (ret < 0)
	{
		MessageBox(_T("�����ļ�ʧ��"), NULL, MB_OK);
		goto _error;
	}

_error:
	m_bProcessUl = FALSE;
	return;
}

void CDataSafe::OnBnClickedUpload()
{
	if (m_bProcessBg)
	{
		MessageBox(_T("�������ڱ�����"), NULL, MB_OK);
		return;
	}

	if (m_bProcessUl)
	{
		MessageBox(_T("�������ڻָ���"), NULL, MB_OK);
		return;
	}

	m_hThreadUl = CreateThreadEx(UploadDataThread, this);
	if (!m_hThreadUl)
	{
		MessageBox(_T("�����ָ��߳�ʧ��"), NULL, MB_OK);
		return;
	}
	m_bProcessUl = TRUE;
}

int CDataSafe::GetDataPath(CString& path)
{
	CFileDialog dlg(TRUE, _T("*.*"), _T("*.*"), OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, _T("��������"), this);
	
	CString strModulePath;
	GetModuleFileName(NULL, strModulePath.GetBufferSetLength(MAX_PATH), MAX_PATH);
	strModulePath.ReleaseBuffer();
	int iPos = strModulePath.ReverseFind(_T('\\'));
	CString strPath = strModulePath.Left(iPos + 1);
	dlg.m_ofn.lpstrInitialDir = strPath;
	if (dlg.DoModal() == IDOK)  //�����Ƿ���
	{
		CStdioFile file;
		CString ss = dlg.GetPathName();
		BOOL res = file.Open(ss, CFile::modeRead | CFile::shareDenyNone | CFile::typeText);
		if(!res)
		{
			MessageBox(ss + _T("��ʧ�ܣ�"));
			return -1;
		}
		else
		{
			path = ss;  // ��ȡ�����ļ�·��
			file.Close();
			return 0;
		}
	}

	return -2;
}