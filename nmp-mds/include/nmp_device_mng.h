#include <rtspwatch.h>
#include "nmp_media_device.h"

#ifndef __NMP_DEVICE_POOL_H__
#define __NMP_DEVICE_POOL_H__

G_BEGIN_DECLS

typedef struct _JpfDevicePool JpfDevicePool;
struct _JpfDevicePool {	/* �豸��/��ϣ�� */
	guint			device_count;	/* �������ϵ��豸�� */

	GMutex			*table_lock;
	GHashTable		*table_devices;

	guint			 timer;			/* ��ʱ�� */
};


typedef struct _JpfAcceptDevMng JpfAcceptDevMng;
struct _JpfAcceptDevMng
{
	GList 			*devices;
	GMutex			*lock;

	guint			 timer;			/* ��ʱ�� */
};


typedef struct _JpfDevMng JpfDevMng;
struct _JpfDevMng {
	gint			ref_count;	/* ���ü��� */
	JpfDevicePool	*dev_pool;	/* �豸�� */
	gchar			*address;	/* ����IP */
	gchar			*service;	/* ����˿� */

	JpfAcceptDevMng *dev_unrecognized;	/* ACCEPT�豸*/
};


JpfDevMng *nmp_rtsp_device_mng_new(gint service);
void nmp_rtsp_device_mng_unref(JpfDevMng *dev_mng);
guint nmp_rtsp_device_mng_attach(JpfDevMng *dev_mng);

gboolean nmp_rtsp_device_mng_accepted(JpfDevMng *dev_mng, 
	JpfMediaDevice *device);

gint nmp_rtsp_device_mng_add_dev(JpfDevMng *dev_mng,
	JpfMediaDevice *device, gchar old_ip[]);
void nmp_rtsp_device_mng_remove(JpfMediaDevice *device);

JpfMediaDevice *nmp_rtsp_device_mng_find_and_get_dev(JpfDevMng *dev_mng, 
	const gchar *id);

G_END_DECLS

#endif /* __NMP_DEVICE_POOL_H__ */
