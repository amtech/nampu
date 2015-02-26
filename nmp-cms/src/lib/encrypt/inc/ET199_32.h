#ifndef _FEITIAN_ET199_32_H_
#define _FEITIAN_ET199_32_H_



#define   HANDLE  void *;

#define   ET_S_SUCCESS			0x00000000	// �����ɹ�
#define   ET_E_KEY_REMOVED		0xF0000001	// �豸δ���ӣ����߱��Ƴ�
#define   ET_E_INVALID_PARAMETER	0xF0000002	// ��������
#define   ET_E_COMM_ERROR		0xF0000003	// ͨѶ�����������ݴ��䳬ʱ
#define   ET_E_INSUFFICIENT_BUFFER	0xF0000004	// �������ռ䲻��
#define   ET_E_NO_LIST			0xF0000005	// û���ҵ��豸�б�
#define   ET_E_DEVPIN_NOT_CHECK		0xF0000006	// �����̿���û����֤
#define   ET_E_USERPIN_NOT_CHECK	0xF0000007	// �û�����û����֤
#define   ET_E_RSA_FILE_FORMAT_ERROR	0xF0000008	// RSA�ļ���ʽ����
#define   ET_E_DIR_NOT_FOUND		0xF0000009	// Ŀ¼û���ҵ�
#define   ET_E_ACCESS_DENIED		0xF000000A	// ���ʱ��ܾ�
#define   ET_E_ALREADY_INITIALIZED	0xF000000B	// ��Ʒ�Ѿ���ʼ��
#define   ET_E_INCORRECT_PIN		0xF0000C00	// ���벻��ȷ
#define   ET_E_DF_SIZE			0xF000000D	// ָ����Ŀ¼�ռ��С����
#define   ET_E_FILE_EXIST		0xF000000E	// �ļ��Ѵ���
#define   ET_E_UNSUPPORTED		0xF000000F	// ���ܲ�֧�ֻ���δ�����ļ�ϵͳ
#define   ET_E_FILE_NOT_FOUND		0xF0000010	// δ�ҵ�ָ�����ļ�
#define   ET_E_ALREADY_OPENED		0xF0000011	// ���Ѿ�����
#define   ET_E_DIRECTORY_EXIST		0xF0000012	// Ŀ¼�Ѵ���
#define   ET_E_CODE_RANGE		0xF0000013	// ������ڴ��ַ���
#define   ET_E_INVALID_POINTER		0xF0000014	// ����������ָ��
#define   ET_E_GENERAL_FILESYSTEM	0xF0000015	// �����ļ�ϵͳ����
#define   ET_E_OFFSET_BEYOND		0xF0000016	// �ļ�ƫ���������ļ���С
#define   ET_E_FILE_TYPE_MISMATCH	0xF0000017	// �ļ����Ͳ�ƥ��
#define   ET_E_PIN_BLOCKED		0xF0000018	// PIN������
#define   ET_E_INVALID_CONTEXT		0xF0000019	// ETContext ��������
#define   ET_E_SHARING_VIOLATION	0XF000001A	// ��һ����������ʹ�ô��ļ��������޷�����
//linux������������
#define   ET_TOOMUCHTHREAD		0XF000001B     //ͬһ�������д������߳��� > 100

#define   ET_E_ERROR_UNKNOWN		0xFFFFFFFF	// δ֪�Ĵ���
#define   ET_E_LOAD_FILE_FAILED		0xF0001001

#define   MAX_ATR_LEN	16	// ���ATR����
#define   MAX_ID_LEN	8       // ���Ӳ��ID����

#define   ET_USER_PIN	0x00000000	// �û�PIN
#define   ET_DEV_PIN	0x00000001      // ������PIN

#define   ET_CREATE_NEW		0x00000000	// �������ļ�
#define   ET_UPDATE_FILE	0x00000001      // ���������ļ�

#define   ET_CREATE_ROOT_DIR	0x00000000      // ������Ŀ¼
#define   ET_CREATE_SUB_DIR	0x00000001      // ������ǰĿ¼����Ŀ¼


#define   ET_LED_UP	0x00000001	// LED����
#define   ET_LED_DOWN	0x00000002	// LED����
#define   ET_LED_WINK 	0x00000003	// LED����˸


#define   ET_GET_DEVICE_TYPE		0x00000011	// ����豸����
#define   ET_GET_SERIAL_NUMBER		0x00000012      // ��ȡӲ�����к�
#define   ET_GET_DEVICE_USABLE_SPACE	0x00000013      // ����豸�ռ��С
#define   ET_GET_DEVICE_ATR		0x00000014      // ����豸ATR
#define   ET_GET_CUSTOMER_NAME		0x00000015      // ��ÿͻ���
#define   ET_GET_MANUFACTURE_DATE	0x00000016      // �����������
#define   ET_GET_DF_AVAILABLE_SPACE	0x00000017      // ��õ�ǰĿ¼��ʣ��ռ�
#define   ET_GET_EF_INFO		0x00000018      // ���ָ���ļ���Ϣ
#define   ET_GET_COS_VERSION		0x00000019	// ���COS�汾��Ϣ

