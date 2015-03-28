#ifndef __RTCP_PACKET_H__
#define __RTCP_PACKET_H__

#include <linux/types.h>
#include <glib.h>


typedef enum {
    RTCP_SR   = 200,
    RTCP_RR   = 201,
    RTCP_SDES = 202,        /* Դ���� */
    RTCP_BYE  = 203,
    RTCP_APP  = 204
}rtcp_type;


typedef enum {              /* Դ�������� */
    RTCP_SDES_END   = 0,
    RTCP_SDES_CNAME = 1,
    RTCP_SDES_NAME  = 2,
    RTCP_SDES_EMAIL = 3,
    RTCP_SDES_PHONE = 4,
    RTCP_SDES_LOC   = 5,
    RTCP_SDES_TOOL  = 6,
    RTCP_SDES_NOTE  = 7,
    RTCP_SDES_PRIV  = 8,
    RTCP_SDES_MAX   = 9
}rtcp_sdes_type;


typedef struct _rtcp_comm_header rtcp_comm_header;
struct _rtcp_comm_header {
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
    __u32 count:5;          /* �������� */
    __u32 padding:1;
    __u32 version:2;
#elif G_BYTE_ORDER == G_BIG_ENDIAN
    __u32 version:2;
    __u32 padding:1;
    __u32 count:5;
#else
# error "Invalid byte order!"
#endif
    __u32 packet_type:8;    /* RTCP�������� */
    __u16 length;           /* RTCP����(��ͷ��4�ֽ�Ϊ��λ)-1*/
};


typedef struct _rtcp_src_desc rtcp_src_desc;
struct _rtcp_src_desc {     /* Դ���� */
    __u8 type;
    __u8 len;
    __u8 data[1];
};


typedef struct _rtcp_rr_block rtcp_rr_block;
struct _rtcp_rr_block {     /* ���ն˱���� */
    __u32 ssrc;             /* Դʶ�� */
    __u32 lost_rate:8;      /* ������(���ϴ�RR/SR) */
    __u32 lost:24;          /* ������(���ϴ�RR/SR��ȫ����ʧ�򲻷���RR) */
    __u32 last_seq;         /* ���յ������seq(��16λ), ��16λ��չΪ���ڼ��� */
    __u32 jitter;           /* ������� */
    __u32 lsr;              /* ��һ��SR��ʶ��NTPʱ������м�32λ */
    __u32 dlsr;             /* �յ���һ��SR�����ʹ�RR֮�����ʱ */
};


typedef struct _rtcp_sr_header rtcp_sr_header;
struct _rtcp_sr_header {    /* ���Ͷ˱��� */
    rtcp_comm_header comm_h;
    __u32 ssrc;             /* ��SR������Դ��ʶ */
    __u32 ntp_hi;           /* 64λNTP */
    __u32 ntp_lo;
    __u32 rtp_ts;           /* RTPʱ��� */
    __u32 pkt_sent;         /* �ѷ��͵�RTP���� */
    __u32 oct_sent;         /* �ѷ��͵�RTP�ֽ��� */
    rtcp_rr_block rr_b[1];  /* �������ն���Ϣ */
};


typedef struct _rtcp_rr_header rtcp_rr_header;
struct _rtcp_rr_header {
    rtcp_comm_header comm_h;
    __u32 ssrc;             /* ��RR������Դ��ʶ */
    rtcp_rr_block rr_b[1];  /* �������ն���Ϣ */
};


typedef struct _rtcp_sdes_header rtcp_sdes_header;
struct _rtcp_sdes_header {  /* Դ���� */
    rtcp_comm_header comm_h;
    __u32 src;
    rtcp_src_desc descrip[1];
};


typedef struct _rtcp_bye_header rtcp_bye_header;
struct _rtcp_bye_header {   /* �뿪ͨ�� */
    rtcp_comm_header comm_h;
    __u32 src[1];           /* Դ��ʶ */
    __u8 reason[1];         /* �뿪ԭ�� */
};


typedef struct _rtcp_app_header rtcp_app_header;
struct _rtcp_app_header {
    rtcp_comm_header comm_h;
    __u32 ssrc;             /* Դ��ʶ */
    __u8 name[4];           /* Ӧ������ */
    __u8 data[1];           /* Ӧ������ */
};


guint32 get_rtcp_sr_src(gpointer sr);
guint32 get_rtcp_sr_lsr(gpointer sr);

void init_rtcp_rr_packet(rtcp_rr_header *rh);
void set_rtcp_rr_src(rtcp_rr_header *rh, guint32 src);
void set_rtcp_rr_ssrc(rtcp_rr_header *rh, guint32 ssrc);
void set_rtcp_rr_lost(rtcp_rr_header *rh, 
    guint8 lost_rate, guint32 lost_packets);
void set_rtcp_rr_jitter(rtcp_rr_header *rh, guint32 jitter);
void set_rtcp_rr_lastseq(rtcp_rr_header *rh, guint32 lastseq);
void set_rtcp_rr_lsr(rtcp_rr_header *rh, guint32 lsr);
void set_rtcp_rr_dlsr(rtcp_rr_header *rh, guint32 dlsr);

void init_rtcp_bye_packet(rtcp_bye_header *bh);
void set_rtcp_bye_src(rtcp_bye_header *bh, guint32 src);

void dump_rtcp_packet(gpointer packet, gint len);

#endif  //__RTCP_PACKET_H__
