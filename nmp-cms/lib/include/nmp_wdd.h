#ifndef __NMP_WDD_H__
#define __NMP_WDD_H__

#include <stdint.h>

#define DEV_PASSWD 				"918273645918273645918273"
#define USER_PASSWD			"91827345"
#define WDD_VERSION_1			0x01
#define WDD_LABEL_LEN			16
#define WDD_HARDWARE_ID_LEN	8
#define WDD_LABEL				"JPF-WDD-1"
#define WDD_MAKER_LABEL		"JPF-WDD-MAKER"
#define WDD_DECODER_LABEL		"JPF-WDD-DECODER"
#define WDD_TIME_LEN			32
#define MAKER_NAME_LEN			32
#define MAKER_PASSWD_LEN		16

#define LIMIT_MAX               ((uint32_t)-1)

#define SET_WDD_VERSION(_w, vernum) \
    ((wdd*)(_w))->version.ver_num = htonl(vernum)
#define GET_WDD_VERSION(_w) \
    ntohl(((wdd*)(_w))->version.ver_num)

#ifndef offsetof
#define offsetof(type, f) ((size_t) \
		((char *)&((type *)0)->f - (char *)(type *)0))
#endif


typedef struct __wdd_ver wdd_ver;
struct __wdd_ver
{
    uint32_t ver_num;       /* ���ݽṹ�汾��WDD_VERSION_1 */
};

typedef struct __wdd_label wdd_label;
struct __wdd_label
{
    uint8_t label[WDD_LABEL_LEN];   /* ��� */
};

typedef struct __wdd_cd wdd_cd;
struct __wdd_cd
{
    uint32_t major;					/* ��������*/
    uint32_t code;						/* ���ܹ����*/
    uint32_t maker_code;				/* ���ܹ���Ӧ�������߱��*/
    uint8_t hardware_id[WDD_HARDWARE_ID_LEN];	/* Ӳ����ʶ*/
};

enum {
    WDD_STYLE_DATE,
    WDD_STYLE_DAY,
    WDD_STYLE_MINUTE,
    WDD_STYLE_FOREVER
};

typedef struct __wdd_time wdd_time;
struct __wdd_time
{
    uint32_t style;         /* ��ʱ��ʽ */

    /* ���������ʱ����ڷ�ʽ: WDD_STYLE_DATE */
    uint16_t expire_year;   /* ���� �� */
    uint8_t expire_mon;     /* ���� �� */
    uint8_t expire_date;    /* ���� �� */

    /* ������������ڷ�ʽ:WDD_STYLE_DAY  */
    uint16_t start_year;    /* ����ʱ�� �� */
    uint8_t start_mon;      /* ����ʱ�� �� */
    uint8_t start_date;     /* ����ʱ�� �� */

    /* ʹ�÷��ӹ��ڷ�ʽ: WDD_STYLE_MINUTE */
    uint32_t expire_ttd;    /* ���� ��ʣ�µķ�����/�򼤻��ʣ�µ����� */

};

enum {
    WDD_SYSTYPE_PF          /* �ۺϹ���ƽ̨ */
};

enum {
    MODULES_CMS = 0,        /* ���Ĺ���ģ�� */
    MODULES_MDS,            /* ת��ģ�� */
    MODULES_MSS,            /* �洢ģ�� */
    MODULES_ALM,            /* ��������ģ�� */
    MODULES_EM,             /* ���ӵ�ͼģ�� */
    MODULES_TW,             /* ����ǽģ�� */
    MODULES_MAX = 32        /* ���ģ���� */
};

/* ���Ĺ�����ģ�� */
enum{
	CMS_HIK = 0,            /* �������� */
	CMS_DAH,                /* �㽭�� */
	CMS_HBGK,               /* ����߿� */
	CMS_HNW,               /* ����Τ�� */
	CMS_XMT,               /* �������� */
	CMS_TPS,               /* ��������ͨ */
};

