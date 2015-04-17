#include "nmp_mod_ams.h"
#include "nmp_message.h"
#include "nmp_share_errno.h"
#include "nmp_memory.h"
#include "nmp_msg_ams.h"
#include "nmp_internal_msg.h"
#include "nmp_shared.h"
#include "nmp_ams_struct.h"
#include "nmp_ams_policy.h"


USING_MSG_ID_MAP(cms);
//#define AMS_MH_TEST


gint
nmp_mod_ams_action_handler(gint dst, gint msg_type, void *parm, guint size)
{
	nmp_warning("<NmpAmsMh> nmp_mod_ams_action_handler begin...");
	gint ret;
	NmpAppObj *self = (NmpAppObj *)nmp_get_mod_ams();

	ret = nmp_cms_mod_deliver_msg_2(self, dst, msg_type,
		parm, size);

	return ret;
}


static __inline__ gint
nmp_mod_ams_register(NmpModAms *self, NmpNetIO *io,  NmpMsgID msg_id,
    NmpAmsRegister *req, NmpAmsRegisterRes *res)
{
    gint ret;
    NmpID conflict;

    G_ASSERT(self != NULL && io != NULL && req != NULL && res != NULL);

    ret = nmp_mod_ams_new_ams(self, io,  req->ams_id, &conflict);
    if (G_UNLIKELY(ret))
        return ret;

    ret = nmp_mod_ams_sync_req(self, msg_id, req,
         sizeof(NmpAmsRegister), res, sizeof(NmpAmsRegisterRes));

    return ret;
}


NmpMsgFunRet
nmp_mod_ams_register_f(NmpAppObj *app_obj, NmpSysMsg *msg)
{
    NmpModAms *self;
    NmpNetIO *io;
    NmpAmsRegister *req_info;
    NmpAmsRegisterRes res_info;
    NmpMsgID msg_id;
    NmpGuestBase *ams_base;
    NmpAms *ams;
    NmpMsgAmsOnlineChange notify_info;
    gint ret;

    self = (NmpModAms*)app_obj;
    io = MSG_IO(msg);
    BUG_ON(!io);

    msg_id = MSG_GETID(msg);

    req_info = MSG_GET_DATA(msg);
    BUG_ON(!req_info);

    memset(&notify_info, 0, sizeof(notify_info));
    notify_info.ams_id[AMS_ID_LEN - 1] = 0;
    strncpy(notify_info.ams_id, req_info->ams_id, AMS_ID_LEN - 1);
    memset(&res_info, 0, sizeof(res_info));
    ret = nmp_mod_ams_register(self, io, msg_id, req_info, &res_info);
    if (ret)
    {
        nmp_print(
            "<NmpModAms> ams:%s register failed, err:%d",
            req_info->ams_id, -ret
        );

        SET_CODE(&res_info, -ret);
        MSG_SET_RESPONSE(msg);
        nmp_sysmsg_set_private_2(msg, &res_info, sizeof(res_info));

        nmp_app_obj_deliver_in((NmpAppObj*)self, msg);
        nmp_mod_acc_release_io((NmpModAccess*)self, io);
        nmp_mod_container_del_io(self->container, io);

        return MFR_ACCEPTED;
    }

    ams_base = nmp_mods_container_get_guest(self->container, io);
    if (G_UNLIKELY(!ams_base))
    {
        ret = -E_NOSUCHGUEST;
	 nmp_warning("<NmpModAms> Can't find ams:'%s' in container, io timeout?", notify_info.ams_id);
    }
    else
   {
        ams = (NmpAms *)ams_base;
        ams->ams_state = STAT_AMS_ONLINE;
        nmp_mods_container_put_guest(self->container, ams_base);

         nmp_print(
             "<NmpModAms> ams:%s register ok",
             req_info->ams_id
         );

        strncpy(res_info.domain_id, nmp_get_local_domain_id(), DOMAIN_ID_LEN - 1);

        nmp_check_keepalive_time(&res_info.keep_alive_time);
        nmp_net_io_set_ttd(io, res_info.keep_alive_time*1000*TIMEOUT_N_PERIODS);

        notify_info.new_status = 1;
        nmp_mod_ams_change_ams_online_status(app_obj, notify_info);
    }

    SET_CODE(&res_info, -ret);
    MSG_SET_RESPONSE(msg);
    nmp_sysmsg_set_private_2(msg, &res_info, sizeof(res_info));
    return MFR_DELIVER_BACK;

}


