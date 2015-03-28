#ifndef __NMP_PORTS_H__
#define __NMP_PORTS_H__

#include <glib.h>

/* ����ȱʡ�˿ڷ�Χ */
gint nmp_media_ports_set_default_range( void );

/* ���ö˿ڷ�Χ */
gint nmp_media_ports_set_range(gint low, gint hi);

/* ����Ҫ�ų��Ķ˿� */
void nmp_media_ports_set_reserved(gint port);

/* ���һ���˿� */
gint nmp_media_ports_get_one(gint *p_port);

/* �ͷ�һ���˿� */
void nmp_media_ports_put_one(gint port);

/* ���һ�Զ˿�: n(ż��), n+1 */
gint nmp_media_ports_get_pair(gint *p_low, gint *p_hi);

/* �ͷ�һ�Զ˿� */
void nmp_media_ports_put_pair(gint low, gint hi);

/* ��ö˿ڷ�Χ */
gint nmp_media_ports_get_range(gint *p_low, gint *p_hi);

#endif	//__NMP_PORTS_H__
