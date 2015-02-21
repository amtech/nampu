/*
 * jpf-search-device:
 * Copyright (C) 2013 by hegui <heguijiss@163.com>
 */

#ifndef __SEARCH_API_H__
#define __SEARCH_API_H__

#include <stdio.h>


#define JPF_SEARCH_ID_LEN               32
#define JPF_SEARCH_IP_LEN               16
#define JPF_SEARCH_MNFCT_LEN            12

#define JPF_SEARCH_USERNAME_LEN         32
#define JPF_SEARCH_PASSWORD_LEN         32

typedef enum JPE_SEARCH_ERROR
{
    JPE_SEARCH_SUCCESS = 0,
    JPE_SEARCH_TIMEOUT = 1,
    JPE_SEARCH_FAILED  = 2,
}JPE_SEARCH_ERROR_E;

typedef struct device_info
{
    int pu_type;                        //�豸����
    int av_mun;                         //����Ƶ�����
    char mnfct[JPF_SEARCH_MNFCT_LEN];   //�豸����
    char pu_id[JPF_SEARCH_ID_LEN];      //�豸��ʶ
    char dev_ip[JPF_SEARCH_IP_LEN];     //�豸ip
    char res[32];
}device_info_t;

typedef struct jpf_platform
{
    char cms_ip[JPF_SEARCH_IP_LEN];     //ƽ̨cms ip
    char mds_ip[JPF_SEARCH_IP_LEN];     //ƽ̨mds ip
    int cms_port;                       //ƽ̨cms�˿ں�
    int mds_port;                       //ƽ̨mds�˿ں�
    int conn_cms;                       //����ƽ̨���أ�1-����  0-������
    char res[32];
}jpf_platform_t;

typedef struct jpf_search
{
    device_info_t  dev_info;
    jpf_platform_t jpf_plt;
}jpf_search_t;

typedef struct search_result
{
    char dst_id[JPF_SEARCH_ID_LEN];
    jpf_search_t jpf_srch;
}search_result_t;

typedef struct search_array
{
    int count;                          //��Ŀ
    int capacity;                       //����
    search_result_t result[0];
}search_array_t;



typedef struct user_info
{
    char usr[JPF_SEARCH_USERNAME_LEN];
    char pwd[JPF_SEARCH_PASSWORD_LEN];
}user_info_t;

typedef struct redirect
{
    char pu_id[JPF_SEARCH_ID_LEN];      //�豸��ʶ
    char cms_ip[JPF_SEARCH_IP_LEN];     //ƽ̨cms ip
    int cms_port;                       //ƽ̨cms�˿ں�
    int conn_cms;                       //����ƽ̨���أ�1-����  0-������
}redirect_t;

typedef struct jpf_redirect
{
    user_info_t user_info;
    redirect_t redirect;
}jpf_redirect_t;


#ifdef __cplusplus
extern "C" {
#endif
    
    int init();
    int uninit();
    
    search_array_t *search_device();
    void destory_search_result(search_array_t *array);
    
    int set_platform_info(char *dst_id, jpf_redirect_t *jpf_red);



#ifdef __cplusplus
}
#endif

#endif //__SEARCH_API_H__

