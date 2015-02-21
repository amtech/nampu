/*
 * =====================================================================================
 *
 *       Filename:  sdk_struct.h
 *
 *    Description:  ���ݽṹ����
 *
 *        Version:  1.0
 *        Created:  2011��05��26�� 02ʱ35��09��
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  maohw (), maohongwei@gmail.com
 *        Company:  jxj
 *
 * =====================================================================================
 */
#ifndef __sdk_struct_h__
#define __sdk_struct_h__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


#define MAX_VER_STR_LEN         32      //�汾��Ϣ����
#define MAX_SERIAL_NO_LEN       32      //���кų���
#define MAX_DVR_NAME_LEN        32      //�豸���Ƴ���
#define MAX_CHANN_NAME_LEN      32      //ͨ�����Ƴ���
#define MAX_CHANN_NUM           32      //���ͨ������
#define MAX_USER_NAME_LEN       32      //�û�������
#define MAX_PASSWD_LEN          32      //���볤��
#define MAX_ALARM_IN_NAME_LEN   32      //�����������Ƴ���
#define MAX_WEEK_NUM            8       //��������
#define MAX_TIME_SEG_NUM        4       //ʱ��θ���
#define MAX_ALARM_OUT_NUM       16      //��󱨾��������
#define MAX_ALARM_IN_NUM        16      //��󱨾��������
#define MAX_IP_ADDR_LEN         40      //IP��ַ����
#define MAX_MAC_ADDR_LEN        20      //MAC��ַ����
#define MAX_ETHERNET_NUM        4       //��������
#define MAX_RECORD_ITEM_LEN     64      //¼���¼���Ƴ���
#define MAX_LOG_DESC_LEN        128     //��־��¼���ݳ���
#define MAX_USER_NUM            16      //����û�����
#define MAX_PRESET_NUM          256     //�����̨Ԥ��λ����
#define MAX_CRUISE_NUM          256     //�����̨Ѳ������
#define MAX_CRUISE_PRESET_NUM   16      //ÿ��Ѳ�������֧�ֵ�Ԥ��λ����
#define MAX_CHANN_CONN_NUM      8       //ÿ��ͨ�����֧�ֵ�������
#define MAX_DISK_NUM            8       //�����̸���
#define MAX_ALARM_DESC_LEN      64      //������¼���ݳ���
#define MAX_SCREEN_NUM          4       //���������Ļ����
#define MAX_WINDOWS_NUM         32      //����Ԥ����Ƶ��󴰿ڸ���
#define MAX_PREVIEW_MODE        8       //���Ԥ�����ָ���
#define MAX_OVERLAY_NUM         4       //ÿ��ͨ����󸲸��������
#define MAX_MOTION_NUM          4       //ÿ��ͨ������ƶ�����������
#define MAX_OSD_STR_LEN         64      //OSD�ַ�������
#define MAX_NTP_SETVER_STR_LEN  32      //NTP��������ַ����
#define MAX_BACKUP_ITEM			16		//��󱸷ݶ���

#define MAX_VDA_SENSITIVE_LEVEL     (9)

/*----------- ��Ϣ���� -----------*/

#define MAX_MSG_SIZE        (64*1024)
#define CHANN_TYPE_ALL      0xFA
#define PARAM_MASK_ALL		0xFFFF		// �ָ���������

#define DEV_TYPE_DVR		1			// dvr
#define DEV_TYPE_NVR		2			// nvr

typedef enum _SDK_MSG_DIR{
      SDK_MSG_RESP= 0x00
    , SDK_MSG_REQ = 0x01
}SDK_MSG_DIR_E;

typedef struct sdk_msg_s {
    uint16_t magic;         //��������չ(���豸����)
    uint16_t version;       //�汾��
#if 1
    union {
        struct {
            uint8_t src;    //Դģ��ID
            uint8_t dst;    //Ŀ��ģ��ID
        }__attribute__((packed)) id;
        uint16_t session_id;//�û��ỰID(�豸�˷���)
    }__attribute__((packed));
    uint16_t sequence_id;   //�������
#endif
#if 1
    uint16_t msg_id;        //����ID
    uint8_t  f_dir:1;       //��SDK_MSG_REQ, SDK_MSG_RESP)
    uint8_t  f_pkg:1;       //1:extend�ֶ������ְ�;
    uint8_t  f_res:6;       //����
    uint8_t  ack;           //������
#endif
    uint32_t args;          //�������(���á���ȡ����;����������������[�û��������������̹���])
    uint32_t extend;        //��չ�ֶ�(8:pkg_total,8:pkg_num, 8:, 8:)
    uint32_t chann;         //ͨ����(CHANN_TYPE_ALL)
    uint32_t size;          //��Ϣ����
    uint8_t  data[0];       //��Ϣ��
}sdk_msg_t;

/*----------- �������� -----------*/

typedef enum _SDK_PARAM_DIR{
      SDK_PARAM_SET	= 0x01	    //���ò���
    , SDK_PARAM_GET        		//��ѯ����
}SDK_PARAM_DIR_E;


/*----------- �����붨�� -----------*/

typedef enum _SDK_ERR_CODE {
      SDK_ERR_SUCCESS = 0x00        //�ɹ�
    , SDK_ERR_FAILURE               //ʧ��
    , SDK_ERR_PASS                  //�������
    , SDK_ERR_USER_NOT_EXIST		//�û���������
    , SDK_ERR_ROOT_USER				//root�û�����ɾ��
    , SDK_ERR_TOO_MANY_USER			//�û�����(�������16���û���)
    , SDK_ERR_USER_ALREADY_EXIST	//�û����Ѵ���
    , SDK_ERR_NET_CFG				//�����������ʧ��
    , SDK_ERR_PERMIT                //Ȩ�޴���
    , SDK_ERR_CHANN                 // 10 ͨ���Ŵ���
    , SDK_ERR_CONN_MAX              //�������������
    , SDK_ERR_CONN                  //���Ӵ���
    , SDK_ERR_SEND                  //���ݷ��ʹ���
    , SDK_ERR_RECV                  //���ݽ��մ���
    , SDK_ERR_BUSY                  //�豸��æ
    , SDK_ERR_DATA                  //���ݸ�ʽ����
    , SDK_ERR_CMD                   //�����ִ���
    , SDK_ERR_VER                   //Э��汾����
    , SDK_ERR_NO_DISK               //�޴���
    , SDK_ERR_DISK_ERR              // 20 ���̴���
    , SDK_ERR_RESOURCE              //��Դ������
    , SDK_ERR_FLASH                 //FLASH��д����
    , SDK_ERR_SET_SYSTIME			//����ϵͳʱ�����
    , SDK_ERR_SET_ENCODE_PARAM		//���ñ����������
    , SDK_ERR_SET_MD_PARAM			//�����ƶ�����������
    , SDK_ERR_SET_OSD_PARAM			//����OSD��������
    , SDK_ERR_SET_OVERLAY_PARAM		//�����ڵ������������
    , SDK_ERR_SET_TV_PARAM			//���ñ߾��С����
    , SDK_ERR_SET_IMAGE_ATTR		//����ͼ�����Դ���
	, SDK_ERR_LOG_QUERY				//��ѯ��־ʧ��
	, SDK_ERR_LOG_EMPTY				//�����־ʧ��
	, SDK_ERR_LOG_BACKUP			//������־ʧ��
	, SDK_ERR_SERIAL_NO				//���ںŴ���
	, SDK_ERR_SERIAL_OPEN			//�򿪴���ʧ��
	, SDK_ERR_SERIAL_PARAM_SET		//���ô��ڲ���ʧ��
	, SDK_ERR_DISK_MOUNT			//���̹���ʧ��
	, SDK_ERR_UMOUNT				//����ж��ʧ��
	, SDK_ERR_BACKUP				//����ʧ��	
	, SDK_ERR_LOG_DEL				//ɾ����־ʧ��
	
    , SDK_ERR_GET_DISK_PART_INOF	//��ȡ���̷�����Ϣ����
    , SDK_ERR_UPGRADING				//����������
    , SDK_ERR_UPGRADE_CHECK_HEAD	//У��������ͷ����
    , SDK_ERR_UPGRADE_FILE_FIND		// ���Ҳ��������ļ�
    , SDK_ERR_UPGRADE				// ����ʧ��

	, SDK_ERR_NVR_NOT_LOGIN				// ǰ���豸��û��½�ɹ�
  
}SDK_ERR_CODE_E;

/*----------- �澯���Ͷ��� -----------*/

