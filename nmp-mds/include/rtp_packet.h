#ifndef __RTP_PACKET_H__
#define __RTP_PACKET_H__

#include <linux/types.h>
#include <glib.h>

#define RTP_MTU         2048
#define RTP_HEADER_LEN  12

typedef struct _rtp_header rtp_header;
struct _rtp_header {
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
    __u32   csrc_count:4;    /* �й���Դ���� */
    __u32   extension:1; 
    __u32   padding:1;
    __u32   version:2; 
    __u32   payload_type:7;  /* �غ����� */
    __u32   marker:1;
#elif G_BYTE_ORDER == G_BIG_ENDIAN
    __u32   version:2;
    __u32   padding:1; 
    __u32   extension:1;
    __u32   csrc_count:4;
    __u32   marker:1;
    __u32   payload_type:7;
#else
    # error "Invalid byte order!"
#endif
    __u16   seq;
    __u32   timestamp;
    __u32   ssrc;            /* ͬ��Դ */
    __u32   csrc[1];         /* �й���Դ, ���ϳɸ�·ͬ��Դ�����в�����(����Դ) */ 
};


guint16 get_rtp_seq(gchar *packet);
guint32 get_rtp_ssrc(gchar *packet);

#endif  //__RTP_PACKET_H__