#define   ET_SET_DEVICE_ATR		0x00000021      // �����豸ATR
#define   ET_SET_DEVICE_TYPE		0x00000022	// �����豸����
#define   ET_SET_SHELL_KEY		0x00000023	// ����8�ֽ���Ǽ���������
#define   ET_SET_CUSTOMER_NAME		0x00000024	// ����һ������, �����ͻ���

#define   ET_RESET_DEVICE		0x00000031      // ��λ�豸

#define   ET_GET_CURRENT_TIME	0x00000032	/* get current time */
#define   ET_GET_PRODUCT_NAMEID	0x00000033	/* get product name ID */



#define   ET_DEVICE_TYPE_PKI	0x01	// �����֤������
#define   ET_DEVICE_TYPE_DONGLE	0x02	// ����������
#define   ET_DEVICE_TYPE_EMPTY	0x04	// ��������


#define   ET_DEFAULT_TRY	0xFF	// Ĭ�����Դ��������޴Σ�

#define   ET_DEFAULT_DEV_PIN	(unsigned char *)"123456781234567812345678"
#define   ET_DEFAULT_USER_PIN	(unsigned char *)"12345678"
#define   ET_DEV_PIN_LEN	24
#define   ET_USER_PIN_LEN	8


#define   ET_EXCLUSIVE_MODE	0        // ��ռģʽ
#define   ET_SHARE_MODE		1        // ����ģʽ

#ifndef	 ET199_FILE_TYPE
#define   ET199_FILE_TYPE


#define  FILE_TYPE_EXE		0	// ��ִ���ļ�
#define  FILE_TYPE_DATA		1	// �����ļ�
#define  FILE_TYPE_RSA_PUBLIC	2	// RSA ��Կ�ļ�
#define  FILE_TYPE_RSA_PRIVATE	3	// RSA ˽Կ�ļ�
#define  FILE_TYPE_INTERNAL_EXE	4	// ��ִ���ļ������ɶ�д��

#endif

struct  ET_CONTEXT {
        int dwIndex;			// ��0��ʼ���豸����
        unsigned long dwVersion;	// �豸COS�汾
        //HANDLE hLock;			// �豸���
        unsigned char reserve[12];	// ����
        unsigned long dwCustomer;	// �ͻ���
        unsigned char bAtr[MAX_ATR_LEN];// ATR
        unsigned char bID[MAX_ID_LEN];	// Ӳ��ID
        unsigned long dwAtrLen;		// ATR����
};

struct  ET_MANUFACTURE_DATE {
        unsigned char byYear;		// ��
        unsigned char byMonth;		// ��
        unsigned char byDay;		// ��
        unsigned char byHour;		// ʱ
        unsigned char byMinute;		// ��
        unsigned char bySecond;		// ��
};


    #ifndef ET199_FILEINFO
    #define ET199_FILEINFO
    #pragma pack (1)
    struct  EFINFO
	{
        unsigned short wFileID;											// �ļ�ID
        unsigned char bFileType;											// �ļ�����
        unsigned short wFileSize;											// �ļ���С
    };
    #pragma pack ()
    #endif


    struct ET_CREATEDIRINFO
	{
        unsigned long dwCreateDirInfoSize;								// �ṹ���С
        unsigned char  szAtr[MAX_ATR_LEN];								// ATR �ַ���
    };

	struct ET_OPENINFO
	{
		unsigned long dwOpenInfoSize;									// �ṹ���С
		unsigned long dwShareMode;									// ����ģʽ
	};

	//====================ET199 COS RSA TLV==================================================
	#define STRUCT_COS_TLV_(Tlv_Length)									   \
	struct																   \
	{																	   \
		unsigned char bTagHigh;											   \
		unsigned char bTagLow;											   \
		unsigned char bLenHigh;											   \
		unsigned char bLenLow;											   \
		unsigned char bData[Tlv_Length];								   \
	}
	//===============ET199 COS RSA ��Կ======================================================

	#define STRUCT_COS_RSA_PUBLIC_KEY_(Bits)								\
	struct																	\
	{																		\
		STRUCT_COS_TLV_(Bits/8)		n;										\
		STRUCT_COS_TLV_(4)			e;										\
	}

	typedef STRUCT_COS_RSA_PUBLIC_KEY_(512 )	COS_RSA_PUBLIC_KEY_512;
	typedef STRUCT_COS_RSA_PUBLIC_KEY_(1024)	COS_RSA_PUBLIC_KEY_1024;
	typedef STRUCT_COS_RSA_PUBLIC_KEY_(2048)	COS_RSA_PUBLIC_KEY_2048;

	//===============ET199 COS RSA ˽Կ======================================================
	#define STRUCT_COS_RSA_CRT_PRIVATE_KEY_(Bits)							\
	struct																	\
	{																		\
		STRUCT_COS_TLV_(Bits/16)	p;										\
		STRUCT_COS_TLV_(Bits/16)	q;										\
		STRUCT_COS_TLV_(Bits/16)	dp;										\
		STRUCT_COS_TLV_(Bits/16)	dq;										\
		STRUCT_COS_TLV_(Bits/16)	InvQ;									\
	}

	typedef STRUCT_COS_RSA_CRT_PRIVATE_KEY_(512 )	COS_RSA_CRT_PRIVATE_KEY_512;
	typedef STRUCT_COS_RSA_CRT_PRIVATE_KEY_(1024)	COS_RSA_CRT_PRIVATE_KEY_1024;
	typedef STRUCT_COS_RSA_CRT_PRIVATE_KEY_(2048)	COS_RSA_CRT_PRIVATE_KEY_2048;

	#define STRUCT_COS_RSA_PRIVATE_KEY_(Bits)								\
	struct																	\
	{																		\
		STRUCT_COS_TLV_(Bits/8)	n;										    \
		STRUCT_COS_TLV_(Bits/8)	d;										    \
	}

	typedef STRUCT_COS_RSA_PRIVATE_KEY_(512 )	COS_RSA_PRIVATE_KEY_512;
	typedef STRUCT_COS_RSA_PRIVATE_KEY_(1024)	COS_RSA_PRIVATE_KEY_1024;
	typedef STRUCT_COS_RSA_PRIVATE_KEY_(2048)	COS_RSA_PRIVATE_KEY_2048;