typedef enum _SDK_EVENT_TYPE{
	  SDK_EVENT_MANUAL_REC = 0x000	//�ֶ�¼���¼�
    , SDK_EVENT_ALARM_IN    		//����澯�¼�
    , SDK_EVENT_MOTION              //�ƶ�����¼�
    , SDK_EVENT_LOST                //��Ƶ��ʧ�¼�
    , SDK_EVENT_HIDE                //��Ƶ�ڵ��¼�(Ŀǰ����)
    , SDK_EVENT_TIMER_REC           //��ʱ¼���¼�
    , SDK_EVENT_HD_ERR              //���̴����¼�
    , SDK_EVENT_HD_IS_EXIST			//¼�����Ƿ�����¼� (pmsg->extend: ������/����[0/1])

	/*8******* ר�����ϱ�������ģ�����Ϣ *************/
	, SDK_EVENT_REC_MSG				//¼���Ƿ����¼�
	, SDK_EVENT_ALARM_IN_MSG
	, SDK_EVENT_MOTION_MSG
	, SDK_EVENT_LOST_MSG
	, SDK_EVENT_HIDE_MSG
	/******** ***********************/
    
    /*13*********add 20120601 for  NVR***************/
    , SDK_DEV_LOGIN				//��¼
    , SDK_DEV_TIMEOUT           //��¼��ʱ
    , SDK_DEV_LOGOUT            //ע��
	, SDK_STREAM_OPEN	//���ڴ���
	, SDK_STREAM_CLOSE  		//���ӹر�
	
    /************add end******************/
	, SDK_EVENT_ALL
    , SDK_EVENT_BUTT
}SDK_EVENT_TYPE_E;


/*----------- ����Ƶ���Ͷ��� -----------*/


typedef enum _SDK_AUDIO_SAMPLE_RATE
{
	SDK_AUDIO_SAMPLE_R8K        = 0,   /* 8K Sample rate     */
	SDK_AUDIO_SAMPLE_R11_025K   = 1,   /* 11.025K Sample rate*/
	SDK_AUDIO_SAMPLE_R16K       = 2,   /* 16K Sample rate    */
	SDK_AUDIO_SAMPLE_R22050     = 3,   /* 22.050K Sample rate*/
	SDK_AUDIO_SAMPLE_R24K       = 4,   /* 24K Sample rate    */
	SDK_AUDIO_SAMPLE_R32K       = 5,   /* 32K Sample rate    */
	SDK_AUDIO_SAMPLE_R44_1K     = 6,   /* 44.1K Sample rate  */
	SDK_AUDIO_SAMPLE_R48K       = 7,   /* 48K Sample rate    */
    SDK_AUDIO_SAMPLE_BUTT,
}SDK_AUDIO_SAMPLE_RATE_E;

typedef enum _SDK_AUDIO_CODEC_FORMAT
{
	SDK_AUDIO_FORMAT_NULL	        = 0,   /*                    */
	SDK_AUDIO_FORMAT_G711A	        = 1,   /* G.711 A            */
	SDK_AUDIO_FORMAT_G711Mu	        = 2,   /* G.711 Mu           */
	SDK_AUDIO_FORMAT_ADPCM	        = 3,   /* ADPCM              */
	SDK_AUDIO_FORMAT_G726_16        = 4,   /* G.726              */
	SDK_AUDIO_FORMAT_G726_24        = 5,   /* G.726              */
	SDK_AUDIO_FORMAT_G726_32        = 6,   /* G.726              */
	SDK_AUDIO_FORMAT_G726_40        = 7,   /* G.726              */
	SDK_AUDIO_FORMAT_AMR	        = 8,   /* AMR encoder format */
	SDK_AUDIO_FORMAT_AMRDTX	        = 9,   /* AMR encoder formant and VAD1 enable */
	SDK_AUDIO_FORMAT_AAC	        = 10,  /* AAC encoder        */
	SDK_AUDIO_FORMAT_ADPCM_DVI4	    = 11,  /* ADPCM              */
	SDK_AUDIO_FORMAT_ADPCM_IMA	    = 12,  /* ADPCM              */
	SDK_AUDIO_FORMAT_MEDIA_G726_16  = 13,  /* G.726              */
	SDK_AUDIO_FORMAT_MEDIA_G726_24  = 14,  /* G.726              */
	SDK_AUDIO_FORMAT_MEDIA_G726_32  = 15,  /* G.726              */
	SDK_AUDIO_FORMAT_MEDIA_G726_40  = 16,  /* G.726              */
    SDK_AUDIO_FORMAT_BUTT,
}SDK_AUDIO_CODEC_FORMAT_E;

typedef enum _SDK_AUDIO_SAMPLE_WIDTH {
    SDK_AUDIO_SAMPLE_WIDTH_8  = 0,    /* 8bits */
    SDK_AUDIO_SAMPLE_WIDTH_16 = 2,    /* 16bits */
    SDK_AUDIO_SAMPLE_WIDTH_BUTT,
}SDK_AUDIO_SAMPLE_WIDTH_E;


/*
 * ��Ƶ֡��Ϣ(�ӽṹ��)
 */
typedef struct sdk_a_frame_info_s {
    uint8_t encode_type;        //�������� SDK_AUDIO_CODEC_FORMAT_E
    uint8_t samples;            //����Ƶ�� SDK_AUDIO_SAMPLE_RATE_E
    uint8_t bits;               //λ��     SDK_AUDIO_SAMPLE_WIDTH_E
    uint8_t channels;           //ͨ����
}sdk_a_frame_info_t;


typedef enum _SDK_VIDEO_ENCODE_FORMAT {
    SDK_VIDEO_FORMAT_H264    = 0, //H.264
    SDK_VIDEO_FORMAT_MPEG4   = 1, //MPEG4
    SDK_VIDEO_FORMAT_MJPEG   = 2, //MJPEG
}SDK_VIDEO_ENCODE_FORMAT_E;


typedef enum _SDK_VIDEO_STANDARD {
    SDK_VIDEO_STANDARD_PAL  = 0, // PAL
    SDK_VIDEO_STANDARD_NTSC = 1, //NTSC
}SDK_VIDEO_STANDARD_E;

typedef enum _SDK_VIDEO_RESOLUTION
{
    SDK_VIDEO_RESOLUTION_QCIF = 0, // (176x144)
    SDK_VIDEO_RESOLUTION_CIF  = 1, // (352x288)
    SDK_VIDEO_RESOLUTION_HD1  = 2, // (704x288)
    SDK_VIDEO_RESOLUTION_D1   = 3, // (704x576)
    SDK_VIDEO_RESOLUTION_MD1  = 4,
    SDK_VIDEO_RESOLUTION_QVGA = 5, // (320x240)
    SDK_VIDEO_RESOLUTION_VGA  = 6, // (640x480��
    SDK_VIDEO_RESOLUTION_720p = 7, // (1280x720)
    SDK_VIDEO_RESOLUTION_1080p= 8, // (1920x1080)
    SDK_VIDEO_RESOLUTION_UXGA = 9, // (1600x1200)
    SDK_VIDEO_RESOLUTION_XGA  = 10,// (1024x768)
    SDK_VIDEO_RESOLUTION_SVGA = 11,// (800x600)
    SDK_VIDEO_RESOLUTION_SXGA = 12,// (1280x1024)
    SDK_VIDEO_RESOLUTION_QXGA = 13,// (2048x1536)
    
    SDK_VIDEO_RESOLUTION_960H = 14,// (960x576)
    
    SDK_VIDEO_RESOLUTION_BUTT      // ----------

}SDK_VIDEO_RESOLUTION_E;


typedef enum _SDK_CODEC_AO_DEV_E
{
    SDK_CODEC_COMM_AO_DEV = 0
    , SDK_CODEC_HDMI_AO_DEV = 1
    , SDK_CODEC_AO_DEV_BUTT
}SDK_CODEC_AO_DEV_E;
typedef enum _SDK_CODEC_AO_MOD_E
{
    SDK_CODEC_PREVIEW_AO_MOD = 0
    , SDK_CODEC_PLAYBACK_AO_MOD = 1
    , SDK_CODEC_TALK_AO_MOD = 2
    , SDK_CODEC_MUTE_AO_MOD = 3
}SDK_CODEC_AO_MOD_E;
/*
 * ��Ƶ֡��Ϣ(�ӽṹ��) 
 */
typedef struct sdk_v_frame_info_s {
    uint8_t encode_type;        //�������� SDK_VIDEO_ENCODE_FORMAT_E
    uint8_t standard;           //��ʽ     0: PAL, 1: NTSC
    uint8_t resolution;         //�ֱ���   SDK_VIDEO_RESOLUTION_E
    uint8_t frame_rate;         //֡��     1-25/30 
}sdk_v_frame_info_t;



typedef enum _SDK_FRAME_TYPE {
    SDK_VIDEO_FRAME_I = 0x01,   //I֡
    SDK_VIDEO_FRAME_P = 0x02,   //P֡
    SDK_VIDEO_FRAME_B = 0x03,   //B֡
    SDK_AUDIO_FRAME_A = 0x04,   //��Ƶ֡A
}SDK_FRAME_TYPE_E;

/*
 * ����Ƶ֡�ṹ�嶨��
 */
