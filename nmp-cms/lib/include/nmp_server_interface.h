


//#include "jpf_msg_sdk.h"

//#include "jpf_client_connect.h"
//#ifndef	__SHARE__
//#define __SHARE__
//#include "nmp_msg_share.h"
//#endif



#ifndef __INTER__
#define __INTER__


#include "nmp_msg_share.h"

typedef struct _server_callback_function
{
	void *proc_register_paramer;
	int (*proc_register)(void *, void *, void *);
}server_callback_function;


/******************************************���ݽṹ��****************************************/

//�ͻ������ݽṹ��
typedef struct _jpf_QueryUser_info
{

	int client_count;	//��ѯ�ͻ��˸���
	int start_line; 	//��ʼ�������
	gchar key;			//ģ����ѯ�����ݣ�����ǰ����Ͳ�ѯ����0
	gchar type;			//��ѯ���ͣ�0����ѯ�����û���1����������2�����ȼ�

}jpf_QueryUser_info;

typedef struct _jpf_QueryUser_info_res
{
	JpfMsgErrCode		code;

	char   username[USER_NAME_LEN]; 	//�˺�
	char   password[USER_PASSWD_LEN];	 //����
	int    group_id;		//������
	int    sex; 	//�Ա�
	char   user_phone[PHONE_NUM_LEN];  //��ϵ��ʽ
	char   user_description[DESCRIPTION_INFO_LEN];	//��ע��Ϣ

}jpf_QueryUser_info_res;

typedef struct _jpf_user_QueryUser_info
{
	char domain[USER_NAME_LEN];
	jpf_QueryUser_info *QueryUser_info;

}jpf_user_QueryUser_info;

typedef struct _jpf_user_QueryUser_info_res_inter
{
	int flag;
	int count;
	jpf_QueryUser_info_res *data_buf;
}jpf_user_QueryUser_info_res_inter;

//�û�����Ϣ
typedef struct _jpf_user_group_info
{
	int count;			//��ѯ�û������
	int start_line; 	//��ʼ�������
	int key;			//ģ����ѯ�����ݣ�����ǰ����Ͳ�ѯ����0
	int type;			//��ѯ���ͣ�0����ѯ�����û���1����������2�����ȼ�

}jpf_user_group_info;


typedef struct _jpf_user_group_info_res
{
	JpfMsgErrCode		code;


	char name[64];	//����
	char id[50]; //��id��
	int level; //�ȼ�
	int permissions; //�û���Ȩ��

}jpf_user_group_info_res;

typedef struct _jpf_user_group_info_res_inter
{
	int flag;
	int count;
	jpf_user_group_info_res *data_buf;
}jpf_user_group_info_res_inter;

typedef struct _jpf_user_group_info_inter
{
	char domain[USER_NAME_LEN];
	jpf_user_group_info *QueryUserGroup_info;

}jpf_user_group_info_inter;

//����Ա��Ϣ
typedef struct _jpf_manager_info_res
{
	JpfMsgErrCode		code;

		char name[64];
		int type;	//����Ա���ͣ�1����������Ա��2����ͨ����Ա
}jpf_manager_info_res;

typedef struct _jpf_manager_info_res_inter
{
	int flag;
	int count;
	jpf_manager_info_res *date_buff;
}jpf_manager_info_res_inter;

typedef struct _jpf_manager_info
{
	int count;			//��ѯ�û������
	int start_line; 	//��ʼ�������
	int key;			//ģ����ѯ�����ݣ�����ǰ����Ͳ�ѯ����0
	int type;			//��ѯ���ͣ�0����ѯ�����û���1����������2�����ȼ�

}jpf_manager_info;


typedef struct _jpf_manager_info_inter
{
	char domain[USER_NAME_LEN];
	jpf_manager_info *QueryManager_info;

}jpf_manager_info_inter;