//===================��������===================================


//
unsigned long  ETEnum(struct ET_CONTEXT *pETContextList, int * pdwDeviceCount);
unsigned long  ETOpen(struct ET_CONTEXT *pETCtx);
unsigned long  ETClose(struct ET_CONTEXT * pETCtx);
unsigned long  ETControl(struct ET_CONTEXT *pETCtx, unsigned int dwCtlCode, unsigned char *pInBuffer, unsigned long dwInBufferLen, unsigned char *pOutBuffer, unsigned int dwOutBufferLen, unsigned long *pdwBytesReturned);
unsigned long  ETCreateDir(struct ET_CONTEXT * pETCtx,  char* lpszDirID,  unsigned long dwDirSize,  unsigned long dwFlags);
unsigned long  ETCreateDirEx(struct ET_CONTEXT * pETCtx, char* lpszDirID,  unsigned long dwDirSize,  unsigned long dwFlags,  struct ET_CREATEDIRINFO * pCreateDirInfo);
unsigned long  ETChangeDir(struct ET_CONTEXT * pETCtx,  char* lpszPath);
unsigned long  ETEraseDir(struct ET_CONTEXT	* pETCtx,  char* lpszDirID);
unsigned long  ETVerifyPin(struct ET_CONTEXT * pETCtx,  unsigned char * pbPin,  unsigned long dwPinLen,  unsigned long dwPinType);
unsigned long  ETChangePin(struct ET_CONTEXT * pETCtx,  unsigned char * pbOldPin,  unsigned long dwOldPinLen,  unsigned char * pbNewPin,  unsigned long dwNewPinLen, unsigned long dwPinType, unsigned char byPinTryCount);
unsigned long  ETCreateFile(struct ET_CONTEXT * pETCtx,  char* lpszFileID,  unsigned long dwFileSize,  unsigned char bFileType);
unsigned long  ETWriteFile(struct ET_CONTEXT * pETCtx,  char* lpszFileID,  unsigned long dwOffset,  unsigned char * pBuffer,  unsigned long dwBufferSize);
unsigned long  ETWriteFileEx(struct ET_CONTEXT	*pETCtx,  char* lpszFileID,  unsigned long	dwOffset, unsigned char * pBuffer,  unsigned long	dwBufferSize, unsigned long dwFileSize, unsigned long * pdwBytesWritten, unsigned long dwFlags, unsigned char bFileType);
unsigned long  ETExecute(struct ET_CONTEXT * pETCtx,  char* lpszFileID,  unsigned char * pInBuffer, unsigned long dwInbufferSize, unsigned char * pOutBuffer, unsigned long dwOutBufferSize, unsigned long * pdwBytesReturned);
unsigned long  PETWriteFile (struct ET_CONTEXT * pETCtx, char* lpszFileID, char* lpszPCFilePath, unsigned long * pdwFileSize, unsigned long dwFlags, unsigned char bFileType, unsigned long *pdwBytesWritten);
unsigned long  ETGenRsaKey(struct ET_CONTEXT *pETCtx,  unsigned short wKeySize,  unsigned long dwE,  char*	lpszPubFileID,  char* lpszPriFileID, unsigned char * pbPubKeyData, unsigned long * dwPubKeyDataSize, unsigned char * pbPriKeyData, unsigned long * dwPriKeyDataSize);
unsigned long  ETFormatErrorMessage( unsigned long dwRet, char*	lpszMessage,  unsigned long dwMsgBufLen);

//==============================================================

#endif

