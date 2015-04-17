// ping.h

#include <iostream>
#include <iomanip>
//#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;


//IP���ݱ�ͷ
typedef struct
{
	unsigned char hdr_len :4;		// length of the header
	unsigned char version :4;		// version of IP
	unsigned char tos;				// type of service
	unsigned short total_len;		// total length of the packet
	unsigned short identifier;		// unique identifier
	unsigned short frag_and_flags;	// flags
	unsigned char ttl;				// time to live
	unsigned char protocol;			// protocol(TCP, UDP etc)
	unsigned short checksum;		// IPchecksum

	unsigned long sourceIP;			// source IP address
	unsigned long destIP;			//destination IP address

} IP_HEADER;


// ICMP ���ݱ�ͷ
typedef struct
{
	BYTE type;			// 8 λ����
	BYTE code;			// 8 λ����
	USHORT cksum;		// 16 λУ���
	USHORT id;			// 16 λ��ʶ��
	USHORT seq;			// 16 λ���к�

} ICMP_HEADER, *PICMP_HEADER;


// ������
typedef struct
{
	USHORT usSeqNO;				// �����к�
	DWORD dwRoundTripTime;		// ����ʱ��
	in_addr dwIPaddr;			// �Զ� IP ��ַ

} DECODE_RESULT;


#define ICMP_ECHO_REQUEST		8		// �������
#define ICMP_ECHO_REPLY			0		// ����Ӧ��
#define ICMP_TIMEOUT			11		// ���䳬ʱ

#define IP_HEADER_SIZE			sizeof(IP_HEADER)
#define DEF_ICMP_DATA_SIZE		32		// Ĭ�� ICMP ���ݲ��ֳ���
#define MAX_ICMP_PACKET_SIZE	1024	// ��� ICMP ���ݱ��Ĵ�С
#define ICMP_HEADER_SIZE		sizeof(ICMP_HEADER)
#define ICMP_PACK_SIZE			(ICMP_HEADER_SIZE + DEF_ICMP_DATA_SIZE)

#define SEND_PACKAGE_TIMES		4		// ���Ͱ��Ĵ���


BOOL Ping(const char *pIP);
