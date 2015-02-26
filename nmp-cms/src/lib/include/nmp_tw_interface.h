/*
 *	author:	zyt
 *	time:	begin in 2012/9/17
 */
#ifndef __NMP_TW_INTERFACE_H__
#define __NMP_TW_INTERFACE_H__


#define	TW_MAX_STEPS_DEF		(32)		//����չ
#define	TW_MAX_STEPS_TOP		(256)	//������߽���
#define	TW_MAX_DIVISIONS		(64)		//������չ

#define	TW_ID_LEN				(32)
#define	TW_SESSION_ID_LEN		(16)
#define	TW_MAX_VALUE_LEN		(64)
#define	TW_MAX_URL_LEN		(1024)

#define	TW_RES_OK						(0)
#define	TW_RES_ERROR					(-1)
#define	TW_RES_EINVAL					(-2)
#define	TW_RES_SENT_TO_DEC_FAILED	(-5)

#define	TW_ILLEGAL_SEQ_NUM			(0xffffffff)
#define	TW_ACTION_TIME_LEN			(15)


typedef enum
{
	GPT_NONE	= 0,
	GPT_STEP,
	GPT_TOUR,
	GPT_GROUP,
	GPT_ACTION_STEP
} TW_GPT_TYPE;

typedef enum
{
	TW_INFO_GET_TOUR		= 0,
	TW_INFO_GET_GROUP,
	TW_INFO_GET_GROUP_STEP_N,
	TW_INFO_GET_DIS_GUID,
	TW_INFO_GET_EC_URL,
	TW_INFO_QUERY_IF_UPDATE_URL,

	TW_INFO_SEND_SCREEN_TO_DEC,
	TW_INFO_SEND_SCREEN_TO_CU,

	TW_INFO_SEND_CMD_RES_TO_CU,

	TW_CLEAR_TO_DEC,
	TW_CLEAR_RESULT_TO_CU,

	TW_CHANGE_DIVISION_MODE_TO_DEC,
	TW_CHANGE_DIVISION_MODE_RESULT_TO_CU,

	TW_FULL_SCREEN_TO_DEC,
	TW_FULL_SCREEN_RESULT_TO_CU,

	TW_EXIT_FULL_SCREEN_TO_DEC,
	TW_EXIT_FULL_SCREEN_RESULT_TO_CU,
} TW_INFO_TYPE;

typedef enum
{
	TW_RUN_STEP	= 0,
	TW_RUN_TOUR,
	TW_RUN_GROUP,
	TW_STOP_TOUR,
	TW_STOP_GROUP,
	TW_IF_RUN_TOUR,
	TW_IF_RUN_GROUP,
	TW_STOP_GPT_BY_DIVISION
} TW_CMD_TYPE;

typedef enum
{
	TW_OPERATE_FULL_SCREEN	= 0,
	TW_OPERATE_EXIT_FULL_SCREEN,
	TW_OPERATE_CHANGE_DIVISION_MODE,
	TW_OPERATE_CLEAR
} TW_OPERATE_TYPE;


typedef struct
{
	char		guid[TW_ID_LEN];
	char		domain_id[TW_ID_LEN];
} tw_general_guid;


/*============================================================
 *				����ǽ����ͨ��Э�� ��Ӧ ���ݽṹ
 *============================================================*/

//����ִ�����ݽṹ			<jpf_tw_run_step>

typedef struct
{
	char		session_id[TW_SESSION_ID_LEN];			//cu�Ựid
	int		tw_id;						//����ǽid
	int		screen_id;					//��ʾ��id
	int		division_id;					//����ģʽ
	int		division_num;				//�ָ��
	char		ec_name[TW_MAX_VALUE_LEN];	//����������
	char		ec_domain_id[TW_ID_LEN];		//���������ڵ���id
	char		ec_guid[TW_ID_LEN];				//������guid
} tw_run_step_request;

typedef struct
{
	tw_run_step_request		req;
	unsigned int		seq;
} tw_run_step_request_with_seq;


//Ѳ��ִ�����ݽṹ			<jpf_tw_run_tour>

typedef struct
{
	char		session_id[TW_SESSION_ID_LEN];			//cu�Ựid
	int		tw_id;						//����ǽid
	int		screen_id;					//��ʾ��id
	int		division_id;					//����ģʽ
	int		division_num;				//�ָ��
	int		tour_id;						//Ѳ��id
} tw_run_tour_request;


//Ⱥ��ִ�����ݽṹ			<jpf_tw_run_group>

