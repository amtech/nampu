#ifndef __rtp_h__
#define __rtp_h__

#include "stdint.h"


typedef struct rtp_pkt_s rtp_pkt_t;
struct rtp_pkt_s {
#ifndef BIGENDIAN
    uint32_t csrc_count:4;    /* �й���Դ���� */
    uint32_t extension:1; 
    uint32_t padding:1;
    uint32_t version:2; 
    uint32_t payload_type:7;  /* �غ����� */
    uint32_t marker:1;
#else
    uint32_t version:2;
    uint32_t padding:1; 
    uint32_t extension:1;
    uint32_t csrc_count:4;
    uint32_t marker:1;
    uint32_t payload_type:7;
#endif
    uint16_t seq;
    uint32_t timestamp;
    uint32_t ssrc;            /* ͬ��Դ */
	uint32_t data[0];
};

#define RTP_PKT_CC(pkt)     (((rtp_pkt_t*)pkt)->csrc_count)
#define RTP_PKT_MARK(pkt)   (((rtp_pkt_t*)pkt)->marker)
#define RTP_PKT_PT(pkt)     (((rtp_pkt_t*)pkt)->payload_type)
#define RTP_PKT_SEQ(pkt)    ntohs(((rtp_pkt_t*)pkt)->seq)
#define RTP_PKT_TS(pkt)     ntohl(((rtp_pkt_t*)pkt)->timestamp)
#define RTP_PKT_SSRC(pkt)   ntohl(((rtp_pkt_t*)pkt)->ssrc)
#define RTP_PKT_DATA(pkt)   (&((rtp_pkt_t*)pkt)->data[0]  + ((rtp_pkt_t*)pkt)->csrc_count)

#define RTPPT_ISDYNAMIC(pt)    (pt >= 96)

typedef struct rtp_ext_hdr_s
{
  uint16_t unused;
  uint16_t length;
  uint8_t  data[0];
}rtp_ext_hdr_t;

typedef struct j_rtp_ext_s
{
#ifdef BIGENDIAN
  uint8_t  version   : 2,
           frame_type: 4,
           reserved  : 2;
#else
  uint8_t  reserved  : 2,
           frame_type: 4, /* ֡���� */
           version   : 2; /* RTP��չ���ְ汾�� */
#endif
  uint8_t  unused;
  uint16_t size;          // ��չ���ݳ���
  uint8_t  data[0];       // ��չ����
}j_rtp_ext_t;

typedef struct j_rtp_v_ext_s
{
  u_int16_t width;         // ��Ƶ���
  u_int16_t height;        // ��Ƶ�߶�
  u_int32_t frame_num;     // ֡��
  u_int32_t frame_length;  // ��Ƶ֡����
  u_int32_t utc_time;
}j_rtp_v_ext_t;

typedef struct j_rtp_a_ext_s
{
  u_int16_t fps;           // ��Ƶ֡��
  u_int16_t reserved;      // ����
  u_int32_t frame_num;     // ��Ƶ֡��
  u_int32_t frame_length;  // ��Ƶ֡��
}j_rtp_a_ext_t;

typedef struct j_rtp_av_ext_s
{
    union {
        j_rtp_v_ext_t v;
        j_rtp_a_ext_t a;
    };
}j_rtp_av_ext_t;

#endif //__rtp_h__