//�豸��Ϣ
typedef struct _jpf_device_info
{
	int count;			//��ѯ�û������
	int start_line; 	//��ʼ�������
	int key;			//ģ����ѯ�����ݣ�����ǰ����Ͳ�ѯ����0
	int type;			//��ѯ���ͣ�0����ѯ�����û���1����������2�����ȼ�

}jpf_device_info;


typedef struct _jpf_device_info_inter
{
	char domain[USER_NAME_LEN];
	jpf_device_info *QueryDevice_info;

}jpf_device_info_inter;


typedef struct _jpf_device_info_res
{
	JpfMsgErrCode		code;

	char puid[16];			//�豸id
	char puName[64];		//�豸��
	char dev_type[20];		//�豸����
	char domain_id[8];		//��id
	char area_id[8];		//����id
	char mdu_id[50];		//ת��������id
	int heatbeat;			//����
	char equipment_manufacturers[50];	//������

}jpf_device_info_res;

typedef struct _jpf_device_info_res_inter
{
	int flag;
	int count;
	jpf_device_info_res *date_buff;
}jpf_device_info_res_inter;

//ҵ�����Ϣ
typedef struct _jpf_profession_point_info
{
	char domainid[16]; //��Id
	char guid[24]; //ҵ���id
	char puid[24]; //�豸id
	int count;	 //��ѯ����
	int start_line; 	//��ʼ�������
	int type;			//��ѯ���ͣ�0����ѯ����Gu��1��������id��puid��ѯ��2��������id��guid��ѯ
}jpf_profession_point_info;

typedef struct _jpf_profession_point_inter
{
	char domain[USER_NAME_LEN];
	jpf_profession_point_info *QueryProfession_info;

}jpf_profession_point_inter;

typedef struct _jpf_profession_point_res
{
	JpfMsgErrCode		code;


	char guid[24];	//ҵ��id
	char id[16]; //ҵ����������
	char puid[16]; //�豸id
	char guName[64]; //ҵ�����
	char type[10];
	int ptz; //1��ʾ����̨��0��ʾû��
	int guAlarmBypass;	//1��ʾ����·������0��ʾû��

}jpf_profession_point_res;

typedef struct _jpf_profession_point_res_inter
{
	int flag;
	int count;
	jpf_profession_point_res *date_buff;
}jpf_profession_point_res_inter;

//������Ϣ
typedef struct _JpfQueryRegion JpfQueryRegion;
struct _JpfQueryRegion
{
    gint               req_num;
    gint               start_num;
    gint               area_id;
};



typedef struct _jpf_region_info
{

	gint				area_id;
	gchar				area_name[AREA_NAME_LEN];
	gint				area_parent;

}jpf_region_info;

typedef struct _jpf_query_region_info_inter
{
	char domain[USER_NAME_LEN];
	JpfQueryRegion *QueryRegion;

}jpf_query_region_info_inter;

typedef struct _JpfQueryRegionRes JpfQueryRegionRes;
struct _JpfQueryRegionRes
{
    JpfMsgErrCode      code;
    gint               total_num;
    gint               req_num;
    jpf_region_info    *region_info;
};



/*
typedef struct _jpf_region_info_res
{
	JpfMsgErrCode		code;
	char Name[64]; //������
	char parent[32];	//�ü������һ����������
	char current_parent[32];		//��ǰ������ĸ�������
	int region_level;	//����ȼ�������һ�����򣬶�������
	int sub_level_region_flag;   //-1:��ʾ��������û���Ӽ�����1����ʾ���Ӽ�����

}jpf_region_info_res;

typedef struct _jpf_region_info_res_inter
{
	int flag;
	int count;
	jpf_region_info_res *date_buff;
}jpf_region_info_res_inter;
*/


//ת����������Ϣ
typedef struct _jpf_relay_server_info
{

	int count;	//��ѯ����
	int start_line; 	//��ʼ�������
	int type;			//��ѯ���ͣ�0����ѯ�����豸��1:���������ѯ�豸
	int key;			//key=1ʱ��ʾ�����ѯ
}jpf_relay_server_info;


typedef struct _jpf_relay_server_inter
{
	char domain[USER_NAME_LEN];
	jpf_relay_server_info *QueryRelayServer_info;

}jpf_relay_server_inter;



