// ping.cpp

#include "stdafx.h"
#include "ping.h"

// ����У���
static USHORT GenerateChecksum(USHORT *pBuff, int nSize)
{
	unsigned long cksum = 0;
	while(nSize > 1)
	{
		cksum += *pBuff++;
		nSize -= sizeof(USHORT);
	}
	if(nSize)
	{
		cksum += *(UCHAR*)pBuff;
	}
	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);

	return (USHORT)(~cksum);
}



// ����õ������ݱ�
static
BOOL DecodeIcmpResponse(char *pBuff, int nPacketSize, DECODE_RESULT& stDecodeResult)
{
	// ������ݵĺϷ���
	IP_HEADER *pIpHdr = (IP_HEADER*)pBuff;
	int nIpHdrLen = pIpHdr->hdr_len * 4;		// �� 4 �ֽ�Ϊ��λ(����� IP ���ݰ��ĸ�ʽ)
	if(nPacketSize < (int)(nIpHdrLen + sizeof(ICMP_HEADER)))
	{
		return FALSE;
	}
	
	// ���� ICMP �����ͼ�� id �ֶκ����к���ȷ���Ƿ��ǳ���Ӧ���յ� ICMP ��
	ICMP_HEADER *pIcmpHdr = (ICMP_HEADER*)(pBuff + nIpHdrLen);	// ��ȥ IP ��ͷ��
	USHORT usID, usSquNO;
	
	if(pIcmpHdr->type == ICMP_ECHO_REPLY)
	{
		usID = pIcmpHdr->id;
		usSquNO = pIcmpHdr->seq;
	}
	else if(pIcmpHdr->type == ICMP_TIMEOUT)
	{
		char *pInnerIpHdr = pBuff + nIpHdrLen + sizeof(ICMP_HEADER);	// �غ��е� IP ͷ
		int nInnerIpHdrLen = ((IP_HEADER*)pInnerIpHdr)->hdr_len * 4;	// �غ��е� IP ͷ��
		ICMP_HEADER *pInnerIcmpHdr = (ICMP_HEADER*)(pInnerIpHdr + nInnerIpHdrLen);	//�غ��е�ICMPͷ
		usID = pInnerIcmpHdr->id;
		usSquNO = pInnerIcmpHdr->seq;
	}
	else
	{
		return FALSE;
	}

	if(usID != (USHORT)GetCurrentProcessId() || usSquNO != stDecodeResult.usSeqNO)
	{
		return FALSE;
	}

	// ������ȷ�յ��� ICMP ���ݱ�
	if(pIcmpHdr->type == ICMP_ECHO_REPLY || pIcmpHdr->type == ICMP_TIMEOUT)
	{
		// ���ؽ�����
		stDecodeResult.dwIPaddr.s_addr = pIpHdr->sourceIP;
		stDecodeResult.dwRoundTripTime = GetTickCount() - stDecodeResult.dwRoundTripTime;

		// ��ӡ��Ļ��Ϣ
		if(stDecodeResult.dwRoundTripTime)
		{
			// cout << setw(6) << stDecodeResult.dwRoundTripTime << "ms" << flush;
		}
		else
		{
			// cout << setw(6) << "< 1 " << "ms" << flush;
		}

		return TRUE;
	}

	return FALSE;
}



// 
BOOL Ping(const char *pIP)
{
	if(pIP == NULL)
	{
		return FALSE;
	}

	// ��ʼ�� winsock2 ����
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{

		return FALSE;
	}

	if(getprotobyname("icmp") == NULL)
	{
		return FALSE;
	}
	
	// �� IP �ַ���ת��Ϊ IP ��ַ
	u_long ulDstIp = inet_addr(pIP);

	SOCKADDR_IN dstSockAddr;
	ZeroMemory(&dstSockAddr, sizeof(SOCKADDR_IN));
	dstSockAddr.sin_family = AF_INET;
	dstSockAddr.sin_addr.s_addr = ulDstIp;
	dstSockAddr.sin_port = htons(0);

	SOCKET RawSock = WSASocket(AF_INET, SOCK_RAW, 
		IPPROTO_ICMP, NULL, 0, WSA_FLAG_OVERLAPPED);

	if(RawSock == INVALID_SOCKET)
	{

		return FALSE;
	}

	// ���ý��ջ�������, ��ʱʱ��Ϊ 1 ��
	int nTimeOut = 1000;
	if(setsockopt(RawSock, SOL_SOCKET, SO_RCVTIMEO, (char*)&nTimeOut, sizeof(nTimeOut)) == SOCKET_ERROR)
	{

		return FALSE;
	}

	// ���÷��ͻ�������, ��ʱʱ��Ϊ 1 ��
	if(setsockopt(RawSock, SOL_SOCKET, SO_SNDTIMEO, (char*)&nTimeOut, sizeof(nTimeOut)) == SOCKET_ERROR)
	{

		return FALSE;
	}

	// ���� ICMP �����ͻ������ͽ��ջ�����
	char szIcmpSendBuff[ICMP_PACK_SIZE];
	char szIcmpRecvBuff[MAX_ICMP_PACKET_SIZE];

	DECODE_RESULT stDecodeResult;
	BOOL bPingSuccess = FALSE;		// ��Ҫ���ڿ��ƴ�ӡ��Ϣ, û��������;
	int nReceivedCount = 0;


	memset(szIcmpSendBuff, 0, sizeof(szIcmpSendBuff));
	memset(szIcmpRecvBuff, 0, sizeof(szIcmpSendBuff));

	// �������͵� ICMP ��
	PICMP_HEADER pIcmpHdr = (PICMP_HEADER)szIcmpSendBuff;
	pIcmpHdr->type = ICMP_ECHO_REQUEST;
	pIcmpHdr->code = 0;
	pIcmpHdr->id = (USHORT)::GetCurrentProcessId();
	memset(szIcmpSendBuff + sizeof(ICMP_HEADER), 'E', DEF_ICMP_DATA_SIZE);

	pIcmpHdr->seq = 0;
	pIcmpHdr->cksum = GenerateChecksum((USHORT*)szIcmpSendBuff, ICMP_PACK_SIZE);

	// ��¼���кź͵�ǰʱ��
	stDecodeResult.usSeqNO = ((ICMP_HEADER*)szIcmpSendBuff)->seq;
	stDecodeResult.dwRoundTripTime = GetTickCount();

	int nRet = ::sendto(RawSock, szIcmpSendBuff, ICMP_PACK_SIZE, 
		0, (SOCKADDR*)&dstSockAddr, sizeof(dstSockAddr));
	if(nRet == SOCKET_ERROR)
	{

		return FALSE;
	}
	sockaddr_in from;
	int nFromLen = sizeof(from);
	int nReadDataLen;


	nReadDataLen = recvfrom(RawSock, szIcmpRecvBuff, 
		MAX_ICMP_PACKET_SIZE, 0, (sockaddr*)&from, &nFromLen);

	if(nReadDataLen != SOCKET_ERROR)
	{
		if(DecodeIcmpResponse(szIcmpRecvBuff, nReadDataLen, stDecodeResult))
		{
			bPingSuccess = TRUE;
			nReceivedCount++;
			
		}
	}
	else if(WSAGetLastError() == WSAETIMEDOUT)
	{
		return FALSE;
	}
	else
	{
		return FALSE;
	}

	if(bPingSuccess == TRUE)
	{
		return TRUE;
	}


	return 0;
}