typedef struct
{
	char		session_id[TW_SESSION_ID_LEN];			//cu�Ựid
	int		group_id;					//Ⱥ��id
} tw_run_group_request;


//Ѳ��ֹͣ����			<jpf_tw_stop_tour>

typedef struct
{
	char		session_id[TW_SESSION_ID_LEN];			//cu�Ựid
	int		tour_id;						//Ѳ��id
} tw_stop_tour_request;


//Ⱥ��ֹͣ����			<jpf_tw_stop_group>

typedef tw_run_group_request tw_stop_group_request;

//��ѯѲ���Ƿ�����			<jpf_tw_if_run_tour>

typedef tw_stop_tour_request tw_if_run_tour_request;

//��ѯȺ���Ƿ�����			<jpf_tw_if_run_group>

typedef tw_run_group_request tw_if_run_group_request;


//ֹͣ�ָ��������ݽṹ		<jpf_tw_stop_gpt_by_division>

typedef struct
{
	char		session_id[TW_SESSION_ID_LEN];			//cu�Ựid
	int		tw_id;						//����ǽid
	int		screen_id;					//��ʾ��id
	int		division_num;				//�ָ��
} tw_division_position;



/*============================================================
 *			����ǽ��ȡ����Ѳ��Ⱥ����ϸ��Ϣ ���ݽṹ
 *============================================================*/

//-> �����ݿ��ȡѲ����Ϣ		->TW_INFO_GET_TOUR

typedef struct
{
	int		tour_id;						//Ѳ��id
} tw_tour_msg_request;


//<- ���ݿⷵ��Ѳ����Ϣ		<-TW_INFO_GET_TOUR

typedef struct
{
	int		step_num;					//�����
	int		step_ttl;						//����
	char 	ec_name[TW_MAX_VALUE_LEN];	//����������
	char 	ec_domain_id[TW_ID_LEN];		//���������ڵ���id
	char 	ec_guid[TW_ID_LEN];				//������guid
	int		level;							//�����ȼ�
} tw_tour_step_response;

typedef struct
{
	int		result;
	int		tour_num;					//Ѳ�ر�ţ����ڼ���
	int		auto_jump;					//Ѳ����Чʱ�Ƿ��Զ���ת
	char		tour_name[TW_MAX_VALUE_LEN];	//Ѳ������
	int		step_count;					//Ѳ���ܲ���
	tw_tour_step_response	*steps;			//ÿһ����Ϣ
} tw_tour_msg_response;


//-> �����ݿ��ȡȺ���Ҫ��Ϣ	->TW_INFO_GET_GROUP

typedef struct
{
	int		group_id;					//Ⱥ��id
} tw_group_msg_request;


//<- ���ݿⷵ��Ⱥ���Ҫ��Ϣ		<-TW_INFO_GET_GROUP

typedef struct
{
	int		result;
	int		tw_id;						//����ǽid
	int		group_num;					//Ⱥ���ţ����ڼ���
	char		group_name[TW_MAX_VALUE_LEN];	//Ⱥ������
	int		step_count;					//Ⱥ���ܲ���
	unsigned int	step_num[TW_MAX_STEPS_TOP];	//����
} tw_group_msg_response;


//-> �����ݿ��ȡȺ���n����Ϣ	->TW_INFO_GET_GROUP_STEP_N

typedef struct
{
	int		group_id;					//Ⱥ��id
	int		step_num;					//����ţ���1��ʼ
} tw_group_step_n_request;


//<- ���ݿⷵ��Ⱥ���n����Ϣ	<-TW_INFO_GET_GROUP_STEP_N

typedef struct
{
	int		division_num;				//�ָ�ţ���0��ʼ
	char		ec_name[TW_MAX_VALUE_LEN];	//����������
	char		ec_domain_id[TW_ID_LEN];		//���������ڵ���id
	char		ec_guid[TW_ID_LEN];				//������guid
	int		level;
} tw_group_division_response;

typedef struct
{
	int		screen_id;					//��ʾ��id
	char		dis_guid[TW_ID_LEN];			//��ʾ��guid
	char		dis_domain_id[TW_ID_LEN];	//��ʾ����id
	int		division_id;					//����ģʽ
	int		div_sum;					//�ָ�����
	tw_group_division_response	divisions[TW_MAX_DIVISIONS];		//�ָ���Ϣ
} tw_group_screen_response;

typedef struct
{
	int		result;
	int		step_ttl;						//����
	int		screen_sum;					//ʹ�õ�������
	tw_group_screen_response	*screens;	//ÿһ����Ϣ
} tw_group_step_n_response;