NmpMsgFunRet
nmp_mod_ams_heart_f(NmpAppObj *app_obj, NmpSysMsg *msg)
{
    NmpModAms *self;
    NmpNetIO *io;
    NmpGuestBase *ams_base;
    NmpAmsHeart *req_info;
    NmpAmsHeartRes res_info;
    NmpMsgID msg_id;
    gint ret = 0;

    self = (NmpModAms*)app_obj;
    io = MSG_IO(msg);
    BUG_ON(!io);

    msg_id = MSG_GETID(msg);
    req_info = MSG_GET_DATA(msg);
    BUG_ON(!req_info);

    memset(&res_info, 0, sizeof(res_info));
    ams_base = nmp_mods_container_get_guest_2(self->container, req_info->ams_id);
    if (G_UNLIKELY(!ams_base))
    {
        ret = -E_NOSUCHGUEST;
        nmp_warning("<NmpModAms> amsId:%s No such guest.", req_info->ams_id);
    }
    else
    {
        nmp_get_utc_time(res_info.server_time);
        nmp_mods_container_put_guest(self->container, ams_base);
    }

    MSG_SET_RESPONSE(msg);
    SET_CODE(&res_info, -ret);
    nmp_sysmsg_set_private_2(msg, &res_info, sizeof(res_info));

    return MFR_DELIVER_BACK;
}


NmpMsgFunRet
nmp_mod_ams_backward(NmpModAms *self, NmpSysMsg *msg, const gchar *id_str)
{
    NmpGuestBase *ams_base;
    NmpNetIO *io;
    gint msg_id;

    msg_id = MSG_GETID(msg);
    ams_base = nmp_mods_container_get_guest_2(self->container, id_str);
    if (G_UNLIKELY(!ams_base))
    {
        nmp_warning("<NmpModAms> deliver msg '%s' failed, AmsId:%s no such ams.",
            MESSAGE_ID_TO_STR(cms, msg_id), id_str);
        nmp_sysmsg_destroy(msg);

        return MFR_ACCEPTED;
    }

    io = IO_OF_GUEST(ams_base);
    BUG_ON(!io);

    MSG_SET_RESPONSE(msg);
    nmp_sysmsg_attach_io(msg, io);
    nmp_mods_container_put_guest(self->container, ams_base);

    return MFR_DELIVER_AHEAD;
}


NmpMsgFunRet
nmp_mod_ams_backward_2(NmpModAms *self, NmpSysMsg *msg, const gchar *id_str, const gchar *session_id)
{
    NmpGuestBase *ams_base;
    NmpNetIO *io;
    gint msg_id;
    NmpErrRes      code;

    memset(&code, 0, sizeof(code));
    msg_id = MSG_GETID(msg);
    ams_base = nmp_mods_container_get_guest_2(self->container, id_str);
    if (G_UNLIKELY(!ams_base))
    {
        nmp_warning("<NmpModAms> deliver msg '%s' failed, AmsId:%s no such ams.",
            MESSAGE_ID_TO_STR(cms, msg_id), id_str);
        //nmp_sysmsg_destroy(msg);


        SET_CODE(&code.code, E_NOSUCHGUEST);
	if (session_id)
            memcpy(code.session, session_id, USER_NAME_LEN - 1);

        MSG_SET_DSTPOS(msg, BUSSLOT_POS_BSS);
        nmp_sysmsg_set_private_2(msg, &code, sizeof(code));
        MSG_SET_RESPONSE(msg);
        return MFR_DELIVER_BACK;
    }

    io = IO_OF_GUEST(ams_base);
    BUG_ON(!io);

    nmp_sysmsg_attach_io(msg, io);
    nmp_mods_container_put_guest(self->container, ams_base);

    return MFR_DELIVER_AHEAD;
}


