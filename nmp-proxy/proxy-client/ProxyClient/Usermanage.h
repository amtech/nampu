/************************************************************************ 
* �ļ�����    Usermanage.h 
* �ļ�������  �������豸ͨ������⽻��
* �����ˣ�    XiaoHe, 2013��03��2��
* �汾�ţ�    1.0 
************************************************************************/ 


#ifndef XX_H
#define XX_H 

#pragma once
#define MAX_ID_LEN				32
#define MAX_NAME_LEN			64
#define MAX_PWD_LEN				64
#define MAX_VERSION_LEN			16
#define MAX_IP_LEN				64
#define COUNT_PER_XML           25   //�������ظ�ʱÿ��XML �豸����Ŀ
#define COUNT_PER_PAG           25  //ÿҳ��ʾ���豸��
#define TIMES                   1   //5��XML, һ�η���1������, ÿ�λ�ȡCOUNT_PER_XML����
#include "MainDevice.h"
#include "MainUser.h"



enum DeviceStyle{DVR,DVS,IPC};
class CMainDevice;
struct S_Prameter{
	CMainDevice* pMaindeviceDlg;
	CMainUser* pMainUserDlg;
};

typedef struct _prx_device_info
{
	//int result;
	
	CString device_port;					//�豸�˿�
	CString platform_port;					//ƽ̨�˿�
	CString device_id;						//�豸ID ����
	CString protocol;						//Ŀǰû�õ�.
	
	CString type;							//�豸����
	CString pu_id;				            //PUID
	CString factoryname;					//����
	CString sdk_version ;					//����汾
	CString device_ip ;						//�豸IP ��ַ
	CString platform_ip ;					//ƽ̨IP ��ַ
	CString username ;						//�û���
	CString password ;						//����
	_prx_device_info()
	{	
		device_id = "";
		protocol ="";

	}
}device_info;


class sdkversion{//�汾����ڵ�
public:
	sdkversion(void);
	CString name;
	sdkversion *next;
};

class device//�豸�б�ڵ�
{
public:
	device(void);
	CString name;
	sdkversion *pVsersion;
	device  *next;
};
class factory//��������ڵ�
{
public:
	factory(void);
	CString name;
	device *pDevice;
	factory *next;

};
class CManage
{
public:
	CString m_name;//��¼�û���
	CString m_pwd;//����
	CString  m_port;//�˿�
	int m_type;
	char m_IP[MAX_IP_LEN];//IP
	IJXmlParser *m_pXmlParser;
	IJDCUCommand *m_pCommand;
	factory *m_pFactory;

	
	long m_infoID;
	long m_loginID;
	long m_userlistID;
	long m_devicelistID;
	long m_heartresponseID;
	long m_AddDevBrocastID;
	long m_DelDevBrocastID;
	long m_ModifyDevBrocastID;
	long m_AddUserBrocastID;
	long m_DelUserBrocastID;
	

	int m_devicecount;//�豸����
	int m_usercount;  //�û�����

	void* m_MaindeviceDlg;

	CManage(void);
	~CManage(void);
	int Login(void *);
	int SetConfig(CString,CString,CString);
	int GetConfig(CString&,CString&,CString&);
	
	int AddUser(const CString &name,const CString &pwd,void* wPram);
	
	int DelUser(const CString &name);
	
	int DelDevice(const CString &);
	

	
	
	void GetUserList(CString name = _T(""),int offet = 0);

	/*
	 * @Date 2013-7-29
	 * @Describe GetDeivceList��GetDeviceInfo������, GetDeviceList���첽��, GetDeivceInfo��ͬ����
	 *           �������ǵ���Ӧ����ͬһ��xml("GetDeviceInfoResponse"), ����GetDeviceList��GetDeviceInfo
	 *           ����"GetDeviceInfoResponse"�Ľ������ͬ, GetDeviceInfo����ͬ������ 
	 *           ����, Ϊ�����첽�ķ�ʽȥ����ͬ���Ľ��, ������ʹ��ͬ��GetDeivceInfo��ʱ��, ��ע���첽
	 *           ��GetDeivcelList��
	 */
	void GetDeviceList(void*,CString factory = _T(""),int mtype = -1,CString kversion = _T(""),int offset = 0,int deviceId = -1);
	device_info GetDeviceInfo(CString deviceid=_T(""));
	
	int AddDevice(device_info device);

	int DeviceModify(device_info device);

	int UserModify(const CString &name,const CString &pwd,const CString &oldpwd=_T(""));


	const char* CString2char(CString str);

	device_info Doc2Device(IJXmlDocument*);//���������豸 ����豸�ṹ��

	BOOL WINAPI fun_callback(IJDCUCommand* pJDCUCommand,
		DWORD dwMsgID, IJXmlDocument* pXmlDoc,void* pParam);

	CString GetDeviceType(CString);//��ö�ٵ��豸����
	CString GetDeviceNum(CString);//���豸���Ƶ�ö��ֵ
	
	void SendHeart(void);//�����˷�������

	IJXmlElement* AppendChile(IJXmlParser*,IJXmlElement*,const char*,CString);
	IJXmlElement* AppendChildEle(IJXmlParser* pXmlParser, IJXmlElement* pParent, const char* pszName, const char* pszValue);

	void GetBaseInfo(void);
	void RegCallBack(void*);

	//void GetCount(void);
	void UnReg(long);

	void RegCallBackDeviceList(void* pPram);

	// ��������
	int DownloadData(CString& port,CString& magic,CString& fileSize);   // ���ط���������Ϣ

	// �ϴ�����
	int UploadData(CString fileSize, CString& port, CString &magic); // info, ���صķ������ϴ�ʱ�Ķ˿�, magic	  
	
	// ���ƹ㲥�豸״̬
	int LimitBroadcastDeviceStatus(CString startDeviceId, CString endDeviceId);
};


#endif