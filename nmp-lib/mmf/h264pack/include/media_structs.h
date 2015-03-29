#ifndef __MEDIA_STRUCTS_H__
#define __MEDIA_STRUCTS_H__

#include <stdint.h>

/*������*/
enum {
     SAMPLE_8K       /*8K Sample rate*/
    ,SAMPLE_90K
};


/*��������*/
enum {
   ENC_H264          /*H264*/
  ,ENC_MPEG4         /*MPEG4*/
  ,ENC_G711A         /*G711A*/
  ,ENC_G711U		 /*G711U*/
};


/*֡����*/
enum {
    FRAME_I  = 0x01 /*��ƵI*/
   ,FRAME_P  = 0x02 /*��ƵP*/
   ,FRAME_B  = 0x03 /*��ƵB*/
   ,FRAME_A  = 0x04 /*��Ƶ֡*/
   ,FRAME_EOF= 0x0F /*������֡*/
};


/*ý������*/
enum {
     MEDIA_VIDEO = 0x01
    ,MEDIA_AUDIO = 0x02
};


/*��Ƶ��չ��Ϣ*/
typedef struct frame_v_ext_s {
    uint16_t   width;           /* ��Ƶ���*/
    uint16_t   height;          /* ��Ƶ�߶�*/
    uint32_t   utc_time;
}frame_v_ext_t;


/*��Ƶ��չ��Ϣ*/
typedef struct frame_a_ext_s {
    uint8_t samples_per_sec;     /*������*/         
    uint8_t bits_per_sample;     /*λ��*/
    uint8_t channel_num;         /*��Ƶͨ����Ŀ, �� 1��2 */
    uint8_t reserved;            /*����*/
}frame_a_ext_t;


/*��Ƶ֡NAL����*/
typedef struct nal_desc_s {
    uint32_t nal_num;           /*NAL����*/
    struct nal_s {
        uint32_t nal_off;       /*NAL��ַ*/
        uint32_t nal_size;      /*NAL��С*/
    }nal[0];
}nal_desc_t;


/*��/��Ƶ֡ͷ*/
typedef struct frame_hdr_s {
    uint16_t   no;          /*֡���*/
    uint16_t   enc_type;    /*��������*/
    uint32_t   timestamp;   /*ʱ��׿�� ms*/
    uint32_t   type;        /*֡����*/
    union
    {
        frame_v_ext_t v;    /*��Ƶ��չ*/
        frame_a_ext_t a;    /*��Ƶ��չ*/
    };
    uint32_t   size;        /*֡���ݳ���*/
}frame_hdr_t;


/*֡����*/
typedef struct frame_s {
    frame_hdr_t hdr;        /*֡ͷ*/
    uint8_t    *data;       /*֡����*/
    nal_desc_t *nal_desc;   /*��Ƶ֡NAL����*/
}frame_t;


/*ͼ�����*/
typedef struct pic_parm_s {
    uint16_t sps_size;      /*sps���ݳ���*/
    uint16_t pps_size;      /*pps���ݳ���*/
    uint8_t  sps[128];      /*������ʼ��*/
    uint8_t  pps[128];      /*������ʼ��*/
}pic_parm_t;


/*��Ƶ��Ϣ*/
typedef struct media_v_s
{
    uint16_t enc_type;        /*��������*/
    uint16_t bitrate;         /*����*/
    uint16_t samples_per_sec; /*������*/
    uint16_t frame_rate;      /*֡��*/
    pic_parm_t pic_parm;      /*ͼ�����*/
}media_v_t;


/*��Ƶ��Ϣ*/
typedef struct media_a_s
{
    uint16_t enc_type;        /*��������*/
    uint16_t bitrate;         /*����*/
    uint16_t samples_per_sec; /*������*/
    uint16_t bits_per_sample; /*λ��*/         
    uint16_t frame_rate;      /*֡��*/
    uint16_t channel_num;     /*��Ƶͨ����Ŀ, �� 1��2 */
}media_a_t;


/*ý����Ϣ*/
typedef struct media_info_s {
    uint32_t  mask;           /*ý����������*/
    uint32_t  begin_time;     /*ý�忪ʼʱ��*/
    uint32_t  end_time;       /*ý�����ʱ��*/
    media_v_t video;          /*��Ƶý����Ϣ*/
    media_a_t audio;          /*��Ƶý����Ϣ*/
}media_info_t;


#endif  //__MEDIA_STRUCTS_H__