typedef struct sdk_frame_s {
    uint16_t  magic;            //��������չ 
    uint8_t   res[1];           //����
    uint8_t   frame_type;       //֡����, ��Ƶ��I, P, B��, ��Ƶ��A��
    uint32_t  frame_size;       //֡����
    uint32_t  frame_no;         //֡���
    uint32_t  sec;              //֡ʱ�䣨�룩
    uint32_t  usec;             //֡ʱ�䣨΢�룩
    uint64_t  pts;              //֡PTS
    union
    {
        sdk_v_frame_info_t video_info;//��Ƶ֡��Ϣ
        sdk_a_frame_info_t audio_info;//��Ƶ֡��Ϣ
    };
    uint8_t   data[0];          //֡����
}sdk_frame_t;


/*----------- ���ò����ṹ���� -----------*/


/*
 * ʱ��ṹ�嶨��
 */
typedef struct sdk_time_s{
    uint32_t year;
    uint32_t mon;
    uint32_t day;
    uint32_t hour;
    uint32_t min;
    uint32_t sec;
}sdk_time_t;

/*
 * ��ϸʱ��ṹ�嶨��
 */
 typedef struct sdk_date_s{
    sdk_time_t _time;
    uint8_t     wday;
    uint8_t     tzone;
    uint8_t     res[2];
}sdk_date_t;



/*
 * ����ṹ�嶨��
 */
typedef struct sdk_rect_s{
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
}sdk_rect_t;

/*
 * ��ṹ�嶨��
 */
typedef struct sdk_point_s{
    uint16_t x;
    uint16_t y;
}sdk_point_t;

/*
 * ʱ��νṹ�嶨��
 */
typedef struct sdk_sched_time_s{
	uint8_t enable;	    //����, ����ʱ¼��ʱ��ʾ¼������;
	uint8_t res[3];
    uint8_t start_hour; //��ʼʱ��
	uint8_t start_min;
	uint8_t stop_hour;  //����ʱ��
	uint8_t stop_min;
}sdk_sched_time_t;


/*
 * �����������̣� SDK_UPGRAD_REQUEST => recv upg_pkg => SDK_UPGRAD_DISK_FILE => SDK_UPGRAD_PROGRESS;
 * GUI�������� :  SDK_UPGRAD_FIND_FILE => SDK_UPGRAD_DISK_FILE => SDK_UPGRAD_PROGRESS;
 */
typedef enum _SDK_UPGRAD_OP {
      SDK_UPGRAD_REQUEST   = 0x001  //��������				upgrade_packet_t
    , SDK_UPGRAD_DISK_FILE          //�������ڴ����ļ�
    , SDK_UPGRAD_MEM_FILE           //���������ڴ�
    , SDK_UPGRAD_PROGRESS           //��������
    , SDK_UPGRAD_FIND_FILE          //GUI��ѯ�������ļ��б�	upgrad_pkg_file_t
}SDK_UPGRAD_OP_E;

/*
 * GUI��ѯ�������ļ��б�
 */
typedef struct upgrad_pkg_file_s {
    uint8_t   device_type[16];//�豸����
    uint8_t   ver[16];        //�汾
    uint8_t   date[16];       //����
    uint32_t  size;           //��С
    uint8_t   name[32];       //���� aa.upg
    uint8_t   file_path[64];  //�����ļ�ȫ·�� /tmp/aa.upg
}upgrad_pkg_file_t;


typedef enum _SDK_USER_OP {
      SDK_USER_AAA = 0x001  //sdk_user_t
    , SDK_USER_ADD          //sdk_user_right_t
    , SDK_USER_DEL          //sdk_user_t
    , SDK_USER_MODI         //sdk_user_right_t
    , SDK_USER_QUERY        //sdk_user_t, sdk_user_right_t
}SDK_USER_OP_E;

typedef enum _SDK_DISK_OP {
      SDK_DISK_QUERY		= 0x001		//sdk_disk_t
    , SDK_DISK_FORMAT
    , SDK_DISK_PROGRESS
    , SDK_DISK_UMOUNT					//ж��U�� chann�ֶα�ʾ"�̺�"
}SDK_DISK_OP_E;


/*
 * �û�����(�û���������)
 */
typedef struct sdk_user_s {
    uint8_t user_name[MAX_USER_NAME_LEN];
    uint8_t user_pwd[MAX_PASSWD_LEN];
}sdk_user_t;


/*
 * �û�Ȩ�޶���
 */
typedef struct sdk_user_right_s {

    sdk_user_t user;   
    uint32_t local_right;           //����GUIȨ��
    /*bit.0: ���ؿ�����̨*/
	/*bit.1: �����ֶ�¼��*/
	/*bit.2: ���ػط�*/
	/*bit.3: �������ò���*/
	/*bit.4: ���ز鿴״̬����־*/
	/*bit.5: ���ظ߼�����(��������ʽ�����������ػ�)*/
    /*bit.6: ���ز鿴���� */
    /*bit.7: ���ع���ģ���IP camera */
    /*bit.8: ���ر��� */
    /*bit.9: ���عػ�/���� */

    uint32_t remote_right;          //Զ��Ȩ��
    /*bit.0: Զ�̿�����̨*/
	/*bit.1: Զ���ֶ�¼��*/
	/*bit.2: Զ�̻ط� */
	/*bit.3: Զ�����ò���*/
	/*bit.4: Զ�̲鿴״̬����־*/
	/*bit.5: Զ�̸߼�����(��������ʽ�����������ػ�)*/
	/*bit.6: Զ�̷��������Խ�*/
	/*bit.7: Զ��Ԥ��*/
	/*bit.8: Զ�����󱨾��ϴ����������*/
	/*bit.9: Զ�̿��ƣ��������*/
	/*bit.10: Զ�̿��ƴ���*/	
    /*bit.11: Զ�̲鿴���� */
    /*bit.12: Զ�̹���ģ���IP camera */
    /*bit.13: Զ�̹ػ�/���� */

    uint8_t local_backup_right[MAX_CHANN_NUM];     //ͨ��Ȩ��
    uint8_t net_preview_right[MAX_CHANN_NUM];
    
}sdk_user_right_t;


typedef enum _SDK_NETWORK_INTERFACE {
      SDK_IF_ETH0 = 0x0  //eth0
    , SDK_IF_ETH1		 //eth1
    , SDK_IF_PPP0		 //ppp0
    , SDK_IF_WIFI		 //wifi
}SDK_NET_IF_E;

/*
 * �������ã��ӽṹ�壩
 */
typedef struct sdk_ethernet_s {
    
    uint8_t ip_addr[MAX_IP_ADDR_LEN];//IP ADDR
    uint8_t mask[MAX_IP_ADDR_LEN];   //IP MASK
    uint8_t gateway[MAX_IP_ADDR_LEN];//����
    uint8_t mac[MAX_MAC_ADDR_LEN];   //MAC STRING
    uint8_t enable_dhcp;            //�Ƿ���DHCP
    uint8_t if_type;                //����ӿ�1-10MBase-T 2-10MBase-Tȫ˫�� 3-100MBase-TX 4-100Mȫ˫�� 5-10M/100M����Ӧ
    uint8_t res[2];                 //����

}sdk_ethernet_t;

/*
 * �������ã��ӽṹ�壩
 */
typedef struct sdk_pppoe_s {
    uint8_t enable;                    		//�Ƿ���PPPOE
    uint8_t if_no;                      	//����ӿ�
    uint8_t res[2];                     	//����
    
    uint8_t user[MAX_USER_NAME_LEN];    	//PPPOE �û���
    uint8_t pass[MAX_PASSWD_LEN];       	//PPPOE ����
    uint8_t pppoe_ip[MAX_IP_ADDR_LEN];  	//PPPOE IP ADDR
}sdk_pppoe_t;


/*
 * ��������
 */
typedef struct sdk_net_cfg_s {
    sdk_ethernet_t ethernet[MAX_ETHERNET_NUM];    //����ӿ�SDK_NET_IF_E
    sdk_pppoe_t    pppoe;                         //PPPOE����
    
    uint8_t        def_if_no;                     //Ĭ������ӿ�
    uint8_t        dns_auto_en;                   //�Զ���ȡDNS������DHCPʱ
    uint8_t        byte_res[2];                   //����
    
    uint8_t        dns1[MAX_IP_ADDR_LEN];         //DNS1
    uint8_t        dns2[MAX_IP_ADDR_LEN];         //DNS2
    uint8_t        multicast[MAX_IP_ADDR_LEN];    //�鲥��ַ
    uint8_t        net_manager[MAX_IP_ADDR_LEN];  //���������IP

    uint16_t       net_manager_port;              //���������PORT
    uint16_t       http_port;                     //DVR HTTP PORT
    uint16_t       dvr_cmd_port;                  //DVR SERVICE PROT
    uint16_t       dvr_data_port;                 //����

    uint8_t         res[64];                      //����
    
}sdk_net_cfg_t;



/*
 * DVR�������ò���
 */

