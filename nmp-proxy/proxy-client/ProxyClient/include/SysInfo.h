#pragma once

//��ȡCPU���к�
const char* GetCPUID();

//��ȡ�������к�
const char* GetDiskID();

//��ȡ����MAC,IP
struct stIPAddrString
{
	char szIP[16];
	char szMask[16];
};

struct stAdaptersInfo
{
	char szMac[32];
	BOOL bEnableDHCP;
	int  nIPCount;
	stIPAddrString IPAddr[16];

	int nGatewayCount;
	stIPAddrString GatewayAddr[4];
};

BOOL GetNetAdaptersInfo(stAdaptersInfo* pInfo,int* nCount);


//��ȡ�ڴ�ʹ���������λM��
void GetMemoryStatus(DWORD& dwTotal , DWORD& dwUsed);

//��ȡ�����ڴ�ʹ���������λM��
BOOL GetProcMemoryUsed(DWORD dwPrcID,long& lUsed);

//��ȡCPUʹ�����
BOOL GetCPUUsed(long& lUsed);

//��ȡ����CPUʹ�����
BOOL GetProcessCPUUsed(DWORD dwPrcID,long& lUsed);

//��ȡCPU����
DWORD GetdwNumberOfProcessors();

//�����������
LONG InterlockedAddLong(LONG volatile *lpAddend,LONG lAddValue);
LONG InterlockedExchangeLong(LONG volatile *lpValue,LONG lNewValue);
LONG InterlockedCompareExchangeLong(LONG volatile *lpValue,LONG lNewValue,LONG lCmpValue);
