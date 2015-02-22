/*
 *	@author:	zyt
 *	@time:	2013/1/9
 */
#ifndef __NMP_SHARE_STRUCT_H__
#define __NMP_SHARE_STRUCT_H__

#include "nmp_msg_share.h"



typedef struct _JpfTimeSeg JpfTimeSeg;
struct _JpfTimeSeg
{
	gint			seg_enable;		//ʱ�����Ч��:0-��Ч��1-��Ч
	gchar		time_seg[TIME_SEG_LEN];
};

typedef struct _JpfWeekday JpfWeekday;
struct _JpfWeekday
{
	gint			weekday;		//0��ʾ����, 1-6�ͱ�ʾ��һ������, 7��ʾÿ��
	gint			time_seg_num;
	JpfTimeSeg	time_segs[TIME_SEG_NUM];
};


typedef struct _JpfShareMssId JpfShareMssId;
struct _JpfShareMssId
{
    gchar			mss_id[MSS_ID_LEN];
};

typedef struct _JpfShareGuid JpfShareGuid;
struct _JpfShareGuid
{
	gchar		domain_id[DOMAIN_ID_LEN];
	gchar		guid[MAX_ID_LEN];
};

typedef struct _JpfSegment JpfSegment;
struct _JpfSegment
{
    gint  open;//����
    gint  begin_sec; //��ʼʱ������ 3600*hour+60*min+sec
    gint  end_sec; //����ʱ������ 3600*hour+60*min+sec
};

typedef struct _IrcutTimerSwitch IrcutTimerSwitch;
struct _IrcutTimerSwitch
{
    	gint			weekday;		//0��ʾ����, 1-6�ͱ�ʾ��һ������, 7��ʾÿ��
	gint			time_seg_num;
    JpfSegment seg_time[TIME_SEG_NUM]; //ʱ��Σ�4�Σ�  in segment time open ir light, otherwise close it
};



#endif	/* __NMP_SHARE_STRUCT_H__ */