typedef struct sdk_comm_cfg_s
{
    uint8_t 	dvr_name[MAX_DVR_NAME_LEN]; //DVR ����
    uint32_t 	dvr_id;                    	//DVR ID,(ң����)
    uint32_t 	recycle_record;            	//�Ƿ�ѭ��¼��,0:����; 1:��
    uint8_t 	language;					//����0: ����  1 :Ӣ��
    uint8_t  	video_mode;					//��Ƶ��ʽ0:PAL  1 NTSC
    uint8_t  	out_device;					//����豸  0: CVBS; 1: VGA-HDMI
    uint8_t  	resolution; 				//�ֱ���0 :1024 * 768    1 : 1280 * 720   2: 1280*1024  3: 1920*1080
    uint8_t 	standby_time; 				//�˵�����ʱ�� 1~60����  0: ��ʾ������
    uint8_t  	boot_guide;					//������ 0 : ��������  1 : ������
    uint8_t  	reserve[2];
} sdk_comm_cfg_t;


/* 
 *
 * DVRϵͳ���ò���
 */

typedef struct sdk_sys_cfg_s {
   
    /*---------- ������Ϣ���ɸ��� ----------*/
    uint8_t serial_no[MAX_SERIAL_NO_LEN];       //���к�
    uint8_t device_type[MAX_VER_STR_LEN];       //�豸�ͺ�
    uint8_t software_ver[MAX_VER_STR_LEN];      //����汾��
    uint8_t software_date[MAX_VER_STR_LEN];     //�����������
    uint8_t panel_ver[MAX_VER_STR_LEN];         //ǰ���汾
    uint8_t hardware_ver[MAX_VER_STR_LEN];      //Ӳ���汾

    uint32_t dev_type;                          //�豸���� (DEV_TYPE_DVR,DEV_TYPE_NVR)    J_DevType_E from j_sdk.h
    
    uint8_t ana_chan_num;                       //ģ��ͨ������
    uint8_t ip_chan_num;                        //����ͨ����
    uint8_t dec_chan_num;                       //����·��
    uint8_t stream_num;                            //����
    
    uint8_t audio_in_num;                       //��������ڵĸ���
    uint8_t audio_out_num;                      //��������ڵĸ���
    uint8_t alarm_in_num;                       //�����������
    uint8_t alarm_out_num;                      //�����������

    uint8_t net_port_num;                       //����ڸ���
    uint8_t rs232_num;                          //232���ڸ���
    uint8_t rs485_num;                          //485���ڸ���
    uint8_t usb_num;                            //USB�ڵĸ���
    
    uint8_t hdmi_num;                           //HDMI�ڵĸ���
    uint8_t vga_num;                            //VGA�ڵĸ���
    uint8_t cvbs_num;                           //cvbs�ڵĸ���
    uint8_t aux_out_num;                        //���ڵĸ���
    
    uint8_t disk_ctrl_num;                      //Ӳ�̿���������
    uint8_t disk_num;                           //Ӳ�̸���
    uint8_t res2[2];                            //����
    
    uint32_t max_encode_res;                    //������ֱ���
    uint32_t max_display_res;                   //�����ʾ�ֱ���
    
    uint32_t dvr_bit;                           //DVR����
    uint8_t  dvr_byte[4];                       //DVR����
}sdk_sys_cfg_t;

/*
 * ƽ̨��Ϣ
 *
 */

typedef struct sdk_platform_s {
    uint8_t pu_id[MAX_USER_NAME_LEN];           
    uint8_t cms_ip[MAX_IP_ADDR_LEN];            //ƽ̨mds ip
    uint8_t mds_ip[MAX_IP_ADDR_LEN];            //ƽ̨mds ip
    uint32_t cms_port;                          //ƽ̨cms�˿ں�
    uint32_t mds_port;                          //ƽ̨mds�˿ں�
    uint32_t protocol;                          //0:tcp   1:udp
    uint32_t plat_enable;                       //ƽ̨����
    
}sdk_platform_t;


/*
 * 
 * ϵͳ�汾��Ϣ
 */

typedef struct sdk_version_s {
    uint8_t serial_no[MAX_SERIAL_NO_LEN];       /* ��Ʒ���к� */
    uint8_t device_type[MAX_VER_STR_LEN];       /* ��Ʒ�ͺ� */
	uint8_t software_ver[MAX_VER_STR_LEN];	    /* �汾�� */
	uint8_t software_date[MAX_VER_STR_LEN];	    /* �汾���� */
    uint8_t panel_ver[MAX_VER_STR_LEN];         //ǰ���汾
    uint8_t hardware_ver[MAX_VER_STR_LEN];      //Ӳ���汾
}sdk_version_t;


/*
 * �ָ�Ĭ�ϲ���
 */
typedef struct sdk_default_param {
   
    uint32_t param_mask;    //������������
   /* bit.0: ������� */
   /* bit.1: ��̨���� */
   /* bit.2: ¼����� */
   /* bit.3: ������� */
   /* bit.4: ͨ������ */
   /* bit.5: ��Ƶ���� */
   /* bit.6: ���ڲ��� */
   /* bit.7: �ڵ�������� */
   /* bit.8: �ƶ���� */
   /* bit.9: ������� */
   /* bit.10: osd���� */
   /* bit.11: �û����� */
   /* bit.12: �����������*/
   /* bit.13: ��Ƶ�ڵ�������*/
   /* bit.14: ��Ƶ��ʧ����*/
   /* bit.15: �߾���ڲ���*/
   /* bit.16: Ѳ�ز���*/

   uint32_t res[1];
}sdk_default_param_t;


/*
 * ϵͳ����״̬��Ϣ
 */
typedef enum _SDK_STATUS_OP {
      SDK_STATUS_DEVICE = 0x01  //�豸����״̬
    , SDK_STATUS_DISK           //����״̬
    , SDK_STATUS_CHANN          //ͨ��״̬
    , SDK_STATUS_ALARM_IN       //���뱨��״̬
    , SDK_STATUS_ALARM_OUT      //�������״̬
}SDK_STATUS_OP_E;

typedef struct sdk_chan_status_s {
    
    uint8_t chan_type;          //ͨ������ 0�����أ�1��IP
    uint8_t record_state;       //¼��״̬,0-��¼��,1-¼��
    uint8_t signal_state;       //�ź�״̬, 0:������1���źŶ�ʧ
    uint8_t encode_state;       //����״̬, 0:�����룬1������
    
    uint32_t bit_rate;          //ʵ������
    uint32_t conn_num;          //ͨ��������
    uint8_t  conn_ip[MAX_CHANN_CONN_NUM][MAX_IP_ADDR_LEN];//����IP
}sdk_chan_status_t;

 
typedef struct sdk_disk_status_s {
    uint32_t volume;        //Ӳ�̵�����
    uint32_t free_space;    //Ӳ�̵�ʣ��ռ�
    uint32_t disk_state;   //Ӳ�̵�״̬,0-�,1-����,2-������
}sdk_disk_status_t;

/*
 * ϵͳ״̬(������ֳ� SDK_STATUS_OP_E)
 */
 
typedef struct sdk_status_s { 
    
	uint32_t            device_status;                      //�豸״̬��0-����,1-CPUռ����̫��,����85%,2-Ӳ������
	sdk_disk_status_t   disk_status[MAX_DISK_NUM];          //Ӳ��״̬
	sdk_chan_status_t   chan_status[MAX_CHANN_NUM];         //ͨ��״̬
	uint8_t             alarm_in_status[MAX_ALARM_IN_NUM];  //�����˿ڵ�״̬,0-û�б���,1-�б���
	uint8_t             alarm_out_status[MAX_ALARM_OUT_NUM];//��������˿ڵ�״̬,0-û�����,1-�б������
	
	uint8_t             local_display;                      //������ʾ״̬, 0:������1��������
	uint8_t             audio_chan_status;                  //����ͨ����״̬ 0-δʹ�ã�1-ʹ����, 0xff��Ч
	uint8_t             res[2];
	
}sdk_status_t;




/*
 * ��־��������
 */
typedef enum _SDK_LOG_OP {
      SDK_LOG_QUERY = 0x01  // ��ѯ sdk_log_item_t, sdk_log_cond_t
    , SDK_LOG_EMPTY         // ���(ȫ��)
    , SDK_LOG_BACKUP        // ����
    , SDK_LOG_DEL			// ɾ��(��ʱ���)
}SDK_LOG_OP_E;

/*
 * ��־���Ͷ��壨�����ͣ����֧��32�֣�
 */
typedef enum _LOG_MAJOR_TYPE {
      LOG_MAJOR_SYSTEM 		= 0x00000001  //ϵͳ��־
    , LOG_MAJOR_ALARM  		= 0x00000002  //�澯��־
    , LOG_MAJOR_OPERATE		= 0x00000004  //������־
    , LOG_MAJOR_NETWORK		= 0x00000008  //������־
    , LOG_MAJOR_PARAM  		= 0x00000010  //������־
    , LOG_MAJOR_EXCEPTION	= 0x00000020  //�쳣��־
    
    , LOG_MAJOR_ALL    		= 0xffffffff  //������־
}LOG_MAJOR_TYPE_E;