static int nmp_get_week_time(NmpTime *nmp_time, char *time)
{
	struct tm cur_tm;
	time_t cur_time;
	sscanf(time, "%d-%d-%d %d:%d:%d",
		&cur_tm.tm_year, &cur_tm.tm_mon, &cur_tm.tm_mday,
		&cur_tm.tm_hour, &cur_tm.tm_min, &cur_tm.tm_sec
	);
	cur_tm.tm_mon -= 1;
	cur_tm.tm_year -= 1900;

	cur_time = mktime(&cur_tm);
	localtime_r(&cur_time, &cur_tm);

	nmp_time->day_of_week = cur_tm.tm_wday;
	nmp_time->cur_time = cur_tm.tm_hour * 60 * 60 + cur_tm.tm_min * 60 + cur_tm.tm_sec;

	return 0;
}

static int nmp_mod_ams_get_alarm_info(NmpAlarmInfo *alarm_info,
	NmpSubmitAlarm *req_info)
{
	memset(alarm_info, 0, sizeof(NmpAlarmInfo));

	strncpy(alarm_info->alarm_guid.domain_id, req_info->domain_id,
		DOMAIN_ID_LEN - 1);
	strncpy(alarm_info->alarm_guid.guid, req_info->guid, MAX_ID_LEN - 1);
	alarm_info->alarm_type = 1 << (guint)(req_info->alarm_type);

	if (strlen(req_info->alarm_time) == 0)
	{
		nmp_warning("<NmpAmsMh>error, alarm_time=%s.", req_info->alarm_time);
		return -1;
	}
	strncpy(alarm_info->alarm_time, req_info->alarm_time, TIME_INFO_LEN - 1);
	return nmp_get_week_time(&alarm_info->time, req_info->alarm_time);
}


/*
 *	if return 0, destroy_msg need to be destroyed
 */
gint nmp_ams_get_action_info_from_dbs(NmpMsgAmsGetActionInfoRes **res,
	NmpAlarmInfo *alarm_info, NmpSysMsg **destroy_msg)
{
	NmpMsgAmsGetActionInfo req;
	NmpSysMsg *msg;
	gint ret;

	req.alarm_guid = alarm_info->alarm_guid;
	msg = nmp_sysmsg_new_2(MSG_AMS_GET_ACTION_INFO, &req,
		sizeof(NmpMsgAmsGetActionInfo), ++msg_seq_generator);
	if (G_UNLIKELY(!msg))
		return -E_NOMEM;

	MSG_SET_DSTPOS(msg, BUSSLOT_POS_DBS);
	ret = nmp_app_mod_sync_request((NmpAppMod*)nmp_get_mod_ams(), &msg);
	if (G_UNLIKELY(ret))
	{
		nmp_warning("<NmpModAms> request action info failed!");
		goto end;
	}

	if (G_UNLIKELY(!msg))	/* sent, but no response */
	{
		nmp_warning("<NmpModAms> request action info timeout!");
		return -E_TIMEOUT;
	}

	*res = MSG_GET_DATA(msg);
	BUG_ON(!(*res));
	if ((*res)->result < 0)
	{
		ret = -1;
		nmp_warning("<NmpModAms> request action info, result < 0!");
		goto end;
	}

	*destroy_msg = msg;
	return 0;

end:
	nmp_sysmsg_destroy(msg);
	return ret;
}


void nmp_mod_ams_do_alarm_action(NmpAlarmInfo *alarm_info)
{
	g_assert(alarm_info);
	NmpMsgAmsGetActionInfoRes *res = NULL;
	NmpSysMsg *msg = NULL;
	gint ret;

	ret = nmp_ams_find_gu_and_action(alarm_info);
	if (ret == 0)	//success
		return ;

	ret = nmp_ams_get_action_info_from_dbs(&res, alarm_info, &msg);
	if (ret != 0)	//failed
		return ;

	ret = nmp_ams_add_gu_action_info(&alarm_info->alarm_guid, res);
	if (ret != 0)	//failed
	{
		nmp_warning("<NmpModAms>nmp_ams_add_gu_action_info failed!");
	}

	if (msg)		//ע�⣬resָ���Ϊmsg�е��ڴ�
		nmp_sysmsg_destroy(msg);

	ret = nmp_ams_find_gu_and_action(alarm_info);
	if (ret != 0)	//failed
	{
		nmp_warning("<NmpModAms>error:second find action failed!");
	}
}


