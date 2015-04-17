/*
 *          file: nmp_proxy_error.h
 *          description:�����Լ�����������������д�������Ϣ
 *
 *          hegui,heguijiss@gmail.com
 *          May 16th, 2013
 */

#ifndef __PROXY_ERROR_H__
#define __PROXY_ERROR_H__


#define JPROXY_SERVER_ERROR_BASE        9000     /* ����������������׼*/
#define JEBASE JPROXY_SERVER_ERROR_BASE


#define E_PRITYPE               (JEBASE + 1)     /* ˽������������Ч */
#define E_NO_PRIDATA            (JEBASE + 2)     /* ��˽������ */
#define E_INIT_DEVICE           (JEBASE + 3)     /* ��ʼ�������豸ʧ�� */


#define E_CONNECT_TIMEOUT       (JEBASE + 10)     /* ����cms ��ʱ */
#define E_REGISTER_TIMEOUT      (JEBASE + 11)     /* ע��cms ��ʱ */
#define E_ONLINE_TIMEOUT        (JEBASE + 12)     /* ���� ��ʱ */



#endif  /* __PROXY_ERROR_H__ */