/*
 * ϵͳ��־������
 */
typedef enum _L_SYSTEM_MINOR_TYPE {
      L_SYSTEM_MINOR_STARTUP = 0x0001   //����
    , L_SYSTEM_MINOR_SHUTDOWN           //�ػ�
    , L_SYSTEM_MINOR_REBOOT				//����
    
    , L_SYSTEM_MINOR_ALL     = 0xffff   //����ϵͳ��־
}L_SYSTEM_MINOR_TYPE_E;

/*
 * �澯��־������
 */
typedef enum _L_ALARM_MINOR_TYPE {
      L_ALARM_MINOR_DI_START = 0x0001   //����澯����
    , L_ALARM_MINOR_DI_STOP             //����澯ֹͣ
    , L_ALARM_MINOR_MD_START            //�ƶ����澯����
    , L_ALARM_MINOR_MD_STOP             //�ƶ����澯ֹͣ
    , L_ALARM_MINOR_VL_START			//��Ƶ��ʧ�澯����
    , L_ALARM_MINOR_VL_STOP				//��Ƶ��ʧ�澯ֹͣ
    
    , L_ALARM_MINOR_ALL		= 0xffff	//���и澯��־
}L_ALARM_MINOR_TYPE_E;

/*
 * ������־������
 */
 typedef enum _L_OPERATE_MINOR_TYPE {
      L_OPERATE_MINOR_LOGIN = 0x0001	// ��½	
    , L_OPERATE_MINOR_LOGOUT 			// ע��
    , L_OPERATE_MINOR_USER_ADD			// �û�����-����
	, L_OPERATE_MINOR_USER_DEL			// �û�����-ɾ��
	, L_OPERATE_MINOR_USER_MODI			// �û�����-�޸�
    , L_OPERATE_MINOR_SETTIME 			// ����ϵͳʱ��
    , L_OPERATE_MINOR_FORMAT_DISK 		// ��ʽ��Ӳ��
    , L_OPERATE_MINOR_DEFAULT 			// �ָ�Ĭ��
    , L_OPERATE_MINOR_UPGRADE 			// ����
    , L_OPERATE_MINOR_PLAYBACK 			// �ط�
    , L_OPERATE_MINOR_PTZ 				// ��̨����
    , L_OPERATE_MINOR_BACKUP 			// ����
    , L_OPERATE_MINOR_RECORD_START 		// ����¼��
    , L_OPERATE_MINOR_RECORD_STOP 		// ֹͣ¼��
    , L_OPERATE_MINOR_CLR_ALARM 		// �������
    , L_OPERATE_MINOR_TALKBACK_START 	// �Խ���ʼ
    , L_OPERATE_MINOR_TALKBACK_STOP 	// �Խ�����
	, L_OPERATE_MINOR_LOG_DEL			// ɾ����־
	, L_OPERATE_MINOR_LOG_EMPTY			// �����־
	, L_OPERATE_MINOR_LOG_BACKUP		// ������־
    , L_OPERATE_MINOR_MANUAL_RECORD_START 		// �ֶ�����¼��
    , L_OPERATE_MINOR_MANUAL_RECORD_STOP 		// �ֶ�ֹͣ¼��	
    , L_OPERATE_MINOR_FORMAT_DISK_U 	// ��ʽ��U��

    , L_OPERATE_MINOR_ALL	= 0xffff	// ���в�����־
}L_OPERATE_TYPE_E;

/*
 * ������־������
 */
typedef enum _L_PARAM_MINOR_TYPE {
      L_PARAM_MINOR_PARAM_NETWORK = 0x0001 	// �����������
    , L_PARAM_MINOR_PARAM_UART 				// ���ڲ�������
    , L_PARAM_MINOR_PARAM_PTZ 				// ��̨��������
    , L_PARAM_MINOR_PARAM_CHAN 				// ͨ����������
    , L_PARAM_MINOR_PARAM_VENC 				// �����������
    , L_PARAM_MINOR_PARAM_TV 				// TV��������
	, L_PARAM_MINOR_PARAM_PIC_ATTR			// ͼ����������
	, L_PARAM_MINOR_PARAM_RECORD			// ¼���������
	, L_PARAM_MINOR_PARAM_MOTION			// �ƶ��������
	, L_PARAM_MINOR_PARAM_VIDEOLOST			// ��Ƶ��ʧ����
	, L_PARAM_MINOR_PARAM_ALARMIN			// ����澯����
	, L_PARAM_MINOR_PARAM_POLL				// ��Ѳ����
	, L_PARAM_MINOR_PARAM_PREVIEW			// Ԥ������
	, L_PARAM_MINOR_PARAM_OVERLAY			// �ڵ���������
	, L_PARAM_MINOR_PARAM_OSD				// OSD����
	, L_PARAM_MINOR_PARAM_COMM				// ��������

	, L_PRARM_MINOR_ALL	= 0xffff			// ���в�����־
}L_PARAM_MINOR_TYPE_E;

/*
 * �쳣��־������
 */
typedef enum _L_EXCEPTION_MINOR_TYPE {
      L_EXCEPTION_HD_FULL 		= 0x0001   	//Ӳ����
    , L_EXCEPTION_HD_ERROR           		//Ӳ�̴���
    , L_EXCEPTION_NET_DISCONNECT			//����Ͽ�
    , L_EXCEPTION_IP_CONFLICT				//IP��ͻ
    
    , L_EXCEPTION_MINOR_ALL     = 0xffff   	//�����쳣��־
}L_EXCEPTION_MINOR_TYPE_E;

/*
 * ��־��¼����
 */
typedef struct sdk_log_item_s {
    sdk_time_t  time;                       //ʱ��
    uint32_t    major_type;                 //����LOG_MAJOR_TYPE_E 
    uint32_t    minor_type;                 //0x0000:ֱ����ʾdesc���ݣ�����ͨ��L_XXX_MINOR_TYPE_E��������.
    uint32_t    args;                       /*�����Ͳ���(args=0ʱ���ý���,�������minor_type�������ݡ�
    										���minor_type��ͨ������أ�args��ʾͨ����;���minor_type�͸澯��أ�args��ʾ�澯�����)*/
    uint8_t     user[MAX_USER_NAME_LEN];    //�����û�
    uint8_t     ip_addr[MAX_IP_ADDR_LEN];   //�û�IP
    uint8_t     desc[MAX_LOG_DESC_LEN];     //��־����(minor_type=0ʱ��Ч)
}sdk_log_item_t;


/*
 * ��־��ѯ����
 */
typedef struct sdk_log_cond_s {
    sdk_time_t  begin_time;                 //��ʼʱ��
    sdk_time_t  end_time;                   //����ʱ��
    uint32_t    type;                       //����
    uint8_t     user[MAX_USER_NAME_LEN];    //�����û�
    uint8_t     ip_addr[MAX_IP_ADDR_LEN];   //�û�IP
}sdk_log_cond_t;



/*
 * ������Ϣ����
 */
typedef struct sdk_alarm_info_s {
    sdk_time_t  time;                   //����ʱ��
    uint32_t    type;                   //��������
    uint32_t    args;                   //��������
    uint8_t     desc[MAX_ALARM_DESC_LEN];//��������
}sdk_alarm_info_t;


/*
 * ���ڲ�������
 */
typedef struct sdk_serial_param_s {
    uint32_t baud_rate;             //���ڲ����� 115200, 57600, ...
    uint8_t  data_bit;              //����λ 5, 6, 7, 8 
    uint8_t  stop_bit;              //ֹͣλ 1, 2
    uint8_t  parity;                //У�� 0:�ޣ�1:��У�� 2:żУ�� 
    uint8_t  flow_ctl;              //����
}sdk_serial_param_t;

/*
 * ������;����
 */
typedef struct sdk_serial_func_cfg_s {
	uint8_t type;	// 0: normal, 1: ptz, 2...
	uint8_t res[3];
	sdk_serial_param_t serial_param;
}sdk_serial_func_cfg_t;


/*
 * ��̨���ò���
 */
 /*
 *  _0: debug, _1: ptz/normal, _2: rs232, _3 mcu
 *  -------------------------, _2: mcu;
 *  0: 1
 *   
 */
typedef struct sdk_ptz_param_s {

    sdk_serial_param_t comm;                //���ڲ�����gui�̶�ֻ���ô���1
    uint8_t          address;               //��̨��ַ
    uint8_t          protocol;              //��̨Э��SDK_PTZ_PROTOCOL_E
    uint8_t          res[2];
    uint8_t          preset_set[MAX_PRESET_NUM];//����Ԥ��λ��־
    uint8_t          cruise_set[MAX_CRUISE_NUM];//����Ѳ����־
}sdk_ptz_param_t;


