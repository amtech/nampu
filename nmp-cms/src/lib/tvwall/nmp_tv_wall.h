/*
 *	author:	zyt
 *	time:	begin in 2012/9/10
 */
#ifndef __NMP_TV_WALL_H__
#define __NMP_TV_WALL_H__

#include <time.h>
#include <pthread.h>

#include "nmp_tw_interface.h"


#define	MAX_SCREENS		(65)		//������չ�����ֻ����64��������1���ڼ�¼����
#define	MAX_GROUPS		(32)		//����չ
#define	INCREASE			(8)

#define	DIS_SCREEN_REG_MODE	(0x01)
#define	DIS_SCREEN_STOP		(0x02)
#define	DIS_SCREEN_COMPLITE	(0x04)

#define	GPF_WAITING			(0x01)
#define	GPF_STOP				(0x02)
#define	GPF_FIRST_TIME_RUN	(0x04)	//[�澯�������]

#define	LOOKUP_DEL			(0x01)	//���Ҳ�ɾ��
#define	LOOKUP_UNQ		(0x02)	//����

#define	MAX_OPERATE_NUM	(1000)


typedef enum
{
	TW_STOP_TYPE_GPT,						//ֹͣ�ָ����ڵ�GPT
	TW_STOP_TYPE_DIVISION,				//ֹͣ�ָ�
	TW_STOP_TYPE_SCREEN_BY_DIVISION_ID	//���÷���ģʽʱ���������ģʽ��һ����������
} TW_STOP_TYPE;



#define g_log_num (0xff)
/*
#define error_msg(fmt, args ...) do {	\
	if (g_log_num & 0x01)	\
		printf("<jtw,error_msg>   _________________________________________________________________ [error] %s[%d]:" \
		fmt, __FUNCTION__, __LINE__, ##args);	\
} while (0)
*/
#define nmp_tw_log_msg(fmt, args ...) do {	\
	if (g_log_num & 0x02)	\
		printf("<jtw,nmp_tw_log_msg> %s[%d]:"fmt, __FUNCTION__, __LINE__, ##args);	\
} while (0)

#define log_2(fmt, args ...) do {	\
	if (g_log_num & 0x04)	\
		printf("<jtw,log_2> %s[%d]:"fmt, __FUNCTION__, __LINE__, ##args);	\
} while (0)

#define log_3(fmt, args ...) do {	\
	if (g_log_num & 0x08)	\
		printf("<jtw,log_3> %s[%d]:"fmt, __FUNCTION__, __LINE__, ##args);	\
} while (0)

#define func_begin(fmt, args ...) do {	\
	if (g_log_num & 0x10)	\
		printf("<jtw,b> %s[%d]__ _"fmt, __FUNCTION__, __LINE__, ##args);		\
} while (0)


typedef struct
{
	unsigned int		seq;
	int				keep_other;
} action_special_t;


typedef struct
{
	int		is_action;
	time_t	action_time;
	int		division_id;
	int		division_num;
} action_step_t;


/**************************************************************
 *				����ǽ�߼��������ݽṹ
 **************************************************************/

typedef struct
{
	int		tw_id;						//����ǽid
	int		screen_id;					//��ʾ��id
	int		division_num;				//�ָ��
	int		division_id;					//����ģʽ�����÷���ģʽ��ʱ���ж�
} division_pos_t;

typedef struct
{
	char		ec_name[TW_MAX_VALUE_LEN];	//����������
	char		ec_domain_id[TW_ID_LEN];		//���������ڵ���id
	char		ec_guid[TW_ID_LEN];				//������guid
	char		ec_url[TW_MAX_URL_LEN];			//��������Ӧ��ת����Ԫ��ַ
	char		ec_dec_plug[TW_ID_LEN];
} encoder_t;

typedef encoder_t *division_t;

typedef struct
{
	int			division_id;				//����ģʽ
	division_t		divisions[TW_MAX_DIVISIONS];	//�ָ�ֲ����������
} division_mode_t;