/* �澯��ģ�� */
enum {
	LINKED_REC = 0,         /* ����¼�� */
	LINKED_MSG,             /* �������� */
	LINKED_MMS,             /* �������� */
	LINKED_CAP,	              /* ����ץ�� */
	LINKED_PRESET,          /* ����Ԥ�� */
	LINKED_TW,                /* ��������ǽ */
	LINKED_IO,                 /* ����IO�澯 */
	LINKED_EMAIL,           /* ����EMAIL */
	LINKED_EMAP             /* �������ӵ�ͼ */
};

enum {
	TW_TOUR = 0,            /* Ѳ�� */
	TW_GROUP,				/* Ⱥ�� */
	TW_KEYBOARD			/* ģ����� */
};

enum {
	VER_STANDARD = 0,		/* ��׼�� */
	VER_ENHANCED,			/* ��ǿ�� */
	VER_ULTIMATE,			/* �콢�� */
	VER_NDMS,				/* NDMS�� */
	VER_TEST				/* ���ð� */
};

typedef struct __wdd_version1 wdd_version1;
struct __wdd_version1
{
    wdd_time authorize;
    uint8_t maker[MAKER_NAME_LEN];	/* ������ */
    uint8_t make_time[WDD_TIME_LEN];	/* ����ʱ�� */
    uint32_t sys_type;      /* ϵͳ���ͣ�WDD_SYSTYPE_PF-�ۺϹ���ƽ̨ */
    uint32_t sys_ver;		/* ϵͳ�汾 */
    uint32_t sys_modules;   /* ϵͳģ�鼯�� */
    uint32_t modules_data[MODULES_MAX]; /* ��ģ��˽������ */
    uint32_t sys_dec;       /* �������Ľ������ͣ������/Ӳ���� */
    uint32_t max_dev;       /* ������������豸���� */
    uint32_t max_av;        /* ����Ƶ��������, LIMIT_MAX���������� */
    uint32_t max_ds;        /* ��ʾͨ�������� */
    uint32_t max_ai;        /* �澯����̽ͷ������ */
    uint32_t max_ao;        /* �澯���̽ͷ������ */
};

typedef struct __wdd_maker0 wdd_maker0;
struct __wdd_maker0
{
    uint8_t	name[MAKER_NAME_LEN];	/* �����ˣ����Լ� */
    uint8_t	make_time[WDD_TIME_LEN];	/* ����ʱ�� */
    uint8_t	passwd[MAKER_PASSWD_LEN];	/* ���� */
    uint32_t	authorize;					/* ������Ȩ�� */
    uint32_t	usb_keys;				/* ������USB-KEY���ܸ��� */
    uint32_t 	max_dev;       /* �豸���� */
    uint32_t 	max_av;        /* ����Ƶ����� */
    uint32_t 	max_ds;        /* ��ʾͨ������ */
    uint32_t 	max_ai;        /* �澯������� */
    uint32_t 	max_ao;        /* �澯������� */
};

typedef struct __wdd_decoder0 wdd_decoder0;
struct __wdd_decoder0
{
    wdd_time authorize;
    uint8_t maker[MAKER_NAME_LEN];	/* ������ */
    uint8_t make_time[WDD_TIME_LEN];	/* ����ʱ�� */
    uint32_t max_ds;        /* ��ʾͨ�������� */
};


typedef struct __wdd_maker wdd_maker;
struct __wdd_maker
{
    wdd_label   label;
    wdd_cd      serial_code;
    wdd_ver     version;
    wdd_maker0	data;
};

typedef struct __wdd_decoder wdd_decoder;
struct __wdd_decoder
{
    wdd_label   label;
    wdd_cd      serial_code;
    wdd_ver     version;
    wdd_decoder0  data;
};

#define WDD_HEAD_LEN	(offsetof(wdd, data))

typedef struct __wdd wdd;
struct __wdd
{
    wdd_label   label;
    wdd_cd      serial_code;
    wdd_ver     version;
    wdd_version1 data;
};


#endif /* __NMP_WDD_H__ */
