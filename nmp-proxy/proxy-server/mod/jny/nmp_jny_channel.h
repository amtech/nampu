#ifndef __J_JNY_CHANNEL_H__
#define __J_JNY_CHANNEL_H__


#include "nmp_jny_srv_impl.h"

typedef struct _frame_data_info
{
	long					nStreamFormat;						//1��ʾԭʼ����2��ʾTS�����
	long					nESStreamType;						//ԭʼ�����ͣ�1��ʾ��Ƶ��2��ʾ��Ƶ
	long					nEncoderType;						//�����ʽ
	long					nCameraNo;							//������ţ���ʾ�������Եڼ�·
	unsigned long			nSequenceId;						//����֡���
	long					nFrameType;							//����֡����,1��ʾI֡, 2��ʾP֡, 0��ʾδ֪����
	long long				nTimeStamp;							//���ݲɼ�ʱ�������λΪ����
	long					nFrameRate;							//֡��
	long					nBitRate;							//��ǰ���ʡ�
	long					nImageFormatId;						//��ǰ��ʽ
	long					nImageWidth;						//��Ƶ���
	long					nImageHeight;						//��Ƶ�߶�
	long					nVideoSystem;						//��ǰ��Ƶ��ʽ
	unsigned long			nFrameBufLen;						//��ǰ���峤��
	long					nStreamId;							// ��ID
	long					nTimezone;							// ʱ��
	long					nDaylightSavingTime;				//����ʱ
	unsigned long			nDataLength;						//������Ч����
	char					pszData[0];							//����
}frame_data_info;


#ifdef __cplusplus
extern "C" {
#endif

extern stream_operation_t jny_strm_opt;


#ifdef __cplusplus
    }
#endif


#endif