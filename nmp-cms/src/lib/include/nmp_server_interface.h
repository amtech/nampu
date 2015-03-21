


//#include "nmp_msg_sdk.h"

//#include "nmp_client_connect.h"
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
typedef struct _nmp_QueryUser_info
{

	int client_count;	//��ѯ�ͻ��˸���
	int start_line; 	//��ʼ�������
	gchar key;			//ģ����ѯ�����ݣ�����ǰ����Ͳ�ѯ����0
	gchar type;			//��ѯ���ͣ�0����ѯ�����û���1����������2�����ȼ�

}nmp_QueryUser_info;

typedef struct _nmp_QueryUser_info_res
{
	NmpMsgErrCode		code;

	char   username[USER_NAME_LEN]; 	//�˺�
	char   password[USER_PASSWD_LEN];	 //����
	int    group_id;		//������
	int    sex; 	//�Ա�
	char   user_phone[PHONE_NUM_LEN];  //��ϵ��ʽ
	char   user_description[DESCRIPTION_INFO_LEN];	//��ע��Ϣ

}nmp_QueryUser_info_res;

typedef struct _nmp_user_QueryUser_info
{
	char domain[USER_NAME_LEN];
	nmp_QueryUser_info *QueryUser_info;

}nmp_user_QueryUser_info;

typedef struct _nmp_user_QueryUser_info_res_inter
{
	int flag;
	int count;
	nmp_QueryUser_info_res *data_buf;
}nmp_user_QueryUser_info_res_inter;

//�û�����Ϣ
typedef struct _nmp_user_group_info
{
	int count;			//��ѯ�û������
	int start_line; 	//��ʼ�������
	int key;			//ģ����ѯ�����ݣ�����ǰ����Ͳ�ѯ����0
	int type;			//��ѯ���ͣ�0����ѯ�����û���1����������2�����ȼ�

}nmp_user_group_info;


typedef struct _nmp_user_group_info_res
{
	NmpMsgErrCode		code;


	char name[64];	//����
	char id[50]; //��id��
	int level; //�ȼ�
	int permissions; //�û���Ȩ��

}nmp_user_group_info_res;

typedef struct _nmp_user_group_info_res_inter
{
	int flag;
	int count;
	nmp_user_group_info_res *data_buf;
}nmp_user_group_info_res_inter;

typedef struct _nmp_user_group_info_inter
{
	char domain[USER_NAME_LEN];
	nmp_user_group_info *QueryUserGroup_info;

}nmp_user_group_info_inter;

//����Ա��Ϣ
typedef struct _nmp_manager_info_res
{
	NmpMsgErrCode		code;

		char name[64];
		int type;	//����Ա���ͣ�1����������Ա��2����ͨ����Ա
}nmp_manager_info_res;

typedef struct _nmp_manager_info_res_inter
{
	int flag;
	int count;
	nmp_manager_info_res *date_buff;
}nmp_manager_info_res_inter;

typedef struct _nmp_manager_info
{
	int count;			//��ѯ�û������
	int start_line; 	//��ʼ�������
	int key;			//ģ����ѯ�����ݣ�����ǰ����Ͳ�ѯ����0
	int type;			//��ѯ���ͣ�0����ѯ�����û���1����������2�����ȼ�

}nmp_manager_info;


typedef struct _nmp_manager_info_inter
{
	char domain[USER_NAME_LEN];
	nmp_manager_info *QueryManager_info;

}nmp_manager_info_inter;


//�豸��Ϣ
typedef struct _nmp_device_info
{
	int count;			//��ѯ�û������
	int start_line; 	//��ʼ�������
	int key;			//ģ����ѯ�����ݣ�����ǰ����Ͳ�ѯ����0
	int type;			//��ѯ���ͣ�0����ѯ�����û���1����������2�����ȼ�

}nmp_device_info;


