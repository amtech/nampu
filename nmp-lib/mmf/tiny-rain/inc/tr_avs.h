/*
 * RTSP/SIP������豸�Խӽӿ�(Ver 1.0)
*/

#ifndef __TINY_RAIN_AV_SERVER_H__
#define __TINY_RAIN_AV_SERVER_H__

#include "media_structs.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CTL_CMD_IFRAME          1

#define AVS_API extern
typedef struct __avs_media avs_media;
typedef void (*exp_cb)(void *u, int32_t err);       /* �������������ص���err->0����ɹ�������ֵ��������ʧ�� */
typedef void (*log_handler)(uint8_t *message);      /* ��־��Ϣ�ص� */

/* ����������ӿ� */
AVS_API void avs_media_set_u(avs_media *m, void *u);                        /* �����û����� */
AVS_API void *avs_media_get_u(avs_media *m);                                /* ��ȡ�û����� */
AVS_API int32_t avs_media_fill(avs_media *m, frame_t *frm);                 /* ʵʱ������ */
AVS_API void avs_media_kill(avs_media *m);                                  /* ����ͨ��AVS */
AVS_API avs_media *avs_media_ref(avs_media *m);                             /* ���ԶԾ�������� */
AVS_API void avs_media_unref(avs_media *m);                                 /* ���ٶԾ�������� */

/* ֡����ӿڣ�������ʷ��pull */
AVS_API frame_t *avs_alloc_frame(uint32_t data_size, uint32_t nal_count);   /* ����һ֡�Ŀռ� */
AVS_API void avs_free_frame(frame_t *frame);                                /* �ͷ�һ֡�ռ䣬�����֡����ʧ��ʱʹ�� */

/* ʵʱ���ӿ� */
typedef struct __ls_avs_ops ls_avs_ops;
struct __ls_avs_ops
{
    int32_t (*probe)(int32_t channel, int32_t level, media_info_t *mi);     /* ��ȡý����Ϣ,���ܱ��������� */
    int32_t (*open)(avs_media *m, int32_t channel, int32_t level);          /* ��ʼ�� */
    int32_t (*play)(avs_media *m);                                          /* ������֮�����ʹ��avs_media_fill()����ʵʱ�� */
    int32_t (*ctrl)(avs_media *m, uint32_t cmd, void *data);                /* ���ƣ�cmd=1,data=NULL ǿ��I֡; */
    void    (*close)(avs_media *m);                                         /* �ر� */
};

/* ��ʷ���ӿ� */
typedef struct __hs_avs_ops hs_avs_ops;
struct __hs_avs_ops
{
    int32_t (*probe)(int32_t channel, int32_t level, int32_t type,       
        uint8_t *start_time, uint8_t *end_time, uint8_t *property,          /* ʱ���ʽ:YYYYMMDDHHMMSS */
        media_info_t *mi);                                                  /* ��ȡý����Ϣ,���ܱ��������� */
    int32_t (*open)(avs_media *m, int32_t channel, int32_t level,
        int32_t type, uint8_t *start_time, uint8_t *end_time, uint8_t *property); /* ��ʼ�� */
    int32_t (*play)(avs_media *m);                                          /* SDK������ʼ�ص�.pull(), ����userʵ����ز��ԣ���Ԥ���ȣ�����ΪNULL */
    int32_t (*pause)(avs_media *m);                                         /* SDK������ͣ�ص�.pull(), ����userʵ����ز��ԣ���Ԥ���ȣ�����ΪNULL */
    int32_t (*lseek)(avs_media *m, uint32_t ts);                            /* ��λ */
    void    (*close)(avs_media *m);                                         /* �ر� */
    int32_t (*pull)(avs_media *m, frame_t **frm);                           /* SDK��ȡ��ʷ��Ƶ��HOOK */
};

AVS_API int32_t avs_init( void );                                           /* ��ʼ�� */
AVS_API int32_t avs_get_version(uint32_t *major, uint32_t *minor);          /* ��ȡAVS�汾�� */
AVS_API int32_t avs_register_ops(ls_avs_ops *lso, hs_avs_ops *hso);         /* ע��ص� */
AVS_API int32_t avs_set_stream_ports_range(uint16_t low, uint16_t hi);      /* �������˿ڷ�Χ������֧��DMZ������·�ɶ˿�ӳ�书�ܣ�Ĭ�ϣ�[15000,20000) */
AVS_API int32_t avs_start(uint16_t port);                                   /* RTSP ����˿ڣ�Ĭ�ϣ�7554 */
AVS_API void    avs_stop( void );                                           /* ֹͣ���� */

/* ƽ̨������ */
AVS_API int32_t avs_start_pf_service(uint8_t *mds_ip, uint16_t port, int32_t pu_type,
    uint8_t *puid, int32_t l4_proto, int32_t ka, exp_cb exp, void *u);      /* ����ƽ̨������ */
AVS_API int32_t avs_stop_pf_service( void );                                /* ֹͣƽ̨������ */


/* ��־�Խ�*/
AVS_API int32_t avs_log_set_handler(log_handler lf);
AVS_API int32_t avs_log_set_verbose(int8_t level);

#ifdef __cplusplus
}
#endif

#endif  /* __TINY_RAIN_AV_SERVER_H__ */