void ams_alarm_info_print(NmpAlarmInfo *alarm_info)
{
	nmp_print("<NmpAmsMh>alarm happen!");
	nmp_print("<NmpAmsMh>alarm domain_id:%s.", alarm_info->alarm_guid.domain_id);
	nmp_print("<NmpAmsMh>alarm guid:%s.", alarm_info->alarm_guid.guid);
	nmp_print("<NmpAmsMh>alarm type:%d.", alarm_info->alarm_type);
	nmp_print("<NmpAmsMh>alarm week:%d, time:%ld.", alarm_info->time.day_of_week,
		alarm_info->time.cur_time);
}


NmpMsgFunRet
nmp_mod_ams_alarm_link_b(NmpAppObj *app_obj, NmpSysMsg *msg)
{
	NmpModAms *self;
	NmpSubmitAlarm *req_info;
	NmpAlarmInfo alarm_info;
	gint ret = 0;

	self = (NmpModAms*)app_obj;
	req_info = MSG_GET_DATA(msg);
	BUG_ON(!req_info);

	ret = nmp_mod_ams_get_alarm_info(&alarm_info, req_info);
	if (ret < 0)
	{
		nmp_warning("<NmpModAms> get alarm info error.");
	}
	else
	{
#ifdef AMS_MH_TEST
		ams_alarm_info_print(&alarm_info);
#endif
		nmp_mod_ams_do_alarm_action(&alarm_info);
	}

	nmp_sysmsg_destroy(msg);

	return MFR_ACCEPTED;
}


NmpMsgFunRet
nmp_mod_ams_change_link_time_policy_b(NmpAppObj *app_obj, NmpSysMsg *msg)
{
	NmpModAms *self;
	NmpShareGuid *req_info;
	gint ret = 0;

	self = (NmpModAms*)app_obj;
	req_info = MSG_GET_DATA(msg);
	BUG_ON(!req_info);

	ret = nmp_ams_remove_alarm_node(req_info);
	if (ret == 0)
	{
		nmp_print("<NmpAmsMh> nmp_ams_remove_alarm_node success");
	}
	else
	{
		nmp_print("<NmpAmsMh> nmp_ams_remove_alarm_node failed");
	}

	nmp_sysmsg_destroy(msg);

	return MFR_ACCEPTED;
}


NmpMsgFunRet
nmp_mod_ams_del_alarm_link_b(NmpAppObj *app_obj, NmpSysMsg *msg)
{
	NmpModAms *self;
	NmpShareGuid *req_info;
	gint ret = 0;

	self = (NmpModAms*)app_obj;
	req_info = MSG_GET_DATA(msg);
	BUG_ON(!req_info);

	ret = nmp_ams_remove_alarm_node(req_info);
	if (ret == 0)
	{
		nmp_print("<NmpAmsMh> nmp_ams_remove_alarm_node success");
	}
	else
	{
		nmp_print("<NmpAmsMh> nmp_ams_remove_alarm_node failed");
	}

	nmp_sysmsg_destroy(msg);

	return MFR_ACCEPTED;
}