/*
 *DVRʵ��Ѳ�����ݽṹ
 */
typedef struct sdk_cruise_param_s {
    uint8_t enable;                           //�Ƿ�����
    uint8_t res[3];                           //����
    uint8_t preset[MAX_CRUISE_PRESET_NUM];    //Ԥ�õ�
    uint8_t speed[MAX_CRUISE_PRESET_NUM];     //�ƶ��ٶ�
    uint8_t dwell_time[MAX_CRUISE_PRESET_NUM];//ͣ��ʱ��
}sdk_cruise_param_t;

//��̨����ѡ��Ŵ���С(˽�� ����ר��)


/*
 * 
 * Ԥ������(��������޸�)
 */
 

typedef enum _SDK_SCREE_SPLIT {
      SDK_SCREE_ONE  = 0x00
    , SDK_SCREE_FOUR
    , SDK_SCREE_NINE
    , SDK_SCREE_SIXTEEN
    , SDK_SCREE_THIRTY_TWO
    , SDK_SCREE_BUTT
}SDK_SCREE_SPLIT_E;


typedef struct sdk_preview_s {
    
    uint8_t preview_mode;   //Ԥ��ģʽ,0-1����,1-4����,2-6����,3-8����,4-9����,0xFF-�����
    uint8_t enable_audio;   //�Ƿ�����Ԥ��,0-��Ԥ��,1-Ԥ��
    uint16_t switch_time;   //�л�ʱ��(��)
    uint8_t windows[MAX_PREVIEW_MODE][MAX_WINDOWS_NUM];//�л�˳��,step[i]Ϊ 0xff��ʾ����

}sdk_preview_t;

/*
 * VO�󶨶���
 */
typedef struct sdk_vo_binding_s {
    
    uint8_t mode;        //����ģʽ,0-1����,1-4����,2-6����,3-8����,4-9����,5-16����,0xff:�����
    uint8_t win_num;     //���ڸ���
    uint8_t res[2];      //����
    uint8_t windows[MAX_WINDOWS_NUM];//��������;

}sdk_vo_binding_t;


/*
 * ���ڽ�������Ļ����
 */
typedef struct sdk_win_s {
    uint8_t valid;          //valid: 0��ʾ����ƵԴ
    uint8_t res[3];         //����
    uint8_t url[256];       //��ƵԴURL
}sdk_win_t;

typedef struct sdk_screen_s {
    uint8_t valid;                 //valid: 0��ʾ��ʾ������ֹ
    uint8_t mode;                  //����ģʽ,0:1����,1:4����,2:6����,3:8����,4:9����,5:16����,0xff:�����
    uint8_t res[2];                //����
    sdk_win_t win[MAX_WINDOWS_NUM];//sdk_win_t
}sdk_screen_t;

/*
 *��Ƶ����
 */
typedef struct sdk_audio_cfg_s {
   
    uint8_t encode_type;        //�������� 1: G711A
    uint8_t samples;            //����Ƶ�� 0: 8000, 
    uint8_t bits;               //λ��     1: 16bit, 
    uint8_t channels;           //ͨ����
    
    uint8_t  bufsize;            //�����С,��֡Ϊ��λ
    uint8_t  resample;           //0 �޲��� 2 2->1 4 4->1 6 6->1
    uint16_t sample_per_frm;     //ÿһ֡���������
}sdk_audio_cfg_t;


/*
 * GUI��ѯ�豸�б�ʱʹ��
 */

typedef enum _MANUFACT_TYPE{
     MANUFACT_JXJ     = 0x00
    ,MANUFACT_SAE     = 0x01
    ,MANUFACT_ONVIF   = 0x02
}MANUFACT_TYPE_E;

typedef struct sdk_device_s {
    uint8_t   ip_addr[MAX_IP_ADDR_LEN];     //Զ���豸IP��ַ
    uint16_t  port;                         //Զ���豸port
    uint8_t   dns_en;                       //�Ƿ�ʹ����������Զ���豸 1:ʹ�ã�0:��ʹ��
    uint8_t   device_type;                  //Զ���豸����  0:IPC 1: DVR 2:NVR 3:DVS
    uint8_t   chann_num;                    //Զ���豸��ͨ����
    uint8_t   chann_stream_num;             //Զ���豸ͨ���������� 1: ������ 2: ˫���� 3:������
    uint8_t   manufacturer;                 //�豸�������� MANUFACT_TYPE_E
    uint8_t   dev_res[1];                   //����
    uint8_t   dns_path[64];                 //Զ���豸������ַ
    uint8_t   dst_id[32];                   //Զ���豸Ψһ��ʾ�� �ַ���
    sdk_user_t user;                        //Զ���豸�û���+���� 
}sdk_device_t;

/*
 *
 * ͨ�����ã�֧��IP���룩
 */

typedef struct sdk_channel_s {
    uint8_t   enable;                        //�Ƿ�����
    uint8_t   is_local;                      //�Ƿ�Ϊ������ƵԴ		1:����; 0:Զ��
    //local vi info
    uint8_t   video_in;                      //������ƵԴ���
    uint8_t   video_format;                  //������ƵԴ�źŸ�ʽ    0��PAL�� 1��NTSC    
    //channel name
    uint8_t   name[MAX_CHANN_NAME_LEN];      //ͨ������
    //net channel info
    sdk_user_t user;                        //Զ���豸�û���+���� 
    uint8_t  chann_no;                      //����Զ���豸ͨ����
    uint8_t  chann_protocol;                //����ͨ������Э��
    uint8_t  chann_audio_en:1;              //����ͨ���Ƿ�֧����Ƶ 1: ֧��   0: ��֧��
    uint8_t  chann_win_mode:2;              //Ԥ������ģʽ 0: �Զ�, 1: ������, 2: ������
    uint8_t  chann_bit_res:5;               //����
    uint8_t  chann_byte_res;                //����
    
    //net device info
    sdk_device_t device;                    //Զ���豸��Ϣ
}sdk_channel_t;


/*
 * ͨ���������(�ӽṹ��)
 */
typedef struct sdk_av_enc_s {
    uint8_t resolution;     //SDK_VIDEO_RESOLUTION_E
    uint8_t bitrate_type;	//�������� 0--������;	1--������
    uint8_t pic_quilty;     //��������0-��ã�1-�κã�2-�Ϻã�3-һ�㣬4-�ϲ5-��	
    uint8_t frame_rate;	    //����֡��1-25(PAL)/30
    uint8_t gop;			//I ֡���1-200
    uint8_t video_enc;      //��Ƶ�����ʽ0--h264 1--MJPEG 2--JPEG	
    uint8_t audio_enc;      //���ӱ����ʽ0:G711A
    uint8_t mix_type;       //����Ƶ��: 0, ��Ƶ��: 1.
    uint16_t bitrate;	    //�������� 32kbps-16000kbps
    uint8_t level;          //����ȼ���h264: 0--baseline, 1--main, 2--high;
    uint8_t h264_ref_mod; 
}sdk_av_enc_t;


/*
 * ͨ���������
 */

typedef struct sdk_encode_s {
    sdk_av_enc_t main;          //������
    sdk_av_enc_t second;        //������
    sdk_av_enc_t res;           //����
}sdk_encode_t;


/*
 *
 *��Ƶ������������
 */
 
typedef struct sdk_overlay_cfg_s {
    uint8_t   enable;                  //�Ƿ���
    uint8_t   max_num;
    uint8_t   res[2];
    uint32_t   mask;                    //bit.0: area[0], bit.1: area[1]
    sdk_rect_t area[MAX_OVERLAY_NUM];   //��������
}sdk_overlay_cfg_t;
typedef struct _sdk_codec_area_zoom_ch_info_s
{
    int is_enable;
    sdk_rect_t area;
}sdk_codec_ch_area_zoom_info_t;


/*
 *
 *TV����
 */
typedef struct sdk_vo_sideSize_s
{
    int top_offset;
    int bottom_offset;
    int left_offset;
    int right_offset;
}sdk_vo_sideSize_t;

/*
 *
 *��ƵOSD����(�ӽṹ��)
 */

typedef struct sdk_osd_info_s {

    sdk_point_t pos;            //λ��
    uint8_t     valid;          // ��ǰ�����Ƿ���Ч
    uint8_t     font;           // ��������
    // [7 6 5 4 - 3 2 1 0]
    // bit[4-7]: display type, 0: time, 1: string, 2 .....
    // bit[0-3]: display format 
    //           sample time format:
    //           bit[2-3], 0: YYYYMMDD, 1: MMDDYYYY, 2: DDMMYYYY
    //           bit[1],   0: '-'       1: '/'
    //           bit[0],   0: 24hour    1: ampm
    uint8_t     format;         // ��ʾ��ʽ
    uint8_t     str_len;        // �ַ�������
    uint8_t     str[MAX_OSD_STR_LEN];//ascii+gb2312�ַ���
}sdk_osd_info_t;