typedef struct _nmp_device_info_inter
{
	char domain[USER_NAME_LEN];
	nmp_device_info *QueryDevice_info;

}nmp_device_info_inter;


typedef struct _nmp_device_info_res
{
	NmpMsgErrCode		code;

	char puid[16];			//�豸id
	char puName[64];		//�豸��
	char dev_type[20];		//�豸����
	char domain_id[8];		//��id
	char area_id[8];		//����id
	char mdu_id[50];		//ת��������id
	int heatbeat;			//����
	char equipment_manufacturers[50];	//������

}nmp_device_info_res;

typedef struct _nmp_device_info_res_inter
{
	int flag;
	int count;
	nmp_device_info_res *date_buff;
}nmp_device_info_res_inter;

//ҵ�����Ϣ
typedef struct _nmp_profession_point_info
{
	char domainid[16]; //��Id
	char guid[24]; //ҵ���id
	char puid[24]; //�豸id
	int count;	 //��ѯ����
	int start_line; 	//��ʼ�������
	int type;			//��ѯ���ͣ�0����ѯ����Gu��1��������id��puid��ѯ��2��������id��guid��ѯ
}nmp_profession_point_info;

typedef struct _nmp_profession_point_inter
{
	char domain[USER_NAME_LEN];
	nmp_profession_point_info *QueryProfession_info;

}nmp_profession_point_inter;

typedef struct _nmp_profession_point_res
{
	NmpMsgErrCode		code;


	char guid[24];	//ҵ��id
	char id[16]; //ҵ����������
	char puid[16]; //�豸id
	char guName[64]; //ҵ�����
	char type[10];
	int ptz; //1��ʾ����̨��0��ʾû��
	int guAlarmBypass;	//1��ʾ����·������0��ʾû��

}nmp_profession_point_res;

typedef struct _nmp_profession_point_res_inter
{
	int flag;
	int count;
	nmp_profession_point_res *date_buff;
}nmp_profession_point_res_inter;

//������Ϣ
typedef struct _NmpQueryRegion NmpQueryRegion;
struct _NmpQueryRegion
{
    gint               req_num;
    gint               start_num;
    gint               area_id;
};



typedef struct _nmp_region_info
{

	gint				area_id;
	gchar				area_name[AREA_NAME_LEN];
	gint				area_parent;

}nmp_region_info;

typedef struct _nmp_query_region_info_inter
{
	char domain[USER_NAME_LEN];
	NmpQueryRegion *QueryRegion;

}nmp_query_region_info_inter;

typedef struct _NmpQueryRegionRes NmpQueryRegionRes;
struct _NmpQueryRegionRes
{
    NmpMsgErrCode      code;
    gint               total_num;
    gint               req_num;
    nmp_region_info    *region_info;
};



/*
typedef struct _nmp_region_info_res
{
	NmpMsgErrCode		code;
	char Name[64]; //������
	char parent[32];	//�ü������һ����������
	char current_parent[32];		//��ǰ������ĸ�������
	int region_level;	//����ȼ�������һ�����򣬶�������
	int sub_level_region_flag;   //-1:��ʾ��������û���Ӽ�����1����ʾ���Ӽ�����

}nmp_region_info_res;

typedef struct _nmp_region_info_res_inter
{
	int flag;
	int count;
	nmp_region_info_res *date_buff;
}nmp_region_info_res_inter;
*/


//ת����������Ϣ
typedef struct _nmp_relay_server_info
{

	int count;	//��ѯ����
	int start_line; 	//��ʼ�������
	int type;			//��ѯ���ͣ�0����ѯ�����豸��1:���������ѯ�豸
	int key;			//key=1ʱ��ʾ�����ѯ
}nmp_relay_server_info;


typedef struct _nmp_relay_server_inter
{
	char domain[USER_NAME_LEN];
	nmp_relay_server_info *QueryRelayServer_info;

}nmp_relay_server_inter;



