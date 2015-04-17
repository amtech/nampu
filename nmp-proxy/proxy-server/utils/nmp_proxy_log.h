
#ifndef __SHOW_LOG_H__
#define __SHOW_LOG_H__

/*********************************************************************************

file:nmp_proxy_log.h
description:
    ���ͷ�ļ��淶�����ǳ���������ԡ����桢�������Ϣ�ķ�ʽ��
    ������Ϣ��Ϊ�������Linux�ṩ���߸��������ǲ�ʹ����ߵ���������
    ���ǳ����пɸ�����Ҫ�á�

    ��������Ӧ�ĺ꺯�����£�(ʹ�÷�ʽ��printf��ͬ)
    show_debug
    show_info
    show_warn
    show_error
    show_critical

    ���У�show_error��show_criticalֻӦ��ϵͳ��errno��ֵ��ʱ���ã�
    ������ļ��Ҳ�����ϵͳ������errno��ֵ��
    show_error��show_critical��ʱ�򣬳��������ָ������Ϣ�����ḽ�����
    errno��Ӧ����Ϣ�������ɷ������������������

*********************************************************************************/

#if _DEBUG_

#define show_debug(fmt, ...) \
    do {\
        printf("DEBUG: %s(%d) "fmt, __FILE__, __LINE__, ##__VA_ARGS__); \
    }while (0)

#define show_info(fmt, ...) \
    do {\
        printf("INFO: %s(%d) "fmt, __FILE__, __LINE__, ##__VA_ARGS__); \
    }while (0)

#define show_warn(fmt, ...) \
    do {\
        printf("WARN: %s(%d) "fmt, __FILE__, __LINE__, ##__VA_ARGS__); \
    }while (0)

#define show_error(fmt, ...) \
    do {\
        printf("ERROR: %s(%d) [%m] "fmt, __FILE__, __LINE__, ##__VA_ARGS__); \
    }while (0)

#define show_critical(fmt, ...) \
    do {\
        printf("CRITICAL: %s(%d) [%m] "fmt, __FILE__, __LINE__, ##__VA_ARGS__); \
    }while (0)

#else

#include "nmp_debug.h"

#define show_debug nmp_print
#define show_info nmp_print
#define show_warn nmp_warning
#define show_error nmp_error
#define show_critical nmp_error

#endif



#endif //__SHOW_LOG_H__