NmpMsgFunRet
nmp_mod_ams_device_info_change_b(NmpAppObj *app_obj, NmpSysMsg *msg)
{
	NmpModAms *self;
	NmpGuestBase *ams_base;
	gint msg_id;
	NmpAmsId *req_info = NULL;

	self = NMP_MODAMS(app_obj);
	req_info = MSG_GET_DATA(msg);
	BUG_ON(!req_info);

	msg_id = MSG_GETID(msg);
	ams_base = nmp_mods_container_get_guest_2(self->container, req_info->ams_id);
	if (G_UNLIKELY(!ams_base))
	{
		nmp_warning("<NmpModAms> deliver msg '%s' failed, AmsId:%s no such ams.",
			MESSAGE_ID_TO_STR(cms, msg_id), req_info->ams_id);
		nmp_sysmsg_destroy(msg);

		return MFR_ACCEPTED;
	}

	nmp_sysmsg_attach_io(msg, IO_OF_GUEST(ams_base));
	nmp_mods_container_put_guest(self->container, ams_base);

	return MFR_DELIVER_AHEAD;
}


NmpMsgFunRet
nmp_mod_ams_get_device_info_f(NmpAppObj *app_obj, NmpSysMsg *msg)
{
	G_ASSERT(app_obj != NULL && msg != NULL);
	NmpModAms *self;
	NmpNetIO *io;
	NmpGuestBase *ams_base;
	NmpAmsGetDeviceInfo *req_info;
	NmpAmsGetDeviceInfoRes res_info;
	NmpMsgID msg_id;
	gint ret = 0;
	memset(&res_info, 0, sizeof(res_info));

	self = (NmpModAms*)app_obj;
	io = MSG_IO(msg);
	BUG_ON(!io);

	msg_id = MSG_GETID(msg);
	req_info = MSG_GET_DATA(msg);
	BUG_ON(!req_info);

	ams_base = nmp_mods_container_get_guest_2(self->container, req_info->ams_id);
	if (G_UNLIKELY(!ams_base))
	{
		ret = -E_NOSUCHGUEST;
		nmp_warning("<NmpModAms> amsId:%s No such guest.", req_info->ams_id);
	}
	else
	{
		MSG_SET_DSTPOS(msg, BUSSLOT_POS_DBS);
		nmp_mods_container_put_guest(self->container, ams_base);
		return MFR_DELIVER_AHEAD;
	}

	MSG_SET_RESPONSE(msg);
	SET_CODE(&res_info, -ret);
	nmp_sysmsg_set_private_2(msg, &res_info, sizeof(res_info));

	return MFR_DELIVER_BACK;
}


NmpMsgFunRet
nmp_mod_ams_get_device_info_b(NmpAppObj *app_obj, NmpSysMsg *msg)
{
    NmpModAms *self;
    NmpAmsGetDeviceInfoRes *res_info;

    self = (NmpModAms*)app_obj;
    res_info = MSG_GET_DATA(msg);
    BUG_ON(!res_info);

    return nmp_mod_ams_backward(self, msg, res_info->ams_id);
}



void
nmp_mod_ams_register_msg_handler(NmpModAms *self)
{
    NmpAppMod *super_self = (NmpAppMod*)self;

    nmp_app_mod_register_msg(
        super_self,
        MESSAGE_AMS_REGISTER,
        nmp_mod_ams_register_f,
        NULL,
        0
    );

    nmp_app_mod_register_msg(
        super_self,
        MESSAGE_AMS_HEART,
        nmp_mod_ams_heart_f,
        NULL,
        0
    );

    nmp_app_mod_register_msg(
        super_self,
        MESSAGE_SUBMIT_ALARM,
        NULL,
        nmp_mod_ams_alarm_link_b,
        0
    );

    nmp_app_mod_register_msg(
        super_self,
        MSG_CHANGE_LINK_TIME_POLICY,
        NULL,
        nmp_mod_ams_change_link_time_policy_b,
        0
    );

	nmp_app_mod_register_msg(
		super_self,
		MSG_DEL_ALARM_LINK,
		NULL,
		nmp_mod_ams_del_alarm_link_b,
		0
	);

	nmp_app_mod_register_msg(
		super_self,
		MESSAGE_AMS_DEVICE_INFO_CHANGE,
		NULL,
		nmp_mod_ams_device_info_change_b,
		0
	);

	nmp_app_mod_register_msg(
		super_self,
		MESSAGE_AMS_GET_DEVICE_INFO,
		nmp_mod_ams_get_device_info_f,
		nmp_mod_ams_get_device_info_b,
		0
	);
}