//-> ����tw_id,screen_id ��ȡ ��ʾ��guid		->TW_INFO_GET_DIS_GUID

typedef struct
{
	int		tw_id;						//����ǽid
	int		screen_id;					//��ʾ��id
} tw_dis_guid_request;


//<- ����tw_id,screen_id ���� ��ʾ��guid		<-TW_INFO_GET_DIS_GUID

typedef struct
{
	int		result;
	tw_general_guid	dis_guid;				//��ʾ��guid
} tw_dis_guid_response;


//-> ���ݱ�������id,guid ��ȡ ������urlf		->TW_INFO_GET_EC_URL

typedef struct
{
	char		dis_guid[TW_ID_LEN];				//������guid
	char		dis_domain_id[TW_ID_LEN];		//���������ڵ���id
	char		ec_guid[TW_ID_LEN];				//������guid
	char		ec_domain_id[TW_ID_LEN];		//���������ڵ���id
} tw_ec_url_request;


//<- ���ݱ�������id,guid ���� ������url		<-TW_INFO_GET_EC_URL

typedef struct
{
	int		result;
	char		ec_url[TW_MAX_URL_LEN];			//������url
	char		ec_dec_plug[TW_ID_LEN];
} tw_ec_url_response;



/*============================================================
 *			����ǽ��Ļ�л�ͨ��Э�� ��Ӧ ���ݽṹ
 *============================================================*/

//����ǽһ��Ļ�л���Ϣ				->TW_INFO_SEND_SCREEN_TO_DEC

typedef struct
{
	int		division_num;				//�ָ��
	char		ec_name[TW_MAX_VALUE_LEN];	//����������
	char		ec_dec_plug[TW_ID_LEN];
	char		*ec_url;						//��������Ӧ��ת����Ԫ��ַ(ָ��)
} tw_division_to_decoder;

typedef struct
{
	TW_GPT_TYPE	gp_type;				//group_t�ṹ���ͣ�1:STEP,2:TOUR,3:GROUP
	char		gp_name[TW_MAX_VALUE_LEN];	//group_t�ṹ������
	int		step_num;					//�����
	char		dis_guid[TW_ID_LEN];				//��ʾ��guid
	int		division_id;					//����ģʽ
	int		keep_other;					//�Ƿ񱣳������ָ������״̬
	int		div_sum;					//�ָ�����
	tw_division_to_decoder		divisions[TW_MAX_DIVISIONS];
} tw_screen_to_decoder;

typedef struct
{
	tw_screen_to_decoder	screen_to_dec;
	unsigned int	seq;						//���к�
} tw_screen_to_decoder_with_seq;



/*============================================================
 *				��Ļ�л�������� ��Ӧ ���ݽṹ
 *============================================================*/

//	<jpf_tw_deal_decoder_res>

typedef struct
{
	int		result;
	int		division_num;				//�ָ��
	char		ec_name[TW_MAX_VALUE_LEN];	//����������
	int		ec_channel;
	int		level;
} tw_decoder_division_rsp;

typedef struct
{
	int		result;
	int		division_id;
	int		div_sum;
	tw_decoder_division_rsp		divisions[TW_MAX_DIVISIONS];
} tw_decoder_rsp;

typedef struct
{
	tw_decoder_rsp	dec_rsp;
	unsigned int	seq;						//���к�
} tw_decoder_rsp_with_seq;



/*============================================================
 *			����״̬����ͨ��Э�� ��Ӧ ���ݽṹ
 *============================================================*/

//����һ��Ļ�л������cu			->TW_INFO_SEND_SCREEN_TO_CU

typedef tw_decoder_division_rsp tw_division_to_cu;

typedef struct
{
	char		session_id[TW_SESSION_ID_LEN];			//cu�Ựid
	TW_GPT_TYPE	gp_type;				//group_t�ṹ���ͣ�1:STEP,2:TOUR,3:GROUP
	char		gp_name[TW_MAX_VALUE_LEN];	//group_t�ṹ������
	int		tw_id;						//����ǽid
	int		screen_id;					//��ʾ��id
	int		division_id;					//����ģʽ
	int		keep_other;					//�Ƿ񱣳������ָ������״̬
	int		div_sum;					//�ָ�����
	tw_division_to_cu		divisions[TW_MAX_DIVISIONS];
} tw_screen_to_cu;


//���͵���ǽ���������cu		->TW_INFO_SEND_CMD_RES_TO_CU