/*
 *
 *��ƵOSD����
 */
typedef struct sdk_osd_cfg_s {
    sdk_osd_info_t  time;        //OSDʱ��
    sdk_osd_info_t  chann_name;  //OSDͨ������
//    sdk_osd_info_t  vloss;      //����
#if 0
    sdk_osd_info_t  res[1];      //����
#else
    uint16_t max_width;
    uint16_t max_height;
    
    uint8_t  st_info_en;
    uint8_t  res1[3];
    
    uint8_t  res2[64];
#endif
}sdk_osd_cfg_t;



/*
 *
 *ͼ����������
 */
typedef struct sdk_image_attr_s {
    uint8_t brightness;         //����
    uint8_t contrast;           //�Աȶ�
    uint8_t saturation;         //���Ͷ�
    uint8_t hue;                //ɫ��
    uint8_t sharpness;          //���
    uint8_t res[3];
}sdk_image_attr_t;


/*
 * ץ�Ľṹ�嶨��
 */
typedef struct sdk_snap_pic_s {
    uint16_t width;             //���
    uint16_t height;            //�߶�
    uint8_t  encode;            //�����ʽ,JPEG
    uint8_t  quilty;            //ͼ������
    uint8_t  res[2];            //����
}sdk_snap_pic_t;

typedef enum _SDK_DISK_STATUS {
	  SDK_DISK_STATUS_DISK_UNMOUNT = 0x00	// δ����
	, SDK_DISK_STATUS_DISK_NOMAL			// ����
	, SDK_DISK_STATUS_DISK_USING			// ����ʹ��
	, SDK_DISK_STATUS_DISK_BUTT
}SDK_DISK_STATUS_E;

/*
 * ������Ϣ�ṹ��
 */
typedef struct sdk_disk_s {
    uint32_t disk_no;       //���̺�
    uint32_t disk_type;     //�������ͣ�0:SATA��1:USB��2:ISCSI; 3:NFS��
    uint32_t status;        //����״̬ SDK_DISK_STATUS_E
    uint32_t total_size;    //��������(MB)
    uint32_t free_size;     //��������(MB)
    uint32_t is_backup;     //�Ƿ񱸷ݴ��� 0:¼����; 1:������
    uint32_t is_raid;       //�Ƿ�raid //�����ĸ�����
}sdk_disk_t;

//����������Ϣ����

//����Ӳ�̽ṹ����


/*
 * ¼��������ӽṹ�壩
 */
typedef struct sdk_record_sched_s {
    uint8_t is_allday;                              //�Ƿ�ȫ��¼��
    uint8_t record_type;                            //¼������
    uint8_t res[2];                                 //����
    sdk_sched_time_t sched_time[MAX_TIME_SEG_NUM];  //����ʱ���
    
}sdk_record_sched_t;

/*
 * ¼�����
 */
typedef struct sdk_record_cfg_s {
    uint8_t enable;                                //������ʱ¼��
    uint8_t res[3];                                 //����
    sdk_record_sched_t record_sched[MAX_WEEK_NUM];  //����ʱ���(0:������; 1:����һ,2:���ڶ�,... ,6:������)
    
    uint32_t pre_record_time;                       //Ԥ¼ʱ��
    uint32_t record_duration_time;                  //¼����ʱ��
    
    uint8_t  enable_redundancy;                     //�Ƿ����౸��
    uint8_t  enable_audio;                          //�Ƿ�¼����Ƶ
    uint8_t  res2[2];                                //����
    
}sdk_record_cfg_t;


/*
 * ¼���¼����
 */
typedef struct sdk_record_item_s {
    uint8_t item_name[MAX_RECORD_ITEM_LEN]; //��¼����
    uint32_t item_handle[8];                //sizeof(stor_fragment_t)
    sdk_time_t start_time;                  //��ʼʱ��
    sdk_time_t stop_time;                   //����ʱ��
    uint32_t item_size;                     //���ݴ�С
    
    uint8_t is_locked;                      //�Ƿ�����
    uint8_t record_type;                    //¼������
    uint8_t res[2];                         //����
    // card no;
}sdk_record_item_t;

/*
 * ¼���ѯ����
 */
typedef struct sdk_record_cond_s {
    uint8_t is_locked;              //����״̬
    uint8_t record_type;            //¼������
    uint8_t res[2];                 //����
    sdk_time_t start_time;          //��ʼʱ��
    sdk_time_t stop_time;           //����ʱ��
    // card no;    
}sdk_record_cond_t;


/*
 *
 * �طſ���������
 */
typedef enum _SDK_PB_GROUP_CONTROL {
      SDK_PB_CONTROL_ONNE  = 0x00 	//
    , SDK_PB_CONTROL_PAUSE  		// ��ͣ
    , SDK_PB_CONTROL_SETP          	// ��֡��
    , SDK_PB_CONTROL_NORMAL        	// ����
    , SDK_PB_CONTROL_DRAG          	// ��ק
    , SDK_PB_CONTROL_FORWARD       	// ǰ��
    , SDK_PB_CONTROL_BACKWARD      	// ����
    , SDK_PB_CONTROL_QUERY_TIME		// ��ѯ��ǰ������֡��ʱ�䣬��λ��
    
    , SDK_PB_CONTROL_BUTT
}SDK_PB_GROUP_CONTROL_E;

/*
 *
 * ǰ�������ٶ�ö��
 */
typedef enum _SDK_PB_GROUP_CONTROL_FORWARD {
      SDK_PB_CONTROL_FW_NORMAL = 0x00  				// ����
    , SDK_PB_CONTROL_FF_1X     						// 1����� (FF-fast forward-��ǰ���)
    , SDK_PB_CONTROL_FF_2X    						// 2�����
    , SDK_PB_CONTROL_FF_4X         					// 4�����
    , SDK_PB_CONTROL_FF_8X							// 8�����
    , SDK_PB_CONTROL_FF_16X							// 16�����

    , SDK_PB_CONTROL_SF_1_2X						// 1������ (SF-slow forward-��ǰ����)
    , SDK_PB_CONTROL_SF_1_4X						// 2������
    , SDK_PB_CONTROL_SF_1_8X						// 4������
    , SDK_PB_CONTROL_SF_1_16X						// 8������

}SDK_PB_GROUP_CONTROL_FORWARD_E;


/*
 * �ط�ͨ���鶨��
 */
typedef struct sdk_pb_group_s {
    sdk_time_t start_time;             //��ʼʱ��
    sdk_time_t stop_time;              //����ʱ��
    uint32_t main_chann;               //��ͨ����
    uint8_t chann_mask[MAX_CHANN_NUM];//ͨ�����루��·�ط�ʱ��
}sdk_pb_group_t;



/* ---------------------------------------*/
// ntp
// ddns
// wifi
// email
// ftp
/* ---------------------------------------*/





/*
 *
 *�豸��Ϣ���豸����ʱ�ã��磺�������ߣ�
 */

typedef struct sdk_device_info_s {
    /*------ �豸������Ϣ ------*/
    sdk_net_cfg_t   net_cfg;        //��������
    sdk_sys_cfg_t   sys_cfg;        //ϵͳ����
    /*---- ϵͳ����ʱ��Ϣ  ----*/
    //��Ҫ��������
}sdk_device_info_t;

/*----------------- �������ýṹ�嶨�� -----------------*/

typedef enum _SDK_PTZ_OP_TYPE {
	  SDK_PTZ_TYPE_NONE = 0x00
	, SDK_PTZ_TYPE_PRESET		// Ԥ��λ
	, SDK_PTZ_TYPE_CRUISE		// Ѳ��
	, SDK_PTZ_TYPE_BUTT
}SDK_PTZ_OP_TYPE_E;

/*
 *  ������������
 */
typedef struct sdk_alarm_handle_s {

    uint8_t record_mask[MAX_CHANN_NUM];   //¼��ͨ������
    uint8_t snap_mask[MAX_CHANN_NUM];     //ץ��ͨ������
    uint8_t alarm_out_mask[MAX_CHANN_NUM];//�����������      
    uint8_t ptz_type[MAX_CHANN_NUM];      //������̨��������(Ԥ��λ/Ѳ��)	SDK_PTZ_OP_TYPE_E
    uint8_t ptz_param[MAX_CHANN_NUM];     //������̨����(Ԥ��λ�ţ�Ѳ����)
    uint8_t res_mask[MAX_CHANN_NUM];

    uint8_t  record_enable;
    uint8_t  record_time;                 //¼����ʱʱ��
    uint8_t  snap_enable;
    uint8_t  snap_interval;               //ץ��ʱ����(��Ч)
    
    uint8_t  snap_num;                    //����ץ������
    uint8_t  beep_enable;                 //�Ƿ������
    uint8_t  beep_time;                   //����ʱ��
    uint8_t  ptz_enable;
    
    uint8_t  alarm_out_enable;
    uint8_t  alarm_out_time;              //�������ʱ��
    uint8_t  res[2+4];                    //email, ftp, 3g;
}sdk_alarm_handle_t;