typedef struct _nmp_relay_server_info_res
{
	NmpMsgErrCode		code;

	char id[10];
	char relay_server_name[32];
	char type[32];
	int heatbeat;
	int device_port;
	int media_port;
}nmp_relay_server_info_res;

typedef struct _nmp_relay_server_info_res_inter
{
	int flag;
	int count;
	nmp_relay_server_info_res *date_buff;
}nmp_relay_server_info_res_inter;


//������Ϣ
typedef struct _nmp_query_factory_info
{
	int count;	//��ѯ����
	int start_line; 	//��ʼ�������
	int type;			//��ѯ���ͣ�0����ѯ�����豸��1:���������ѯ�豸
	int key;			//key=1ʱ��ʾ�����ѯ
}nmp_query_factory_info;

typedef struct _nmp_query_factory_info_inter
{
	char domain[USER_NAME_LEN];
	nmp_query_factory_info *QueryFactory_info;

}nmp_query_factory_info_inter;

typedef struct _nmp_query_factory_info_res
{
	NmpMsgErrCode		code;

	char factory_name[32];
	char flag[10];

}nmp_query_factory_info_res;

typedef struct _nmp_query_factory_info_res_inter
{
	int flag;
	int count;
	nmp_query_factory_info_res *date_buff;
}nmp_query_factory_info_res_inter;

//�洢��������Ϣ
typedef struct _nmp_query_storage_server_info
{
	int count;			//��ѯ����
	int start_line; 	//��ʼ�������
	int type;			//��ѯ���ͣ�0����ѯ�����豸��1:���������ѯ�豸
	int key;			//key=1ʱ��ʾ�����ѯ
}nmp_query_storage_server_info;

typedef struct _nmp_query_storage_server_info_inter
{
	char domain[USER_NAME_LEN];
	nmp_query_storage_server_info *QueryStorageServer_info;

}nmp_query_storage_server_info_inter;

typedef struct _nmp_query_storage_server_info_res
{
	NmpMsgErrCode		code;

	char id[32];
	char name[32];
	int heatbeat;

}nmp_query_storage_server_info_res;

typedef struct _nmp_query_storage_server_info_res_inter
{
	int flag;
	int count;
	nmp_query_storage_server_info_res *date_buff;
}nmp_query_storage_server_info_res_inter;


/**************************************�ӿ�*****************************************/


//server�˳�ʼ��
void nmp_server_mods_init( void );

//void nmp_server_lib_init( void );


//ƽ̨��ʼ��
int sdk_init(int heartbeat, int port);


//��ѯ������Ϣ
int get_region_info(nmp_query_region_info_inter *in_para, NmpQueryRegionRes *out);

//��ѯ�洢��������Ϣ
int get_storage_server_info(nmp_query_storage_server_info_inter *in_para, nmp_query_storage_server_info_res *out);

//��ѯ������Ϣ
int get_factory_info(nmp_query_factory_info_inter *in_para, nmp_query_factory_info_res *out);

//��ѯת���������б���Ϣ
int get_relay_server_info(nmp_relay_server_inter *in_para, nmp_relay_server_info_res *out);

//��ѯҵ����б���Ϣ
int get_profession_point_info(nmp_profession_point_inter *in_para, nmp_profession_point_res *out);

//��ѯ�豸�б���Ϣ
int get_device_info(nmp_device_info_inter *in_para, nmp_device_info_res *out);

//��ѯ����Ա�б���Ϣ
int get_manager_info(nmp_manager_info_inter *in_para, nmp_user_group_info_res *out);

//��ѯ�û�����Ϣ
int get_user_group_info(nmp_user_group_info_inter *in_para, nmp_user_group_info_res *out);

//��ѯ�ͻ�����Ϣ
int get_client_user_info(nmp_user_QueryUser_info *in_para, nmp_QueryUser_info_res *out);

int nmp_server_register_callback(server_callback_function *fun, void *ower);



#endif