typedef struct
{
	char				session_id[TW_SESSION_ID_LEN];			//cu�Ựid
	unsigned int		cu_seq;
	TW_CMD_TYPE	tw_cmd_type;				//����ǽ��������
	int				result;						//0:��ȷ����0:����
} tw_run_res;



/*============================================================
 *					������ ��Ӧ ���ݽṹ
 *============================================================*/

typedef struct
{
	char		session_id[TW_SESSION_ID_LEN];			//cu�Ựid
	int		tw_id;						//����ǽid
	int		screen_id;					//��ʾ��id
	int		division_id;					//����ģʽ
	int		division_num;				//�ָ��
	int		operate_mode;				//���ģʽʱ��0:����ָ� 1:ֹͣ����
} tw_operate;

typedef struct
{
	tw_operate	operate;
	unsigned int	seq;
} tw_operate_with_seq;


typedef struct
{
	char		session_id[TW_SESSION_ID_LEN];			//cu�Ựid
	TW_OPERATE_TYPE	operate_type;				//��������
	int		tw_id;						//����ǽid
	int		screen_id;					//��ʾ��id
	int		division_id;					//����ģʽ
	int		division_num;				//�ָ��
	int		operate_mode;				//���ģʽʱ��0:����ָ� 1:ֹͣ����
	int		result;
} tw_operate_result_to_cu;

typedef struct
{
	tw_operate_result_to_cu	to_cu;
	unsigned int	seq;
} tw_operate_result_to_cu_with_seq;


typedef struct
{
	char		dis_guid[TW_ID_LEN];			//��ʾ��guid
	int		division_id;					//����ģʽ
	int		division_num;				//�ָ��
} tw_operate_to_decoder;

typedef struct
{
	tw_operate_to_decoder		operate_to_dec;
	unsigned int	seq;						//���к�
} tw_operate_to_decoder_with_seq;


typedef struct
{
	int		result;
} tw_operate_decoder_rsp;

typedef struct
{
	tw_operate_decoder_rsp operate_dec_rsp;
	unsigned int	seq;						//���к�
} tw_operate_decoder_rsp_with_seq;



/*============================================================
 *				�鿴����url ��Ӧ ���ݽṹ
 *============================================================*/

typedef struct
{
	int		gp_id;
	int		screen_id;
	int		step_num;		//��1��ʼ
	int		division_num;	//��0��ʼ
} tw_encoder_position;

typedef struct
{
	tw_encoder_position	ec_position;
	char		dis_guid[TW_ID_LEN];				//������guid
	char		dis_domain_id[TW_ID_LEN];		//���������ڵ���id
	char		ec_guid[TW_ID_LEN];				//������������guid
	char		ec_domain_id[TW_ID_LEN];		//���������ڵ���id
	char		ec_url[TW_MAX_URL_LEN];			//��������Ӧ��ת����Ԫ��ַ
} tw_update_url;




void jpf_tw_init_log_path(const char *folder_path, const char *name);

void jpf_tw_init_tvwall_module();

int jpf_tw_tvwall_work();

int jpf_tw_tvwall_clear();		//����ʱʹ��


int jpf_tw_run_step(tw_run_step_request_with_seq *msg_with_seq);

int jpf_tw_run_tour(tw_run_tour_request *msg);

int jpf_tw_run_group(tw_run_group_request *msg);

int jpf_tw_run_action_step(tw_run_step_request *msg);

int jpf_tw_stop_tour(tw_stop_tour_request *msg);

int jpf_tw_stop_group(tw_stop_group_request *msg);

int jpf_tw_if_run_tour(tw_if_run_tour_request *msg);

int jpf_tw_if_run_group(tw_if_run_group_request *msg);

int jpf_tw_stop_gpt_by_division(tw_division_position *msg);

int jpf_tw_screen_operate(tw_operate_with_seq *msg_with_seq, TW_INFO_TYPE type);


typedef int (*event_handler_t)(TW_INFO_TYPE cmd, void *in_parm, void *out_parm);

void jpf_tw_set_event_handler(event_handler_t hook);


int jpf_tw_deal_decoder_res(tw_decoder_rsp_with_seq *dec_rsp_with_seq);

int jpf_tw_deal_decoder_operate_res(tw_operate_decoder_rsp_with_seq *dec_rsp_with_seq,
	TW_INFO_TYPE type);


int jpf_tw_destroy_screen_to_dec(tw_screen_to_decoder_with_seq *to_dec_with_seq,
	int size);


int jpf_tw_update_url(tw_update_url *update_url);


#endif