typedef struct
{
	int				step_num;			//�����
	int				step_ttl;				//����
	division_mode_t	division_mode;		//��Ļ���
} step_t;

struct __group_t;

typedef struct
{
	unsigned int		seq;					//���к�
	char				dis_guid[TW_ID_LEN];		//��ʾ��guid
	char				dis_domain_id[TW_ID_LEN];	//��ʾ����id
	int				dis_flags;				//@{PAUSE,STOP,...}
	int				dis_steps;				//����һ�����ܲ������ϸ�Ӧ������󲽺�

	int				screen_id;				//��ʾ����
	division_mode_t	dis_division_mode;		//@{valid when REG_MODE}

	step_t			*dis_pstep;
	int				steps_capacity;

	action_special_t	action_special;			//[�澯�������]
	action_step_t		action;					//[�澯�������]

	struct __group_t	*dis_group;				//@{this channel belongs to}

	step_t			steps_init[TW_MAX_STEPS_DEF];
} dec_screen_t;		//һ���а����ಽ

typedef struct __group_t
{
	int				gp_id;					//@{Ѳ�أ�Ⱥ�飬�򵥲�ID,������ʵ��ʱ�ḳһ������ID}
	TW_GPT_TYPE	gp_type;				//@{���ͣ�GPT_TOUR-Ѳ�� GPT_GROUP-Ⱥ�� GPT_STEP-����}
	int				gp_flags;				//���Ʊ��(Group Flags)ȡֵ��GPF_WAITING/GPF_STOP/GPF_FIRST_TIME_RUN

	int				gp_tw_id;				//@{��Ӧ�ĵ���ǽID}

	int				gp_num;				//@{Ⱥ��/Ѳ�ر�ţ������ڽ��̣�}

	dec_screen_t		*gp_dis_screens;		//��������
	int				gp_screens;				//����ͨ����������ʾGUID���֣�������ʾ����

	int				gp_auto_jump;			//Ѳ�ز���Чʱ�Զ���ת
	int				gp_max_steps;			//�����
	int				gp_now_step;			//��������ִ�еĲ�

	time_t			gp_switch_time;			//��һ�β��л�ʱ��
	time_t			gp_alive;				//ʹ��ʱ�䣬����ɾ����ʱ�Ľ��

	int				gp_screens_capacity;	//gp_dis_screensָ��Ŀռ��С
	char				gp_name[TW_MAX_VALUE_LEN];
	char				gp_session_id[TW_SESSION_ID_LEN];	//cu�ỰID
	unsigned int		gp_cu_seq;					//��¼cu seq

	dec_screen_t		dis_screen_init[MAX_SCREENS];	//����ʾͨ����������MAXCHANS�������gp_dis_screensָ������
} group_t;

typedef struct
{
	group_t			**gv_parr;

	int				gv_size;					//gv��group_t���󣨴���Ѳ�أ�Ⱥ�飬�򵥲�������Ŀ
	int				gv_capacity;				//gv_parr��ָ��Ŀռ��С

	pthread_mutex_t	gv_mutex;
	group_t			*groups_init[MAX_GROUPS];
} group_vec_t;

typedef struct
{
	group_vec_t		tw_group_vec_ok;		//����������Ϣ��group_t���󣨴���Ѳ�أ�Ⱥ�飬�򵥲���
	group_vec_t		tw_group_vec_wait;		//��Ϣ��������������DBS������Ϣ
} tv_wall_t;



typedef struct
{
	unsigned int		seq;					//����dec�ڲ�ά����seq
	char				session_id[TW_SESSION_ID_LEN];		//cu�Ựid
	unsigned int		cu_seq;					//cu������Ӧseq
	int				tw_id;					//����ǽid
	int				screen_id;				//��ʾ��id
	int				division_id;				//����ģʽ
	int				division_num;			//�ָ��
} tw_operate_unit;

typedef struct
{
	pthread_mutex_t	operate_mutex;
	tw_operate_unit	unit[MAX_OPERATE_NUM];
} tw_operate_info;


#endif

