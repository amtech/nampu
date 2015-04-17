#ifndef __JLOCKMEM_H__
#define __JLOCKMEM_H__


#define MAX_THREAD_COUNT		1024				//����߳�����

#define READ_STATUS			1
#define WRITE_STATUS		2

struct stMemBlockLock
{
	long	lWriteRequestCount;						//д��������
	long	lWriteCount;							//����д����
	long	lReadCount;								//���ڶ�����
	long	lThreadCount;							//�����߳�����
	DWORD	dwTheadId[MAX_THREAD_COUNT];			//�����߳�ID
	long	lThreadWriteCount[MAX_THREAD_COUNT];	//�߳�����д״̬����
	long	lThreadReadCount[MAX_THREAD_COUNT];		//�߳������״̬����
	long	lThreadPreReadCount[MAX_THREAD_COUNT];	//�߳��ɶ�ת��д״̬ʱ�Ķ�״̬����
};

class CLockMem
{
public:
	CLockMem();
	virtual ~CLockMem();

public:
	long Init(const char* szName = NULL);
	BOOL LockRead(DWORD dwTimeout = INFINITE);
	BOOL LockWrite(DWORD dwTimeout = INFINITE);
	void UnlockRead(BOOL bReleaseResource = TRUE);
	void UnlockWrite(BOOL bReleaseResource = TRUE);

protected:
	void Close();
	void AddPlaceStatus(long lPlace, DWORD dwThreadId, long lStatus, long lCount = 1);
	void RemovePlaceStatus(long lPlace, BOOL bReleaseResource);
	long FindThreadPlace(DWORD dwThreadId);

	void ReLockRead(DWORD dwThreadId, long lReadCount);

	BOOL LockMemBlock(DWORD dwTimeout);
	void UnlockMemBlock();

private:
	HANDLE				m_hMutexMemBlock;
	HANDLE				m_hMapFile;

	stMemBlockLock*		m_pMemBlock;
};


#endif