/*
 * �������루IO����������
 */
typedef struct sdk_alarm_in_cfg_s {
    uint8_t name[MAX_ALARM_IN_NAME_LEN];                        //������������
    uint8_t type;                                               //�����������ͣ�1������(Ĭ��)��0������
    uint8_t enable;                                             //��������
    uint8_t res[2];                                             //����
    sdk_sched_time_t sched_time[MAX_WEEK_NUM][MAX_TIME_SEG_NUM];//����ʱ���
    sdk_alarm_handle_t alarm_handle;                            //��������
}sdk_alarm_in_cfg_t;

/*
 * ��Ƶ�ƶ��������
 */
typedef enum _SDK_VDA_MOD_E {
      SDK_VDA_MD_MOD = 0
    , SDK_VDA_OD_MOD = 1
}SDK_VDA_MOD_E;
typedef struct sdk_vda_codec_cfg_s
{
    uint8_t enable;                                             //��������
    uint8_t sensitive;                                          //������(0[���������]----6[���])
    uint8_t mode;                                             	/* 0:MD �ƶ� 1:OD �ڵ� */
    uint8_t res;
    uint32_t mask;												//��λ
    sdk_rect_t area[MAX_MOTION_NUM];                            //����
}sdk_vda_codec_cfg_t;

typedef struct sdk_motion_cfg_v2_s {
    sdk_vda_codec_cfg_t codec_vda_cfg;						    			
    sdk_sched_time_t sched_time[MAX_WEEK_NUM][MAX_TIME_SEG_NUM];//����ʱ���
    sdk_alarm_handle_t alarm_handle;                            //��������
}sdk_motion_cfg_v2_t;

typedef struct sdk_motion_cfg_s {
    //uint8_t scope[18][22];                                    //��Ҫȷ��
    uint8_t enable;                                             //��������
    uint8_t sensitive;                                          //������(0[���������]----6[���])
    uint8_t res[2];                                             //����
    uint32_t mask;							// ��λ
    sdk_rect_t area[MAX_MOTION_NUM];                            //����
	sdk_sched_time_t sched_time[MAX_WEEK_NUM][MAX_TIME_SEG_NUM];//����ʱ���
    sdk_alarm_handle_t alarm_handle;                            //��������
}sdk_motion_cfg_t;


/*
 * ��Ƶ�ڵ��������
 */
typedef struct sdk_hide_cfg_s {
    uint8_t enable;                                             //��������
	uint8_t sensitive;                                          //������(0[���������]----6[���])
	uint8_t res[2];                                             //����
    uint32_t mask;												 // ��λ
    sdk_rect_t area[MAX_MOTION_NUM];                            //����
    sdk_sched_time_t sched_time[MAX_WEEK_NUM][MAX_TIME_SEG_NUM];//����ʱ���
    sdk_alarm_handle_t alarm_handle;                            //��������
}sdk_hide_cfg_t;

/*
 * ��Ƶ��ʧ�������
 */
typedef struct sdk_lost_cfg_s {
    uint8_t enable;                                             //��������
    uint8_t res[3];                                             //����
    sdk_sched_time_t sched_time[MAX_WEEK_NUM][MAX_TIME_SEG_NUM];//����ʱ���
    sdk_alarm_handle_t alarm_handle;                            //��������
}sdk_lost_cfg_t;


/*
 * ¼�����
 */
typedef struct sdk_manual_record_s {
    uint8_t manual_record[MAX_CHANN_NUM];	// �ֶ�¼��
    uint8_t stop_record[MAX_CHANN_NUM];		// ��ֹ¼��
    uint8_t res[MAX_CHANN_NUM];				// ����λ
}sdk_manual_record_t;

/*
 * �ֶ�����(ֹͣ)����������
 */
typedef struct sdk_manual_alarmin_s {
    uint8_t enable_alarmin[MAX_ALARM_IN_NUM];	// 0:ֹͣ; 1:����(Ĭ��ȫ����)
    uint8_t res[MAX_ALARM_IN_NUM];				// ����λ
}sdk_manual_alarmin_t;

/*
 * �ֶ�����(ֹͣ)�������
 */
typedef struct sdk_manual_alarmout_s {
    uint8_t enable_alarmout[MAX_ALARM_OUT_NUM];	// 0:ֹͣ(Ĭ��ȫֹͣ); 1:����
    uint8_t res[MAX_ALARM_OUT_NUM];				// ����λ
}sdk_manual_alarmout_t;


/*
 * ¼�񱸷�
 */
typedef enum _SDK_BACKUP_OP {
      SDK_BACKUP_START		= 0x001		//sdk_record_backup_t
    , SDK_BACKUP_PROGRESS				//pmsg->chan:���ݽ���
    , SDK_BACKUP_BUTT
}SDK_BACKUP_OP_E;

typedef struct sdk_record_handle_s {
	uint32_t  	item_handle[8];			//sizeof(stor_fragment_t)
	uint32_t 	item_size;				//�δ�С
	sdk_time_t 	start_time;          	//��ʼʱ��
    sdk_time_t 	end_time;           	//����ʱ��
    uint8_t  	res[4];					//����
}sdk_record_handle_t;

typedef struct sdk_record_backup_s {
	sdk_record_handle_t item_arr[MAX_BACKUP_ITEM];
	uint8_t item_num;				//ʵ�ʱ��ݶ���
	uint8_t record_type;            //¼������
	uint8_t res[2];					//����
}sdk_record_backup_t;


/*
 * �ر�ϵͳ
 */
typedef enum _SDK_CLOSE_SYS_OP {
      SDK_CLOSE_SYS_SHUTDOWN	= 0x001		//�ػ�
    , SDK_CLOSE_SYS_REBOOT					//����
    , SDK_COLSE_SYS_LOGOUT
    , SDK_CLOSE_SYS_BUTT
}SDK_CLOSE_SYS_OP_E;

/*
 * ��Ƶ����
 */
typedef enum _SDK_AUDIO_CONTROL_OP {
      SDK_AUDIO_CONTROL_OPEN	= 0x001		//����
    , SDK_AUDIO_CONTROL_MUTE				//����
    , SDK_AUDIO_CONTROL_TALK				//�Խ�
    , SDK_AUDIO_CONTROL_SPECIAL_CMD			//��������(GUI֪ͨ���ؽ���طŽ��棬pmsg->extend:1����; 0:�˳�)
    
    , SDK_AUDIO_CONTROL_BUTT
}SDK_AUDIO_CONTROL_OP_E;


/*
 * ��������
 */

#define 	MAX_DDNS_USER_LEN   	64				// DDNS�û�����󳤶�
#define 	MAX_DDNS_PWD_LEN    	32				// DDNS������󳤶�
#define 	MAX_DDNS_NAME_LEN   	128				// DDNS������󳤶�

typedef enum _SDK_DDNS_TYPE {
	  SDK_DDNS_TYPE_DYNDNS	= 0x00		// Dyndns
	, SDK_DDNS_TYPE_3322				// 3322
	, SDK_DDNS_TYPE_ORAY				// Oray
	
	, SDK_DDNS_TYPE_BUTT
}SDK_DDNS_TYPE_E;

typedef enum _SDK_DDNS_ORAY_USERTYPE {
	  SDK_ORAY_USERTYPE_COMMON	= 0x01	// ��ͨ�û�
	, SDK_ORAY_USERTYPE_EXPERT			// רҵ�û�

	, SDK_ORAY_USERTYPE_BUTT
}SDK_DDNS_ORAY_USERTYPE;

typedef struct sdk_ddns_cfg_s {
	uint8_t enable;						// �Ƿ�����DDNS 0-��1-��
	uint8_t type;						// DDNS���ͣ�SDK_DDNS_TYPE_E
	uint8_t user_type;					// �û����ͣ�SDK_DDNS_ORAY_USERTYPE (���������д�ѡ��)
	uint8_t domain_num;					// ���������������ĸ���
	uint8_t reserve[4];					// ����
	
	uint32_t interval;					// ��������(��λ:��)
	uint32_t port;						// DDNS�˿�
	uint8_t server[MAX_DDNS_NAME_LEN];	// DDNSЭ���Ӧ�ķ�������ַ(IP����������)
	uint8_t user[MAX_DDNS_USER_LEN];	// �û���
	uint8_t pwd[MAX_DDNS_PWD_LEN];		// ����
	uint8_t domain[MAX_DDNS_NAME_LEN];	// �û������������ַ(Ŀǰ��dyndns�ô˲���,���domainʹ��','����)
	uint8_t client_ip[MAX_IP_ADDR_LEN];	// �豸��IP
	uint8_t dn[16][MAX_DDNS_NAME_LEN]; 	// ���������ص�����
}sdk_ddns_cfg_t;






/* ---------------------------------*/

#ifdef __cplusplus
}
#endif

#endif //__sdk_struct_h__

