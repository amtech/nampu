#ifndef __NMP_AMS_STRUCT_H__
#define __NMP_AMS_STRUCT_H__

#include "nmp_mods.h"

typedef enum
{
	STAT_AMS_REGISTERING,
	STAT_AMS_ONLINE,
	STAT_AMS_OFFLINE
}NmpAmsState;

typedef struct _NmpAms NmpAms;
struct _NmpAms
{
	NmpGuestBase	guest_base;

	NmpAmsState 	ams_state;
	gint            ttl;      /*time to live*/
	gint            hb_freq;  /*keep alive frequency(sec)*/
};


#endif	//__NMP_AMS_STRUCT_H__
