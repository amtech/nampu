/*
 * tiny-rain:
 * (c) Author:
 *
 * A simple multi-media server application framework.
*/

#ifndef __TINY_RAIN_PORTS_RANGE_H__
#define __TINY_RAIN_PORTS_RANGE_H__

#include "def.h"

BEGIN_NAMESPACE

//@{
#define E_NOMEM			1
#define E_OUTOFPORTS 	1
#define __export
//:}

/* ��ʼ���˿� */
void tr_ports_init( void );

/* ����ȱʡ�˿ڷ�Χ */
int32_t tr_ports_set_default_range( void );

/* ���ö˿ڷ�Χ */
int32_t tr_ports_set_range(int32_t low, int32_t hi);

/* ����Ҫ�ų��Ķ˿� */
void tr_ports_set_reserved(int32_t port);

/* ���һ���˿� */
int32_t tr_ports_get_one(int32_t *p_port);

/* �ͷ�һ���˿� */
void tr_ports_put_one(int32_t port);

/* ���һ�Զ˿�: n(ż��), n+1 */
int32_t tr_ports_get_pair(int32_t *p_low, int32_t *p_hi);

/* �ͷ�һ�Զ˿� */
void tr_ports_put_pair(int32_t low, int32_t hi);

/* ��ö˿ڷ�Χ */
int32_t tr_ports_get_range(int32_t *p_low, int32_t *p_hi);

END_NAMESPACE

#endif	//__TINY_RAIN_PORTS_RANGE_H__