typedef struct _jpf_relay_server_info_res
{
	JpfMsgErrCode		code;

	char id[10];
	char relay_server_name[32];
	char type[32];
	int heatbeat;
	int device_port;
	int media_port;
}jpf_relay_server_info_res;

typedef struct _jpf_relay_server_info_res_inter
{
	int flag;
	int count;
	jpf_relay_server_info_res *date_buff;
}jpf_relay_server_info_res_inter;


//������Ϣ
typedef struct _jpf_query_factory_info
{
	int count;	//��ѯ����
	int start_line; 	//��ʼ�������
	int type;			//��ѯ���ͣ�0����ѯ�����豸��1:���������ѯ�豸
	int key;			//key=1ʱ��ʾ�����ѯ
}jpf_query_factory_info;

typedef struct _jpf_query_factory_info_inter
{
	char domain[USER_NAME_LEN];
	jpf_query_factory_info *QueryFactory_info;

}jpf_query_factory_info_inter;

typedef struct _jpf_query_factory_info_res
{
	JpfMsgErrCode		code;

	char factory_name[32];
	char flag[10];

}jpf_query_factory_info_res;

typedef struct _jpf_query_factory_info_res_inter
{
	int flag;
	int count;
	jpf_query_factory_info_res *date_buff;
}jpf_query_factory_info_res_inter;

//�洢��������Ϣ
typedef struct _jpf_query_storage_server_info
{
	int count;			//��ѯ����
	int start_line; 	//��ʼ�������
	int type;			//��ѯ���ͣ�0����ѯ�����豸��1:���������ѯ�豸
	int key;			//key=1ʱ��ʾ�����ѯ
}jpf_query_storage_server_info;

typedef struct _jpf_query_storage_server_info_inter
{
	char domain[USER_NAME_LEN];
	jpf_query_storage_server_info *QueryStorageServer_info;

}jpf_query_storage_server_info_inter;

typedef struct _jpf_query_storage_server_info_res
{
	JpfMsgErrCode		code;

	char id[32];
	char name[32];
	int heatbeat;

}jpf_query_storage_server_info_res;

typedef struct _jpf_query_storage_server_info_res_inter
{
	int flag;
	int count;
	jpf_query_storage_server_info_res *date_buff;
}jpf_query_storage_server_info_res_inter;


/**************************************�ӿ�*****************************************/


//server�˳�ʼ��
void jpf_server_mods_init( void );

//void jpf_server_lib_init( void );


//ƽ̨��ʼ��
int sdk_init(int heartbeat, int port);


//��ѯ������Ϣ
int get_region_info(jpf_query_region_info_inter *in_para, JpfQueryRegionRes *out);

//��ѯ�洢��������Ϣ
int get_storage_server_info(jpf_query_storage_server_info_inter *in_para, jpf_query_storage_server_info_res *out);

//��ѯ������Ϣ
int get_factory_info(jpf_query_factory_info_inter *in_para, jpf_query_factory_info_res *out);

//��ѯת���������б���Ϣ
int get_relay_server_info(jpf_relay_server_inter *in_para, jpf_relay_server_info_res *out);

//��ѯҵ����б���Ϣ
int get_profession_point_info(jpf_profession_point_inter *in_para, jpf_profession_point_res *out);

//��ѯ�豸�б���Ϣ
int get_device_info(jpf_device_info_inter *in_para, jpf_device_info_res *out);

//��ѯ����Ա�б���Ϣ
int get_manager_info(jpf_manager_info_inter *in_para, jpf_user_group_info_res *out);

//��ѯ�û�����Ϣ
int get_user_group_info(jpf_user_group_info_inter *in_para, jpf_user_group_info_res *out);

//��ѯ�ͻ�����Ϣ
int get_client_user_info(jpf_user_QueryUser_info *in_para, jpf_QueryUser_info_res *out);

int jpf_server_register_callback(server_callback_function *fun, void *ower);



#endif






